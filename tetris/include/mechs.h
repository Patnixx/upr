#ifndef MECHS_H
#define MECHS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "settings.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800
#define CELL_SIZE 40
#define CELLS_X (WINDOW_WIDTH - 200) / CELL_SIZE
#define CELLS_Y WINDOW_HEIGHT / CELL_SIZE
#define BOARD_WIDTH 400

typedef struct {
    bool filled;
    SDL_Color color;
} Cell;

typedef struct {
    int shape[4][4];
    SDL_Color color;
    int x;
    int y;
} Block;
typedef enum {
    MENU,
    GAME,
    SETTINGS,
    GAMEOVER,
    QUIT
} State;

typedef struct {
    SDL_Rect rect;
    SDL_Color color;
    char text[32];
} MenuButton;

extern Cell board[CELLS_Y][CELLS_X];
extern Block current;
extern Block next;
extern int score;
extern MenuButton playBtn;
extern MenuButton settingsBtn;
extern MenuButton quitBtn;
extern MenuButton backBtn;

//game mechs
void initCells(void);
void spawnBlock(void);
bool canMove(Block* t, int newX, int newY);
void moveBlock(int dx, int dy);
void dropBlock(Block *b);
void rotateBlock(void);
void lockBlock(void);
void updateFall(void);
void drawCell(SDL_Renderer* renderer, int x, int y, SDL_Color color);
void renderBoard(SDL_Renderer* renderer);
void renderCurrent(SDL_Renderer* renderer);
void showNextBlock(SDL_Renderer* renderer, int startX, int startY);
void checkLines(Settings settings);

//menu mechs
void renderButton(SDL_Renderer* r, TTF_Font* font, MenuButton* b);
bool buttonClicked(MenuButton* b, SDL_Event* e);
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y);

void drawHeart(SDL_Renderer* renderer, int x, int y);

#endif
