/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:55 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/04 17:45:43 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_H
#define MANAGE_H

//Lib the project ft_ping
#include "dns.h"
#include "ping.h"
#include "dataStruct.h"

void free_struct(t_ping *network_trame);
bool init_struct(t_ping *network_trame);

#endif