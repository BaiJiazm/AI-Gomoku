#include<iomanip>
#include<cstring>
#include<graphics.h>
using namespace std;

#include "Global.h"
#include "Evaluate.h"
#include "AI.h"
#include "Display.h"

int chess[MAX_BORDER][MAX_BORDER];

void setChess(const STEP&step, SIDE side) {
	chess[step.row][step.col] = side;
}

#define compSide 1
void playChess() {
	STEP step, nextStep;
	SIDE humanSide = compSide ? BLACKCHESS : WHITECHESS;
	SIDE computerSide = compSide ? WHITECHESS : BLACKCHESS;
	init(humanSide);

	if (computerSide == BLACKCHESS) {
		nextStep = { 7 + TOP,7 + LEFT };
		setChess(nextStep, computerSide);
		showOneChess(nextStep.col, nextStep.row, computerSide == BLACKCHESS ? BLACKCHESS_COLOR : WHITECHESS_COLOR);
	}

	while (1) {
		showDialog("Turn to you ...    ");
		humanAction(step, humanSide);
		setChess(step, humanSide);
		if (isWin(step, humanSide)) {
			showResult(true);
			break;
		}

		showDialog("AI is thinking ...");
		AISearch(computerSide, step, nextStep);
		setChess(nextStep, computerSide);
		showOneChess(nextStep.col, nextStep.row, computerSide == BLACKCHESS ? BLACKCHESS_COLOR : WHITECHESS_COLOR);
		if (isWin(nextStep, computerSide)) {
			showResult(false);
			break;
		}
	}
	system("pause");
}

int main() {
	playChess();
	return 0;
}