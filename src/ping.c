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
        printf("Error: Socket file descriptor not received!\n");
        free_struct(network_trame);
        exit(1);
    }
}

// Calculate the checksum (RFC 1071)
unsigned short checksum(void *b, int len)
{
    unsigned short  *buf;
    unsigned int    sum;
    unsigned short  result;

    buf = b;
    sum = 0;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;

    if (len == 1)
        sum += *(unsigned char *)buf;

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);

    result = ~sum;

    return (result);
}

void    socket_option(t_ping  *network_trame)
{
    if (setsockopt(network_trame->socket, SOL_IP, IP_TTL, \
        &network_trame->ttl_size, sizeof(network_trame->ttl_size)) != 0)
    {
        printf("\nError: Setting socket options to TTL failed!\n");
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


    for (i = 0; i < sizeof(packet_icmp->msg); i++)
    {
        packet_icmp->msg[i] =  msg[i];
        if (i + 1 == sizeof(packet_icmp->msg))
        {
            i++;
            break;
        }
        i++;
    }

    packet_icmp->msg[i] = '\0';
    packet_icmp->header.un.echo.sequence = network_trame->count_pck_send++;
    packet_icmp->header.checksum = checksum(&packet_icmp, sizeof(packet_icmp));
    
}

void    send_pkt(t_ping *network_trame, t_icmp_headedr *icmp_v4, struct timespec time)
{
    clock_gettime(CLOCK_MONOTONIC, &time);
    if (!sendto(network_trame->socket, icmp_v4, sizeof(icmp_v4), 0,  (struct sockaddr*)&network_trame->ip_hdr->addr_con, sizeof(network_trame->ip_hdr->addr_con)))
    {
        printf("\nError: Packet Sending Failed!\n");
    }
}


void icmp_network(t_ping *network_trame, char **input)
{
    t_ip            *ip_header;
    struct hostent  *host_server;

    loop_icmp = true;
    ip_header = network_trame->ip_hdr;
    host_server = network_trame->ip_hdr->host_server;

    (void) input;
    (void) ip_header;
    (void) host_server;

    chrono_time(CLOCK_MONOTONIC, &network_trame->tm_packet->tfs);
    
    socket_option(network_trame);

    addr_info(network_trame, HEADER_PRINT);

    signal(SIGINT, signal_exit_loop_cmp);

    while (loop_icmp)
    {
        // create packet and set header icmp
        create_packet(network_trame, network_trame->ip_hdr->icmp_v4, "hellod");
        // 1sec
        usleep(PING_SLEEP_RATE);

        // Send packet
        send_pkt(network_trame, network_trame->ip_hdr->icmp_v4, network_trame->tm_packet->time_start);
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
            sizeof(network_trame->ip_hdr->icmp_v4->header)+\
            sizeof(network_trame->ip_hdr->sa)));

        //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
        // (ICMP Header + ICMP msg  + IPv4)
    }
    else
    {
        printf("\n");
        printf("END\n");
    }
}