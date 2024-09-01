#ifndef BALL_H
#define BALL_H

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
} Ball;

void drawBall(Ball *ball, char matrix[23][80]);

void updateBallPos(Ball *ball, char matrix[23][80], int *playerOneScore, int *playerTwoScore);

void resetBall(Ball *ball, char matrix[23][80]);

#endif
