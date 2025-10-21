#include <stdio.h>
#include <stdlib.h>

char* initGrid(int *rows, int *cols)
{
    char *grid = (char *) malloc((*rows) * (*cols) * sizeof(char));
    for (int i = 0; i < ((*rows) * (*cols)); i++)
    {
        grid[i] = '.';
    }

    return grid;
}

char* initTurtles(int *turtles)
{
    char *turtle = (char *) malloc((*turtles) * 3 * sizeof(char));
    for(int i = 0; i < 3; i++)
    {
        turtle[i] = 0;
        if(i == 2)
        {
            turtle[i] = 'r';
        }
    }

    return turtle;
}

char* addTurtles(int *turtles, char *turtle)
{
    (*turtles)++;
    turtle = (char *) realloc(turtle, (*turtles) * 3 * sizeof(char));
    for(int i = ((*turtles) - 1) * 3; i < (*turtles) * 3; i++)
    {
        turtle[i] = 0; 
        if(i % 3 == 2)
        {
            turtle[i] = 'r';
        }
    }

    return turtle;
}

void printGrid(char *grid, int rows, int cols)
{
    for (int i = 0; i < (rows * cols); i++)
    {
        printf("%c", grid[i]);
        if((i +1) % cols == 0)
        {
            printf("\n");
        }
    }
}

void printTurtles(char *turtle, int turtles)
{
    for(int i = 0; i < turtles; i++)
    {
        printf("Turtle %d: row=%d, col=%d, dir=%c\n", i + 1, turtle[i * 3], turtle[i * 3 + 1], turtle[i * 3 + 2]);
    }
}

void turtleMove(char *turtle, int *turtles, int cols, int rows)
{
    for(int i = 0; i < *turtles; i++)
    {
        switch (turtle[i * 3 + 2])
        {
            case 'r':
                if(turtle[i * 3 + 1] == cols-1)
                    turtle[i * 3 + 1] = 0;
                else
                    turtle[i * 3 + 1]++;
                break;
            case 'l':
                if(turtle[i * 3 + 1] == 0)
                    turtle[i * 3 + 1] = cols-1;
                else
                    turtle[i * 3 + 1]--;
                break;
            case 'd':
                if(turtle[i * 3] == rows-1)
                    turtle[i * 3] = 0;
                else
                    turtle[i * 3]++;
                break;
            case 'u':
                if(turtle[i * 3] == 0)
                    turtle[i * 3] = rows-1;
                else
                    turtle[i * 3]--;
                break;
        }
    }
}

void turtleRotate(char *turtle, int *turtles, char command)
{
    char turns[] = {'r', 'd', 'l', 'u'};
    int nTurns = 4;

    for (int i = 0; i < *turtles; i++)
    {
        // nájdeme index aktuálneho smeru
        char current = turtle[i * 3 + 2];
        int index = 0;
        while (index < nTurns && turns[index] != current) index++;

        if (index < nTurns)
        {
            if (command == 'r')
                turtle[i * 3 + 2] = turns[(index + 1) % nTurns];  // posun doprava
            else if (command == 'l')
                turtle[i * 3 + 2] = turns[(index + nTurns - 1) % nTurns];  // posun doľava
        }
    }
}

void turtleDraw(char *grid, char *turtle, int *turtles, int cols)
{
    for(int i = 0; i < *turtles; i++)
    {
        int row = turtle[i * 3];
        int col = turtle[i * 3 + 1];
        char current = grid[row * cols + col];
        if(current == '.')
        {
            grid[row * cols + col] = 'o';
        }
        else if(current == 'o')
        {
            grid[row * cols + col] = '.';
        }
    }
}

int main() {
    int rows, cols = 0;
    int turtles = 1;
    scanf("%d%d", &rows, &cols);
    //printf("\n");

    char *grid = initGrid(&rows, &cols);
    //printGrid(grid, rows, cols);
    char *turtle = initTurtles(&turtles);
    //turtle = addTurtles(&turtles); 
    
    while(1)
    {
        char command;
        scanf(" %c", &command);
        if(command == 'r' || command == 'l')
        {
            turtleRotate(turtle, &turtles, command);
            printGrid(grid, rows, cols);
            printTurtles(turtle, turtles);
            printf("\n");
        }
        else if(command == 'o')
        {
            turtleDraw(grid, turtle, &turtles, cols);
            printGrid(grid, rows, cols);
            printTurtles(turtle, turtles);
            printf("\n");
        }
        else if(command == 'm')
        {
            turtleMove(turtle, &turtles, cols, rows);
            printGrid(grid, rows, cols);
            printTurtles(turtle, turtles);
            printf("\n");
        }
        else if(command == 'f' && turtles < 3)
        {
            turtle = addTurtles(&turtles, turtle);
            printGrid(grid, rows, cols);
            printTurtles(turtle, turtles);
            printf("\n");
        }
        else if(command == 'x')
        {
            printGrid(grid, rows, cols);
            printTurtles(turtle, turtles);
            printf("\n");
            break;
        }
    }

    free(grid);
    free(turtle);
}