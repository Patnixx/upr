#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct Statistic {
    int lowercase;
    int uppercase;
    int spaces;
};

void readLines(char input[51]) {
    fgets(input, 50, stdin);
}

void initBaseStats(struct Statistic *stat, char input[51]) {
    stat->lowercase = 0;
    stat->uppercase = 0;
    stat->spaces = 0;

    for (int i = 0; i < strlen(input); i++) {
        if (input[i] >= 'a' && input[i] <= 'z') { //ascii porovnavanie
            stat->lowercase++;
        } else if (input[i] >= 'A' && input[i] <= 'Z') { //ascii porovnavanie
            stat->uppercase++;
        } else if (input[i] == ' ') {
            stat->spaces++;
        }
    }
}

void normalize(char input[51], char normal[51], char letters[53], struct Statistic *normStat)
{
    normStat->lowercase = 0;
    normStat->uppercase = 0;
    normStat->spaces = 0;
    strcpy(normal, input);
    char *norm_line = strpbrk(normal, letters); //medzery na zaciatku
    int len = strlen(norm_line);
    while(len > 0 && norm_line[len - 1] == ' ') { //medzery na konci
        norm_line[len - 1] = '\0';
        len--;
    }

    len = strlen(norm_line);
    for (int i = 0; i < len; i++) {
        if(norm_line[i] == ' ' && norm_line[i + 1] == ' ') { //len jedna medzera medzi slovami
            memmove(&norm_line[i], &norm_line[i + 1], strlen(&norm_line[i + 1]) + 1);
            i--;
        }
    }

    //stats
    for (int i = 0; i < strlen(norm_line); i++) {
        if (norm_line[i] >= 'a' && norm_line[i] <= 'z') { //ascii porovnavanie
            normStat->lowercase++;
        } else if (norm_line[i] >= 'A' && norm_line[i] <= 'Z') { //ascii porovnavanie
            normStat->uppercase++;
        } else if (norm_line[i] == ' ') {
            normStat->spaces++;
        }
    }

    char merged[51];
    char *word = strtok(norm_line, " ");
    bool empty = true;
    while (word != NULL)
    {
        //prezriet ci tam neni velke pismeno
        int has_upper = 0;
        for (int k = 0; word[k] != '\0'; k++) {
            if (isupper(word[k])) {
                has_upper = 1;
                break;
            }
        }
        //ak je/neni tak upravit slovo
        if (has_upper) {
            word[0] = toupper(word[0]);
            for (int k = 1; word[k]; k++)
                word[k] = tolower(word[k]);
        } 
        else {
            for (int k = 0; word[k]; k++)
                word[k] = toupper(word[k]);
            }


        //odstranenie duplicitnych pismen v slove
        int w = 1;
        for (int k = 1; word[k]; k++) {
            if (word[k] != word[k-1])
                word[w++] = word[k];
        }
        word[w] = '\0';

        if (empty == false) 
        {
            strcat(merged, " ");
        }
        else
        {
            strcat(merged, word);
        empty = false;
        }

        word = strtok(NULL, " ");
    }
    printf("%s\n", merged);
    
}

void printStats(const struct Statistic *stat, const struct Statistic *normalised) {

    printf("lowercase: %d -> %d\n", stat->lowercase, normalised->lowercase);
    printf("uppercase: %d -> %d\n", stat->uppercase, normalised->uppercase);
    printf("spaces: %d -> %d\n", stat->spaces, normalised->spaces);
}

int main() {
    int numOfLines = 0;
    char input[51];
    char normal[51];
    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    struct Statistic stat;
    struct Statistic normalised;

    readLines(input);
    initBaseStats(&stat, input);
    printStats(&stat, &normalised);
    normalize(input, normal, letters, &normalised);
}