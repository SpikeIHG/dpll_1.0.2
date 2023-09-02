#include"Utility.hpp"
#define DEBUG
void traverse(const CNF& cnf)
{
	CNode* scan = cnf.first_clause_head;
	for (int i = 1; i <= cnf.cls_num; ++i, scan = scan->next)
	{
		Node* first_elem = scan->first_elem_r;
		printf("%d ", first_elem->value);
		for (Node* cur = first_elem->next; cur != first_elem; cur = cur->next)
			printf("%d ", cur->value);
		putchar('\n');
	}
}
void check_the_stack(const Stack& s)
{
	int idx{ 1 };
	Snode* step = s;
	while (step)
	{
		printf("第%d步操作：\t", idx);
		switch (step->cls_idx) {
		case NODE:
		{
			printf("删除结点，结点的值是%d,结点所属的句子序号是%d \n", step->pos->value, step->pos->cls_idx);
			break;
		}
		case LINE:
		{
			printf("删除的是一列数，被删除的数的值是%d\n", step->line_del->first_elem_l->value);
			break;
		}
		case SECRETNUM:
		{
			printf("这是一次分段点*********************************\n");
			break;
		}
		default:
		{
			printf("删除的是一个句子，句子的序号是%d,\n", step->cls_idx);
			break;
		}
		}
		++idx; step = step->next;
	}
}
void present_answer(const CNF& cnf,int n)
{
	for (int i = 1; i <= n; ++i)
		printf("变量%d 的取值是 %d \n", i, (cnf.literal_set[i]->is_positive ? i : -i));
}
inline void check_right_flow(FILE* f)
{
	if (!f)
		exit(EXIT_FAILURE);
}
inline void featline(FILE* f)
{
	char word[100];
	while (fscanf(f, "%s", word) && strcmp(word, "cnf"))
		continue;
}
int cmp(const void* a, const void* b)
{
	return (*(int*)b) - (*(int*)a);
}
void CNF_EXACTER(CNF& cnf, char filename[],int&n)
{
	FILE* infile = fopen(filename, "r");
	check_right_flow(infile);
	featline(infile);

	fscanf(infile, "%d%d", &cnf.ltr_num, &cnf.cls_num);			// 读入对应的数量
	n = cnf.ltr_num;
	cnf.clause_set = (Cset)malloc(sizeof(CNode*) * (cnf.cls_num + 1));
	cnf.literal_set = (Lset)malloc(sizeof(LNode*) * (cnf.ltr_num + 1));
	memset(cnf.clause_set, 0, sizeof(CNode*) * (cnf.cls_num + 1));
	memset(cnf.literal_set, 0, sizeof(LNode*) * (cnf.ltr_num + 1));
	int val{ 0 };

	for (int i = 1; i <= cnf.cls_num; ++i)
	{
		CNode* new_clause = (CNode*)malloc(sizeof(CNode));
		new_clause->first_elem_r = nullptr;
		new_clause->row_value_n = 0;
		cnf.clause_set[i] = new_clause;

		if (i == 1) {
			cnf.first_clause_head = new_clause->prev = new_clause->next = new_clause;
		}
		else
		{
			cnf.clause_set[1]->prev = new_clause;
			cnf.clause_set[i - 1]->next = new_clause;
			new_clause->prev = cnf.clause_set[i - 1];
			new_clause->next = cnf.clause_set[1];
		}

		while (fscanf(infile,"%d", &val) && val)
		{
			Node* pnew = (Node*)malloc(sizeof(Node));			// 分配一个新的结点
			if (!new_clause->row_value_n) {			// 当是第一个自变量时
				pnew->next = pnew->prev = pnew;
				new_clause->first_elem_r = pnew;
			}
			else {
				new_clause->first_elem_r->prev->next = pnew;
				pnew->prev = new_clause->first_elem_r->prev;
				pnew->next = new_clause->first_elem_r;
				new_clause->first_elem_r->prev = pnew;
			}
			pnew->value = val;
			pnew->cls_idx = i;
			++new_clause->row_value_n;			// 增加字面量数的统计
			if (!cnf.literal_set[abs(val)])
			{
				LNode* new_line = (LNode*)malloc(sizeof(LNode));
				new_line->is_positive = 0;
				new_line->line_value_n = 0;
				if (!cnf.first_literal_head)
				{
					new_line->prev = new_line->next = new_line;
					cnf.first_literal_head = new_line;
				}
				else		// 还没有任何的指针
				{
					new_line->next = cnf.first_literal_head;
					new_line->prev = cnf.first_literal_head->prev;
					cnf.first_literal_head->prev->next = new_line;
					cnf.first_literal_head->prev = new_line;
				}
				// 还没有任何的指针
				cnf.literal_set[abs(val)] = new_line;
				new_line->first_elem_l = pnew;
				pnew->front = pnew->rear = pnew;
			}
			else
			{
				cnf.literal_set[abs(val)]->first_elem_l->front->rear = pnew;
				pnew->front = cnf.literal_set[abs(val)]->first_elem_l->front;
				pnew->rear = cnf.literal_set[abs(val)]->first_elem_l;
				cnf.literal_set[abs(val)]->first_elem_l->front = pnew;
			}
			++cnf.literal_set[abs(val)]->line_value_n;
		}
	}
	fclose(infile);
}
inline void eatline(FILE*f)
{
	char word[100];
	while (fscanf(f, "%s", word) && strcmp(word, "cnf"))
		printf("%s", word);

}
void push(Stack& s, Node* n, CNode* cls, LNode* ltr, int idx,int neg=-1)
{
	Snode* newp = (Snode*)malloc(sizeof(Snode));
	newp->clause_del = cls;
	newp->pos = n;
	newp->cls_idx = idx;
	newp->next = s;
	newp->line_del = ltr;
	newp->is_positive = neg;
	s = newp;
}
inline void stamp(Stack& s)
{
	Snode* mark = (Snode*)malloc(sizeof(Snode));
	mark->clause_del = nullptr;
	mark->line_del = nullptr;
	mark->pos = nullptr;
	mark->cls_idx = SECRETNUM;
	mark->is_positive = -1;
	mark->next = s;
	s = mark;
}
inline Status set_is_empty(const CNF& cnf)
{
	return cnf.cls_num == 0;
}
Status clause_is_empty(const CNF& cnf)
{
	for (CNode* scan = cnf.first_clause_head->next; scan != cnf.first_clause_head; scan = scan->next)
		if (!scan->row_value_n)
		{
#ifdef DEBUG
			printf("\n%d是空的\n", scan->first_elem_r->cls_idx);
#endif // DEBUG

			return OK;
		}
	return cnf.first_clause_head->row_value_n == 0;
}
void delnode(CNF& cnf, Node* cur, Stack& history)
{
	push(history, cur, nullptr,nullptr,NODE);					// 先进行回溯			就可以保证不改了
	if (cur->next != cur) {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		if (cnf.clause_set[cur->cls_idx]->first_elem_r == cur)
			cnf.clause_set[cur->cls_idx]->first_elem_r = cur->next;			// 保证指向始终有效
	}
	if (cur->rear != cur) {
		cur->rear->front = cur->front;
		cur->front->rear = cur->rear;
		if (cnf.literal_set[abs(cur->value)]->first_elem_l == cur)
			cnf.literal_set[abs(cur->value)]->first_elem_l = cur->rear;
	}

	--cnf.clause_set[cur->cls_idx]->row_value_n;
	--cnf.literal_set[abs(cur->value)]->line_value_n;
}
void delclause(CNF& cnf, Node* cur, Stack& history)
{
	push(history, nullptr, cnf.clause_set[cur->cls_idx], nullptr, cur->cls_idx);				// 先进行push 这样才不改变
	for (Node* scan = cur->next; scan != cur; scan = scan->next)
		delnode(cnf, scan, history);
	delnode(cnf, cur, history);
#ifdef DEBUG
	if (cnf.clause_set[cur->cls_idx]->row_value_n) { printf("%BAD----------"); exit(0); }
#endif
	// 还需要回收句子
	if (cnf.clause_set[cur->cls_idx]->next == cnf.clause_set[cur->cls_idx])
	{
		cnf.cls_num = 0;
		return;
	}
	else
	{
		cnf.clause_set[cur->cls_idx]->next->prev = cnf.clause_set[cur->cls_idx]->prev;
		cnf.clause_set[cur->cls_idx]->prev->next = cnf.clause_set[cur->cls_idx]->next;
		if (cnf.clause_set[cur->cls_idx] == cnf.first_clause_head)
			cnf.first_clause_head = cnf.clause_set[cur->cls_idx]->next;
	}
	cnf.cls_num--;
	//cnf.clause_set[cur->cls_idx] = nullptr;
}
void delline(CNF& cnf, LNode* cur, Stack& history)
{
	push(history, nullptr, nullptr, cur, LINE, cur->is_positive);
	if (cur->next == cur)
	{
		cnf.cls_num = 0;
		return;
	}
	else
	{
		cur->next->prev = cur->prev;
		cur->prev->next = cur->next;
		if (cur == cnf.first_literal_head)
			cnf.first_literal_head = cur->next;
	}

	if (cur->first_elem_l->value > 0)
		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 1;
	else
		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 0;

	--cnf.ltr_num;
}
void UnitPropgate(CNF& cnf, Stack& history)
{
	CNode* tern = cnf.first_clause_head;
	for (CNode* scan = cnf.first_clause_head->next; /*flag ||*/ scan != cnf.first_clause_head; scan = scan->next)
	{
		if (scan->row_value_n == 1)
		{
			Node* key = scan->first_elem_r;			// 拿到关键的结点
			for (Node* cur = key->rear; cur!= key; cur = cur->rear)				// 先要进行上下遍历
			{
				if (cur->value == key->value)
					delclause(cnf, cur, history);
				else 
				{
					delnode(cnf, cur, history);
				}
			}
		}
	}
	if (tern->row_value_n == 1)
	{
		Node* key = tern->first_elem_r;			// 拿到关键的结点
		for (Node* cur = key->rear; cur != key; cur = cur->rear)				// 先要进行上下遍历
		{
			if (cur->value == key->value)
				delclause(cnf, cur, history);
			else 
				delnode(cnf, cur, history);
		}
	}
}
void PureLiteralAssign(CNF& cnf, Stack& history)
{
	LNode* term = cnf.first_literal_head;
	for (LNode* scan = term->next; scan != term; scan = scan->next)
	{
		if (scan->line_value_n == 1)
		{
			delclause(cnf, scan->first_elem_l, history);
			delline(cnf, scan, history);												// 就是赋值并且删除
		}
	}
	if (term->line_value_n == 1)
	{
		delclause(cnf, term->first_elem_l, history);
		delline(cnf, term, history);												// 就是赋值并且删除
	}
}
void set_value(CNF& cnf, LNode* cur, Stack& history, int val)			// 赋值
{
	Node* key = cur->first_elem_l;
	for (Node* cur = key->rear; cur != key; cur = cur->rear)
	{
		if (cur->value == val)
			delclause(cnf, cur, history);
		else
		{
			delnode(cnf, cur, history);
		}
	}
	if (key->value == val)
		delclause(cnf, key, history);
	else
	{
		delnode(cnf, key, history);
	}
	delline(cnf, cur, history);
}
int ChooseBetterValue(const CNF& cnf,int arr[])
{
	
	return cnf.first_literal_head->first_elem_l->value;
}


void revert(CNF& cnf, Stack& s)					// 回溯的函数
{
	while (s && s->cls_idx != SECRETNUM)
	{
		switch (s->cls_idx) {
		case NODE:
		{
			if (s->pos->next != s->pos)
			{
				s->pos->prev->next = s->pos;
				s->pos->next->prev = s->pos;
			}
			if (s->pos->front != s->pos)
			{
				s->pos->front->rear = s->pos;
				s->pos->rear->front = s->pos;
			}
			++cnf.clause_set[s->pos->cls_idx]->row_value_n;
			++cnf.literal_set[abs(s->pos->value)]->line_value_n;
			break;
		}
		case LINE:
		{
			s->line_del->next->prev = s->line_del;
			s->line_del->prev->next = s->line_del;
			s->line_del->is_positive = s->is_positive;
			++cnf.ltr_num;
			break;
		}
		default:
		{
			s->clause_del->next->prev = s->clause_del;
			s->clause_del->prev->next = s->clause_del;
			++cnf.cls_num;
			break;
		}
		}
		Snode* del = s;
		s = s->next;
		free(del);
	}
	if (s->cls_idx == SECRETNUM)
	{
		Snode* del = s;
		s = s->next;
		free(del);
	}
}


Status DPLL(CNF& cnf,Stack&history,int arr[],const int x)
{
	static long long counts{ 0 };++counts;
	printf(". ");
	if (!(counts % 21))
		putchar('\n');

	stamp(history);								// 每一次递归调用先打个标记
	UnitPropgate(cnf, history);
	PureLiteralAssign(cnf, history);

	if (set_is_empty(cnf)) {
		revert(cnf, history);
		return SATISFIED;
	}
	if (clause_is_empty(cnf)) {
		revert(cnf, history);
		return DISATISFIED;
	}

	stamp(history);

	if (!(counts % 10))
		qsort(arr, x, sizeof(int), cmp);
	int lucky_num = arr[1];
		//ChooseBetterValue(cnf,arr);
	set_value(cnf, cnf.literal_set[abs(lucky_num)], history,lucky_num);
	cnf.literal_set[abs(lucky_num)]->is_positive = lucky_num > 0 ? 1 : 0;
	printf("%d  ", lucky_num);

	if (DPLL(cnf, history)) {
		revert(cnf, history);
		return SATISFIED;
	}
	else {
		revert(cnf, history);
		set_value(cnf, cnf.literal_set[abs(lucky_num)], history,-lucky_num);
		cnf.literal_set[abs(lucky_num)]->is_positive = lucky_num > 0 ? 0 : 1;
		if (DPLL(cnf, history)) {
			revert(cnf, history);
			return SATISFIED;
		}
		else
		{
			revert(cnf, history);			// 去除unit与pure
			return DISATISFIED;
		}
	}
}







int main(void)
{
	CNF cnf; 
	char filename[MAXLEN]="2.cnf";
	int ltr_num{ 0 };
	CNF_EXACTER(cnf, filename,ltr_num);
#ifndef DEBUG
	Stack history{ nullptr };
	DPLL(cnf, history);
	present_answer(cnf);

#else
	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	int *arr = (int*)malloc(sizeof(int) + (cnf.ltr_num + 1));
	for (int i = 1; i <= cnf.ltr_num; ++i)
		arr[i] = cnf.literal_set[i]->line_value_n;
	const int num = cnf.ltr_num;
	traverse(cnf);
	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	Stack history{ nullptr };
	//UnitPropgate(cnf, history);
	//traverse(cnf);
	//PureLiteralAssign(cnf, history);
	//traverse(cnf);


	if (!DPLL(cnf, history, arr,num))
		printf("BADDDDDDDDDDDD");

	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//traverse(cnf);
	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	//check_the_stack(history);

	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	present_answer(cnf,ltr_num);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
	free(arr);
#endif // DEBUG

	return 0;
}
