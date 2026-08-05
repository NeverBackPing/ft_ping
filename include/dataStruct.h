#ifndef MANAGE_STRUCT_H
#define MANAGE_STRUCT_H

//Lib the project ft_ping
#include "ping.h"

/*comment need et name*/
enum display
{
    HEADER_PRINT,
    END_PRINT
};

typedef struct s_ip
{
    char                *ip_addr;
    char                *rev_hostname;
    struct sockaddr_in  addr_con;
    struct hostent      *host_server;

} t_ip;

typedef struct s_ping
{
    t_ip *ip_hdr;

} t_ping;

#endif