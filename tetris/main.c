#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include <stdbool.h>    
#include "mechs.h"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

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

    TTF_Font* font = TTF_OpenFont("Jersey.ttf", 24);
    if (!font) {
        printf("Chyba fontu: %s\n", TTF_GetError());
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color board = {24, 24, 24, 255};

    //next
    SDL_Surface* nextSurface = TTF_RenderUTF8_Blended(font, "Next:", white);
    SDL_Texture* nextTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
    SDL_Rect nextRect = {405, 95, 0, 0};
    SDL_QueryTexture(nextTexture, NULL, NULL, &nextRect.w, &nextRect.h);
    SDL_FreeSurface(nextSurface);

    SDL_Event event;

    bool quit = false;
    srand(SDL_GetTicks());
    initCells();
    spawnBlock();

    char scoreText[32];
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect = {405, 50, 0, 0};


    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        moveBlock(-1, 0);
                        break;
                    case SDLK_RIGHT:
                        moveBlock(1, 0);
                        break;
                    case SDLK_DOWN:
                        moveBlock(0, 1);
                        break;
                    case SDLK_UP:
                        rotateBlock();
                        break;
                    case SDLK_SPACE:
                        dropBlock(&current);
                        break;
                }
            }
        }

        updateFall();
        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a); //bg
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, board.r, board.g, board.b, board.a); //hracia plocha
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 400;
        rect.h = WINDOW_HEIGHT;
        SDL_RenderFillRect(renderer, &rect); 

        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
        for(int i = 0; i <= BOARD_WIDTH; i += CELL_SIZE) // Čiary medzi kockami
        {
            SDL_RenderDrawLine(renderer, i, 0, i, WINDOW_HEIGHT);
        }

        for(int j = 0; j <= WINDOW_HEIGHT; j += CELL_SIZE) // Čiary medzi kockami
        {
            SDL_RenderDrawLine(renderer, 0, j, BOARD_WIDTH, j);
        }

        renderBoard(renderer);
        renderCurrent(renderer);
        showNextBlock(renderer, 420, 130);
        checkLines();
        SDL_RenderCopy(renderer, nextTexture, NULL, &nextRect);

        sprintf(scoreText, "Score: %d", score);
        if (scoreTexture) SDL_DestroyTexture(scoreTexture);

        scoreSurface = TTF_RenderUTF8_Blended(font, scoreText, white);
        scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreRect.w, &scoreRect.h);
        SDL_FreeSurface(scoreSurface);

        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);


        SDL_RenderPresent(renderer);
    }

    if (scoreTexture) SDL_DestroyTexture(scoreTexture);
    SDL_DestroyTexture(nextTexture);
    TTF_CloseFont(font);
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();

    return 0;
}