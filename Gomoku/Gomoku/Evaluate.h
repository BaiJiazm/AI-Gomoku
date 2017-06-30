#ifndef EVALUATE_H
#define EVALUATE_H

#include"Global.h"
/* ���η��� */

#define INF 0x3f3f3f3f
#define VALUE_MAX	1000000		//����/���� ��ʤ

#define VALUE_L4	8000		//����
#define VALUE_W4	7000		//����
#define VALUE_D4    20			//����

#define VALUE_L3	6000		//����
#define VALUE_W3	3000		//����
#define VALUE_D3    15			//����

#define VALUE_L2	500 		//���
#define VALUE_W2	200 		//���
#define VALUE_D2    10			//����

#define VALUE_L1	100 		//��һ
#define VALUE_W1	50 			//��һ
#define VALUE_D1    0			//��һ

#define ADDSCORE	500

int getStepScore(const STEP& step, SIDE side);
int evaluateWholeChess(SIDE side);
int evaluateExtend(const STEP&step);
int evaluateExtend(const STEP&step, SIDE side);

bool isWin(const STEP step, SIDE side);

#endif