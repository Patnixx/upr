#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
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

    TTF_Font* largeFont = TTF_OpenFont("Jersey.ttf", 48);
    if (!largeFont) {
        printf("Chyba fontu: %s\n", TTF_GetError());
    }

    /*FILE *f_read = fopen("highscore.txt", "r");
    if (f_read) {
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), f_read)) {
            printf("Highscore: %s", buffer);
        }
        fclose(f_read);
    }*/

    // vars/objects
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    SDL_Color board = {24, 24, 24, 255};

    char scoreText[32];

    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect = {405, 50, 0, 0};
    
    MenuButton playBtn = {{200,440,200,60},{0,160,0,255},"PLAY"};
    MenuButton settingsBtn = {{200,520,200,60},{0,0,160,255},"SETTINGS"};
    MenuButton quitBtn = {{200,600,200,60},{160,0,0,255},"QUIT"};
    MenuButton backBtn = {{490,760,100,30},{120,120,120,255},"BACK"};
    MenuButton playAgainBtn = {{200,440,200,60},{0,160,0,255},"PLAY AGAIN"};
    MenuButton menuBtn = {{200,520,200,60},{0,0,160,255},"MENU"};
    State state = MENU;


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


    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (state == MENU) {
                if (buttonClicked(&playBtn, &event)) {
                    state = GAME;
                    initCells();
                    spawnBlock();
                    if (!canMove(&current, current.x, current.y)) {
                        FILE *f = fopen("highscore.txt", "w");
                        if (f) {
                            fprintf(f, "Score: %d\n", score);
                            fclose(f);
                        }
                        state = GAMEOVER;
                    } else {
                        state = GAME;
                    }
                }
                if (buttonClicked(&settingsBtn, &event))
                    state = SETTINGS;
                if (buttonClicked(&quitBtn, &event))
                    quit = true;
            }

            if (state == SETTINGS) {
                if (buttonClicked(&backBtn, &event))
                    state = MENU;
            }

            if (state == GAME && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  moveBlock(-1,0); break;
                    case SDLK_RIGHT: moveBlock(1,0); break;
                    case SDLK_DOWN:  moveBlock(0,1); break;
                    case SDLK_UP:    rotateBlock(); break;
                    case SDLK_SPACE: dropBlock(&current); break;
                    case SDLK_ESCAPE: state = MENU; break;
                }
            }

            if( state == GAMEOVER) { 
                if (buttonClicked(&playAgainBtn, &event)) {
                    score = 0;
                    initCells();
                    spawnBlock();
                    state = GAME;
                }
                if (buttonClicked(&menuBtn, &event)) {
                    state = MENU;
                }
            }
        }

        if (state == GAME) {
            updateFall();
            checkLines();

            if (!canMove(&current, current.x, current.y)) {
                FILE *f = fopen("highscore.txt", "w");
                if (f) {
                    fprintf(f, "Score: %d\n", score);
                    fclose(f);
                }
                state = GAMEOVER;
            }
        }

        SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, 255);
        SDL_RenderClear(renderer);

        if (state == MENU) {
            renderButton(renderer, font, &playBtn);
            renderButton(renderer, font, &settingsBtn);
            renderButton(renderer, font, &quitBtn);
        }

        if (state == SETTINGS) {
            renderButton(renderer, font, &backBtn);
        }

        if (state == GAMEOVER) {
            renderText(renderer, largeFont, "GAME OVER", white, 195, 200);
            renderButton(renderer, font, &playAgainBtn);
            renderButton(renderer, font, &menuBtn);
            renderButton(renderer, font, &quitBtn);
            /*SDL_Surface* s = IMG_Load("heart.png");
            SDL_Texture* heart = SDL_CreateTextureFromSurface(renderer, s);
            SDL_FreeSurface(s);

            SDL_Rect dst = {275,300, 64, 64 };
            SDL_RenderCopy(renderer, heart, NULL, &dst);*/
        }

        if (state == GAME) {

            SDL_SetRenderDrawColor(renderer, board.r, board.g, board.b, 255);
            SDL_Rect rect = {0,0,400,WINDOW_HEIGHT};
            SDL_RenderFillRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, 255);
            for(int i=0;i<=BOARD_WIDTH;i+=CELL_SIZE)
                SDL_RenderDrawLine(renderer,i,0,i,WINDOW_HEIGHT);
            for(int j=0;j<=WINDOW_HEIGHT;j+=CELL_SIZE)
                SDL_RenderDrawLine(renderer,0,j,BOARD_WIDTH,j);

            renderBoard(renderer);
            renderCurrent(renderer);
            showNextBlock(renderer,420,130);
            SDL_RenderCopy(renderer,nextTexture,NULL,&nextRect);

            sprintf(scoreText,"Score: %d",score);
            //if(scoreTexture) SDL_DestroyTexture(scoreTexture);
            scoreSurface = TTF_RenderUTF8_Blended(font,scoreText,white);
            scoreTexture = SDL_CreateTextureFromSurface(renderer,scoreSurface);
            SDL_QueryTexture(scoreTexture,NULL,NULL,&scoreRect.w,&scoreRect.h);
            SDL_FreeSurface(scoreSurface);
            SDL_RenderCopy(renderer,scoreTexture,NULL,&scoreRect);
        }

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