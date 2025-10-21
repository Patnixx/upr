#include <stdio.h>
#include <stdlib.h>


struct Turtle{
    int direction;
    int pos_x;
    int pos_y;
};

char* grid_init(int rows, int cols){
    int total_size = rows * cols;
    char* grid = malloc(total_size * sizeof(char));

    for(int i = 0; i < total_size; i++){
        grid[i] = '.';
    }

    return grid;
}

void grid_print(char* grid, int rows, int cols){
    for(int i = 0; i < rows * cols; i++){
        printf("%c", grid[i]);
        if((i + 1) % cols == 0){
            printf("\n");
        }
    }
}

struct Turtle* turtles_init(){
    struct Turtle* turtles = malloc(sizeof(struct Turtle));
    turtles[0].direction = 1;
    turtles[0].pos_x = 0;
    turtles[0].pos_y = 0;

    return turtles;
}

struct Turtle* turtles_add(struct Turtle* current, int* num){
    (*num)++;
    struct Turtle* turtles = realloc(current, *num * sizeof(struct Turtle));

    turtles[(*num) - 1].direction = 1;
    turtles[(*num) - 1].pos_x = 0;
    turtles[(*num) - 1].pos_y = 0;

    return turtles;
}

void turtles_move(struct Turtle* turtles, int turtles_num, int rows, int cols) {
    for(int i = 0; i < turtles_num; i++){
        struct Turtle* turtle = &turtles[i];

        if(turtle->direction == 0) turtle->pos_y = (turtle->pos_y - 1 + rows) % rows;
        else if(turtle->direction == 1) turtle->pos_x = (turtle->pos_x + 1) % cols;
        else if(turtle->direction == 2) turtle->pos_y = (turtle->pos_y + 1) % rows;
        else if(turtle->direction == 3) turtle->pos_x = (turtle->pos_x - 1 + cols) % cols;
    }
}

void turtles_turn(struct Turtle* turtles, char direction, int num){
    for(int i = 0; i < num; i++){
        struct Turtle* turtle = &turtles[i];

        if(direction == 'r') turtle->direction = (turtle->direction + 1) % 4;
        if(direction == 'l') turtle->direction = (turtle->direction - 1 + 4) % 4;
    }
}

void turtles_write(struct Turtle* turtles, char* grid, int num, int cols){
    for(int i = 0; i < num; i++){
        struct Turtle* turtle = &turtles[i];

        int index = (turtle->pos_y * cols) + turtle->pos_x;

        if(grid[index] != 'o') grid[index] = 'o';
        else grid[index] = '.';
    }
}


int main(){

    int rows, cols;
    int num = 1;
    scanf("%d %d", &rows, &cols);

    char* grid = grid_init(rows, cols);
    struct Turtle* turtles = turtles_init();

    char c;
    while(1){
        scanf(" %c", &c);

        if(c == 'm') turtles_move(turtles, num, rows, cols);
        else if(c == 'r') turtles_turn(turtles, 'r', num);
        else if(c == 'l') turtles_turn(turtles, 'l', num);
        else if(c == 'o') turtles_write(turtles, grid, num, cols);
        else if(c == 'f' && num < 3) turtles = turtles_add(turtles, &num);
        else if(c == 'x') break;
    }

    grid_print(grid, rows, cols);
    /* printf("%d %d %d\n", turtles[0].direction, turtles[0].pos_x, turtles[0].pos_y);
    printf("%d %d %d\n", turtles[1].direction, turtles[1].pos_x, turtles[1].pos_y);
    printf("%d %d %d\n", turtles[2].direction, turtles[2].pos_x, turtles[2].pos_y); */

    free(grid);
    free(turtles);

    return 0;
}