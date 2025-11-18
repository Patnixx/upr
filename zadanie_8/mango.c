#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//du3 voids
void reset_color() {
    printf("\x1b[0m");
    fflush(stdout);
}

void set_red_color() {
    printf("\x1b[41;1m");
    fflush(stdout);
}

void bonus(char *line, char *needle){
    size_t needle_len = strlen(needle);
    for(size_t i = 0; i < strlen(line); i++) {
        if(strncmp(&line[i], needle, needle_len) == 0) { //ak je zhoda
            set_red_color();
            for(size_t j = 0; j < needle_len; j++) {
                printf("%c", line[i + j]);
            }
            reset_color();
            i += needle_len - 1; //skip slova
        }
        else printf("%c", line[i]);
    }
    printf("\n");
}

int fill_vars(char *input_file, char *needle, char *output_file, int *case_sens, int argc, char *argv[], int *o_path){
    if(argc < 2) {
        printf("Input path not provided\n");
        exit(1);
    }
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-i") == 0){
            if(*case_sens != 0) {
                printf("Parameter -i provided multiple times\n");
                exit(1);
            }
            *case_sens = 1;
        }
        else if(strcmp(argv[i], "-o") == 0){
            if(i+1 >= argc) {
                printf("Missing output path\n");
                exit(1);
            }
            else if(*o_path != 0) {
                printf("Parameter -o provided multiple times\n");
                exit(1);
            }
            strcpy(output_file, argv[i+1]);
            *o_path = 1;
            i++;
        }
        else {            
            if(strlen(input_file) == 0) strcpy(input_file, argv[i]);
            else if(strlen(needle) == 0) strcpy(needle, argv[i]);
            else{
                printf("Too many parameters provided\n");
                exit(1);
            }
        }
    }
    return 0;
}

int primary_alerts(char *input_file, char *needle){
    if(strlen(input_file) == 0){
        printf("Input path not provided\n");
        exit(1);
    }
    else if(strlen(needle) == 0){
        printf("Needle not provided\n");
        exit(1);
    }
    return 0;
}

int main(int argc, char *argv[]){
    char input_file[256] = {0};
    char needle[256] = {0};
    int case_sens = 0;
    int o_path = 0;
    char output_file[256] = {0};

    fill_vars(input_file, needle, output_file, &case_sens, argc, argv, &o_path);
    primary_alerts(input_file, needle);

    FILE *input = fopen(input_file, "r");
    FILE *output = NULL;
    if(o_path){
        output = fopen(output_file, "w");
    }

    char line[101];
    while(fgets(line, sizeof(line), input)) {
        size_t len = strlen(line);
        if(line[len - 1] == '\n') line[len - 1] = '\0';

        if(case_sens) {
            if(o_path) {
                if(strcasestr(line, needle)) fprintf(output, "%s\n", line);
            }
            else {
                if(strcasestr(line, needle)) printf("%s\n", line);
                    //bonus(line, needle);
            }
        }
        else {
            if(o_path) {
                if(strstr(line, needle)) fprintf(output, "%s\n", line);
            }
            else {
                if(strstr(line, needle)) printf("%s\n", line);
                    //bonus(line, needle);
            }
        }
    }
    if(output != NULL) fclose(output);
    fclose(input);
}