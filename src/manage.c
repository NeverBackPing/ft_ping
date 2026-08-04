/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:52 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/04 16:36:29 by sjossain         ###   ########.fr       */
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
    free(network_trame->ip_hdr);
}