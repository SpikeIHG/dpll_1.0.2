#pragma once
#ifndef UTILITY_H_
#define UTILITY_H_

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<algorithm>

#define SATISFIED	1
#define DISATISFIED	0
#define OK	1
#define BAD	0

#define MAXLEN	100
// Push ������س���
#define NODE	0		// ����ɾ�����ǽ��
#define LINE	-1		// ɾ������һ�� ��������������
#define SECRETNUM	-0x905820
typedef int ElemType;
typedef int Status;

typedef struct node {
	ElemType value;		//��ʱ������ ����  ͬʱ����ֵҲ��������
	int cls_idx;		// �����Ӿ���±�
	struct node* prev, * next;
	struct node* front, * rear;
}Node;								// ��ͨ��ֵ���


typedef struct cnode {
	int row_value_n{ 0 };			// �����еı�����
	Node* first_elem_r{ nullptr };		// ��һ��Ԫ��  �޸�Ԫ�ص�ͷ�ڵ�
	struct cnode* prev, * next;		// ͷ�ڵ��˫������
}CNode;			// �����ͷ���


typedef struct lnode {
	int line_value_n;			// һ������
	Node* first_elem_l;		// ��һ��Ԫ��
	struct lnode* prev, * next;		// ˫������
	bool is_positive{ 0 };
}LNode;

typedef CNode** Cset;
typedef LNode** Lset;

typedef struct cnf{
	Cset clause_set;			// ֧��������ʵ�ָ������
	Lset literal_set;

	CNode* first_clause_head{ nullptr };
	LNode* first_literal_head{ nullptr };

	int cls_num, ltr_num;		//�����п�֮���
}CNF;	

typedef struct snode {
	//int val_idx{ 0 };		// �ƺ�����
	int cls_idx{ 0 };			// 0 ����ɾ�����ǽ�� ������Ƕ�Ӧ��ɾ���ľ������ Ŀǰֻ������������ -1 ������һ�α��
	Node* pos;		// ��¼ɾ���Ľ���ָ�� ���ڻ��� �ƺ�һ���Ϳ������ ��������ǰ��
	CNode* clause_del;		// ��¼ɾ���ľ��ӵ�ָ��
	LNode* line_del;
	int is_positive;
	struct snode* next;			/// ����������õ�

}Snode, * Stack;

//Status pop(Stack&s)
//{
//	if (s)
//	{
//		struct snode* dell = s;
//		s = s->next;
//		free(dell);
//	}
//	return 1;
//}

/* ��cnf�ļ���ȡ�����������ݽṹ */
void CNF_EXACTER(CNF& cnf);
void UnitPropgate(CNF& cnf, Stack& history);
void PureLiteralAssign(CNF& cnf, Stack& history);
void revert(CNF&cnf,Stack& history);					// ���ݵĺ���
Status set_is_empty(const CNF& cnf);
Status clause_is_empty(const CNF& cnf);
int ChooseBetterValue(const CNF& cnf);
void AddUnitClause(CNF& cnf, int val);
Status DPLL(CNF& cnf,Stack&history);

#endif // !UTILITY_H_

