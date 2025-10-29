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
    if (fgets(input, 51, stdin) == NULL) //input riadkov 
    { 
        input[0] = '\0'; 
        return; 
    }

    size_t n = strlen(input); //kelvin warning fix
    if (n > 0 && input[n-1] == '\n') //vymaze posledny znak 
    {
        input[n-1] = '\0';
    }
    if (n > 1 && input[n-2] == '\r') //vymaze predposledny znak
    {
        input[n-2] = '\0';
    }
}

void initBaseStats(struct Statistic *stat, char input[51]) {
    stat->lowercase = 0;
    stat->uppercase = 0;
    stat->spaces = 0;
    for (size_t i = 0; i < strlen(input); i++) {
        if (input[i] >= 'a' && input[i] <= 'z') //ascii porovnanie
        {
            stat->lowercase++;
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')  //ascii porovnanie
        {
            stat->uppercase++;
        }
        else if (input[i] == ' ') 
        {
            stat->spaces++;
        }
    }
}

int gateToNarnia(const char *character) { //custom atoi()
    int num = 0;
    int i = 0;
    while (character[i] != '\0' && character[i] >= '0' && character[i] <= '9') 
    {
        num = num * 10 + (character[i] - '0'); //mala nasobilka type shit
        i++;
    }
    return num;
}

void normalize(char input[51], char normal[51], char letters[53], struct Statistic *normStat) {
    normStat->lowercase = 0;
    normStat->uppercase = 0;
    normStat->spaces = 0;
    strcpy(normal, input);

    char *norm_line = strpbrk(normal, letters); //preskoci medzery na zaciatku
    if (!norm_line) //ak je len medzera
    {
        norm_line = normal;
    }

    size_t len = strlen(norm_line); //kelvin warning fix
    while(len > 0 && norm_line[len - 1] == ' ') //medzery od konca
    { 
        norm_line[len - 1] = '\0'; 
        len--; 
    }

    len = strlen(norm_line); //medzery medzi slovami
    for (size_t i = 0; i < len; i++) 
    {
        if(norm_line[i] == ' ' && norm_line[i + 1] == ' ') 
        {
            memmove(&norm_line[i], &norm_line[i + 1], strlen(&norm_line[i + 1]) + 1); //posunie znaky z pamate aby bola medzi nimi jedna medzera
            i--;
        }
    }

    char final[50] = ""; //final array kde budu pospajane slova
    char *word = strtok(norm_line, " ");
    bool empty = true;
    while (word != NULL) 
    {
        size_t word_len = strlen(word);
        bool is_upper = false;

        for (int i = 0; word[i] != '\0'; i++)  //prejde slovo ci tam je velke pismeno
        { 
            if (isupper(word[i]))  
            {   is_upper = true; 
                break; 
            }
        }

        if(is_upper) //nastavi prve pismeno velke ak su dalsie pismena v slove 
        { 
            for(size_t k = 0; k < word_len; k++)
            {
                if(k == 0) 
                {
                    word[k] = toupper(word[k]);
                }
                else 
                {
                    word[k] = tolower(word[k]);
                }
            }
        } 

        else //iba prve pismeno bude velke 
        { 
            for(size_t k = 0; k < word_len; k++) 
            {
                word[k] = toupper(word[k]);
            }
        }

        //picovske duplicitne znaky v slove
        int picus = 1;
        for (int k = 1; word[k]; k++) 
        {
            if (word[k] != word[k-1]) 
            {
                word[picus++] = word[k];
            }
        }
        word[picus] = '\0';

        if (!empty) strcat(final, " ");
        strcat(final, word);
        empty = false;

        word = strtok(NULL, " "); //uzavrie slovo a ide na dalsie
    }

    for (size_t i = 0; i < strlen(final); i++) 
    {
        if (final[i] >= 'a' && final[i] <= 'z') //ascii porovnanie
            {
                normStat->lowercase++;
            }
        else if (final[i] >= 'A' && final[i] <= 'Z') //ascii porovnanie
            {
                normStat->uppercase++;
            }
        else if (final[i] == ' ') 
            {
                normStat->spaces++;
            }
    }
    printf("%s\n", final);
}

void printStats(const struct Statistic *stat, const struct Statistic *normalised) {
    printf("lowercase: %d -> %d\n", stat->lowercase, normalised->lowercase);
    printf("uppercase: %d -> %d\n", stat->uppercase, normalised->uppercase);
    printf("spaces: %d -> %d\n", stat->spaces, normalised->spaces);
}

int main() {
    //vars
    char input[51];
    char normal[51];
    char letters[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    struct Statistic stat;
    struct Statistic normalised;

    char numOfLinesStr[16] = "";
    if (fgets(numOfLinesStr, sizeof(numOfLinesStr), stdin) == NULL) //ziadny ciselny vstup (test1) 
        {
            return 0;
        }

    size_t lines = strlen(numOfLinesStr);
    if (lines && numOfLinesStr[lines-1] == '\n') //odjebe zo vstupu \n 
        {
            numOfLinesStr[lines-1] = '\0';
        }

    int numOfLines = gateToNarnia(numOfLinesStr); //custom atoi()


    for (int i = 0; i < numOfLines; i++)
    {
        readLines(input);
        initBaseStats(&stat, input);
        normalize(input, normal, letters, &normalised);
        printStats(&stat, &normalised);
        if (i != numOfLines - 1) printf("\n");
    }
    return 0;
}