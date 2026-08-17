/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: never <never@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 17:40:52 by sjossain          #+#    #+#             */
/*   Updated: 2026/08/17 01:11:31 by never            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/manage.h"


/**
 * @brief init structure
 * 
 * @param network_trame init instance in this struct
 * @return true 
 * @return false 
 */
bool init_struct(t_ping *network_trame)
{
    network_trame->ip_hdr = (struct s_ip*) malloc(sizeof(t_ip));
    
    if (network_trame->ip_hdr ==  NULL)
    {
        printf("\033[31mError\033[0m: malloc \033[31mError\033[0m\n");
        exit(1);
    }
    
    network_trame->tm_packet = (struct s_time_packet *) malloc(sizeof(t_time_packet));
    
    if (network_trame->tm_packet ==  NULL)
    {
        free(network_trame->ip_hdr);
        printf("\033[31mError\033[0m: malloc \033[31mError\033[0m\n");
        exit(1);
    }

    network_trame->ip_hdr->icmp_v4 = (struct s_icmp_headedr *) malloc(sizeof(t_icmp_headedr));
    
    if (network_trame->ip_hdr->icmp_v4 ==  NULL)
    {
        free(network_trame->ip_hdr->icmp_v4);
        printf("\033[31mError\033[0m: malloc \033[31mError\033[0m\n");
        exit(1);
    }

    // init all a 0
    ft_bzero(network_trame->ip_hdr->icmp_v4, sizeof(t_icmp_headedr));
    
    network_trame->ip_hdr->dest_addr = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in)); // size 64
    
    if (network_trame->ip_hdr->dest_addr ==  NULL)
    {
        free(network_trame->ip_hdr->dest_addr);
        printf("\033[31mError\033[0m: malloc \033[31mError\033[0m\n");
        exit(1);
    }
    
    network_trame->is_ip = false; // check if a ip or hostname
    network_trame->flag_sent = false; // interface communication
    network_trame->socket = -1; // interface communication
    network_trame->ttl_size = DATA_SIZE; // Value de l'option  TTL (Time to Live)
    network_trame->rtt_ms = 0;
    network_trame->total_ms = 0;
    network_trame->time_nano_out.tv_usec = 0; // Run start
    network_trame->time_nano_out.tv_sec = 1; //Timout 1 sec 
    network_trame->ip_hdr->ip_addr = NULL;
    network_trame->ip_hdr->rev_hostname = NULL;

    return (false);
}

/**
 * @brief free the instance allocate
 * 
 * @param network_trame 
 */
void free_struct(t_ping *network_trame)
{
    if (network_trame->tm_packet  != NULL)
        free(network_trame->tm_packet);
        
    if (network_trame->socket >=  0)
    {
        close(network_trame->socket);
        network_trame->socket = -1;
    }
    
    if (network_trame->ip_hdr->rev_hostname != NULL)
        free(network_trame->ip_hdr->rev_hostname);
    
    if (network_trame->ip_hdr->ip_addr != NULL)
        free(network_trame->ip_hdr->ip_addr);
    
    if (network_trame->ip_hdr->icmp_v4 != NULL)
        free(network_trame->ip_hdr->icmp_v4);
        
    if (network_trame->ip_hdr->dest_addr != NULL)
        free(network_trame->ip_hdr->dest_addr);
        
    free(network_trame->ip_hdr);
    network_trame = NULL;
}
