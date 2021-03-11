#include <arpa/inet.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <fstream>


int main(int argc, char **argv) {

  if (argc != 2) {
	printf("Usage: chats <channel_name>\n");
	return 1;
  }

  std::string username, key;
  std::ifstream config("config");
  std::string channel = argv[1];
  getline(config, username);
  getline(config, key);


  int connected = 0;
  char server[] = "irc.chat.twitch.tv";
  int port = 6667;
  std::string nick_prefix = "NICK ";
  std::string nick = nick_prefix + username + "\n";
  std::string join_prefix = "JOIN #";
  std::string join = join_prefix + channel + "\n";
  std::string pass_prefix = "PASS ";
  std::string pass = pass_prefix + key + "\n";

  /** structs that hold the socket info **/
  struct sockaddr_in addr;
  struct addrinfo hints, *res;
  struct hostent *host;

  host = gethostbyname(server);

  addr.sin_addr.s_addr = *(unsigned long *)host->h_addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons((unsigned short)port);

  int sockd = socket(AF_INET, SOCK_STREAM, 0);

  int c = connect(sockd, (struct sockaddr *)&addr, sizeof(addr));

  // COMMANDS
  send(sockd, &pass[0], pass.length()+1, 0);
  send(sockd, &nick[0], nick.length()+1, 0);
  send(sockd, &join[0], join.length()+1, 0);

  char sockbuff[4096];
  while (1) {
	memset(&sockbuff, '\0', sizeof(sockbuff));
	recv(sockd, sockbuff, sizeof(sockbuff), 0);

	char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
	sscanf(sockbuff, ":%31[^!]%s%s%s%c%c%256[^\n]",
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
