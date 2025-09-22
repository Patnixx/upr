#include <stdio.h>

int main() 
{
    /*printf("Hello, world!\n");
    return 0;*/

    int input = 0;

    //scanf("%d", &input);

    if (input == 0)
    {
        printf("Input is zero.\n");
    }
    else if (input > 0)
    {
        printf("Input is positive.\n");
    }
    
    else 
    {
        printf("Input is negative.\n");
    }

    int num = 5;
    int fact = 1;

    while (num > 1)
    {
        fact *= num;
        num--;
    }

    printf("Factorial: %d\n", fact);

    int base = 2;
    int exp = 10;
    int power = 1;

    while (exp >0)
    {
        power *= base;
        exp--;
    }

    printf("Power: %d\n", power);

    int y = 16;
    while (y >= -16)
    {
        int x = -16;
        while (x <= 16)
        {
            if (x == 0 && y == 0)
            {
                printf("+");
            }
            else if (x == 0)
            {
                printf("|");
            }
            else if (y == 0)
            {
                printf("-");
            }
            else {
                printf(" ");
            }
            x++;
        }
        printf("\n");
        --y;
    }
    

    return 0;
}