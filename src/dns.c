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
    return (false);
}