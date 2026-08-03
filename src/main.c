#include "../dep/libft/libft.h"
#include "../include/ping.h"

/*bool addr_info(t_ping *network_trame)
{
    t_ip *ip_headr;
    struct hostent *host_server;

    ip_headr = network_trame->ip_hdr;
    host_server = network_trame->ip_hdr->host_server;

    ip_headr->ip_addr = (char *)malloc(NI_MAXHOST * sizeof(char));
    if (!ip_headr->ip_addr)
    {

        return (true);
    }

    //strcpy(ip_headr->ip_addr, inet_ntoa(*(struct in_addr *)host_server->h_addr));
    (ip_headr->addr_con).sin_family = host_server->h_addrtype;
    (ip_headr->addr_con).sin_port = htons(0);
    //(ip_headr->addr_con).sin_addr.s_addr = *(long *)host_server->h_addr;
}*/

/*comment need*/
void addr_info(t_ping *network_trame, int code_step)
{
    struct hostent *host_server;

    host_server = network_trame->ip_hdr->host_server;
    if (code_step == 0)
    {
        char ip_str[INET_ADDRSTRLEN];
        printf("FT_PING %s ", host_server->h_name);
        /*comment need*/
        printf("( %s ) ", inet_ntop(host_server->h_addrtype, host_server->h_addr_list[0], ip_str, sizeof(ip_str)));
        printf("<payload ICMP>(%d + ICMP Header + ICMP Header) bytes of data.\n", host_server->h_length);
    }
}

/*comment need*/
bool lookup(char *ip_hostg, t_ping *network_trame)
{
    t_ip *ip_headr;

    ip_headr = network_trame->ip_hdr;
    ip_headr->host_server = gethostbyname(ip_hostg);

    if (ip_headr->host_server == NULL)
    {
        printf("ft_ping: %s: Name or service not known\n", ip_hostg);
        return (true);
    }
    addr_info(network_trame, HEADER_PRINT);
    return (false);
}

int main(int ac, char **av)
{
    (void)av;

    if (ac < 2)
    {
        printf("sudo ./ft_ping [OPTION] <adresse>\n");
        return (0);
    }

    t_ping network_trame;

    
    if (lookup(av[2], &network_trame))
        return (0);

    //PING 8.8.8.8 (8.8.8.8) 56(84) bytes of data.

    //main_loop(icmp_sock, packet, packlen);
    return (0);
}