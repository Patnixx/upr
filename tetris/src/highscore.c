#include "../include/highscore.h"
#include <stdio.h>

HighScores scores;

void loadHighScores(HighScores* scores) {
    FILE* file = fopen("assets/txt/highscore.txt", "r");
    if (file) {
        fscanf(file, "%d,%d,%d", &scores->t1, &scores->t2, &scores->t3);
        fclose(file);
    } else {
        scores->t1 = 0;
        scores->t2 = 0;
        scores->t3 = 0;
    }
}

void compareHighScore(int score, HighScores* scores) {
    if (score > scores->t1) {
        scores->t3 = scores->t2;
        scores->t2 = scores->t1;
        scores->t1 = score;
    } else if (score > scores->t2) {
        scores->t3 = scores->t2;
        scores->t2 = score;
    } else if (score > scores->t3) {
        scores->t3 = score;
    }
}

void saveHighScores(HighScores* scores) {
    FILE* file = fopen("assets/txt/highscore.txt", "w");
    if (file) {
        fprintf(file, "%d,%d,%d", scores->t1, scores->t2, scores->t3);
        fclose(file);
    }
}