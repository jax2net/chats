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

    if (TTF_Init() == -1) {
        printf("Failed to initialize TTF: %s", SDL_GetError());
    }

    TTF_Font *font = TTF_OpenFont("ComicNeue-Regular.ttf", 45);
    if (!font) {
        printf("Failed to open font: %s\n", TTF_GetError());
    }
    SDL_Color text_color = {0, 0, 0};
    SDL_Color background_color = {255, 255, 255};

    SDL_Rect dstrect = {50, 300, 600, 70};

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
        int msg_len = recv(sockd, &sockbuff[0], sizeof(sockbuff)/sizeof(sockbuff[0]), 0);

        SDL_Texture *font_texture;
        if (msg_len > 0) {
            char n[32], z[32], x[32], y[32], m[256], q[1], w[1];
            // @TODO: Dont hardcode this
            sscanf(sockbuff, ":%31[^!]%s%s%s%c%c%256[^\n]",
                   n, x, y, z, q, w, m);
            strcat(n, ": ");
            printf("%s: ", n);
            strcat(m, "\n");
            printf("%s", m);

            char msg[500];
            strcat(msg, n);
            strcat(msg, m);

            SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, msg, text_color, 700);
            font_texture = SDL_CreateTextureFromSurface(renderer, surface);
        }
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1); // background
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, font_texture, NULL, &dstrect);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(font_texture);
    }
    TTF_Quit();
    SDL_Quit();
    return 0;
}
