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

typedef struct s_icmp_headedr
{
    struct icmphdr header;
} t_icmp_headedr;

typedef struct s_ip
{
    char                *ip_addr;
    char                *rev_hostname;
    struct sockaddr         sa;
    struct sockaddr_in  addr_con;
    struct hostent      *host_server;
    t_icmp_headedr      icmp_v4;

} t_ip;

typedef struct s_ping
{
    int     socket;
    t_ip    *ip_hdr;

} t_ping;

#define PING_SLEEP_RATE 1000000 

#endif