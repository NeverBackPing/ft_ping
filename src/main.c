/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/05 17:50:11 by sjossain         ###   ########.fr       */
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

    while (true)
    {

    }
    
    //main_loop(icmp_sock, packet, packlen);
    return (0);
}