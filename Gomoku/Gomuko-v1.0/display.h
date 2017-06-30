#ifndef DISPLAY_H
#define DISPLAY_H

#define GRID_SIZE 30
#define WIDTH GRID_SIZE*(CHESS_SIZE+1)
#define HEIGHT GRID_SIZE*(CHESS_SIZE+1)
#define MOUSE_P1 10
#define MOUSE_P2 20

#define MOUSE_COLOR LIGHTGRAY
#define BACKGROUND_COLOR DARKGRAY

#define BLACKCHESS_COLOR 0
#define WHITECHESS_COLOR 0xFFFFFF

//初始化
void init(SIDE humanSide);

//画出棋盘网格
void drawChessBoard();

//显示各方棋色提示
void showSide(SIDE humanSide);

//指定位置画出一颗棋子
void showOneChess(int x, int y, int color);

//显示会话
void showDialog(char *dialog);

//显示博弈结果
void showResult(bool humanWin);

//显示鼠标位置
void showMouse(int x, int y, int color);

//移动鼠标时更新界面
void moveMouse(int x, int y, int nx, int ny);

//人类下棋前端交互
void humanAction(STEP &step, SIDE side);

#endif
