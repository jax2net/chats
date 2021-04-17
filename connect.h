#ifndef CONNECT_H
#define CONNECT_H

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 6667
void connect_server(char *channel, int *sockd);

#endif // CONNECT_H
