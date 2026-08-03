/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/03 18:04:10 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"

/*bool addr_info(t_ping *network_trame)
{
    t_ip *ip_headr;
    struct hostent *host_server;

    ip_headr = network_trame->ip_hdr;
    host_server = network_trame->ip_hdr->host_server;

    ip_headr->ip_addr = (char *)malloc(NI_MAXHOST * sizeof(char));
    if (!ip_headr->ip_addr)
    {

        return (true);
    }

    //strcpy(ip_headr->ip_addr, inet_ntoa(*(struct in_addr *)host_server->h_addr));
    (ip_headr->addr_con).sin_family = host_server->h_addrtype;
    (ip_headr->addr_con).sin_port = htons(0);
    //(ip_headr->addr_con).sin_addr.s_addr = *(long *)host_server->h_addr;
}*/

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("sudo ./ft_ping [OPTION] <adresse>\n");
        return (0);
    }

    t_ping network_trame;

    if (init_struct(&network_trame))
        return (1);

    if (lookup(av[ac - 1], &network_trame))
        return (0);

    //main_loop(icmp_sock, packet, packlen);


    free_struct(&network_trame);
    return (0);
}