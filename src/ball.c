#include "ball.h"

#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void drawBall(Ball *ball, char matrix[23][80]) { matrix[ball->y][ball->x] = 'O'; }

void updateBallPos(Ball *ball, char matrix[23][80], int *playerOneScore, int *playerTwoScore)
{
    // Случаи, когда мяч уже преодолел ракетки
    // Преодолел левую
    if (ball->x + ball->dx <= 0)
    {
        ++(*playerTwoScore);
        resetBall(ball, matrix);
        return;
    }

    // Преодолел правую
    if (ball->x + ball->dx >= 79)
    {
        ++(*playerOneScore);
        resetBall(ball, matrix);
        return;
    }

    // Попали в одну из ракеток
    if (matrix[ball->y + ball->dy][ball->x + ball->dx] == '|')
    {
        // Меняем направление по X на противоположное
        ball->dx *= (-1);

        // Точка, которую мы сейчас покинем
        matrix[ball->y][ball->x] = ' ';
        // Точка, в которую мы сейчас зайдем
        matrix[ball->y + ball->dy][ball->x + ball->dx] = 'O';
        // ОБновление позиции мяча

        ball->x = ball->x + ball->dx;
        ball->y = ball->y + ball->dy;
        return;
    }

    // Попали в одну из горизонтальных стенок
    if (ball->y + ball->dy <= 0 || ball->y + ball->dy >= 22)
    {
        ball->dy *= (-1);

        // Точка, которую мы сейчас покинем
        matrix[ball->y][ball->x] = ' ';
        // Точка, в которую мы сейчас зайдем
        matrix[ball->y + ball->dy][ball->x + ball->dx] = 'O';
        // ОБновление позиции мяча
        ball->x = ball->x + ball->dx;
        ball->y = ball->y + ball->dy;
        return;
    }

    // Обычное перемещение
    matrix[ball->y][ball->x] = ' ';
    // Точка, в которую мы сейчас зайдем
    matrix[ball->y + ball->dy][ball->x + ball->dx] = 'O';
    // ОБновление позиции мяча
    ball->x = ball->x + ball->dx;
    ball->y = ball->y + ball->dy;
}

void resetBall(Ball *ball, char matrix[23][80])
{
    matrix[ball->y][ball->x] = ' ';

    srand(time(NULL));
    int randNumber = rand() % 2;

    matrix[23 / 2][80 / 2] = 'O';
    ball->x = 80 / 2;
    ball->y = 23 / 2;
    ball->dx = (randNumber == 0) ? 1 : -1;
    ball->dy = (randNumber == 1) ? 1 : -1;
}