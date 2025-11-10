#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char input[50];
    char prev;
    int lines;
    char prev_word[50] = "none";
    size_t cislo = 0;

    fgets(input, sizeof(input), stdin);

    size_t len = strlen(input);

    if(len && input [len-1] == '\n'){
        input[len-1] = '\0';
    }
    
    prev = input[len-2];
    cislo = atoi(strchr(input, ' '));

    scanf("%d\n", &lines);

    for(int i = 0; i < lines; i++)
    {
        char line[50];
        fgets(line, sizeof(line), stdin);

        size_t line_len = strlen(line);
        if(line_len && line[line_len-1] == '\n'){
            line[line_len-1] = '\0';
        }

        if((line_len-1) < cislo)
        {
            printf("%s (none)\n", line);
            strcpy(prev_word, line);
        }
        else{
            printf("%s (%s)\n", line, prev_word);
            strcpy(prev_word, line);
        }
    }
    return 0;
}