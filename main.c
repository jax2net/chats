#include "connect.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: chats <channel_name>\n");
        return 1;
    }

    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;

    SDL_Window *window;
    SDL_Renderer *renderer;
    if (SDL_CreateWindowAndRenderer(WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &window, &renderer)) {
        printf("Failed to make window and renderer: %s", SDL_GetError());
        return -1;
    }
    SDL_Texture *texture;

    int sockd;
    connect_server(argv[1], &sockd);

    char sockbuff[4096];
    char ping[] = "PING :tmi.twitch.tv";
    char pong[] = "PONG :tmi.twitch.tv";
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) { quit = 1; }
        }

        memset(&sockbuff[0], '\0', sizeof(sockbuff));
        recv(sockd, &sockbuff[0], sizeof(sockbuff)/sizeof(sockbuff[0]), 0);

        char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
        // @TODO: Dont hardcode this
        sscanf(sockbuff, ":%31[^!]%s%s%s%c%c%256[^\n]",
               n, x, y, z, q, w, m);

        printf("%s: ", n);
        printf("%s\n", m);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }
    SDL_Quit();
    return 0;
}
