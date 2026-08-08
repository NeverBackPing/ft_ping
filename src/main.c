/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/08 21:32:13 by never            ###   ########.fr       */
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

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("sudo ./ft_ping [OPTION] <adresse>\n");
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

    open_socked(&network_trame);
    
    while (loop_icmp)
    {
        sleep(1);
    }
    
    addr_info(&network_trame, END_PRINT);
    
    free_struct(&network_trame);
    //main_loop(icmp_sock, packet, packlen);
    return (0);
}