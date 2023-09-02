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
// Push 函数相关常量
#define NODE	0		// 代表删除的是结点
#define LINE	-1		// 删除的是一列 其余正数代表行
#define SECRETNUM	-0x905820
typedef int ElemType;
typedef int Status;

typedef struct node {
	ElemType value;		//暂时不区分 正负  同时绝对值也是纵坐标
	int cls_idx;		// 所属子句的下标
	struct node* prev, * next;
	struct node* front, * rear;
}Node;								// 普通的值结点


typedef struct cnode {
	int row_value_n{ 0 };			// 句子中的变量数
	Node* first_elem_r{ nullptr };		// 第一个元素  无该元素的头节点
	struct cnode* prev, * next;		// 头节点的双向链表
}CNode;			// 横向的头结点


typedef struct lnode {
	int line_value_n;			// 一列数量
	Node* first_elem_l;		// 第一个元素
	struct lnode* prev, * next;		// 双向链表
	bool is_positive{ 0 };
}LNode;

typedef CNode** Cset;
typedef LNode** Lset;

typedef struct cnf{
	Cset clause_set;			// 支持随机访问的指针数组
	Lset literal_set;

	CNode* first_clause_head{ nullptr };
	LNode* first_literal_head{ nullptr };

	int cls_num, ltr_num;		//用于判空之类的
}CNF;	

typedef struct snode {
	//int val_idx{ 0 };		// 似乎不用
	int cls_idx{ 0 };			// 0 代表删除的是结点 非零就是对应的删除的句子序号 目前只有这两个有用 -1 代表是一次标记
	Node* pos;		// 记录删除的结点的指针 便于回溯 似乎一个就可以完成 上下左右前后
	CNode* clause_del;		// 记录删除的句子的指针
	LNode* line_del;
	int is_positive;
	struct snode* next;			/// 这个还是有用的

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

/* 从cnf文件读取到并建立数据结构 */
void CNF_EXACTER(CNF& cnf);
void UnitPropgate(CNF& cnf, Stack& history);
void PureLiteralAssign(CNF& cnf, Stack& history);
void revert(CNF&cnf,Stack& history);					// 回溯的函数
Status set_is_empty(const CNF& cnf);
Status clause_is_empty(const CNF& cnf);
int ChooseBetterValue(const CNF& cnf);
void AddUnitClause(CNF& cnf, int val);
Status DPLL(CNF& cnf,Stack&history);

#endif // !UTILITY_H_

