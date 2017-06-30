#ifndef GLOBAL_H
#define GLOBAL_H

#define LEFT 5
#define TOP 5
#define RIGHT 19
#define DOWN 19
#define MAX_BORDER 25
#define CHESS_SIZE 15

typedef enum {
    EMPTY = 0,
    BLACKCHESS = 1,
    WHITECHESS = 2
} SIDE;

class STEP {
public:
	int row;
	int col;
	STEP(int r = 0, int c = 0) :row(r), col(c) {};
};

extern int chess[MAX_BORDER][MAX_BORDER];
void setChess(const STEP&step);
void eraseChess(const STEP&step);
#endif
