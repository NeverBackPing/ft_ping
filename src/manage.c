/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:52 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/08 12:04:06 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manage.h"


/**
 * @brief init structure
 * 
 * @param network_trame init instance in this struct
 * @return true 
 * @return false 
 */
bool init_struct(t_ping *network_trame)
{
    network_trame->ip_hdr = (struct s_ip*) malloc(sizeof(t_ip));
    
    if (network_trame->ip_hdr ==  NULL)
    {
        printf("Error: malloc error\n");
        exit(1);
    }
    
    network_trame->socket = -1;
    network_trame->ip_hdr->ip_addr = NULL;
    network_trame->ip_hdr->rev_hostname = NULL;
    return (false);
}
/**
 * @brief free the instance allocate
 * 
 * @param network_trame 
 */
void free_struct(t_ping *network_trame)
{
    if (network_trame->socket >=  0)
        close(network_trame->socket);
    network_trame->socket = -1;
    if (network_trame->ip_hdr->rev_hostname)
        free(network_trame->ip_hdr->rev_hostname);
    if (network_trame->ip_hdr->ip_addr != NULL)
        free(network_trame->ip_hdr->ip_addr);
    free(network_trame->ip_hdr);
    network_trame = NULL;
}