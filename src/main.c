/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/14 18:24:02 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"
#include "../include/dataStruct.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        printf("sudo ./ft_ping [OPTION] <adresse>\n");
        return (0);
    }
    
    t_ping  network_trame;
    
    if (init_struct(&network_trame))
        return (1);
        
    if (lookup(av[ac - 1], &network_trame))
        return (0);

    if (reverse(&network_trame))
        return (0);

    open_socked(&network_trame);
    
    icmp_network(&network_trame, av);
    
    addr_info(&network_trame, END_PRINT);
    
    free_struct(&network_trame);
    
    return (0);
}