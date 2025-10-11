#include <stdio.h>

void input_values()
{
    char graf;
    scanf("%c", &graf);

    if(graf != 'h' && graf != 'v')
    {
        printf("Neplatny mod vykresleni\n");
    }

    int num_of_nums = 0;
    int num_range = 0;
    scanf("%d", &num_of_nums);
    scanf("%d", &num_range);
    //printf("%c %d %d", graf, num_of_nums, num_range);

    int values[9] = {};
    for(int i = 0; i < num_of_nums; i++)
    {
        int value = 0;
        scanf("%d", &value);
        values[i] = value;
    }

    /*for(int j = 0; j < 10; j++)
    {
        printf("%d ", values[j]);
    }*/
}

int main(){
    char graf;
    scanf("%c", &graf);

    if(graf != 'h' && graf != 'v')
    {
        printf("Neplatny mod vykresleni\n");
    }

    int num_of_nums = 0;
    int min_num = 0;
    int invalid = 0;
    scanf("%d", &num_of_nums);
    scanf("%d", &min_num);
    int max_num = min_num + 8;
    //printf("%c %d %d", graf, num_of_nums, min_num);

    int counts[9] = {0};
    for(int i = 0; i < num_of_nums; i++)
    {
        int value = 0;
        scanf("%d", &value);
        if(value < min_num || value > max_num)
        {
            invalid++;
        }
        else if (value >= min_num && value <= max_num)
        {
            int width = value - min_num;
            counts[width]++;
        }
    }

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
            printf("%d ", min_num + j);

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
    else if(graf == 'v')
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
    }
}

//FIXME - test-invalid-mode -> vypne kod po zlej hodnote 
//FIXME - upravit to na funkcie