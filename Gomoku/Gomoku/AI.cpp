#include<vector>
#include<algorithm>
#include<fstream>
#include<iomanip>
using namespace std;

#include "Global.h"
#include "Evaluate.h"
#include "AI.h"

fstream fout("search.txt", ios::out);

STEP bestStep;
SIDE AIside;

void AISearch(SIDE side, STEP&step, STEP &nextStep) {
	AIside = side;
	alphaBetaSearch(side, step, 0, -INF, INF, 0);
	nextStep = bestStep;

	//fout << endl << "#########    AI搜索结果    ##########" << endl;
	//fout << "bestStep 【 row,col 】 = 【 " << bestStep.row - TOP + 1 << "," << bestStep.row - LEFT + 1 << " 】" << endl;
}

int alphaBetaSearch(SIDE side, const STEP&step, int depth, int alpha, int beta, int iterValue) {
	if (depth >= MAX_DEPTH) {
//		return -iterValue;
		int tem =evaluateWholeChess(side);
		//fout << "叶子节点  whole=" << tem << endl;
		return tem;
	}

	int debug = getStepScore(step, side);
	/*fout << endl << endl << "深度：" << depth << (side == WHITECHESS ? " 白 " : " 黑 ")
		<< endl << " 位置【" << step.row - TOP + 1 << "," << step.col - LEFT + 1 << "】" << " 分：" << debug << endl;*/

	SIDE otherSide = side == WHITECHESS ? BLACKCHESS : WHITECHESS;
	if (isWin(step, otherSide))
		return -VALUE_MAX;

	/*if (getStepScore(step) >= VALUE_MAX)
		return -VALUE_MAX;*/


	vector<pair<STEP, int>>nextStep;
	extendNextStep(side, step, nextStep);
	int trySize = min((int)nextStep.size(), MAX_SEARCH_STEP);

	for (int i = 0; i < trySize; ++i) {
		STEP &nstep = nextStep[i].first;
		chess[nstep.row][nstep.col] = side;

		int ivalue = iterValue + (side == AIside ? nextStep[i].second : -nextStep[i].second);
		int value = -alphaBetaSearch(otherSide, nstep, depth + 1, -beta, -alpha, ivalue);

		/*fout << "【" << setw(2) << nstep.row - TOP + 1 << "," << setw(2) << nstep.col - LEFT + 1 << "】 得分" << setw(5) << nextStep[i].second << endl;
		fout << "i=" << i << " ivalue=" << ivalue << " value=" << value << endl;*/

		chess[nstep.row][nstep.col] = EMPTY;
		if (value >= beta)
			return value;
		if (value > alpha) {
			alpha = value;
			//fout << "alpha=" << alpha << endl;
			if (!depth)
				bestStep = nstep;
		}
	}

	//fout << endl << "深度：" << depth << (side == WHITECHESS ? " 白 " : " 黑 ") << " 位置【" << step.row - TOP + 1 << "," << step.col - LEFT + 1 << "】" << " 返回：" << alpha << endl;
	return alpha;
}

bool myPairCmp(const pair<STEP, int>&p1, const pair<STEP, int>&p2) {
	return p1.second > p2.second;
}

void extendNextStep(SIDE side, const STEP &curStep, vector<pair<STEP, int>>&nextStep) {
	int left = max(curStep.col - MAX_EXTEND, LEFT);
	int right = min(curStep.col + MAX_EXTEND, RIGHT);
	int top = max(curStep.row - MAX_EXTEND, TOP);
	int down = min(curStep.row + MAX_EXTEND, DOWN);
	for (int i = top; i <= down; ++i)
		for (int j = left; j <= right; ++j)
			if (chess[i][j] == EMPTY) {
				STEP temStep(i, j);
				nextStep.push_back({ temStep,evaluateExtend(temStep,side) });
			}
	//可适当考虑其它位置
	sort(nextStep.begin(), nextStep.end(), myPairCmp);

	/*int i = 0;
	for (auto &a : nextStep) {
		fout << "【" << setw(2) << a.first.row - TOP + 1 << "," << setw(2) << a.first.col - LEFT + 1 << "】 得分" << setw(5) << a.second;
		if (++i % 5 == 0)
			fout << endl;
	}*/
}