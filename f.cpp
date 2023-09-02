//void UnitPropgate(CNF& cnf, Stack& history)
//{
//	int flag{ 0 };
//	if (cnf.cls_num == 1)
//		flag = 1;
//	for (CNode* scan = cnf.first_clause_head; flag || scan->next != cnf.first_clause_head; scan = scan->next)
//	{
//		flag = 0;						// 标记不再起作用
//		if (scan->row_value_n == 1)
//		{
//			Node* key = scan->first_elem_r;			// 拿到关键的结点
//			for (Node* cur = key->rear; cur != key; cur = cur->rear)				// 先要进行上下遍历
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