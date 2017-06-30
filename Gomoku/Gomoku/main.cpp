#include<fstream>
#include<iomanip>
#include<cstring>
#include<graphics.h>
using namespace std;

#include "Global.h"
#include "Evaluate.h"
#include "AI.h"
#include "Display.h"
extern fstream fout;
int chess[MAX_BORDER][MAX_BORDER];

void setChess(const STEP&step, SIDE side) {
	chess[step.row][step.col] = side;
}

void eraseChess(const STEP&step);

void showDialog(char *dialog) {
	settextstyle(20, 0, _T("Consolas"));
	outtextxy(30, 5, _T(dialog));
}

void showResult(bool humanWin) {
	settextstyle(30, 0, _T("����"));
	if (humanWin) {
		setcolor(RED);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 10, _T("��Ӯ�ˣ�"));
	}
	else {
		setcolor(GREEN);
		outtextxy(WIDTH / 2 - GRID_SIZE * 2, 10, _T("�����ˣ�"));
	}
}

void playChess() {
	STEP step, nextStep;
	SIDE humanSide = BLACKCHESS;
	SIDE computerSide = WHITECHESS;
	init();

	while (1) {
		showDialog("Turn to you ...         ");
		humanAction(step, humanSide);
		setChess(step, humanSide);
		fout << "************************   ���������  *************************" << endl;
		if (isWin(step, humanSide)) {
			showResult(true);
			break;
		}

		showDialog("Computer is thinking ...");
		AISearch(computerSide, step, nextStep);
		setChess(nextStep, computerSide);
		showOneChess(nextStep.col, nextStep.row, WHITECHESS_COLOR);
		fout << "************************   AI�����  *************************" << endl;
		fout << "AI����λ�ã�" << nextStep.row - TOP + 1 << " " << nextStep.col - LEFT + 1 << endl;
		if (isWin(nextStep, computerSide)) {
			showResult(false);
			break;
		}
		//cout << nextStep.row - TOP << " " << nextStep.col - LEFT << endl;
	}
	system("pause");
}

int main() {
	playChess();
	return 0;
}