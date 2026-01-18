#ifndef PING_H
# define PING_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <netinet/ip_icmp.h>// sockaddr_in

#include "token.h"
#include "parsing.h"
#include "hub_struct.h"
#include "../incl/lexer.h"
#include "./dep/libft/libft.h"


typedef struct s_ping
{
    char *ip_addr; // stock ip address 0.0.0.0 | 255.255.255.255 DNS lookup
    char *reverse_hostname; // stock name domain  with associated a domain name Reverse DNS lookup
    char **option;
} t_ping;

typedef struct s_client
{
    struct sockaddr_in socketaddr;
    t_ping *ping;

} t_client;

#endif
