#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "ball.h"
#include "racket.h"

#define WIDTH 80
#define HEIGHT 25
#define FIELD_HEIGHT 23

bool flagToQuit = false;

void clearScreen();

void displayField(char field[23][80]);

void initializeField(char field[23][80]);

void handleUserInput(Racket *leftRacket, Racket *rightRacket, char matrix[23][80], Ball *ball, int *player_1,
                     int *player_2);

void displayScore(int player_1, int player_2);

int main()
{
    srand(time(NULL));
    // Making the window 80x25 symbols
    printf("\x1b[8;25;80t]");

    // Объявление переменной игрового поля
    char field[23][80];

    // Счет в игре между двумя игроками
    int scorePlayerOne = 0, scorePlayerTwo = 0;

    // ИНициализация двух ракеток
    Racket leftRacket = {3, FIELD_HEIGHT / 2};
    Racket rightRacket = {80 - 3, FIELD_HEIGHT / 2};

    // Инициализация поля
    initializeField(field);

    // Отрисовка ракеток
    drawRacket(&leftRacket, field);
    drawRacket(&rightRacket, field);

    // Инициализация мяча
    int randInt = rand() % 2;
    Ball ball = {80 / 2, 23 / 2, randInt == 1, randInt == 0};
    resetBall(&ball, field);

    while (1)
    {
        // Game logics
        // ВАЖНО: СНАЧАЛА ОБНОВЛЯЕМ РАКЕТКИ, ПОТОМ МЯЧ !!!
        displayScore(scorePlayerOne, scorePlayerTwo);
        displayField(field);
        handleUserInput(&leftRacket, &rightRacket, field, &ball, &scorePlayerOne, &scorePlayerTwo);

        // Clearing
        clearScreen();

        // Отслеживания нажатия 'q'
        if (flagToQuit)
        {
            return 0;
        }

        if (((scorePlayerOne >= scorePlayerTwo) ? scorePlayerOne : scorePlayerTwo) == 21)
        {
            // TODO: Вывести на экран, какой игрок победил
            return 0;
        }
    }

    return 0;
}

void clearScreen() { printf("\033[H\033[j"); }

void displayField(char field[23][80])
{
    for (int h = 0; h < 23; ++h)
    {
        for (int w = 0; w < 80; ++w)
        {
            printf("%c", field[h][w]);
        }
        if (h != 22)
        {
            printf("\n");
        }
    }
}

void initializeField(char field[23][80])
{
    for (int height = 0; height < 23; ++height)
    {
        for (int width = 0; width < 80; ++width)
        {
            field[height][width] = ' ';

            if (width == 0 || width == 79)
            {
                field[height][width] = '|';
            }

            if (height == 0 || height == 22)
            {
                field[height][width] = '-';
            }
        }
    }
}

void handleUserInput(Racket *leftRacket, Racket *rightRacket, char matrix[23][80], Ball *ball, int *player_1,
                     int *player_2)
{
    char userInput;

    printf("\nEnter the command: ");
    int result = scanf("%c", &userInput);
    printf("\n");

    if (result == 1)
    {
        switch (tolower(userInput))
        {
        case 'a':
            changeRacketPos(leftRacket, matrix, 1);
            break;
        case 'z':
            changeRacketPos(leftRacket, matrix, -1);
            break;
        case 'k':
            changeRacketPos(rightRacket, matrix, 1);
            break;
        case 'm':
            changeRacketPos(rightRacket, matrix, -1);
            break;
        case 'q':
            flagToQuit = true;
            break;
        default:
            // smth...
            break;
        }

        updateBallPos(ball, matrix, player_1, player_2);
    }
}

void displayScore(int player_1, int player_2)
{
    printf("\nSCORE:  %d  ::  %d                                                                \n", player_1,
           player_2);
}