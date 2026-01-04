#include "../include/settings.h"
#include <stdio.h>

Settings settings;

/** 
 * @brief Načíta nastavenia zo súboru
 * @param settings Settings štruktúra
 * @param filename Cesta k súboru
*/
void loadSettings(Settings* settings, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char inputStr[16];
        char themeStr[16];
        char soundStr[16];
        fscanf(file, "%s\n", inputStr);
        fscanf(file, "%s\n", themeStr);
        fscanf(file, "%s", soundStr);

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

        if (strcmp(soundStr, "SOUND_ON") == 0) {
            settings->sound = SOUND_ON;
        } else {
            settings->sound = SOUND_OFF;
        }

        fclose(file);
    } else {
        // Default settings
        settings->input = ARROWS;
        settings->theme = DARK;
        settings->sound = SOUND_ON;
    }
}

/** 
 * @brief Uloží nastavenia do súboru
 * @param settings Settings štruktúra
 * @param filename Cesta k súboru
*/
void saveSettings(Settings* settings, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file) {
        char inputStr[16];
        char themeStr[16];
        char soundStr[16];

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

        if (settings->sound == SOUND_ON) {
            strcpy(soundStr, "SOUND_ON");
        } else {
            strcpy(soundStr, "SOUND_OFF");
        }

        fprintf(file, "%s\n", inputStr);
        fprintf(file, "%s\n", themeStr);
        fprintf(file, "%s", soundStr);
        fclose(file);
    }
}