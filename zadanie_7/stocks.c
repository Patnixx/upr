#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stock {
    int day;
    char name[20]; //riadok ma max 100 chars a 5 udajov cize 100/5 = 20
    float start;
    float end;
    int trades;

};

int main(int argc, char *argv[]) {
    char stock[20];
    int params = 5;
    struct Stock line;

    strcpy(stock, argv[1]);
    int lines = atoi(argv[2]);
    
    char input[101];
    fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if(len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *token = strtok(input, ",");
    while(token && params > 0) {
        switch(params) {
            case 5: {
                line.day = atoi(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 4: {
                strcpy(line.name, token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 3: {
                line.start = atof(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 2: {
                line.end = atof(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 1: {
                line.trades = atoi(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
        }
    }
}