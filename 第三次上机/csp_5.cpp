#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct PointSignal
{
	int x;
	int y;
}PointSignal,Signal[10];

class Window
{
public:
	int start[2];
	int end[2];
	int id;
	Window(int x1, int y1, int x2, int y2 ,int ID)
	{
		start[0] = x1;
		start[1] = y1;
		end[0] = x2;
		end[1] = y2;
		id = ID;
	}
};
typedef Window ElemType;

typedef struct LNode
{
	ElemType win;
	struct LNode* next;
}LNode,*ListPtr;

typedef struct LinkList
{
	int length;
	struct LNode* head;
}LinkList;

Status InitList(LinkList& L)
{
	L.head = (ListPtr)malloc(sizeof(LNode));
	if (!L.head) exit(OVERFLOW);
	L.head->next = NULL;
	L.length = 0;
	return OK;
}

Status DestroyList(LinkList& L)
{
	if (!L.head) return ERROR;
	ListPtr p = L.head->next, q = L.head;
	while (p)
	{
		free(q);
		q = p;
		p = p->next;
	}
	free(q);
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
		while (p->next!=NULL)
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
	if (p1->win.start[0] == p2->win.start[0] && p1->win.start[1] == p2->win.start[1] && p1->win.end[0] == p2->win.end[0] && p1->win.end[1] == p2->win.end[1])
		return TRUE;
	else
		return FALSE;
}

int ListDelete(LinkList& L, ListPtr del_node)
{
	if (!L.head) return ERROR;
	ListPtr p = L.head, q = L.head->next;
	for (;!compare(q,del_node);)
	{
		q = q->next;
		p = p->next;
	}
	p->next = q->next;
	--L.length;
	return OK;
}

Status WindowsPoint(LinkList& L)
{
	if (!L.head) return ERROR;
	int x1, y1, x2, y2;
	int m, n;
	Signal signal;
	scanf_s("%d%d", &m, &n);
	if (m > 10 || n > 10)
		return ERROR;
	for (int i = 1; i <= m; ++i)
	{
		scanf_s("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > 2559 || x2 > 2559 || y1 > 1439 || y2 > 1439)
			return ERROR;
		Window w(x1, y1, x2, y2, i);
		ListPtr new_node = (LNode*)malloc(sizeof(LNode));
		new_node->win = w;
		ListInsert(L, 1, new_node);
	}
	for (int i = 0; i < n; ++i)
	{
		scanf_s("%d%d", &x1, &y1);
		signal[i].x = x1;
		signal[i].y = y1;
	}
	ListPtr p = L.head->next;
	for (int i = 0; i < n; ++i)
	{
		while (p != NULL)
		{
			if (p->win.start[0] <= signal[i].x && p->win.start[1] <= signal[i].y && p->win.end[0] >= signal[i].x && p->win.end[1] >= signal[i].y)
			{
				ListDelete(L, p);
				ListInsert(L, 1, p);
				printf("%d\n", p->win.id);
				break;
			}
			p = p->next;
		}
		if (p == NULL)
		{
			printf("IGNORED\n");
		}
	}
	return OK;
}

int main()
{
	LinkList L;
	InitList(L);
	WindowsPoint(L);
	DestroyList(L);
	return 0;
}