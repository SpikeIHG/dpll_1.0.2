//#include"Utility.hpp"
//#define DEBUG
//
//void traverse(const CNF& cnf)
//{
//	CNode* scan = cnf.first_clause_head;
//	for (int i = 1; i <= cnf.cls_num; ++i, scan = scan->next)
//	{
//		Node* first_elem = scan->first_elem_r;
//		printf("%d ", first_elem->value);
//		for (Node* cur = first_elem->next; cur != first_elem; cur = cur->next)
//			printf("%d ", cur->value);
//		putchar('\n');
//	}
//}
//void check_the_stack(const Stack& s)
//{
//	int idx{ 1 };
//	Snode* step = s;
//	while (step)
//	{
//		printf("��%d��������\t", idx);
//		switch (step->cls_idx) {
//		case NODE:
//		{
//			printf("ɾ����㣬����ֵ��%d,��������ľ��������%d \n", step->pos->value, step->pos->cls_idx);
//			break;
//		}
//		case LINE:
//		{
//			printf("ɾ������һ��������ɾ��������ֵ��%d\n", step->line_del->first_elem_l->value);
//			break;
//		}
//		case SECRETNUM:
//		{
//			printf("����һ�ηֶε�*********************************\n");
//			break;
//		}
//		default:
//		{
//			printf("ɾ������һ�����ӣ����ӵ������%d,\n", step->cls_idx);
//			break;
//		}
//		}
//		++idx; step = step->next;
//	}
//}
//void present_answer(const CNF& cnf)
//{
//	for (int i = 1; i <= 4; ++i)
//		printf("����%d ��ȡֵ�� %d \n", i, (cnf.literal_set[i]->is_positive ? i : -i));
//}
//
//
//inline void check_right_flow(FILE* f)
//{
//	if (!f)
//		exit(EXIT_FAILURE);
//}
//inline void featline(FILE* f)
//{
//	char word[100];
//	while (fscanf(f, "%s", word) && strcmp(word, "cnf"))
//		continue;
//}
//
//void CNF_EXACTER(CNF& cnf, char filename[])
//{
//	FILE* infile = fopen(filename, "r");
//	check_right_flow(infile);
//	featline(infile);
//
//	fscanf(infile, "%d%d", &cnf.ltr_num, &cnf.cls_num);			// �����Ӧ������
//	cnf.clause_set = (Cset)malloc(sizeof(CNode*) * (cnf.cls_num + 1));
//	cnf.literal_set = (Lset)malloc(sizeof(LNode*) * (cnf.ltr_num + 1));
//	memset(cnf.clause_set, 0, sizeof(CNode*) * (cnf.cls_num + 1));
//	memset(cnf.literal_set, 0, sizeof(LNode*) * (cnf.ltr_num + 1));
//	int val{ 0 };
//
//	for (int i = 1; i <= cnf.cls_num; ++i)
//	{
//		CNode* new_clause = (CNode*)malloc(sizeof(CNode));
//		new_clause->first_elem_r = nullptr;
//		new_clause->row_value_n = 0;
//		cnf.clause_set[i] = new_clause;
//
//		if (i == 1) {
//			cnf.first_clause_head = new_clause->prev = new_clause->next = new_clause;
//		}
//		else
//		{
//			cnf.clause_set[1]->prev = new_clause;
//			cnf.clause_set[i - 1]->next = new_clause;
//			new_clause->prev = cnf.clause_set[i - 1];
//			new_clause->next = cnf.clause_set[1];
//		}
//
//		while (fscanf(infile, "%d", &val) && val)
//		{
//			Node* pnew = (Node*)malloc(sizeof(Node));			// ����һ���µĽ��
//			if (!new_clause->row_value_n) {			// ���ǵ�һ���Ա���ʱ
//				pnew->next = pnew->prev = pnew;
//				new_clause->first_elem_r = pnew;
//			}
//			else {
//				new_clause->first_elem_r->prev->next = pnew;
//				pnew->prev = new_clause->first_elem_r->prev;
//				pnew->next = new_clause->first_elem_r;
//				new_clause->first_elem_r->prev = pnew;
//			}
//			pnew->value = val;
//			pnew->cls_idx = i;
//			++new_clause->row_value_n;			// ��������������ͳ��
//			if (!cnf.literal_set[abs(val)])
//			{
//				LNode* new_line = (LNode*)malloc(sizeof(LNode));
//				new_line->is_positive = 0;
//				new_line->line_value_n = 0;
//				if (!cnf.first_literal_head)
//				{
//					new_line->prev = new_line->next = new_line;
//					cnf.first_literal_head = new_line;
//				}
//				else		// ��û���κε�ָ��
//				{
//					new_line->next = cnf.first_literal_head;
//					new_line->prev = cnf.first_literal_head->prev;
//					cnf.first_literal_head->prev->next = new_line;
//					cnf.first_literal_head->prev = new_line;
//				}
//				// ��û���κε�ָ��
//				cnf.literal_set[abs(val)] = new_line;
//				new_line->first_elem_l = pnew;
//				pnew->front = pnew->rear = pnew;
//			}
//			else
//			{
//				cnf.literal_set[abs(val)]->first_elem_l->front->rear = pnew;
//				pnew->front = cnf.literal_set[abs(val)]->first_elem_l->front;
//				pnew->rear = cnf.literal_set[abs(val)]->first_elem_l;
//				cnf.literal_set[abs(val)]->first_elem_l->front = pnew;
//				//cnf.literal_set[abs(val)]->first_elem_l = pnew;
//			}
//			++cnf.literal_set[abs(val)]->line_value_n;
//		}
//	}
//	fclose(infile);
//}
//inline void eatline(FILE* f)
//{
//	char word[100];
//	while (fscanf(f, "%s", word) && strcmp(word, "cnf"))
//		printf("%s", word);
//
//}
//void push(Stack& s, Node* n, CNode* cls, LNode* ltr, int idx)
//{
//	Snode* newp = (Snode*)malloc(sizeof(Snode));
//	newp->clause_del = cls;
//	newp->pos = n;
//	newp->cls_idx = idx;
//	newp->next = s;
//	newp->line_del = ltr;
//	s = newp;
//}
//void delnode(CNF& cnf, Node* cur, Stack& history)
//{
//	push(history, cur, nullptr, nullptr, NODE);					// �Ƚ��л���			�Ϳ��Ա�֤������
//	//if (cur->next == cur)				// ֻ��һ��Ԫ��
//	//{
//	//	cnf.clause_set[cur->cls_idx]->first_elem_r = nullptr;
//	//}
//	//else
//	//{
//	if (cur->next != cur) {
//		cur->prev->next = cur->next;
//		cur->next->prev = cur->prev;
//		if (cnf.clause_set[cur->cls_idx]->first_elem_r == cur)
//			cnf.clause_set[cur->cls_idx]->first_elem_r = cur->next;			// ��ָ֤��ʼ����Ч
//	}
//	//}
///*if (cur->rear == cur)
//{
//	if (cur->value > 0)
//		cnf.literal_set[abs(cur->value)]->is_positive = 1;
//	else
//		cnf.literal_set[abs(cur->value)]->is_positive = 0;
//
//	cnf.literal_set[abs(cur->value)]->first_elem_l = nullptr;
//}*/
//	if (cur->rear != cur) {
//		cur->rear->front = cur->front;
//		cur->front->rear = cur->rear;
//		if (cnf.literal_set[abs(cur->value)]->first_elem_l == cur)
//			cnf.literal_set[abs(cur->value)]->first_elem_l = cur->rear;
//	}
//
//	--cnf.clause_set[cur->cls_idx]->row_value_n;
//	--cnf.literal_set[abs(cur->value)]->line_value_n;
//}
//void delclause(CNF& cnf, Node* cur, Stack& history)
//{
//	push(history, nullptr, cnf.clause_set[cur->cls_idx], nullptr, cur->cls_idx);				// �Ƚ���push �����Ų��ı�
//	for (Node* scan = cur->next; scan->next != scan; scan = scan->next)
//		delnode(cnf, scan, history);
//	delnode(cnf, cur, history);
//	// ����Ҫ���վ���
//	if (cnf.clause_set[cur->cls_idx]->next == cnf.clause_set[cur->cls_idx])
//	{
//		cnf.cls_num = 0;
//		return;
//	}
//	else
//	{
//		cnf.clause_set[cur->cls_idx]->next->prev = cnf.clause_set[cur->cls_idx]->prev;
//		cnf.clause_set[cur->cls_idx]->prev->next = cnf.clause_set[cur->cls_idx]->next;
//		if (cnf.clause_set[cur->cls_idx] == cnf.first_clause_head)
//			cnf.first_clause_head = cnf.clause_set[cur->cls_idx]->next;
//
//	}
//	cnf.cls_num--;
//	//cnf.clause_set[cur->cls_idx] = nullptr;
//}
//void UnitPropgate(CNF& cnf, Stack& history)
//{
//	/*int flag{ 0 };
//	if (cnf.cls_num == 1)
//		flag = 1;*/
//	CNode* tern = cnf.first_clause_head;
//	for (CNode* scan = cnf.first_clause_head->next; /*flag ||*/ scan != cnf.first_clause_head; scan = scan->next)
//	{
//		//flag = 0;						// ��ǲ���������
//		if (scan->row_value_n == 1)
//		{
//			Node* key = scan->first_elem_r;			// �õ��ؼ��Ľ��
//			for (Node* cur = key->rear; cur != key; cur = cur->rear)				// ��Ҫ�������±���
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
//	if (tern->row_value_n == 1)
//	{
//		Node* key = tern->first_elem_r;			// �õ��ؼ��Ľ��
//		for (Node* cur = key->rear; cur != key; cur = cur->rear)				// ��Ҫ�������±���
//		{
//			if (cur->value == key->value)
//				delclause(cnf, cur, history);
//			else if (cur->value + key->value == 0)
//			{
//				delnode(cnf, cur, history);
//			}
//		}
//	}
//}
//void delline(CNF& cnf, LNode* cur, Stack& history)
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
//		if (cur == cnf.first_literal_head)
//			cnf.first_literal_head = cur->next;
//	}
//
//	if (cur->first_elem_l->value > 0)
//		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 1;
//	else
//		cnf.literal_set[abs(cur->first_elem_l->value)]->is_positive = 0;
//
//	//cnf.literal_set[abs(cur->first_elem_l->value)]->first_elem_l = nullptr;
//	//cur = nullptr;				// ��Ϊ���ﴫ��������
//	--cnf.ltr_num;
//}
//void set_value(CNF& cnf, LNode* cur, Stack& history)			// ��ֵ
//{
//	Node* key = cur->first_elem_l;
//	int val = cur->is_positive ? abs(key->value) : -abs(key->value);
//	for (Node* cur = key->rear; cur != key; cur = cur->rear)
//	{
//		if (cur->value == val)
//			delclause(cnf, cur, history);
//		else if (cur->value + val == 0)
//		{
//			delnode(cnf, cur, history);
//		}
//	}
//	if (key->value == val)
//		delclause(cnf, key, history);
//	else
//		delnode(cnf, key, history);
//	delline(cnf, cur, history);
//	if (val > 0)
//		cur->is_positive = 1;
//	else
//		cur->is_positive = 0;
//}
//
//void PureLiteralAssign(CNF& cnf, Stack& history)
//{
//	LNode* term = cnf.first_literal_head;
//	for (LNode* scan = term->next; scan != term; scan = scan->next)
//	{
//		if (scan->line_value_n == 1)
//		{
//			delclause(cnf, scan->first_elem_l, history);
//			delline(cnf, scan, history);												// ���Ǹ�ֵ����ɾ��
//		}
//	}
//	if (term->line_value_n == 1)
//	{
//		delclause(cnf, term->first_elem_l, history);
//		delline(cnf, term, history);												// ���Ǹ�ֵ����ɾ��
//	}
//}
//inline Status set_is_empty(const CNF& cnf)
//{
//	return cnf.cls_num == 0;
//}
//Status clause_is_empty(const CNF& cnf)
//{
//	for (CNode* scan = cnf.first_clause_head->next; scan != cnf.first_clause_head; scan = scan->next)
//		if (!scan->row_value_n)
//			return OK;
//	return cnf.first_clause_head->row_value_n == 0;
//}
//int ChooseBetterValue(const CNF& cnf)
//{
//	return cnf.first_literal_head->first_elem_l->value;
//}
//// ���ݵĺ�����
//inline void stamp(Stack& s)
//{
//	Snode* mark = (Snode*)malloc(sizeof(Snode));
//	mark->clause_del = nullptr;
//	mark->line_del = nullptr;
//	mark->pos = nullptr;
//	mark->next = s;
//	mark->cls_idx = SECRETNUM;
//	s = mark;
//}
//
//void revert(CNF& cnf, Stack& s)					// ���ݵĺ���
//{
//	while (s && s->cls_idx != SECRETNUM)
//	{
//		switch (s->cls_idx) {
//		case NODE:
//		{
//			if (s->pos->next != s->pos)
//			{
//				s->pos->prev->next = s->pos;
//				s->pos->next->prev = s->pos;
//			}
//			s->pos->front->rear = s->pos;
//			s->pos->rear->front = s->pos;
//			++cnf.clause_set[s->pos->cls_idx]->row_value_n;
//			++cnf.literal_set[abs(s->pos->value)]->line_value_n;
//			break;
//		}
//		case LINE:
//		{
//			s->line_del->next->prev = s->line_del;
//			s->line_del->prev->next = s->line_del;
//			++cnf.ltr_num;
//			break;
//		}
//		default:
//		{
//			s->clause_del->next->prev = s->clause_del;
//			s->clause_del->prev->next = s->clause_del;
//			++cnf.cls_num;
//			break;
//		}
//		}
//		Snode* del = s;
//		s = s->next;
//		free(s);
//	}
//}
//
//Status DPLL(CNF& cnf, Stack& history)
//{
//	static long long counts{ 0 }; ++counts;
//	printf(". ");
//	if (!(counts % 21))
//		putchar('\n');
//
//	stamp(history);								// ÿһ�εݹ�����ȴ�����
//	UnitPropgate(cnf, history);
//	PureLiteralAssign(cnf, history);
//
//	if (set_is_empty(cnf))
//		return SATISFIED;
//	if (clause_is_empty(cnf)) {
//		revert(cnf, history);
//		return DISATISFIED;
//	}
//
//	stamp(history);
//
//	int lucky_num = ChooseBetterValue(cnf);
//	cnf.literal_set[abs(lucky_num)]->is_positive = 1;
//	set_value(cnf, cnf.literal_set[abs(lucky_num)], history);
//
//	if (DPLL(cnf, history))
//		return SATISFIED;
//	else {
//		revert(cnf, history);
//		cnf.literal_set[abs(lucky_num)]->is_positive = 0;
//		set_value(cnf, cnf.literal_set[abs(lucky_num)], history);
//		return DPLL(cnf, history);
//	}
//}
//
//int main(void)
//{
//	CNF cnf;
//	char filename[MAXLEN] = "anomaly.cnf";
//
//	CNF_EXACTER(cnf, filename);
//#ifndef DEBUG
//	Stack history{ nullptr };
//	DPLL(cnf, history);
//	present_answer(cnf);
//
//#else
//	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	//traverse(cnf);
//	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	Stack history{ nullptr };
//	//UnitPropgate(cnf, history);
//	//traverse(cnf);
//	//PureLiteralAssign(cnf, history);
//	DPLL(cnf, history);
//
//	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	//traverse(cnf);
//	//printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	//check_the_stack(history);
//	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++\n");
//	//present_answer(cnf);
//#endif // DEBUG
//
//
//
//
//
//
//
//
//
//
//
//
//
//	return 0;
//}