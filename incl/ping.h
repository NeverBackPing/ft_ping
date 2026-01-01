#ifndef PING_H
# define PING_H

#include "./dep/libft/libft.h"
#include <stdio.h>
#include <in.h> // sockaddr_in


typedef struct s_ping
{
    char *ip_addr; // stock ip address 0.0.0.0 | 255.255.255.255 DNS lookup
    char *reverse_hostname; // stock name domain  with associated a domain name Reverse DNS lookup
    struct sockaddr_in serv_addr;



} t_ping;


#endif
