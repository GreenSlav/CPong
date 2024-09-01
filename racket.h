#ifndef RACKET_H
#define RACKET_H

typedef struct
{
    int x;
    int y;
} Racket;

void drawRacket(Racket *racket, char matrix[23][80]);
void changeRacketPos(Racket *racket, char matrix[23][80], int direction); // 1 - up; 0 - down

#endif
