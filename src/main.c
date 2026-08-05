/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/05 15:45:07 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"

int main(int ac, char **av)
{
    signal(SIGINT, signalHandler);
    
    if (ac < 2)
    {
        printf("sudo ./ft_functionping [OPTION] <adresse>\n");
        return (0);
    }
    //t_ping  network_trame;
    if (init_struct(&network_trame))
        return (1);

    if (lookup(av[ac - 1], &network_trame))
        return (0);

    while (true)
    {
        
    }
    
    //main_loop(icmp_sock, packet, packlen);

    free_struct(&network_trame);
    return (0);
}