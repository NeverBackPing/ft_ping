/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:52 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/07 19:21:26 by never            ###   ########.fr       */
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
        return (true);

    return (false);
}
/**
 * @brief free the instance allocate
 * 
 * @param network_trame 
 */
void free_struct(t_ping *network_trame)
{
    if (network_trame->ip_hdr->rev_hostname != NULL)
        free(network_trame->ip_hdr->rev_hostname);
    if (network_trame->ip_hdr->ip_addr != NULL)
        free(network_trame->ip_hdr->ip_addr);
    free(network_trame->ip_hdr);
    network_trame = NULL;
}