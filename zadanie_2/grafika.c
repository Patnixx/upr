#include <stdio.h>

int main() {
    int obrazec = 0; //tvary/zadania
    int a = 0; //x-osa
    int b = 0; //y-osa

    scanf("%d%d%d", &obrazec, &a, &b);
    
    //printf("Obrazec: %d\n Sirka: %d \n Vyska: %d \n", obrazec, a, b);

    switch (obrazec)
    {
    case 0:
        // Obdlznik
        while (b > 0)
        {
            int x = a;
            while (x > 1)
            {
                printf("x");
                x--;
            }
            printf("x \n");
            b--;
        }
        break;
    
    case 1:
        // Obdlznik ale obvod
        int y = b;
        while (y > 0)
        {
            int x = a;
            while (x > 0)
            {
                if(y == b || y == 1)
                {
                    printf("x");
                }
                else if (y < b && y != 1)
                {
                    if(x == a || x == 1) 
                    {
                        printf("x");
                    }
                    else 
                    {
                        printf(" ");
                    }
                }
                else 
                {
                    printf(" ");
                }
                x--;
            }
            printf("\n");
            y--;
        }
        break;
    case 2:
        // obdlznik s cislami inside
        y = b;
        int num = 0;
        while (y > 0)
        {
            int x = a;
            while (x > 0)
            {
                if(y == b || y == 1)
                {
                    printf("x");
                }
                else if (y < b && y != 1)
                {
                    if(x == a || x == 1) 
                    {
                        printf("x");
                    }
                    else 
                    {
                        if (num > 9)
                            num = 0;
                        printf("%d", num);
                        num++;
                    }
                }
                else 
                {
                    printf(" ");
                }
                x--;
            }
            printf("\n");
            y--;
        }
        break;
    
    case 3:
    //diagonala RD
        for (int i = 0; i < a; i++)
        {
            printf("x \n");
            for (int j = -1; j < i; j++)
            {
                printf(" ");
            }
        }
        break;

    case 4:
    //diagonala LD
        for (int i = 0; i < a; i++)
        {
            for (int j = i; j < a; j++)
            {
                printf(" ");
            }
            printf("x \n");
        }
        break;

    case 5:
        //trojuholnik
        int x = a;
        int x_num = (a*2) - 1;
        int medzera = -1;
        while (x > 0)
        {
            for (int i = 1; i < x; i++)
            {
                printf(" ");
            }
            if(x > 1)
            {
                printf("x");
                if(x < a)
                {
                    for (int j = 0; j < medzera; j++)
                    {
                        printf(" ");
                    }
                }
                if(x == a)
                {
                    printf("\n");
                }
                else
                {
                    printf("x\n");
                }
                medzera = medzera + 2;
            }
            else
            {
                for(int j = 0; j < x_num; j++)
                {
                    printf("x");
                }
                printf("\n");
            }
            x--;
        }
        break;

    case 6:
        //pismeno T
        int zvysok = a%2;
        int stred = (a/2) + zvysok;
        y = b;

        while (y > 0)
        {
            int x = a;
            while (x > 0)
            {
                if(y == b)
                {
                    printf("x");
                }
                else
                {
                    if(x == stred)
                    {
                        printf("x");
                    }
                    else{
                        printf(" ");
                    }
                }
                x--;
            }
            printf("\n");
            y--;
        }
        break;

    case 7:
        //pismeno P
        int zvysok_p = b%2;
        int stred_p = (b / 2) + zvysok_p;
        int noha_p = b - stred_p;
        y = stred_p;

        while (y > 0)
        {
            int x = a;
            while (x > 0)
            {
                if(y == stred_p || y == 1)
                {
                    printf("x");
                }
                else if (y < b && y != 1)
                {
                    if(x == a || x == 1) 
                    {
                        printf("x");
                    }
                    else 
                    {
                        printf(" ");
                    }
                }
                else 
                {
                    printf(" ");
                }
                x--;
            }
            printf("\n");
            y--;
        }

        for(int i = 0; i <noha_p; i++)
        {
            printf("x \n");
        }
        break;

    case 9:
        //cisla v stlpci
        y = 0;
        while (y < b) 
        {
            int x = 0;
            while (x < a) 
            {
                if (y == 0 || y == b - 1) {
                    printf("x");
                }
                
                else if(x == 0 || x == a - 1) {
                    printf("x");
                }

                else {
                    int riadok = y - 1;
                    int stlpec = x - 1;
                    int poloha = stlpec * (b-2) + riadok;
                    int cislo = poloha % 10; //%10 lebo zvysok je to cislo co tam ma byt
                    printf("%d", cislo);
                }
                x++;
            }
            printf("\n");
            y++;
        }
        break;

    default:
        printf("Neznamy obrazec \n");
        break;
    }

    return 0;
}