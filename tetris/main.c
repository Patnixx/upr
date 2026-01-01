#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define BLOCK_SIZE 40
#define BOARD_WIDTH 400

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    // Vytvoření okna
    SDL_Window* window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_Event event;
    bool quit = false;

    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //bg
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255); //hracia plocha
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 400;
        rect.h = WINDOW_HEIGHT;
        SDL_RenderFillRect(renderer, &rect); 

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //čierna farba
        for(int i = 0; i <= BOARD_WIDTH; i += BLOCK_SIZE) // Čiary medzi kockami
        {
            SDL_RenderDrawLine(renderer, i, 0, i, WINDOW_HEIGHT);
        }

        for(int j = 0; j <= WINDOW_HEIGHT; j += BLOCK_SIZE) // Čiary medzi kockami
        {
            SDL_RenderDrawLine(renderer, 0, j, BOARD_WIDTH, j);
        }

        SDL_RenderPresent(renderer);
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}