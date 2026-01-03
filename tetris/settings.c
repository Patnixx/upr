#include "include/settings.h"
#include <stdio.h>

Settings settings;

void loadSettings(Settings* settings, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char inputStr[8];
        char themeStr[8];
        fscanf(file, "%s\n", inputStr);
        fscanf(file, "%s", themeStr);

        if (strcmp(inputStr, "ARROWS") == 0) {
            settings->input = ARROWS;
        } else {
            settings->input = WASD;
        }

        if (strcmp(themeStr, "DARK") == 0) {
            settings->theme = DARK;
        } else {
            settings->theme = LIGHT;
        }

        fclose(file);
    } else {
        // Default settings
        settings->input = ARROWS;
        settings->theme = DARK;
    }
}

void saveSettings(Settings* settings, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        char inputStr[8];
        char themeStr[8];

        if (settings->input == ARROWS) {
            strcpy(inputStr, "ARROWS");
        } else {
            strcpy(inputStr, "WASD");
        }

        if (settings->theme == DARK) {
            strcpy(themeStr, "DARK");
        } else {
            strcpy(themeStr, "LIGHT");
        }

        fprintf(file, "%s\n", inputStr);
        fprintf(file, "%s", themeStr);
        fclose(file);
    }
}