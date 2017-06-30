#ifndef AI_H
#define AI_H

#include"Global.h"
#include<vector>

#define MAX_DEPTH 7
#define MAX_EXTEND 5
#define MAX_SEARCH_STEP 10

void AISearch(SIDE side, STEP&step, STEP &nextStep);

int alphaBetaSearch(SIDE side, const STEP&step, int depth, int alpha, int beta, int iterValue);

void extendNextStep(SIDE side, const STEP &curStep, vector<pair<STEP, int>>&nextStep);

#endif