#include "connect.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: chats <channel_name>\n");
        return 1;
    }

    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;

    int sockd;
    connect_server(argv[1], &sockd);

    char sockbuff[4096];
    /* char ping[] = "PING :tmi.twitch.tv"; */
    /* char pong[] = "PONG :tmi.twitch.tv"; */
    int quit = 0;
    while (!quit) {

        memset(&sockbuff[0], '\0', sizeof(sockbuff));
        int msg_len = recv(sockd, &sockbuff[0], sizeof(sockbuff)/sizeof(sockbuff[0]), 0);

        if (msg_len > 0) {
            char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
            // @TODO: Dont hardcode this
            sscanf(sockbuff, ":%31[^!]%s%s%s%c%c%256[^\n]",
                   n, x, y, z, q, w, m);
            strcat(n, ": ");
            strcat(m, "\n");


            char msg[500];
            strcat(msg, n);
            strcat(msg, m);
            printf("%s", msg);
        }
    }
    return 0;
}
