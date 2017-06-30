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

//��ʼ��
void init(SIDE humanSide);

//������������
void drawChessBoard();

//��ʾ������ɫ��ʾ
void showSide(SIDE humanSide);

//ָ��λ�û���һ������
void showOneChess(int x, int y, int color);

//��ʾ�Ự
void showDialog(char *dialog);

//��ʾ���Ľ��
void showResult(bool humanWin);

//��ʾ���λ��
void showMouse(int x, int y, int color);

//�ƶ����ʱ���½���
void moveMouse(int x, int y, int nx, int ny);

//��������ǰ�˽���
void humanAction(STEP &step, SIDE side);

#endif
