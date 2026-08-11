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

void chrono_time(int CLOCK, struct timespec *time)
{
    clock_gettime(CLOCK, time); //sans risque d'erreurs si l'heure du système change
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

    chrono_time(CLOCK_MONOTONIC, &network_trame->tm_packet.tfs);
    
    signal(SIGINT, signal_exit_loop_cmp);

    while (loop_icmp)
    {
        usleep(PING_SLEEP_RATE); // 1sec
    }
    
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
        printf("<payload ICMP>(%d + ICMP Header + ICMP Header) bytes of data.\n", host_server->h_length);

        //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
    }
    else
    {
        printf("\n");
        printf("END\n");
    }
}