#include "../include/dns.h"

/**
 * @brief Check if the IPV4 or hostname address is valable
 * 
 * @param ip_host Content the IPv4 or hostname
 * @param network_trame Struct who storage information of the trame
 * @return true 
 * @return false 
 */
bool lookup(char *ip_hostg, t_ping *network_trame)
{
    t_ip *ip_headr;

    ip_headr = network_trame->ip_hdr;
    ip_headr->host_server = gethostbyname(ip_hostg);

    if (ip_headr->host_server == NULL)
    {
        printf("ft_ping: %s: Name or service not known\n", ip_hostg);
        return (true);
    }

    addr_info(network_trame, HEADER_PRINT);

    ip_headr->ip_addr = (char *)malloc(NI_MAXHOST * sizeof(char));
    if (!ip_headr->ip_addr)
    {
        printf("Error: Init malloc\n");
        return (true);
    }
    
    // Fill up address structure
    ft_strcpy(ip_headr->ip_addr, ip_headr->host_server->h_name);
    printf("ip_addr = %s\n", ip_headr->host_server->h_name);
    printf("ip_addr = %s\n", ip_headr->ip_addr);
    (ip_headr->addr_con).sin_family = ip_headr->host_server->h_addrtype;
    (ip_headr->addr_con).sin_port = htons(0); // Addresse de socket
    (ip_headr->addr_con).sin_addr.s_addr = *(long *)ip_headr->host_server->h_addr_list;
    return (false);
}