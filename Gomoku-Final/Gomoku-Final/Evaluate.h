//Evaluate.h

#ifndef EVALUATE_H
#define EVALUATE_H

#include"Global.h"
// 棋形分数 

#define INF 0x3f3f3f3f
#define VALUE_MAX	10000000	//长连/成五 获胜

#define VALUE_L4	150000		//活四
#define VALUE_W4	7500		//冲四
#define VALUE_D4    20			//死四

#define VALUE_L3	7500		//活三
#define VALUE_W3	2000		//冲三
#define VALUE_D3    10			//死三

#define VALUE_L2	1000 		//活二
#define VALUE_W2	200 		//冲二
#define VALUE_D2    5			//死二

#define VALUE_L1	100 		//活一
#define VALUE_W1	50 			//冲一
#define VALUE_D1    0			//死一

#define ADDSCORE	500

//计算返回某个方向的估分
int returnScore();

//对下棋位置的四个方向估分
int getSideScore(const STEP&step, SIDE side);

//对当前状态整个棋盘估分
int evaluateWholeChess(SIDE side);

//计算位置的启发值，优化搜索
int evaluateExtend(const STEP&step, SIDE side);

//判断某一方是否取胜
bool isWin(const STEP step, SIDE side);

#endif