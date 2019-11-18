#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef int ElemType;

typedef struct LNode
{
	ElemType data;
	struct LNode* next;
}LNode,*ListPtr;

typedef struct LinkList
{
	struct LNode* head;
	int length;
}LinkList;

Status InitList(LinkList& L)
{
	L.head = (LNode*)malloc(sizeof(LNode));
	if (!L.head) exit(OVERFLOW);
	L.head->next = NULL;
	L.length = 0;
	return OK;
}

Status DestroyList(LinkList& L)
{
	if (!L.head) return ERROR;
	ListPtr p = L.head, q = L.head->next;
	while (p->next)
	{
		free(p);
		p = q;
		q = q->next;
	}
	free(p);
	L.length = 0;
	return OK;
}

int ListLength(LinkList L)
{
	if (!L.head) return ERROR;
	return L.length;
}

Status ListInsert(LinkList& L, int i, ListPtr new_node)
{
	if (!L.head) return ERROR;
	if (i<1 || i>ListLength(L) + 1)
		return ERROR;
	ListPtr p = L.head, q = L.head->next;
	if (i == ListLength(L) + 1)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = new_node;
		new_node->next = NULL;
		++L.length;
		return OK;
	}
	else
	{
		for (int n = 1; n < i; ++n)
		{
			q = q->next;
			p = p->next;
		}

		p->next = new_node;
		new_node->next = q;
		++L.length;
		return OK;
	}
}

Status compare(ListPtr p1, ListPtr p2)
{
	if (p1->data==p2->data)
		return TRUE;
	else
		return FALSE;
}

int ListDelete(LinkList& L, ListPtr del_node)
{
	if (!L.head) return ERROR;
	ListPtr p = L.head, q = L.head->next;
	for (; !compare(q, del_node);)
	{
		q = q->next;
		p = p->next;
	}
	p->next = q->next;
	--L.length;
	return OK;
}

Status GetRemain(LinkList& L,ListPtr q, int p)
{
	int remain;
	ListPtr nt = q->next;
	if (q->data % 5 != 0)
		remain = 6 - (q->data % 5);
	else
		remain = 1;
	if (p <= remain)
	{
		for (int i = 1; i <= p; ++i)
		{
			printf("%d ", q->data);
			ListDelete(L, q);
			q = nt;
			nt = nt->next;
		}
	}
	else
	{
		for (int i = 1; i <= remain; ++i)
		{
			q = nt;
			nt = nt->next;
		}
		GetRemain(L, q, p);
	}
	return OK;
}

Status GetTicket(LinkList& L)
{
	int n, p[101];
	//bool flag = FALSE;
	scanf_s("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf_s("%d", &p[i]);
	}
	for (int i = 1; i <= n; ++i)
	{
		ListPtr q = L.head->next, nt = L.head->next->next;
		if (p[i] > ListLength(L)) return ERROR;
		else if (p[i] == ListLength(L))
		{
			for (int j = 1; j <= p[i]; ++j)
			{
				printf("%d ", q->data);
				ListDelete(L, q);
				q = nt;
				if(nt)
					nt = nt->next;
			}
		}
		else
		{
			GetRemain(L, q, p[i]);
		}
		printf("\n");
	}
	return OK;
}

int main()
{
	LinkList L;
	InitList(L);
	ListPtr new_node;
	for (int i = 1; i <= 100; ++i)
	{
		new_node = (LNode*)malloc(sizeof(LNode));
		new_node->data = i;
		ListInsert(L, i, new_node);
	}
	GetTicket(L);
	DestroyList(L);
	return 0;
}