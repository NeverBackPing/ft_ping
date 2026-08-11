#ifndef MANAGE_STRUCT_H
#define MANAGE_STRUCT_H

#define PING_SLEEP_RATE 1000000
#define DATA_SIZE 64 // Payload data ICMP

//Lib the project ft_ping
#include "ping.h"

/*Display data command ping*/
enum display
{
    HEADER_PRINT,
    END_PRINT
};

/*Time*/
struct s_time_packet
{
    // unity: nanosecondes
    struct timespec tfs;
    struct timespec tfe;
    struct timespec time_end;
    struct timespec time_start;
} t_time_packet;


/*ICMP*/
typedef struct s_icmp_headedr
{
    int             checksum; // 
    char            msg[DATA_SIZE - sizeof(struct icmphdr)]; // 56 octets
    struct icmphdr  header; // 8 octets
} t_icmp_headedr;

/*IP*/
typedef struct s_ip
{
    char                *ip_addr; // IPv4
    char                *rev_hostname; // Reverse hostname IP
    struct hostent      *host_server; // Datas for single hostname (addr, name host, len, list addr)
    t_icmp_headedr      icmp_v4; // Protocole ICMP for Ipv4
    struct sockaddr     sa; // Internet socket address (Port, Ip addr IPv4)
    struct sockaddr_in  addr_con; // Internet socket address (Port, Ip addr IPv4)
} t_ip;

/*Command ping*/
typedef struct s_ping
{
    int                 socket; // Interface of communication
    long double             rtt_ms; // Round-Trip Time  in microseconde
    long double             total_ms; // total in microseconde
    t_ip                    *ip_hdr; // IP header
    struct timeval          time_nano_out; //Time send packet unity: microseconde
    struct t_time_packet    *tm_packet; //clock manager
} t_ping;

#endif