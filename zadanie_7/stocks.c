#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stock {
    int day;
    char name[20]; //riadok ma max 100 chars a 5 udajov cize 100/5 = 20
    float start;
    float end;
    float diff;
    int trades;
};

int main(int argc, char *argv[]) {
    char stock[20];
    int params = 6;
    struct Stock line;
    char input[101];

    strcpy(stock, argv[1]);
    int lines = atoi(argv[2]);
    
    for(int i = 0; i < lines; i++) {
        fgets(input, sizeof(input), stdin);
        size_t len = strlen(input);
        if(len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }

        char *token = strtok(input, ",");
        //den
        if(!token) break;
        line.day = atoi(token);
        token = strtok(NULL, ",");
        //nazov
        if(!token) break;
        strcpy(line.name, token);
        token = strtok(NULL, ",");
        //start
        if(!token) break;
        line.start = atof(token);
        token = strtok(NULL, ",");
        //end
        if(!token) break;
        line.end = atof(token);
        token = strtok(NULL, ",");
        //diff
        float difference = line.end - line.start;
        line.diff = difference;
        //trades
        if(!token) break;
        line.trades = atoi(token);
        token = strtok(NULL, ",");
    }


    /*fgets(input, sizeof(input), stdin);
    size_t len = strlen(input);
    if(len > 0 && input[len - 1] == '\n') {
        input[len - 1] = '\0';
    }

    char *token = strtok(input, ",");
    while(token && params > 0) {
        switch(params) {
            case 6: {
                line.day = atoi(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 5: {
                strcpy(line.name, token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 4: {
                line.start = atof(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }
            case 3: {
                line.end = atof(token);
                token = strtok(NULL, ",");
                params--;
                break;
            }

            case 2: {
                float difference = line.end - line.start;
                line.diff = difference;
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
    }*/
}