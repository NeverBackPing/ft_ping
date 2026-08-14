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
        free_struct(network_trame);
        exit(1);
    }

    ip_headr->ip_addr = (char *)malloc(NI_MAXHOST * sizeof(char));
    if (!ip_headr->ip_addr)
    {
        printf("\033[31mError\033[0m: Init malloc\n");
        free_struct(network_trame);
        exit(1);
    }
    
    // Fill up address structure
    ft_strcpy(ip_headr->ip_addr, ip_headr->host_server->h_name);
    ip_headr->dest_addr->sin_port = htons(0); // Addresse de socket
    ip_headr->dest_addr->sin_family = ip_headr->host_server->h_addrtype; // IP version
    ft_memcpy(
        &ip_headr->dest_addr->sin_addr,
        ip_headr->host_server->h_addr_list[0],
        sizeof(ip_headr->dest_addr->sin_addr)
    ); // IP 
    return (false);
}

/**
 * @brief That allows you to retrieve the domain name associated with an IP address
 * 
 * @param network_trame Struct who storage information of the trame
 * @return true 
 * @return false 
 */
bool reverse(t_ping *network_trame)
{
    int     register_ptr;
    t_ip    *ip_header;
    char    buf[NI_MAXHOST];

    ip_header = network_trame->ip_hdr;
    
    ip_header->dest_addr->sin_family = AF_INET; //IP version 
    ip_header->dest_addr->sin_port = htons(0);  // port
    ft_memcpy(
        &ip_header->dest_addr->sin_addr,
        ip_header->host_server->h_addr_list[0],
        sizeof(ip_header->dest_addr->sin_addr)
    ); // IP  // binary data in network byte order.
    register_ptr = getnameinfo((const struct sockaddr *)&ip_header->dest_addr,\
    sizeof(struct sockaddr), buf, NI_MAXHOST, NULL, 0, NI_NAMEREQD);
    if (register_ptr)
    {
        if (ip_header->host_server->h_addr_list)
            return (false);
        printf("ft_ping: Could not resolve reverse lookup of hostname\n");
        free_struct(network_trame);
        exit(1);
    }
    
    ip_header->rev_hostname = (char *)malloc((ft_strlen(buf) + 1) * sizeof(char));
    ft_strcpy(ip_header->rev_hostname, buf);

    return (false);
}