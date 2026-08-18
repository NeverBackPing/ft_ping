#ifndef MANAGE_STRUCT_H
#define MANAGE_STRUCT_H

#define PING_SLEEP_RATE 1000000
#define DATA_SIZE 64 // Payload data ICMP
#define RECV_SIZE 1024 // receive reply

//Lib the project ft_ping
#include "ping.h"

/*Display data command ping*/
enum display
{
    HEADER_PRINT,
    PING,
    END_PRINT
};

/*Time*/
typedef struct s_time_packet
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
    struct icmphdr  header; // 8 octets
    char            msg[DATA_SIZE - sizeof(struct icmphdr)]; // 56 octets
} t_icmp_headedr;

/*IP*/
typedef struct s_ip
{
    char                *ip_addr; // IPv4
    char                *rev_hostname; // Reverse hostname IP

    struct hostent      *host_server; // Datas for single hostname (addr, name host, len, list ip)
    t_icmp_headedr      *icmp_v4; // Protocole ICMP for Ipv4

    struct sockaddr_in  *dest_addr; // Internet socket address client (Port, Ip addr IPv4)
    struct sockaddr_in  src_addr; // Internet socket address server (Port, Ip addr IPv4)
} t_ip;

/*Command ping*/
typedef struct s_ping
{

    bool                     is_ip;
    bool                     flag_sent; // flag if packet send
    bool                     option; // flag if packet send

    char                    receiv_buffer[4096];
    int                     count_pck_send; // count packeyt send
    int                     count_pck_received; // packet receiv
    int                     ttl_size; // size protocole
    int                     socket; // Interface of communication

    long double             rtt_values[10000];
    long double             rtt_min;
    long double             rtt_max;
    long double             rtt_sum;
    long double             rtt_avg;
    long double             rtt_mdev;
    long double             rtt_ms; // Round-Trip Time  in microseconde
    long double             total_ms; // total in microseconde

    t_ip                    *ip_hdr; // IP header
    struct timeval          time_nano_out; //Time send packet unity: microseconde
    t_time_packet           *tm_packet; //clock manager
} t_ping;

#endif