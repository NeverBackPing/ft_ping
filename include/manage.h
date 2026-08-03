/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:55 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/03 18:11:53 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGE_H
#define MANAGE_H

#include "ping.h"
#include "dns.h"
#include <stdlib.h>

void free_struct(t_ping *network_trame);
bool init_struct(t_ping *network_trame);

#endif