#include <cstring>
#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <fstream>
#include "connect.h"


int main(int argc, char **argv) {

  if (argc != 2) {
	printf("Usage: chats <channel_name>\n");
	return 1;
  }

  int sockd;
  connect(argv[1], sockd);

  char sockbuff[4096];
  char ping[] = "PING :tmi.twitch.tv";
  char pong[] = "PONG :tmi.twitch.tv";
  while (1) {
	memset(&sockbuff[0], '\0', sizeof(sockbuff));
	recv(sockd, &sockbuff[0], sizeof(sockbuff)/sizeof(sockbuff[0]), 0);

	char tmp[20];
	strncpy(tmp, sockbuff, 20);
	tmp[19] = '\0';
	if (strcmp(tmp, ping) == 0) {
		std::cout << "!!!!!!!!GOT PING FROM SERVER!!!!!" << std::endl;
		send(sockd, &pong[0], sizeof(pong)/sizeof(pong[0]), 0);
	}

	char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
	sscanf(sockbuff, ":%31[^!]%s%s%s%c%c%256[^\n]",
		   n, x, y, z, q, w, m);

	 printf("%s: ", n);
	 printf("%s\n", m);
	 std::cout << "sockbuff: " << sockbuff << "\n";
  }
  return 0;
}
