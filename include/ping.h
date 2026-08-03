/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:59 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/03 17:57:04 by sjossain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
#define PING_H




#include <stdio.h>
#include <stdbool.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../include/dns.h"
#include "../include/manage.h"

/*comment need et name*/
enum 
{
    HEADER_PRINT
};

typedef struct s_ip {

    char                *ip_addr;
    char                *rev_hostname;
    struct sockaddr_in  addr_con;
    struct hostent      *host_server;

} t_ip;

typedef struct s_ping {

    t_ip *ip_hdr;

} t_ping;

void addr_info(t_ping *network_trame, int code_step);

#endif