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

  std::string sockbuff(4096, '*');
  std::string pong = "PONG :tmi.twitch.tv";
  while (1) {
	memset(&sockbuff[0], '\0', sizeof(sockbuff));
	recv(sockd, &sockbuff[0], sockbuff.length()+1, 0);

	if (sockbuff == "PING :tmi.twitch.tv") {
		std::cout << "!!!!!!!!GOT PING FROM SERVER!!!!!" << std::endl;
		send(sockd, &pong[0], pong.length()+1, 0);
	}

	char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
	sscanf(sockbuff.c_str(), ":%31[^!]%s%s%s%c%c%256[^\n]",
		   n, x, y, z, q, w, m);

	// printf("nick: %s\n", n);
	printf("%s: ", n);
	printf("%s\n", m);
	// printf("u: %s\n", u);
	// printf("s: %s\n", s);
	// printf("ch: %s\n", ch);
  }
  return 0;
}
