#include "../include/ping.h"

bool loop_icmp;

void signal_exit_loop_cmp(int sig)
{
    (void)sig;
    loop_icmp = false;
}

/**
 * @brief Open communication with another computer
 * 
 * @param network_trame Struct content information of the trame
 */
void open_socked(t_ping  *network_trame)
{
    network_trame->socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (network_trame->socket < 0)
    {
        printf("\033[31mError\033[0m: Socket file descriptor not received!\n");
        free_struct(network_trame);
        exit(1);
    }
}

// Calculate the checksum (RFC 1071)
unsigned short checksum(void *data, int len)
{
    unsigned short  *buf;
    unsigned int    sum;

    buf = data;
    sum = 0;

    while (len > 1)
    {
        sum += *buf++;
        len -= 2;
    }

    if (len == 1)
        sum += *(unsigned char *)buf;

    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);

    return (~sum);
}

void    socket_option(t_ping  *network_trame)
{
    struct timeval timeout;

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    //if (setsockopt(network_trame->socket, SOL_IP, IP_TTL,
    //    &network_trame->ttl_size, sizeof(network_trame->ttl_size)) != 0)
    if (setsockopt(network_trame->socket,
                SOL_SOCKET,
                SO_RCVTIMEO,
                &timeout,
                sizeof(timeout)) < 0)
    {
        printf("\n\033[31mError\033[0m: Setting socket options to TTL failed!\n");
        free_struct(network_trame);
        exit(1);
    }
}

void chrono_time(int CLOCK, struct timespec *time)
{
    clock_gettime(CLOCK, time); //sans risque d'erreurs si l'heure du système change
}

void create_packet(t_ping *network_trame, t_icmp_headedr *packet_icmp, char *msg)
{
    size_t  i;

    // Fill the packet
    ft_bzero(packet_icmp, sizeof(packet_icmp));
    packet_icmp->header.type = ICMP_ECHO;
    packet_icmp->header.un.echo.id = getpid();

    for (i = 0; i < sizeof(msg); i++)
    {
        packet_icmp->msg[i] =  msg[i];
        if (i + 1 == sizeof(msg) && i + 1 < sizeof(packet_icmp->msg))
        {
            break;
        }
    }

    packet_icmp->msg[i] = '\0';
    packet_icmp->header.un.echo.sequence = network_trame->count_pck_send++;
    packet_icmp->header.checksum = 0;
    packet_icmp->header.checksum = checksum((uint64_t *)packet_icmp, sizeof(*packet_icmp));
}
/**
 * @brief Send ping for the server
 * 
 * @param network_trame 
 * @param icmp_v4 
 * @param time 
 */
bool    send_pkt(t_ping *network_trame, t_icmp_headedr *icmp_v4)
{
    if (sendto(
        network_trame->socket, 
        icmp_v4,
        sizeof(*icmp_v4), 
        0,
        (struct sockaddr *)network_trame->ip_hdr->dest_addr,  
        sizeof(*network_trame->ip_hdr->dest_addr)
    ) < 0)
    {
        printf("\n\033[31mError\033[0m Packet Sending Failed!\n");
        return (false);
    }
    return (false);
}
/**
 * @brief For know answer server for client resuqest
 * 
 * @param network_trame 
 * @param icmp_v4 
 * @param time
 */
bool    receive_pkt(t_ping *network_trame)
{
    socklen_t   len_addr;

    len_addr = sizeof(network_trame->ip_hdr->src_addr);
    size_t ret;

    ret = recvfrom(
        network_trame->socket,
        network_trame->receiv_buffer,
        RECV_SIZE,
        0,
        (struct sockaddr *)&network_trame->ip_hdr->src_addr,
        &len_addr
    );
    if (ret <= 0)
    {
        if (errno == EINTR)
        {
            return (true);;
        }
    }

    network_trame->flag_sent = true;
    return (false);
}

void time_time(t_ping *network_trame, t_time_packet *time)
{
    network_trame->rtt_ms =
        (time->time_end.tv_sec - time->time_start.tv_sec) * 1000.0
        + (time->time_end.tv_nsec - time->time_start.tv_nsec) / 1000000.0;
}


void icmp_network(t_ping *network_trame)
{
    struct icmphdr *recv_header;

    loop_icmp = true;

    chrono_time(CLOCK_MONOTONIC, &network_trame->tm_packet->tfs);
    
    socket_option(network_trame);

    addr_info(network_trame, HEADER_PRINT);

    signal(SIGINT, signal_exit_loop_cmp);

    while (loop_icmp)
    {
        network_trame->flag_sent = false;
        
        // create packet and set header icmp
        create_packet(network_trame, network_trame->ip_hdr->icmp_v4, "hello");

        // 1sec
        usleep(PING_SLEEP_RATE);

        chrono_time(CLOCK_MONOTONIC, &network_trame->tm_packet->time_start);

        // Send packet
        send_pkt(network_trame,network_trame->ip_hdr->icmp_v4);

        //Receive packet
        receive_pkt(network_trame);
        if (network_trame->flag_sent)
        {
            clock_gettime(CLOCK_MONOTONIC, &network_trame->tm_packet->time_end);

            time_time(network_trame, network_trame->tm_packet);

            recv_header = &network_trame->ip_hdr->icmp_v4->header;

            if (recv_header->type != 0 && recv_header->code != 0)
            {
                printf("Request timeout for icmp_seq %d\n",  recv_header->un.echo.sequence);
            } 
            else
            {
                printf("%ld bytes from %s (%s) msg_seq = %d ttl = %d rtt = %.2Lf ms.\n", 
                    sizeof(*network_trame->ip_hdr->icmp_v4),\
                    network_trame->ip_hdr->host_server->h_name,\
                    network_trame->ip_hdr->host_server->h_addr_list[0],\
                    network_trame->ip_hdr->icmp_v4->header.un.echo.sequence,\
                    network_trame->ttl_size,\
                    network_trame->rtt_ms
                );
                
                //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
                //64 bytes from 8.8.8.8: icmp_seq=1 ttl=116 time=3.32 ms

                //PING google.com (172.217.22.46) 56(84) bytes of data.
                //64 bytes from pnpara-ad-in-f14.1e100.net (172.217.22.46): icmp_seq=1 ttl=117 time=2.45 ms
            }
        }
    }

    chrono_time(CLOCK_MONOTONIC, &network_trame->tm_packet->tfe);
    
    addr_info(network_trame, END_PRINT);
    free_struct(network_trame);
    exit(0);
}

/**
 * @brief Display like command ping 
 *  
 * @param network_trame Struct content information of the trame
 * @param code_step Code of the step display
 */
void addr_info(t_ping *network_trame, int code_step)
{
    struct hostent  *host_server;

    host_server = network_trame->ip_hdr->host_server;
    if (code_step == 0)
    {
        char ip_str[INET_ADDRSTRLEN];

        //PING 8.8.8.8
        printf("FT_PING %s ", host_server->h_name); 

        // (8.8.8.8)
        printf("(%s) ", inet_ntop(host_server->h_addrtype, *host_server->h_addr_list, ip_str, sizeof(ip_str)));

        // 56(84) bytes of data.
        printf("%ld(%ld) bytes of data.\n", \
            (DATA_SIZE - sizeof(network_trame->ip_hdr->icmp_v4->header)), \
            (DATA_SIZE - sizeof(network_trame->ip_hdr->icmp_v4->header)+\
            sizeof(network_trame->ip_hdr->host_server->h_addr_list[0])+\
            sizeof(*network_trame->ip_hdr->dest_addr)));

        //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
        // (ICMP Header + ICMP msg  + IPv4)
    }
    else
    {
        //64 bytes from 8.8.8.8: icmp_seq=1 ttl=116 time=3.32 ms
        printf("\n");
        printf("END\n");
    }
}