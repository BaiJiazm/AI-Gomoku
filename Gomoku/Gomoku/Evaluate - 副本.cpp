#include<fstream>
using namespace std;
extern fstream fout;

#include"Evaluate.h"

const int dir[4][2] = { {1,0},{0,1},{1,1},{1,-1} };	//×ÝÏò ºáÏò ÓÒÐ± ×óÐ±
const int liveScore[5] = { VALUE_L1,VALUE_L2,VALUE_L3,VALUE_L4,VALUE_MAX };
const int withScore[5] = { VALUE_W1,VALUE_W2,VALUE_W3,VALUE_W4,VALUE_W4 };
const int deathScore[5] = { VALUE_D1,VALUE_D2,VALUE_D3,VALUE_D4,VALUE_D4 };

int score;
int countChess;
bool leftLive, rightLive;
bool leftDeath, rightDeath;

int returnScore() {
	countChess = countChess >= 4 ? 4 : countChess;
	if (!leftDeath&!rightDeath)
		return leftLive&rightLive ? liveScore[countChess] : withScore[countChess];
	else if (leftDeath&rightDeath)
		if (countChess < 3)
			return deathScore[countChess];
		else
			return leftLive&rightLive ? liveScore[countChess] : deathScore[countChess];
	else
		if (leftLive&rightLive)
			return liveScore[countChess];
		else
			return withScore[countChess];
	return 0;
}

int getStepScore(const STEP&step, SIDE side) {
	/*fout << (side == WHITECHESS ? " °× " : " ºÚ ") << "¡¾" << step.row - TOP + 1 << "," << step.col - LEFT + 1 << "¡¿" << " ÅÐ¶ÏÆåÐÎ£º" << endl;
	int left = step.col - 5;
	int right = step.col + 5;
	int top = step.row - 5;
	int down = step.row + 5;
	for (int i = top; i <= down; ++i) {
		for (int j = left; j <= right; ++j)
			if (i == step.row&&j == step.col)
				fout << " 5";
			else
				fout << " " << chess[i][j];
		fout << endl;
	}*/

	score = 0;
	int row, col, emptyLeave;
	for (int i = 0; i < 4; ++i) {
		countChess = 0; emptyLeave = 2;
		for (row = step.row, col = step.col; emptyLeave;) {
			row += dir[i][0];
			col += dir[i][1];
			if (chess[row][col] == EMPTY)
				--emptyLeave;
			else if (chess[row][col] == side)
				++countChess;
			else
				break;
		}
		leftDeath = !(chess[row][col] == EMPTY);
		leftLive = chess[row - dir[i][0]][col - dir[i][1]] == EMPTY;

		emptyLeave = 2;
		for (row = step.row, col = step.col; emptyLeave;) {
			row -= dir[i][0];
			col -= dir[i][1];
			if (chess[row][col] == EMPTY)
				--emptyLeave;
			else if (chess[row][col] == side)
				++countChess;
			else
				break;
		}
		rightDeath = !(chess[row][col] == EMPTY);
		rightLive = chess[row + dir[i][0]][col + dir[i][1]] == EMPTY;

		/*int debugValue;
		fout << "leftLive   " << leftLive << " leftDeath  " << leftDeath << endl
			<< "rightLive  " << rightLive << " rightDeath " << rightDeath << endl
			<< "countChess " << countChess << endl
			<< "·½Ïò " << i << " µÃ·Ö " << (debugValue = returnScore()) << endl;
		score += debugValue;*/
		score += returnScore();
	}
	return score;
}

int getStepScore(const STEP& step) {
	return getStepScore(step, BLACKCHESS) + getStepScore(step, WHITECHESS);
}

bool isWin(const STEP step, SIDE side) {
	return getStepScore(step, side) >= VALUE_MAX;
}