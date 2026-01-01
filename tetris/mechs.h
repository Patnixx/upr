#ifndef MECHS_H
#define MECHS_H

#include <SDL2/SDL.h>
#include <stdbool.h>

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

extern Cell board[CELLS_Y][CELLS_X];
extern Block current;
extern Block next;
extern int linesCleared;
extern int score;


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
void checkLines(void);

#endif
