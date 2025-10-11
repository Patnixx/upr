#include <stdio.h>
#include <stdlib.h>

void input_values(char *graf, int *num_of_nums, int *min_num, int counts[9], int *invalid)
{
    scanf(" %c", graf);

    if(*graf != 'h' && *graf != 'v' && *graf != 'H' && *graf != 'V')
    {
        printf("Neplatny mod vykresleni\n");
        exit(1); //pekna picovina
    }

    scanf("%d", num_of_nums);
    scanf("%d", min_num);
    int max_num = *min_num + 8;
    //printf("%c %d %d", graf, num_of_nums, min_num);

    for(int i = 0; i < *num_of_nums; i++)
    {
        int value = 0;
        scanf("%d", &value);
        if(value < *min_num || value > max_num)
        {
            (*invalid)++;
        }
        else if (value >= *min_num && value <= max_num)
        {
            int width = value - *min_num;
            counts[width]++;
        }
    }
}

void print_horizontal(int min_num, int counts[9], int invalid)
{
    int max_num = min_num + 8;

    for(int j = 0; j < 9; j++)
        {
            //whitespaces
            int max = max_num;
            int current_digits = 0;
            int max_digits = 0;
            for(int i = max; i > 0; i /= 10)
            {
                max_digits++;
            }
            for(int k = min_num+j; k > 0; k /= 10)
            {
                current_digits++;
            }
            int spaces = max_digits - current_digits;
            for(int s = 0; (s < spaces) && min_num != 0; s++)
            {
                printf(" ");
            }
            printf("%d", min_num + j);
            if(counts[j] > 0)
            {
                printf(" "); //kelvin type shit
            }

            //values
            for(int k = 0; k < counts[j]; k++)
            {
                printf("#");
            }
            printf("\n");
        }

        //invalid values
        if(invalid > 0)
        {
            printf("invalid: ");
            for(int l = 0; l < invalid; l++)
            {
                printf("#");
            }
            printf("\n");
        }
        
}

void print_vertical(int min_num, int counts[9], int invalid, int max_count)
{
    int y = 0;
        if(invalid > max_count)
        {
            y = invalid;
        }
        else
        {
            y = max_count;
        }
        while (y > 0)
        {
            int x = 0;
            while(x < 10)
            {
                if(x == 0)
                {
                    if(invalid >= y)
                    {
                        printf("#");
                        invalid--;
                    }
                    else
                    {
                        printf(" ");
                    }
                }
                else if(counts[x-1] == y)
                {
                    printf("#");
                    counts[x-1]--;
                }
                else
                {
                    printf(" ");
                }
                x++;
            }
            printf("\n");
            y--;
        }
    
        printf("i");
        for(int j = 0; j < 9; j++)
        {
            printf("%d", min_num + j);
        }
        printf("\n");
}

int main(){
    char graf;
    int num_of_nums = 0;
    int min_num = 0;
    int invalid = 0;
    int counts[9] = {0};

    input_values(&graf, &num_of_nums, &min_num, counts, &invalid);

    int max_count = 0;
    for(int j = 0; j < 9; j++)
    {
        if(counts[j] > max_count)
        {
            max_count = counts[j];
        }
    }

    if(graf == 'h')
    {
        print_horizontal(min_num, counts, invalid);
    }
    else if(graf == 'v')
    {
        print_vertical(min_num, counts, invalid, max_count);
    }
}