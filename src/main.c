/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/07 01:27:30 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"
#include "../include/dataStruct.h"

t_ping  network_trame;

void signalHandler(int sig)
{
    //Voir pour mettre la fonction free_struct() et addr_info()
    addr_info(&network_trame, END_PRINT);
    free_struct(&network_trame);
    exit(sig);
}
/**
 * @brief A reverse DNS record is simply an entry that 
 *        resolves an IP address back to a host name
 * 
 * @param network_trame Struct content information of the trame
 */
bool reverse(t_ping *network_trame)
{
    t_ip                *ip_header;
    char                buf[1025];

    ip_header = network_trame->ip_hdr;
    
    ip_header->addr_con.sin_family = AF_INET; //IP version 
    printf("ICI\n");
    printf("ip_addr = %s\n", ip_header->ip_addr);
    
    ip_header->addr_con.sin_addr.s_addr = inet_addr(ip_header->ip_addr); // binary data in network byte order.
    int i = getnameinfo((const struct sockaddr *)&ip_header->addr_con, sizeof(ip_header->addr_con), buf, sizeof(buf), NULL, 0, NI_NAMEREQD);
    printf("i = %d\n", i);
    if (i)
    {
        printf("ft_ping: Could not resolve reverse lookup of hostname\n");
        free_struct(network_trame);
        return (true);
    }
    ip_header->rev_hostname = (char *)malloc((ft_strlen(buf) + 1) * sizeof(char));
    ft_strlcpy(ip_header->rev_hostname, buf, ft_strlen(buf));

    printf("ip_addr = %s\n", ip_header->rev_hostname);

    
    return (false);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("sudo ./ft_functionping [OPTION] <adresse>\n");
        return (0);
    }
    
    if (init_struct(&network_trame))
        return (1);
    
    signal(SIGINT, signalHandler);
    
    if (lookup(av[ac - 1], &network_trame))
        return (0);

    if (reverse(&network_trame))
        return (0);
    printf("hostname: %s\n", network_trame.ip_hdr->rev_hostname);
    while (true)
    {

    }
    
    //main_loop(icmp_sock, packet, packlen);
    return (0);
}