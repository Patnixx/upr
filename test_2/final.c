#include <stdio.h>

#include <string.h>

#include <stdlib.h>

#include <ctype.h>

struct Letter{

    int id;

    int score;

};

struct Token{

    char word[256];

    int occurence;

    int value;

};

int main(int argc, char *argv[]) {

    char num[16];

    strcpy(num, argv[1]);

    int lines = atoi(num);

    struct Token *line = NULL;

    struct Token *temp = realloc(line, lines * 3 * sizeof(struct Token));

    line = temp;

    //load inputs

    for(int i = 0; i < lines; i++) {

        char input[256];

        fgets(input, 256, stdin);

        char *token = strtok(input, ",");

        strcpy(line[i].word, token);

        token = strtok(NULL, ",");

        line[i].value = atoi(token);

    }//potialto to funguje 

    //toto mal robit elf a nie ja

    char letter[2048];

    fgets(letter, 2048, stdin);

    

    //this section penetrates me harder than a 9mm

    char *token = strtok(letter, "---");

    struct Letter *message = malloc(2*sizeof(struct Letter));

    int letter_count = 0;

    while(token){

        letter_count += 1;

        struct Letter *tem = realloc(message, letter_count * 2 * sizeof(struct Letter));

        message = tem;

        for(int j = 0; j < lines; j++){

            size_t len = strlen(line[j].word);

            size_t text_len = strlen(token);

            for(size_t k = 0; k < text_len; k++){

                if(strncmp(&token[k], line[j].word, len) == 0){

                    line[j].occurence++;

                    message[letter_count-1].score += line[j].value;

                    k += len-1;

                }

            }

        }

        token = strtok(NULL, "---");

    }

    for(int l = 0; l < letter_count; l++) {

        printf("Letter #%d\n", l+1);

        for(int m = 0; m < lines; m++){

            printf("Token '%s': %d occurrence, AI score: %d\n", line[m].word, line[m].occurence, line[m].value);

        }

        printf("Total AI score: %d\n", message[l].score);

        if(letter_count > 1){

            printf("\n");

        }

    }

}