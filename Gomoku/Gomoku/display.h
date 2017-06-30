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

void init();
void humanAction(STEP &step, SIDE side);
void showOneChess(int x, int y, int color);

#endif
