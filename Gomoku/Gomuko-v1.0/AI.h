#ifndef AI_H
#define AI_H

#include"Global.h"
#include<vector>

#define MAX_DEPTH 6			//����������
#define MAX_EXTEND 7		//ÿһ���������չ��Χ
#define MAX_SEARCH_STEP 10	//ÿһ���������������

//AI����ӿ�
void AISearch(SIDE aiSide, STEP&step, STEP &nextStep);

//��-�¼�֦�㷨
int alphaBetaSearch(SIDE side, STEP step, int depth, int alpha, int beta);

//��չ��һ�����λ��
void extendNextStep(SIDE side, const STEP &curStep, vector<pair<STEP, int>>&nextStep);

#endif