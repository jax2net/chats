#include "connect.h"

void connect_server(char *channel, int *sockd) {
    // get config
    //char *home = getenv("HOME");
    FILE *fp;
    fp = fopen("/home/j/.config/chats/config", "r");
    char nick_i[255];
    char key_i[255];
    fscanf(fp, "%s", nick_i);
    fscanf(fp, "%s", key_i);
    char nick[30] = "NICK ";
    char pass[80] = "PASS ";
    char join[20] = "JOIN #";

    strcat(nick, nick_i);
    strcat(pass, key_i);
    strcat(nick, "\n");
    strcat(pass, "\n");

    char server[] = "irc.chat.twitch.tv";

    strcat(join, channel);
    strcat(join, "\n");

    /** structs that hold the socket info **/
    struct sockaddr_in addr;
    struct addrinfo hints, *res;
    struct hostent *host;

    host = gethostbyname(server);

    addr.sin_addr.s_addr = *(unsigned long *)host->h_addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((unsigned short) PORT);

    *sockd = socket(AF_INET, SOCK_STREAM, 0);

    int c = connect(*sockd, (struct sockaddr *)&addr, sizeof(addr));
    if (c == -1) { printf("Cannot establish connection to server."); }


    // COMMANDS
    send(*sockd, &pass[0], sizeof(pass)/sizeof(pass[0]), 0);
    send(*sockd, &nick[0], sizeof(nick)/sizeof(nick[0]), 0);
    send(*sockd, &join[0], sizeof(join)/sizeof(join[0]), 0);
}
