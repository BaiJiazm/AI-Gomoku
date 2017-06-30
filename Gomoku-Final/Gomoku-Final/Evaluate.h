//Evaluate.h

#ifndef EVALUATE_H
#define EVALUATE_H

#include"Global.h"
// ���η��� 

#define INF 0x3f3f3f3f
#define VALUE_MAX	10000000	//����/���� ��ʤ

#define VALUE_L4	150000		//����
#define VALUE_W4	7500		//����
#define VALUE_D4    20			//����

#define VALUE_L3	7500		//����
#define VALUE_W3	2000		//����
#define VALUE_D3    10			//����

#define VALUE_L2	1000 		//���
#define VALUE_W2	200 		//���
#define VALUE_D2    5			//����

#define VALUE_L1	100 		//��һ
#define VALUE_W1	50 			//��һ
#define VALUE_D1    0			//��һ

#define ADDSCORE	500

//���㷵��ĳ������Ĺ���
int returnScore();

//������λ�õ��ĸ��������
int getSideScore(const STEP&step, SIDE side);

//�Ե�ǰ״̬�������̹���
int evaluateWholeChess(SIDE side);

//����λ�õ�����ֵ���Ż�����
int evaluateExtend(const STEP&step, SIDE side);

//�ж�ĳһ���Ƿ�ȡʤ
bool isWin(const STEP step, SIDE side);

#endif