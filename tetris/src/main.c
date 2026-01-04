#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include <stdbool.h>    
#include "../include/mechs.h"
#include "../include/settings.h"
#include "../include/audio.h"
#include "../include/highscore.h"

int main(int argc, char* argv[]) {

    SDL_SetHint(SDL_HINT_SHUTDOWN_DBUS_ON_QUIT, "1"); //fake leaks fix
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    initAudio();

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

    TTF_Font* font = TTF_OpenFont("assets/font/Jersey.ttf", 24);
    if (!font) {
        printf("Chyba fontu: %s\n", TTF_GetError());
    }
    
    TTF_Font* largeFont = TTF_OpenFont("assets/font/Jersey.ttf", 48);
    if (!largeFont) {
        printf("Chyba fontu: %s\n", TTF_GetError());
    }

    TTF_Font* massiveFont = TTF_OpenFont("assets/font/Jersey.ttf", 96);
    if (!massiveFont) {
        printf("Chyba fontu: %s\n", TTF_GetError());
    }

    Settings settings;
    HighScores scores;
    loadSettings(&settings, "assets/txt/settings.txt");
    loadHighScores(&scores);

    //colors
    SDL_Color text;
    SDL_Color board;
    SDL_Color bg;

    //score string
    char scoreText[32];

    //sdl objects for score
    SDL_Surface* scoreSurface;
    SDL_Texture* scoreTexture;
    SDL_Rect scoreRect = {405, 50, 0, 0};
    
    //menu btns & state
    MenuButton playBtn = {{200,440,200,60},{0,160,0,255},"PLAY"};
    MenuButton settingsBtn = {{200,520,200,60},{0,0,160,255},"SETTINGS"};
    MenuButton quitBtn = {{200,600,200,60},{160,0,0,255},"QUIT"};
    MenuButton backBtn = {{490,760,100,30},{120,120,120,255},"BACK"};
    MenuButton playAgainBtn = {{200,440,200,60},{0,160,0,255},"PLAY AGAIN"};
    MenuButton menuBtn = {{200,520,200,60},{0,0,160,255},"MENU"};

    //settings btns & state
    MenuButton inputBtn = {{200,440,200,60},{160,160,0,255}, ""};
    MenuButton themeBtn = {{200,520,200,60},{160,0,160,255}, ""};
    MenuButton soundBtn = {{200,600,200,60},{160,160,160,255}, ""};

    strcpy(inputBtn.text, settings.input == ARROWS ? "ARROWS" : "WASD");
    strcpy(themeBtn.text, settings.theme == DARK ? "DARK" : "LIGHT");
    strcpy(soundBtn.text, settings.sound == SOUND_ON ? "SOUND ON" : "SOUND OFF");

    State state = MENU;

    SDL_Event event;
    bool quit = false;
    srand(SDL_GetTicks());
    initCells();
    spawnBlock();

    while (quit == false)
    {
        while (SDL_PollEvent(&event))
        {
            //quit cez okno
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            //menu btn states
            if (state == MENU) {
                //play btn
                if (buttonClicked(&playBtn, &event)) {
                    state = GAME;
                    initCells();
                    spawnBlock();
                    if(settings.sound == SOUND_ON) playTheme();
                    //bugfix
                    if (!canMove(&current, current.x, current.y)) {
                        compareHighScore(score, &scores);
                        saveHighScores(&scores);
                        state = GAMEOVER;
                    } else state = GAME;
                }
                if (buttonClicked(&settingsBtn, &event)) state = SETTINGS; //setting btn
                if (buttonClicked(&quitBtn, &event)) quit = true; //quit btn
            }

            //settings btn states
            if (state == SETTINGS) {
                if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) state = MENU;
                if (buttonClicked(&inputBtn, &event)) {
                    //toggle input setting
                    if (settings.input == ARROWS) {
                        settings.input = WASD;
                    } else {
                        settings.input = ARROWS;
                    }
                    strcpy(inputBtn.text, settings.input == ARROWS ? "ARROWS" : "WASD");
                    saveSettings(&settings, "assets/txt/settings.txt");
                }
                if (buttonClicked(&themeBtn, &event)) {
                    //toggle theme setting
                    if (settings.theme == DARK) {
                        settings.theme = LIGHT;
                    } else {
                        settings.theme = DARK;
                    }
                    strcpy(themeBtn.text, settings.theme == DARK ? "DARK" : "LIGHT");
                    saveSettings(&settings, "assets/txt/settings.txt");
                }

                if (buttonClicked(&soundBtn, &event)) {
                    //toggle sound setting
                    if (settings.sound == SOUND_ON) {
                        settings.sound = SOUND_OFF;
                    } else {
                        settings.sound = SOUND_ON;
                    }
                    strcpy(soundBtn.text, settings.sound == SOUND_ON ? "SOUND ON" : "SOUND OFF");
                    saveSettings(&settings, "assets/txt/settings.txt");
                }

                if (buttonClicked(&backBtn, &event)) state = MENU;
            }

            //game btn states
            if (state == GAME && event.type == SDL_KEYDOWN) {
                if( settings.input == ARROWS)
                {
                    switch (event.key.keysym.sym) {
                        //arrows
                        case SDLK_LEFT:  moveBlock(-1,0); break;
                        case SDLK_RIGHT: moveBlock(1,0); break;
                        case SDLK_DOWN:  moveBlock(0,1); break;
                        case SDLK_UP:    rotateBlock(); break;
                    }
                }

                else {
                    switch (event.key.keysym.sym) {
                        //wasd
                        case SDLK_a: moveBlock(-1,0); break;
                        case SDLK_d: moveBlock(1,0); break;
                        case SDLK_s: moveBlock(0,1); break;
                        case SDLK_w: rotateBlock(); break;
                    }
                }
                switch (event.key.keysym.sym)
                {
                    //misc
                    case SDLK_SPACE: dropBlock(&current); break;
                    case SDLK_ESCAPE: 
                        state = MENU; 
                        stopTheme();
                        break;
                }
            }

            //gameover btn states
            if( state == GAMEOVER) {
                //play again btn 
                if (buttonClicked(&playAgainBtn, &event)) {
                    score = 0;
                    initCells();
                    spawnBlock();
                    state = GAME;
                }
                if (buttonClicked(&menuBtn, &event)) state = MENU; //menu btn
                if (buttonClicked(&quitBtn, &event)) quit = true; //quit btn
            }
        }

        if(settings.theme == DARK) {
            board = (SDL_Color){24, 24, 24, 255};
            bg = (SDL_Color){0, 0, 0, 255};
            text = (SDL_Color){255, 255, 255, 255};
        } else {
            board = (SDL_Color){220, 220, 220, 255};
            bg = (SDL_Color){255, 255, 255, 255};
            text = (SDL_Color){0, 0, 0, 255};
        }

        //render window
        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, 255);
        SDL_RenderClear(renderer);


        //menu state mimo event loop
        if (state == MENU) {
            renderText(renderer, massiveFont, "TETRES", text, 160, 100);
            renderButton(renderer, font, &playBtn);
            renderButton(renderer, font, &settingsBtn);
            renderButton(renderer, font, &quitBtn);
        }

        //setting state mimo event loop
        if (state == SETTINGS) {
            renderText(renderer, massiveFont, "SETTINGS", text, 120, 100);
            renderButton(renderer, font, &inputBtn);
            renderButton(renderer, font, &themeBtn);
            renderButton(renderer, font, &soundBtn);
            renderButton(renderer, font, &backBtn);
        }

        //gameover state mimo event loop
        if (state == GAMEOVER) {
            if(settings.sound == SOUND_ON) playGameOverSound();
            renderText(renderer, largeFont, "GAME OVER", text, 195, 100);
            renderText(renderer, font, "High Scores:", text, 200, 200);
            char hsText[64];
            sprintf(hsText, "1. %d", scores.t1);
            renderText(renderer, font, hsText, text, 200, 250);
            sprintf(hsText, "2. %d", scores.t2);
            renderText(renderer, font, hsText, text, 200, 300);
            sprintf(hsText, "3. %d", scores.t3);
            renderText(renderer, font, hsText, text, 200, 350);
            renderButton(renderer, font, &playAgainBtn);
            renderButton(renderer, font, &menuBtn);
            renderButton(renderer, font, &quitBtn);
        }

        //game state mimo event loop
        if (state == GAME) {
            updateFall();
            checkLines(settings);

            if (!canMove(&current, current.x, current.y)) {
                compareHighScore(score, &scores);
                saveHighScores(&scores);
                state = GAMEOVER;
            }

            //board render + lines
            SDL_SetRenderDrawColor(renderer, board.r, board.g, board.b, 255);
            SDL_Rect rect = {0,0,400,WINDOW_HEIGHT};
            SDL_RenderFillRect(renderer, &rect);

            SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, 255);
            for(int i=0;i<=BOARD_WIDTH;i+=CELL_SIZE)
                SDL_RenderDrawLine(renderer,i,0,i,WINDOW_HEIGHT);
            for(int j=0;j<=WINDOW_HEIGHT;j+=CELL_SIZE)
                SDL_RenderDrawLine(renderer,0,j,BOARD_WIDTH,j);

            //next block text
            SDL_Surface* nextSurface = TTF_RenderUTF8_Blended(font, "Next:", text);
            SDL_Texture* nextTexture = SDL_CreateTextureFromSurface(renderer, nextSurface);
            SDL_Rect nextRect = {405, 95, 0, 0};
            SDL_QueryTexture(nextTexture, NULL, NULL, &nextRect.w, &nextRect.h);
            SDL_FreeSurface(nextSurface);

            //update renders
            renderBoard(renderer);
            renderCurrent(renderer);
            showNextBlock(renderer,420,130);
            SDL_RenderCopy(renderer,nextTexture,NULL,&nextRect);

            sprintf(scoreText,"Score: %d",score);
            scoreSurface = TTF_RenderUTF8_Blended(font,scoreText,text);
            scoreTexture = SDL_CreateTextureFromSurface(renderer,scoreSurface);
            SDL_QueryTexture(scoreTexture,NULL,NULL,&scoreRect.w,&scoreRect.h);
            SDL_FreeSurface(scoreSurface);
            SDL_RenderCopy(renderer,scoreTexture,NULL,&scoreRect);
        }

        //update window
        SDL_RenderPresent(renderer);
    }

    //destroy sdl objects
    TTF_CloseFont(font);
    TTF_CloseFont(largeFont);
    TTF_CloseFont(massiveFont);
    TTF_Quit();

    cleanUpAudio();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}