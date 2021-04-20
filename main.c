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
        printf("Failed to make window and renderer: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Texture *texture;

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s", SDL_GetError());
    }

    TTF_Font *font = TTF_OpenFont("ComicNeue-Regular.ttf", 23);
    if (!font) {
        printf("Failed to open font: %s\n", TTF_GetError());
    }
    SDL_Color color;
    color.r = 0;
    color.g = 0;
    color.b = 0;

    SDL_Rect srcrect;
    SDL_Rect dstrect;

    srcrect.x = 0;
    srcrect.y = 0;
    srcrect.w = 300;
    srcrect.h = 300;

    dstrect.x = 50;
    dstrect.y = 300;
    dstrect.w = 600;
    dstrect.h = 60;

    int sockd;
    connect_server(argv[1], &sockd);

    char sockbuff[4096];
    /* char ping[] = "PING :tmi.twitch.tv"; */
    /* char pong[] = "PONG :tmi.twitch.tv"; */
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

        char msg[500];
        strcat(msg, n);
        strcat(msg, m);

        SDL_Surface *surface = TTF_RenderText_Blended(font, msg, color);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
    }
    TTF_Quit();
    SDL_Quit();
    return 0;
}
