#include <stdio.h>
#include <string.h>

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

void normalizeLine(char input[51], char normal[51], char letters[53])
{
    strcpy(normal, input);
    normal = strpbrk(normal, letters);
    printf("%s\n", normal);
}

void printStats(const struct Statistic *stat, char input[51]) {
    printf("%s\n", input);
    printf("lowercase: %d\n", stat->lowercase);
    printf("uppercase: %d\n", stat->uppercase);
    printf("spaces: %d\n", stat->spaces);
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
    printStats(&stat, input);
    normalizeLine(input, normal, letters);
}