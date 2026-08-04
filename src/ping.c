#include "../include/ping.h"

void signalHandler(int sig)
{
    //Voir pour mettre la fonction free_struct() et addr_info()
    _exit(sig);
}

/**
 * @brief Display like command ping 
 *  
 * @param network_trame Struct content information of the trame
 * @param code_step Code of the step display
 */
void addr_info(t_ping *network_trame, int code_step)
{
    struct hostent *host_server;

    host_server = network_trame->ip_hdr->host_server;
    if (code_step == 0)
    {
        char ip_str[INET_ADDRSTRLEN];
        printf("FT_PING %s ", host_server->h_name);
        /*comment need*/
        printf("( %s ) ", inet_ntop(host_server->h_addrtype, *host_server->h_addr_list, ip_str, sizeof(ip_str)));
        printf("<payload ICMP>(%d + ICMP Header + ICMP Header) bytes of data.\n", host_server->h_length);
        
        //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.
    }
}