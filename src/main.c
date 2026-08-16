/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:41:08 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/16 19:55:30 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dep/libft/libft.h"
#include "../include/ping.h"
#include "../include/dns.h"
#include "../include/manage.h"
#include "../include/dataStruct.h"

void check_option(int count_arg, char *option)
{
    if (count_arg == 2)
        return ;
    if (option[0] != '-' || option[1] != 'v' || ft_strlen(option) != 2)
    {
        printf("\033[31mError\033[0m: Bad option:\n");
        exit(1);
    }
}

int main(int ac, char **av)
{
    if (ac != 2 && ac != 3)
    {
        printf("\033[31mError\033[0m: Bad argument run CLI like below:\n");
        printf("sudo ./ft_ping <adresse>\n");
        printf("sudo ./ft_ping [OPTION] <adresse>\n");
        return (0);
    }
    
    t_ping network_trame = {0};
    
    // check option
    check_option(ac, av[ac - 2]); 
    
    // init instance
    init_struct(&network_trame); 
    
    // finding the IP address associated with a domain name.
    lookup(av[ac - 1], &network_trame);

    // reverse DNS
    reverse(&network_trame);

    // Get INTF for mak econnection
    open_socked(&network_trame);
    
    //send ping
    icmp_network(&network_trame);
    
    // end print summary 
    addr_info(&network_trame, END_PRINT);
    
    free_struct(&network_trame);
    
    return (0);
}