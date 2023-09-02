//#define _CRT_SECURE_NO_WARNINGS
//#include"Utility.hpp"
//
//inline void check_right_flow(FILE* f)
//{
//	if (!f)
//		exit(EXIT_FAILURE);
//}
//inline void featline(FILE* f)
//{
//	while (fgetc(f) != '0')
//		continue;
//}
//
//void CNF_EXACTER(CNF& cnf,char filename[])
//{
//	FILE* infile = fopen(filename, "r");
//	check_right_flow(infile);
//
//	while (fgetc(infile) == 'c')
//		featline(infile);
//	if (fgetc(infile) == 'p')
//	{
//		char s[5];
//		fscanf(infile, "%s%d%d", s, &cnf.ltr_num, &cnf.cls_num); featline(infile);				// 读入对应的数量
//		cnf.clause_set = (Cset)malloc(sizeof(CNode*) * (cnf.cls_num + 1));
//		cnf.literal_set = (Lset)malloc(sizeof(LNode*) * (cnf.ltr_num + 1));
//		memset(cnf.clause_set, 0, sizeof(CNode*) * (cnf.cls_num + 1));
//		memset(cnf.literal_set, 0, sizeof(LNode*) * (cnf.ltr_num + 1));
//		int val{ 0 };
//
//		for (int i = 1; i <= cnf.cls_num; ++i)
//		{
//			CNode* new_clause = (CNode*)malloc(sizeof(CNode));
//			cnf.clause_set[i] = new_clause;
//
//			if (i == 1)
//				cnf.first_clause_head=new_clause->prev = new_clause->next = new_clause;
//			else
//			{
//				cnf.clause_set[1]->prev = new_clause;
//				cnf.clause_set[i - 1]->next = new_clause;
//				new_clause->prev = cnf.clause_set[i - 1];
//				new_clause->next = cnf.clause_set[1];
//			}
//
//			while (scanf("%d", &val) && val)
//			{
//				Node* pnew = (Node*)malloc(sizeof(Node));			// 分配一个新的结点
//				if (!new_clause->row_value_n) {			// 当是第一个自变量时
//					pnew->next = pnew->prev = pnew;
//					new_clause->first_elem_r = pnew;
//				}
//				else {
//					new_clause->first_elem_r->prev->next = pnew;
//					pnew->prev = new_clause->first_elem_r->prev;
//					pnew->next = new_clause->first_elem_r;
//					new_clause->first_elem_r->prev = pnew;
//				}
//				pnew->value = val;
//				pnew->cls_idx = i;
//				++new_clause->row_value_n;			// 增加字面量数的统计
//				if (!cnf.literal_set[abs(val)])
//				{
//					LNode* new_line = (LNode*)malloc(sizeof(LNode));
//					if (!cnf.first_literal_head)
//					{
//						new_line->prev = new_line->next = new_line;
//						cnf.first_literal_head = new_line;
//					}
//					else		// 还没有任何的指针
//					{
//						new_line->next = cnf.first_literal_head;
//						new_line->prev = cnf.first_literal_head->prev;
//						cnf.first_literal_head->prev->next = new_line;
//						cnf.first_literal_head->prev = new_line;
//					}
//					// 还没有任何的指针
//					cnf.literal_set[abs(val)] = new_line;
//					new_line->first_elem_l = pnew;
//					pnew->front = pnew->rear = pnew;
//				}
//				else
//				{
//					cnf.literal_set[abs(val)]->first_elem_l->front->rear = pnew;
//					pnew->front = cnf.literal_set[abs(val)]->first_elem_l->front;
//					pnew->rear = cnf.literal_set[abs(val)]->first_elem_l;
//					cnf.literal_set[abs(val)]->first_elem_l->front = pnew;
//					cnf.literal_set[abs(val)]->first_elem_l = pnew;
//				}
//				++cnf.literal_set[abs(val)]->line_value_n;
//			}
//			//featline(infile);
//		}
//	}
//	else
//		exit(EXIT_FAILURE);
//}
//
//void push(Stack& s, Node* n,CNode*cls,LNode*ltr=nullptr ,int idx = 0)
//{
//	Snode* newp = (Snode*)malloc(sizeof(Snode));
//	newp->clause_del = cls;
//	newp->pos = n;
//	newp->cls_idx = idx;
//	newp->next = s;
//	s = newp;
//}
//
//Status pop(Stack& s)
//{
//	if (s->cls_idx == 0)
//	{
//
//	}
//	if (s->cls_idx > 0)
//	{
//
//	}
//	return 0;
//}
//
//
//
//void delnode(CNF& cnf, Node* cur, Stack& history)
//{
//	push(history, cur,nullptr);					// 先进行回溯			就可以保证不改了
//	if (cur->next == cur)				// 只用一个元素
//	{
//		cnf.clause_set[cur->cls_idx]->first_elem_r = nullptr;
//	}
//	else
//	{
//		cur->prev->next = cur->next;
//		cur->next->prev = cur->prev;
//		if (cnf.clause_set[cur->cls_idx]->first_elem_r == cur)
//			cnf.clause_set[cur->cls_idx]->first_elem_r = cur->next;			// 保证指向始终有效
//	}
//	if (cur->rear == cur)
//	{
//		if (cur->value > 0)
//			cnf.literal_set[abs(cur->value)]->is_positive = 1;
//		else
//			cnf.literal_set[abs(cur->value)]->is_positive = 0;
//
//		cnf.literal_set[abs(cur->value)]->first_elem_l = nullptr;
//	}
//	else
//	{
//		cur->rear->front = cur->front;
//		cur->front->rear = cur->rear;
//		if (cnf.literal_set[abs(cur->value)]->first_elem_l == cur)
//			cnf.literal_set[abs(cur->value)]->first_elem_l = cur->rear;
//	}
//
//	--cnf.clause_set[cur->cls_idx]->row_value_n;
//	--cnf.literal_set[abs(cur->value)]->line_value_n;
//}
//
//
//void delclause(CNF& cnf,Node*cur,Stack& history)
//{
//	push(history, nullptr, cnf.clause_set[cur->cls_idx], nullptr,cur->cls_idx);				// 先进行push 这样才不改变
//	for (Node* scan = cur; cur->next != cur; cur = cur->next)
//		delnode(cnf, scan, history);
//	delnode(cnf, cur, history);
//	// 还需要回收句子
//	
//	if (cnf.clause_set[cur->cls_idx]->next == cnf.clause_set[cur->cls_idx])
//	{
//		cnf.cls_num = 0;
//		return;
//	}
//	else
//	{
//		cnf.clause_set[cur->cls_idx]->next->prev = cnf.clause_set[cur->cls_idx]->prev;
//		cnf.clause_set[cur->cls_idx]->prev->next = cnf.clause_set[cur->cls_idx]->next;
//	}
//
//	cnf.cls_num--;
//	cnf.clause_set[cur->cls_idx] = nullptr;
//}
//
//
//void UnitProgate(CNF& cnf, Stack& history)
//{
//	int flag{ 0 };
//	if (cnf.cls_num== 1)
//		flag = 1;
//	for (CNode* scan = cnf.first_clause_head; flag || scan->next != scan; scan = scan->next)
//	{
//		flag = 0;						// 标记不再起作用
//		if (scan->row_value_n == 1)
//		{
//			Node* key = scan->first_elem_r;			// 拿到关键的结点
//			for (Node*cur=key;cur->next!=cur;cur=cur->next)				// 先要进行上下遍历
//			{
//				if (cur->value == key->value)
//					delclause(cnf, cur, history);
//				else if (cur->value + key->value == 0)
//				{
//					delnode(cnf, cur, history);
//				}
//			}
//		}
//	}
//}
//
//// 目前看起来似乎不用 删除整个列 
//void delline(CNF& cnf, LNode*& cur, Stack& history)
//{
//	push(history, nullptr, nullptr, cur, LINE);
//	if (cur->next == cur)
//	{
//		cnf.cls_num = 0;
//		return;
//	}
//	else
//	{
//		cur->next->prev = cur->prev;
//		cur->prev->next = cur->next;
//	}
//
//	cur = nullptr;				// 因为这里传的是引用
//	--cnf.ltr_num;
//}
//
//
//void set_value(CNF&cnf,LNode*cur,Stack&history)			// 赋值
//{
//
//
//}
//
//void PureLiteralAssign(CNF& cnf, Stack& history)
//{
//	int flag{ 0 };
//	if (cnf.ltr_num == 1)
//		flag = 1;
//	for (LNode* scan = cnf.first_literal_head; flag || scan->next != scan; scan = scan->next)
//	{
//		if (scan->line_value_n == 1)
//		{
//			delclause(cnf, scan->first_elem_l, history);
//			delline(cnf, scan,history);												// 就是赋值并且删除
//		}
//	}
//}
//
//void revert(Stack& history)					// 回溯的函数
//{
//
//}
//inline Status set_is_empty(const CNF& cnf)
//{
//	return cnf.cls_num == 0;
//}
//
//Status clause_is_empty(const CNF& cnf)
//{
//	for (CNode* scan = cnf.first_clause_head; scan->next != cnf.first_clause_head; scan = scan->next)
//		if (!scan->row_value_n)
//			return OK;
//	return cnf.first_clause_head->row_value_n == 0;
//}
//
//int ChooseBetterValue(const CNF& cnf)
//{
//	
//}
//
//
//Status DPLL(CNF& cnf)
//{
//	static Stack history;
//	UnitPropgate(cnf, history);
//	PureLiteralAssign(cnf, history);
//
//	if (set_is_empty(cnf))
//		return SATISFIED;
//	if (clause_is_empty(cnf))
//		return DISATISFIED;
//
//	int lucky_num = ChooseBetterValue(cnf);
//	//AddUnitClause(cnf, lucky_num);
//	if (DPLL(cnf))
//		return SATISFIED;
//	else
//	{
//		//AddUnitClause(cnf, -lucky_num);
//		return DPLL(cnf);
//	}
//}
//
//
////int main(void)
////{
////	int *p = (int*)malloc(sizeof(int) * 10);
////	memset(p, 0, sizeof(p));
////
////	printf("%d", *(p + 7));
////
////	return 0;
////}
