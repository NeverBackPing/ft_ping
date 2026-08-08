#ifndef DNS_H
#define DNS_H

//Lib the project ft_ping
#include "ping.h"
#include "manage.h"
#include "dataStruct.h"

bool reverse(t_ping *network_trame);
bool lookup(char *ip_hostg, t_ping *network_trame);

#endif