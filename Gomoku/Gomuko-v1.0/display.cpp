#include "Global.h"
#include "display.h"
#include <graphics.h>

//画出棋盘网格
void drawChessBoard() {
	for (int i = 1; i <= CHESS_SIZE; ++i)
		line(GRID_SIZE, i*GRID_SIZE, CHESS_SIZE*GRID_SIZE, i*GRID_SIZE);
	for (int i = 1; i <= CHESS_SIZE; ++i)
		line(i*GRID_SIZE, GRID_SIZE, i*GRID_SIZE, CHESS_SIZE*GRID_SIZE);
}

//显示各方棋色提示
void showSide(SIDE humanSide) {
	settextstyle(18, 0, _T("楷体"));
	outtextxy(WIDTH - GRID_SIZE * 6, 6, _T(humanSide == BLACKCHESS ? "AI：白    人：黑" : "AI：黑    人：白"));
}

//初始化
void init(SIDE humanSide) {
	initgraph(WIDTH, HEIGHT);
	setbkcolor(BACKGROUND_COLOR);
	cleardevice();
	FlushMouseMsgBuffer();
	drawChessBoard();
	showSide(humanSide);
	showSide(humanSide);
}

//指定位置画出一颗棋子
void showOneChess(int x, int y, int color) {
	x -= LEFT - 1, y -= TOP - 1;
	x *= GRID_SIZE, y *= GRID_SIZE;
	setcolor(color);
	setfillcolor(color);
	setfillstyle(BS_SOLID);
	fillcircle(x, y, GRID_SIZE / 2);
}

//显示会话
void showDialog(char *dialog) {
	settextstyle(20, 0, _T("Consolas"));
	outtextxy(30, 5, _T(dialog));
}

//显示博弈结果
void showResult(bool humanWin) {
	settextstyle(30, 0, _T("楷体"));
	if (humanWin) {
		setcolor(RED);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 0, _T("你赢了！"));
	}
	else {
		setcolor(GREEN);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 0, _T("你输了！"));
	}
}

//显示鼠标位置
void showMouse(int x, int y, int color) {
	static const int p1[4][2] = { { MOUSE_P1 ,MOUSE_P1 },{ MOUSE_P1,-MOUSE_P1 },{ -MOUSE_P1,MOUSE_P1 },{ -MOUSE_P1,-MOUSE_P1 } };
	static const int p2[4][2] = { { MOUSE_P2 ,MOUSE_P2 },{ MOUSE_P2,-MOUSE_P2 },{ -MOUSE_P2,MOUSE_P2 },{ -MOUSE_P2,-MOUSE_P2 } };
	setlinecolor(color);
	x *= GRID_SIZE, y *= GRID_SIZE;
	for (int i = 0; i < 4; ++i)
		line(x + p1[i][0], y + p1[i][1], x + p2[i][0], y + p2[i][1]);
}

//移动鼠标时更新界面
void moveMouse(int x, int y, int nx, int ny) {
	showMouse(x, y, BACKGROUND_COLOR);
	showMouse(nx, ny, MOUSE_COLOR);
}

//人类下棋前端交互
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
			case WM_MOUSEMOVE:     //移动
				if (nowx != windowx || nowy != windowy)
					moveMouse(nowx, nowy, windowx, windowy);
				break;
			case WM_LBUTTONDOWN:  //按下
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