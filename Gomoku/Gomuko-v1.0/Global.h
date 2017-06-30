#ifndef GLOBAL_H
#define GLOBAL_H

#define LEFT 5			//棋盘左边界
#define TOP 5			//棋盘上边界
#define RIGHT 19		//棋盘右边界
#define DOWN 19			//棋盘下边界
#define MAX_BORDER 25	//棋盘存储大小
#define CHESS_SIZE 15	//棋盘最大网格数

//下棋方定义
typedef enum {
    EMPTY = 0,
    BLACKCHESS = 1,
    WHITECHESS = 2
} SIDE;

//下棋步数定义
class STEP {
public:
	int row;
	int col;
	STEP(int r = 0, int c = 0) :row(r), col(c) {};
};

extern int chess[MAX_BORDER][MAX_BORDER];
void setChess(const STEP&step);
#endif
