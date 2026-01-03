#include "include/mechs.h"
#include <string.h>
#include <stdlib.h>

Cell board[CELLS_Y][CELLS_X];
Block current;
Block next;

int score;
Uint32 lastFall = 0;

const int SHAPES[7][4][4] = {
    {
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }, // O
    {
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }, // I
    {
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }, // T
    {
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0}
    }, // S
    {
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }, // Z
    {
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }, // L
    {
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0}
    }  // J
};

const SDL_Color COLORS[7] = {
    {255,255,0,255}, //zlta
    {0,255,255,255}, //tyrkysova
    {160,0,240,255}, //fialova
    {0,255,0,255}, //zelena
    {255,0,0,255}, //cervena
    {255,165,0,255}, //oranzova
    {0,0,255,255} //modra
};

const SDL_Color THEMES[2] = {
    {30,30,30,255}, //dark
    {220,220,220,255} //light
};

//game section
void initCells(void) {
    for (int y = 0; y < CELLS_Y; y++)
        for (int x = 0; x < CELLS_X; x++)
            board[y][x].filled = false;
}

void spawnBlock(void) {
    if(!next.shape[1][1]) {
        int id = rand() % 7;
        memcpy(current.shape, SHAPES[id], sizeof(current.shape));
        current.color = COLORS[id];
        current.x = 5;
        current.y = 0;
    }
    else {
        memcpy(current.shape, next.shape, sizeof(next.shape));
        current.color = next.color;
        current.x = next.x;
        current.y = 0;
    }

    int next_id = rand() % 7;
    memcpy(next.shape, SHAPES[next_id], sizeof(next.shape));
    next.color = COLORS[next_id];
    next.x = 5;
    next.y = 0;
}

bool canMove(Block* b, int newX, int newY) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (b->shape[y][x]) {
                int bx = newX + x;
                int by = newY + y;

                if (bx < 0 || bx >= CELLS_X || by >= CELLS_Y) //kolizia so stenou
                    return false;

                if (by >= 0 && board[by][bx].filled) //kolizia s inym blokom
                    return false;
            }
        }
    }
    return true;
}

void moveBlock(int new_x, int new_y) {
    if (canMove(&current, current.x + new_x, current.y + new_y)) {
        current.x += new_x;
        current.y += new_y;
    } else if (new_y == 1) {
        lockBlock();
        spawnBlock();
    }
}

void dropBlock(Block *b) {
    while (canMove(b, b->x, b->y + 1)) {
        b->y += 1;
    }
    lockBlock();
    spawnBlock();
}

void rotateBlock(void) {
    int tmp[4][4];

    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            tmp[x][3 - y] = current.shape[y][x];

    Block test = current;
    memcpy(test.shape, tmp, sizeof(tmp));

    if (canMove(&test, test.x, test.y))
        memcpy(current.shape, tmp, sizeof(tmp));
}

void lockBlock(void) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (current.shape[y][x]) {
                int bx = current.x + x;
                int by = current.y + y;
                board[by][bx].filled = true;
                board[by][bx].color = current.color;
            }
}

void updateFall(void) {
    Uint32 now = SDL_GetTicks();
    if (now - lastFall > 500) {
        moveBlock(0, 1);
        lastFall = now;
    }
}

void drawCell(SDL_Renderer* r, int x, int y, SDL_Color c) {
    SDL_Rect rect = {
        x * CELL_SIZE,
        y * CELL_SIZE,
        CELL_SIZE,
        CELL_SIZE
    };

    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, 255);
    SDL_RenderFillRect(r, &rect);
}

void renderBoard(SDL_Renderer* renderer) {
    for (int y = 0; y < CELLS_Y; y++)
        for (int x = 0; x < CELLS_X; x++)
            if (board[y][x].filled)
                drawCell(renderer, x, y, board[y][x].color);
}

void renderCurrent(SDL_Renderer* renderer) {
    for (int y = 0; y < 4; y++)
        for (int x = 0; x < 4; x++)
            if (current.shape[y][x])
                drawCell(renderer, current.x + x, current.y + y, current.color);
}

void showNextBlock(SDL_Renderer* renderer, int startX, int startY) {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (next.shape[y][x]) {
                SDL_Rect rect = {
                    startX + x * CELL_SIZE,
                    startY + y * CELL_SIZE,
                    CELL_SIZE,
                    CELL_SIZE
                };

                SDL_SetRenderDrawColor(renderer, next.color.r, next.color.g, next.color.b, 255);
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

void checkLines(void) {
    for (int y = CELLS_Y - 1; y > 0; y--) {
        bool lineFull = true;
        for (int x = 0; x < CELLS_X; x++) {
            if (!board[y][x].filled) {
                lineFull = false;
                break;
            }
        }

        if (lineFull) {
            for (int ty = y; ty > 0; ty--) {
                for (int tx = 0; tx < CELLS_X; tx++) {
                    board[ty][tx] = board[ty-1][tx];
                }
            }
            for (int tx = 0; tx < CELLS_X; tx++) {
                board[0][tx].filled = false;
            }
            score += 100;
            y++;
        }
    }
}

//menu section
void renderButton(SDL_Renderer* r, TTF_Font* font, MenuButton* b) {
    SDL_SetRenderDrawColor(r, b->color.r, b->color.g, b->color.b, 255);
    SDL_RenderFillRect(r, &b->rect);

    SDL_Color white = {255,255,255,255};
    SDL_Surface* surf = TTF_RenderText_Blended(font, b->text, white);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(r, surf);

    SDL_Rect textRect = {
        b->rect.x + (b->rect.w - surf->w) / 2,
        b->rect.y + (b->rect.h - surf->h) / 2,
        surf->w,
        surf->h
    };

    SDL_RenderCopy(r, texture, NULL, &textRect);
    SDL_FreeSurface(surf);
    SDL_DestroyTexture(texture);
}

bool buttonClicked(MenuButton* b, SDL_Event* e) {
    if (e->type == SDL_MOUSEBUTTONDOWN) {
        int mx = e->button.x;
        int my = e->button.y;
        return mx >= b->rect.x && mx <= b->rect.x + b->rect.w && my >= b->rect.y && my <= b->rect.y + b->rect.h;
    }
    return false;
}

void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, SDL_Color color, int x, int y)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, text, color);
    if (!surface) {
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Always clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
//settings section

//others