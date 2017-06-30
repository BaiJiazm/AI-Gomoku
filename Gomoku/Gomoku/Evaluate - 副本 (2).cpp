#include<fstream>
#include<algorithm>
using namespace std;
extern fstream fout;

#include"Evaluate.h"

const int dir[4][2] = { {-1,0},{0,-1},{-1,-1},{1,-1} };	// |  -  \  /
const int liveScore[6] = { 0,VALUE_L1,VALUE_L2,VALUE_L3,VALUE_L4,VALUE_MAX };
const int withScore[6] = { 0,VALUE_W1,VALUE_W2,VALUE_W3,VALUE_W4,VALUE_W4 };
const int deathScore[6] = { 0, VALUE_D1,VALUE_D2,VALUE_D3,VALUE_D4,VALUE_D4 };

int score;
int cmid, cleft, cright;
bool left1, left2, right1, right2;

int returnScore() {
	cmid = min(cmid + 1, 5);
	int cnt = min(cmid + cleft + cright, 5);
	if (cmid == 5)
		return VALUE_MAX;
	if (left1&right1) {
		if (cmid >= 4)
			return liveScore[cmid];
		else if (left2&right2)
			return cleft | cright ? withScore[cnt] : liveScore[cnt];
		else if (!left2&!right2)
			return cnt >= 4 ? withScore[cnt] : deathScore[cnt];
		else
			return cleft | cright ? withScore[cnt] : liveScore[cnt];
	}
	else if (!left1&!right1)
		return deathScore[cmid];
	else {
		if (cmid >= 4)
			return withScore[cmid];
		else if (left1&right2 | left2&right1)
			return cnt >= 4 ? withScore[cnt] : deathScore[cnt];
		else
			return withScore[cnt];
	}
	return 0;
}

int getStepScore(const STEP&step, SIDE side) {
	/*fout << endl << (side == WHITECHESS ? " °× " : " ºÚ ") << "¡¾" << step.row - TOP + 1 << "," << step.col - LEFT + 1 << "¡¿" << " ÅÐ¶ÏÆåÐÎ£º" << endl;
	int left = step.col - 5;
	int right = step.col + 5;
	int top = step.row - 5;
	int down = step.row + 5;
	for (int i = top; i <= down; ++i) {
		for (int j = left; j <= right; ++j)
			if (i == step.row&&j == step.col)
				fout << " *";
			else
				fout << " " << chess[i][j];
		fout << endl;
	}*/

	score = 0;
	int row, col, i;
	for (i = 0; i < 4; ++i) {
		cmid = cleft = cright = 0;
		left1 = left2 = right1 = right2 = true;

		for (row = step.row + dir[i][0], col = step.col + dir[i][1]; chess[row][col] == side; ++cmid) {
			row += dir[i][0];
			col += dir[i][1];
		}
		left1 = chess[row][col] == EMPTY;
		if (left1) {
			for (row += dir[i][0], col += dir[i][1]; chess[row][col] == side; ++cleft) {
				row += dir[i][0];
				col += dir[i][1];
			}
			left2 = chess[row][col] == EMPTY;
		}

		for (row = step.row - dir[i][0], col = step.col - dir[i][1]; chess[row][col] == side; ++cmid) {
			row -= dir[i][0];
			col -= dir[i][1];
		}
		right1 = chess[row][col] == EMPTY;
		if (right1) {
			for (row -= dir[i][0], col -= dir[i][1]; chess[row][col] == side; ++cright) {
				row -= dir[i][0];
				col -= dir[i][1];
			}
			right2 = chess[row][col] == EMPTY;
		}

		/*fout << endl << "·½Ïò£º" << i << endl;
		fout << "left2=" << left2 << " cleft=" << cleft << " left1=" << left1 << endl
			<< "cmid=" << cmid + 1 << endl
			<< "right1=" << right1 << " cright=" << cright << " right2=" << right2 << endl;*/
		fout << (left2 ? 0 : 2);
		for (int t = 0; t < cleft; ++t)
			fout << 1;
		fout << (left1 ? 0 : 2);
		for (int t = 0; t < cmid + 1; ++t)
			fout << 1;
		fout << (right1 ? 0 : 2);
		for (int t = 0; t < cright; ++t)
			fout << 1;
		fout << (right2 ? 0 : 2);

		int debugValue = returnScore();
		fout  << " score" << debugValue << endl;
		score += debugValue;
		
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