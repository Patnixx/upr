#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* 
- pre bonus treba odkomentovat riadky: 17, 136, 143, 182, 183, 193, 198, treba potom zakomentovat pri znakoch tie pod nimi;
- je to bud zmena znaku v gride z '.' na ' ' alebo uz samotna funkcia a sleep
- pri animacii to zobrazi aj Z aj O ked pipinka kresli ale ako hovori kodex: ked to funguje, nema sa toho nikto chytat
- enjoy :)
*/

char* initGrid(int *rows, int *cols)
{
    char *grid = (char *) malloc((*rows) * (*cols) * sizeof(char));
    for (int i = 0; i < ((*rows) * (*cols)); i++)
    {
        //grid[i] = ' ';
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
    int num_of_turns = 4;

    for (int i = 0; i < *turtles; i++)
    {
        char current = turtle[i * 3 + 2];
        int index = 0;
        while (index < num_of_turns && turns[index] != current) //prechadza to pipinky kým nenajde jej smer
        {
            index++;
        }
        if (command == 'r')
            turtle[i * 3 + 2] = turns[(index + 1) % num_of_turns];
        else if (command == 'l')
            turtle[i * 3 + 2] = turns[(index + num_of_turns - 1) % num_of_turns];
    }
}

void turtleDraw(char *grid, char *turtle, int *turtles, int cols)
{
    for(int i = 0; i < *turtles; i++)
    {
        int row = turtle[i * 3];
        int col = turtle[i * 3 + 1];
        char current = grid[row * cols + col];
        //if(current == ' ')
        if(current == '.')
        {
            grid[row * cols + col] = 'o';
        }
        else if(current == 'o')
        {
            //grid[row * cols + col] = ' ';
            grid[row * cols + col] = '.';
        }
    }
}

void pipinka(char *grid, int rows, int cols, char *turtle, int *turtles)
{
    for (int i = 0; i < (rows * cols); i++)
    {
        for (int j = 0; j < *turtles; j++)
        {
            if (i == turtle[j * 3] * cols + turtle[j * 3 + 1])
            {
                putchar('Z');
            }
        }
        if (grid[i] != 'Z')
        {
            putchar(grid[i]);
        }

        if ((i + 1) % cols == 0)
        {
            putchar('\n');
        }
    }
}

int main() {
    int rows, cols = 0;
    int turtles = 1;
    scanf("%d%d", &rows, &cols);

    char *grid = initGrid(&rows, &cols);
    char *turtle = initTurtles(&turtles);
    
    while(1)
    {
        //usleep(150000);
        //printf("\x1b[2J\x1b[1;1F");
        char command;
        scanf(" %c", &command);
        if(command == 'r' || command == 'l')
        {
            turtleRotate(turtle, &turtles, command);
        }
        else if(command == 'o')
        {
            turtleDraw(grid, turtle, &turtles, cols);
            //pipinka(grid, rows, cols, turtle, &turtles);
        }
        else if(command == 'm')
        {
            turtleMove(turtle, &turtles, cols, rows);
            //pipinka(grid, rows, cols, turtle, &turtles);
        }
        else if(command == 'f' && turtles < 3)
        {
            turtle = addTurtles(&turtles, turtle);
        }
        else if(command == 'x')
        {
            printGrid(grid, rows, cols);
            break;
        }
    }

    free(grid);
    free(turtle);
}