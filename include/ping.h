/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:59 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/07 00:49:49 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H

//Lib include user
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h> 
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <bits/socket.h>

//Lib the project ft_ping
#include "dns.h"
#include "manage.h"
#include "dataStruct.h"
#include "../dep/libft/libft.h"

void addr_info(t_ping *network_trame, int code_step);

#endif