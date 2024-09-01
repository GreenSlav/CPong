#include "racket.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void drawRacket(Racket *racket, char matrix[23][80])
{
    // We guarantee that the racket will not go beyond the limits when initialized
    matrix[racket->y][racket->x] = '|';
    matrix[racket->y + 1][racket->x] = '|';
    matrix[racket->y - 1][racket->x] = '|';
}

void changeRacketPos(Racket *racket, char matrix[23][80], int direction)
{ // 1 - up; 0 - still, -1 - down
    if (direction == 1)
    {
        if (racket->y - 2 > 0 && matrix[racket->y - 2][racket->x] != 'O')
        {
            racket->y -= 1;
            matrix[racket->y - 1][racket->x] = '|'; // верхняя граница
            matrix[racket->y + 2][racket->x] = ' ';
        }
    }
    else if (direction == -1)
    {
        if (racket->y + 2 < 22 && matrix[racket->y + 2][racket->x] != 'O')
        {
            racket->y += 1;

            matrix[racket->y + 1][racket->x] = '|'; // нижняя граница
            matrix[racket->y - 2][racket->x] = ' ';
        }
    }
}
