/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/07 20:04:47 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"
#include "../include/dataStruct.h"

bool loop_icmp;

void signalHandler(int sig)
{
    (void)sig;
    loop_icmp = false;
}
/**
 * @brief A reverse DNS record is simply an entry that 
 *        resolves an IP address back to a host name
 * 
 * @param network_trame Struct content information of the trame
 */
bool reverse(t_ping *network_trame)
{
    int     register_ptr;
    t_ip    *ip_header;
    char    buf[NI_MAXHOST];

    ip_header = network_trame->ip_hdr;
    
    ip_header->addr_con.sin_family = AF_INET; //IP version 
    
    ip_header->addr_con.sin_addr.s_addr = inet_addr(ip_header->ip_addr); // binary data in network byte order.
    register_ptr = getnameinfo((const struct sockaddr *)&ip_header->addr_con,\
    sizeof(struct sockaddr), buf, NI_MAXHOST, NULL, 0, NI_NAMEREQD);
    if (register_ptr)
    {
        printf("ft_ping: Could not resolve reverse lookup of hostname\n");
        free_struct(network_trame);
        return (true);
    }
    
    ip_header->rev_hostname = (char *)malloc((ft_strlen(buf) + 1) * sizeof(char));
    ft_strcpy(ip_header->rev_hostname, buf);

    return (false);
}

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("sudo ./ft_functionping [OPTION] <adresse>\n");
        return (0);
    }

    loop_icmp = true;
    
    t_ping  network_trame;
    
    if (init_struct(&network_trame))
        return (1);
    
    signal(SIGINT, signalHandler);
    
    if (lookup(av[ac - 1], &network_trame))
        return (0);

    if (reverse(&network_trame))
        return (0);

    while (loop_icmp)
    {
        sleep(1);
    }
    
    addr_info(&network_trame, END_PRINT);
    
    free_struct(&network_trame);
    //main_loop(icmp_sock, packet, packlen);
    return (0);
}