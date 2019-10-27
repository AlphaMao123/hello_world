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

Status ListDelete(LinkList& L, int i, ElemType& e)
{
	if (L.head)
	{
		if (i<1 || i>ListLength(L))
			return ERROR;
		L.current = L.head->next;
		ListPtr prior = L.head;
		for (int n = 1; n < i; ++n)
		{
			L.current = L.current->next;
			prior = prior->next;
		}
		if (i == ListLength(L))
		{
			L.rear = prior;
			L.rear->next = NULL;
			e = L.current->data;
			free(L.current);
			return OK;
		}
		else
		{
			prior->next = L.current->next;
			e = L.current->data;
			free(L.current);
			return OK;
		}
	}
	else
		return ERROR;
}

Status GetElem(LinkList L, int i, ElemType& e)
{
	if (L.head)
	{
		if (i<1 || i>ListLength(L)) return ERROR;
		L.current = L.head->next;
		for (int n = 1; n < i; n++)
		{
			L.current = L.current->next;
		}
		e = L.current->data;
	}
	else
		return ERROR;
}
Status circular_count(LinkList& L, int n, int m)
{
	int num;
	int index = 1;
	ListPtr p = L.head->next;
	for (int i = 1; i <= n; ++i)
	{
		ListInsert(L, i, i);
	}
	if (ListLength(L) <= 1)
		return ERROR;
	while (ListLength(L) > 1)
	{
		index = (index + m) % ListLength(L)-1;
		if (index ==0)
			index += ListLength(L);
		ListDelete(L, index, num);
		printf("%d ", num);
	}
	GetElem(L, 1, num);
	printf("%d", num);
	return 0;
}



int main()
{
	LinkList L;
	InitList(L);
	int m, n;
	printf("请输入m的值：");
	scanf("%d", &m);
	printf("请输入n的值：");
	scanf("%d", &n);
	circular_count(L, n, m);
	printf("\n");
	DestoryList(L);
	return 0;
}