#include<vector>
#include<algorithm>
#include<iomanip>
using namespace std;

#include "Global.h"
#include "Evaluate.h"
#include "AI.h"

STEP bestStep;
SIDE AIside;

//AI下棋接口
void AISearch(SIDE aiSide, STEP&step, STEP &nextStep) {
	AIside = aiSide;
	alphaBetaSearch(aiSide, step, 0, -INF, INF);
	nextStep = bestStep;
}

//α-β剪枝算法
int alphaBetaSearch(SIDE side, STEP step, int depth, int alpha, int beta) {
	if (depth >= MAX_DEPTH)
		return evaluateWholeChess(side);

	SIDE otherSide = side == WHITECHESS ? BLACKCHESS : WHITECHESS;
	if (isWin(step, otherSide))
		return -VALUE_MAX;

	vector<pair<STEP, int>>nextStep;
	extendNextStep(side, step, nextStep);
	int trySize = min((int)nextStep.size(), MAX_SEARCH_STEP);

	int value, flag = 0;
	for (int i = 0; i < trySize; ++i) {
		pair<STEP, int>&nspair = nextStep[i];
		STEP &nstep = nextStep[i].first;
		chess[nstep.row][nstep.col] = side;

		if (nspair.second >= VALUE_L4) {
			if (!depth) {
				bestStep = nstep;
				chess[nstep.row][nstep.col] = EMPTY;
				return alpha;
			}
			flag = 1;
		}
		if (!flag || nspair.second >= VALUE_L4)
			value = -alphaBetaSearch(otherSide, nstep, depth + 1, -beta, -alpha);

		chess[nstep.row][nstep.col] = EMPTY;
		if (value >= beta)
			return value;
		if (value > alpha) {
			alpha = value;
			if (!depth)
				bestStep = nstep;
			if (alpha >= VALUE_MAX)
				return alpha;
		}
	}

	return alpha;
}

//定义排序顺序
bool myPairCmp(const pair<STEP, int>&p1, const pair<STEP, int>&p2) {
	return p1.second > p2.second;
}

//扩展下一步棋的位置
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
	sort(nextStep.begin(), nextStep.end(), myPairCmp);
}