#ifndef EVALUATE_H
#define EVALUATE_H

#include"Global.h"
/* 棋形分数 */

#define INF 0x3f3f3f3f
#define VALUE_MAX	1000000		//长连/成五 获胜

#define VALUE_L4	8000		//活四
#define VALUE_W4	7000		//冲四
#define VALUE_D4    20			//死四

#define VALUE_L3	6000		//活三
#define VALUE_W3	3000		//冲三
#define VALUE_D3    15			//死三

#define VALUE_L2	500 		//活二
#define VALUE_W2	200 		//冲二
#define VALUE_D2    10			//死二

#define VALUE_L1	100 		//活一
#define VALUE_W1	50 			//冲一
#define VALUE_D1    0			//死一

#define ADDSCORE	500

int getStepScore(const STEP& step, SIDE side);
int evaluateWholeChess(SIDE side);
int evaluateExtend(const STEP&step);
int evaluateExtend(const STEP&step, SIDE side);

bool isWin(const STEP step, SIDE side);

#endif