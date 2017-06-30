#ifndef AI_H
#define AI_H

#include"Global.h"
#include<vector>

#define MAX_DEPTH 6			//最大搜索深度
#define MAX_EXTEND 7		//每一步棋最大扩展范围
#define MAX_SEARCH_STEP 10	//每一步棋最大搜索步数

//AI下棋接口
void AISearch(SIDE aiSide, STEP&step, STEP &nextStep);

//α-β剪枝算法
int alphaBetaSearch(SIDE side, STEP step, int depth, int alpha, int beta);

//扩展下一步棋的位置
void extendNextStep(SIDE side, const STEP &curStep, vector<pair<STEP, int>>&nextStep);

#endif