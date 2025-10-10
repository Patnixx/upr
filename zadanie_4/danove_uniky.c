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
    for(int j = 0; j < 9; j++)
    {
        printf("%d ", min_num + j);
        for(int k = 0; k < counts[j]; k++)
        {
            printf("#");
        }
        printf("\n");
    }
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

//FIXME - test-invalid-mode -> vypne kod po zlej hodnote 
//FIXME - test-cent -> medzery pred menejciferne cisla
//FIXME - test-large-range ->   -||-
//FIXME - dokoncit vertikal
//FIXME - upravit to na funkcie