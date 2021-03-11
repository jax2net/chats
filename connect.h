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

void connect(std::string chan, int &sockd) {

  std::string username, key;
  std::string home = getenv("HOME");
  std::ifstream config(home + "/.config/chats/config");
  std::string channel = chan;
  getline(config, username);
  getline(config, key);
  std::cout << username << std::endl;
  std::cout << key << std::endl;

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

  sockd = socket(AF_INET, SOCK_STREAM, 0);

  int c = connect(sockd, (struct sockaddr *)&addr, sizeof(addr));

  // COMMANDS
  send(sockd, &pass[0], pass.length()+1, 0);
  send(sockd, &nick[0], nick.length()+1, 0);
  send(sockd, &join[0], join.length()+1, 0);
}
