#include "Global.h"
#include "display.h"
#include <graphics.h>

//������������
void drawChessBoard() {
	for (int i = 1; i <= CHESS_SIZE; ++i)
		line(GRID_SIZE, i*GRID_SIZE, CHESS_SIZE*GRID_SIZE, i*GRID_SIZE);
	for (int i = 1; i <= CHESS_SIZE; ++i)
		line(i*GRID_SIZE, GRID_SIZE, i*GRID_SIZE, CHESS_SIZE*GRID_SIZE);
}

//��ʾ������ɫ��ʾ
void showSide(SIDE humanSide) {
	settextstyle(18, 0, _T("����"));
	outtextxy(WIDTH - GRID_SIZE * 6, 6, _T(humanSide == BLACKCHESS ? "AI����    �ˣ���" : "AI����    �ˣ���"));
}

//��ʼ��
void init(SIDE humanSide) {
	initgraph(WIDTH, HEIGHT);
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	FlushMouseMsgBuffer();
	drawChessBoard();
	showSide(humanSide);
	showSide(humanSide);
}

//ָ��λ�û���һ������
void showOneChess(int x, int y, int color) {
	x -= LEFT - 1, y -= TOP - 1;
	x *= GRID_SIZE, y *= GRID_SIZE;
	setcolor(color);
	setfillcolor(color);
	setfillstyle(BS_SOLID);
	fillcircle(x, y, GRID_SIZE / 2);
}

//��ʾ�Ự
void showDialog(char *dialog) {
	settextstyle(20, 0, _T("Consolas"));
	outtextxy(30, 5, _T(dialog));
}

//��ʾ���Ľ��
void showResult(bool humanWin) {
	settextstyle(30, 0, _T("����"));
	if (humanWin) {
		setcolor(RED);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 0, _T("��Ӯ�ˣ�"));
	}
	else {
		setcolor(GREEN);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 0, _T("�����ˣ�"));
	}
}

//��ʾ���λ��
void showMouse(int x, int y, int color) {
	static const int p1[4][2] = { { MOUSE_P1 ,MOUSE_P1 },{ MOUSE_P1,-MOUSE_P1 },{ -MOUSE_P1,MOUSE_P1 },{ -MOUSE_P1,-MOUSE_P1 } };
	static const int p2[4][2] = { { MOUSE_P2 ,MOUSE_P2 },{ MOUSE_P2,-MOUSE_P2 },{ -MOUSE_P2,MOUSE_P2 },{ -MOUSE_P2,-MOUSE_P2 } };
	setlinecolor(color);
	x *= GRID_SIZE, y *= GRID_SIZE;
	for (int i = 0; i < 4; ++i)
		line(x + p1[i][0], y + p1[i][1], x + p2[i][0], y + p2[i][1]);
}

//�ƶ����ʱ���½���
void moveMouse(int x, int y, int nx, int ny) {
	showMouse(x, y, BACKGROUND_COLOR);
	showMouse(nx, ny, MOUSE_COLOR);
}

//��������ǰ�˽���
void humanAction(STEP &step, SIDE side) {
	MOUSEMSG m;
	int nowx = -1, nowy = -1;
	while (1) {
		m = GetMouseMsg();
		int windowx = (m.x + (GRID_SIZE >> 1)) / GRID_SIZE;
		int windowy = (m.y + (GRID_SIZE >> 1)) / GRID_SIZE;
		int chessx = windowx + LEFT - 1;
		int chessy = windowy + TOP - 1;
		if (chessx >= LEFT && chessx <= RIGHT&&chessy >= TOP && chessy <= DOWN) {
			switch (m.uMsg)
			{
			case WM_MOUSEMOVE:     //�ƶ�
				if (nowx != windowx || nowy != windowy)
					moveMouse(nowx, nowy, windowx, windowy);
				break;
			case WM_LBUTTONDOWN:  //����
				if (chess[chessy][chessx] != EMPTY)
					break;
				showOneChess(chessx, chessy, side == BLACKCHESS ? BLACKCHESS_COLOR : WHITECHESS_COLOR);
				step = { chessy ,chessx };
				return;
			}
			nowx = windowx, nowy = windowy;
		}
	}
}