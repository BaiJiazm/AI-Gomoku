#include<fstream>
#include<algorithm>
using namespace std;
extern fstream fout;

#include"Evaluate.h"

const int dir[4][2] = { {-1,0},{0,-1},{-1,-1},{-1,1} };	// |  -  \  /
const int live[6] = { 0,VALUE_L1,VALUE_L2,VALUE_L3,VALUE_L4,VALUE_MAX };
const int with[6] = { 0,VALUE_W1,VALUE_W2,VALUE_W3,VALUE_W4,VALUE_W4 };
const int death[6] = { 0, VALUE_D1,VALUE_D2,VALUE_D3,VALUE_D4,VALUE_D4 };

int score;
int cmid, cleft, cright, cnt, leftmid, midright;
int left1, left2, right1, right2;
int flag;

int returnScore() {
	cmid = min(cmid + 1, 5);
	if (cmid == 5)
		return VALUE_MAX;
	cnt = min(cmid + cleft + cright, 5);
	leftmid = min(cleft + cmid, 5);
	midright = min(cmid + cright, 5);
	flag = left2 << 3 | left1 << 2 | right1 << 1 | right2;

	switch (flag) {
	case 0b0000:
		return live[cnt];
	case 0b0001:
	case 0b1000:
		return max(live[leftmid], with[cnt]);
	case 0b0010:
	case 0b0011:
		return with[leftmid];
	case 0b0100:
	case 0b1100:
		return with[midright];
	case 0b0101:
	case 0b1101:
		return midright >= 4 ? with[midright] : death[midright];
	case 0b1010:
	case 0b1011:
		return leftmid >= 4 ? with[leftmid] : death[leftmid];
	case 0b0110:
	case 0b0111:
	case 0b1110:
	case 0b1111:
		return death[cmid];
	case 0b1001:
		return cnt >= 4 ? max(live[cmid], with[cnt]) : death[cnt];
	}
	return 0;
}

int getSideScore(const STEP&step, SIDE side) {
	score = 0;
	int row, col, i;
	for (i = 0; i < 4; ++i) {
		cmid = cleft = cright = 0;
		left1 = left2 = right1 = right2 = 0;

		for (row = step.row + dir[i][0], col = step.col + dir[i][1]; chess[row][col] == side; ++cmid) {
			row += dir[i][0];
			col += dir[i][1];
		}
		left1 = chess[row][col] != EMPTY;
		if (left1) {
			for (row += dir[i][0], col += dir[i][1]; chess[row][col] == side; ++cleft) {
				row += dir[i][0];
				col += dir[i][1];
			}
			left2 = chess[row][col] != EMPTY;
		}

		for (row = step.row - dir[i][0], col = step.col - dir[i][1]; chess[row][col] == side; ++cmid) {
			row -= dir[i][0];
			col -= dir[i][1];
		}
		right1 = chess[row][col] != EMPTY;
		if (right1) {
			for (row -= dir[i][0], col -= dir[i][1]; chess[row][col] == side; ++cright) {
				row -= dir[i][0];
				col -= dir[i][1];
			}
			right2 = chess[row][col] != EMPTY;
		}

		/*fout << (!left2 ? 0 : 2);
		for (int t = 0; t < cleft; ++t)
			fout << 1;
		fout << (!left1 ? 0 : 2);
		for (int t = 0; t < cmid + 1; ++t)
			fout << 1;
		fout << (!right1 ? 0 : 2);
		for (int t = 0; t < cright; ++t)
			fout << 1;
		fout << (!right2 ? 0 : 2);

		int debugValue = returnScore();
		fout << " score" << debugValue << endl;
		score += debugValue;*/

		score += returnScore();
	}
	return score;
}

int getStepScore(const STEP& step, SIDE side) {
	int stepValue = getSideScore(step, BLACKCHESS) - getSideScore(step, WHITECHESS);
	return side == BLACKCHESS ? stepValue : -stepValue;
}

int evaluateWholeChess(SIDE side) {
	int returnValue = 0;
	for (int i = TOP; i <= DOWN; ++i)
		for (int j = LEFT; j <= RIGHT; ++j)
			if (chess[i][j] == side)
				returnValue += getSideScore(STEP(i, j), side);
			else if (chess[i][j] != EMPTY)
				returnValue -= getSideScore(STEP(i, j), (SIDE)chess[i][j]);
	return returnValue;
}

int evaluateExtend(const STEP&step, SIDE side) {
	return max(getSideScore(step, BLACKCHESS) + (side == BLACKCHESS ? 0 : ADDSCORE), getSideScore(step, WHITECHESS) + (side == WHITECHESS ? 0 : ADDSCORE));
}

bool isWin(const STEP step, SIDE side) {
	return getSideScore(step, side) >= VALUE_MAX;
}