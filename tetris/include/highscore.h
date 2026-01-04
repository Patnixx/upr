#ifndef HIGHSCORE_H
#define HIGHSCORE_H

typedef struct {
    int t1;
    int t2;
    int t3;
} HighScores;

void loadHighScores(HighScores* scores);
void compareHighScore(int score, HighScores* scores);
void saveHighScores(HighScores* scores);

#endif