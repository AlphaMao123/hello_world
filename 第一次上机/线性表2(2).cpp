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
}LNode, * ListPtr;

typedef struct LinkList
{
	struct LNode* head;
	struct LNode* current;
	struct LNode* rear;
}LinkList;

Status InitList(LinkList& L)
{
	L.head = (ListPtr)malloc(sizeof(LNode));
	if (!L.head) exit(OVERFLOW);
	L.current = L.rear = L.head;
	return OK;
}

Status DestoryList(LinkList& L)
{
	if (L.head)
	{
		L.current = L.head;
		ListPtr post = L.head->next;
		while (L.current != L.rear)
		{
			free(L.current);
			L.current = post;
			post = post->next;
		}
		free(L.current);
		L.head = NULL;
		L.current = NULL;
		L.rear = NULL;
		post = NULL;
		if (!L.head)
		{
			printf("线性链表销毁成功！\n");
			return OK;
		}
		else
		{
			printf("线性链表销毁失败！\n");
			return ERROR;
		}
	}
	else
		return ERROR;
}

int ListLength(LinkList L)
{
	if (L.head)
	{
		int i = 0;
		L.current = L.head;
		while (L.current != L.rear)
		{
			L.current = L.current->next;
			++i;
		}
		return i;
	}
	else
		return ERROR;

}

Status ListInsert(LinkList& L, int i, ElemType e)
{
	if (L.head)
	{
		if (i<1 || i>ListLength(L) + 1)
			return ERROR;
		ListPtr new_node = (LNode*)malloc(sizeof(LNode));
		new_node->data = e;
		ListPtr prior = L.head;
		L.current = L.head->next;
		if (i == ListLength(L) + 1)
		{
			L.rear->next = new_node;
			L.rear = new_node;
			new_node->next = NULL;
			return OK;
		}
		else
		{
			for (int n = 1; n < i; ++n)
			{
				L.current = L.current->next;
				prior = prior->next;
			}
			prior->next = new_node;
			new_node->next = L.current;
			return OK;
		}
	}
	else
		return ERROR;
}

Status visit(LinkList L, int i)
{
	if (L.head)
	{
		if (i<1 || i>ListLength(L))
			return ERROR;
		L.current = L.head->next;
		for (int n = 1; n < i; ++n)
		{
			L.current = L.current->next;
		}
		printf("%d ", L.current->data);
		return OK;
	}
	else
		return ERROR;
}

Status ListTraverse(LinkList L, Status(*vistptr)(LinkList, int) = visit)
{
	if (L.head)
	{
		L.current = L.head->next;
		for (int n = 1; n <= ListLength(L); ++n)
		{
			vistptr(L, n);
			L.current = L.current->next;
		}
		printf("\n");
		return OK;
	}
	else
		return ERROR;
}

Status ListReverse(LinkList &L)
{
	if (L.head)
	{
		L.current = L.head->next;
		ListPtr s = L.current->next;
		ListPtr q;
		if (L.current == L.head || !s) return OK;
		L.current->next = NULL;
		L.rear = L.current;
		while (s->next)
		{
			q = s->next;
			s->next = L.current;
			L.current = s;
			s = q;
		}
		s->next = L.current;
		L.head->next = s;
		return OK;
	}
	else
		return ERROR;
}

int main()
{
	LinkList L;
	InitList(L);
	for (int i = 0; i < 9; i++)
	{
		ListInsert(L, 1, i);
	}
	//置逆前：
	ListTraverse(L);
	ListReverse(L);
	//置逆后：
	ListTraverse(L);
	DestoryList(L);
	return 0;
}