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
	L.current = L.head->next = NULL;
	L.rear = L.head;
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
		L.current = L.head->next;
		while (L.current != NULL)
		{
			L.current = L.current->next;
			++i;
		}
		return i;
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
		return OK;
	}
	else
		return ERROR;
}

Status compare(ElemType m, ElemType n)
{
	if (m == n)
		return TRUE;
	else
		return FALSE;
}

int LocateElem(LinkList L, ElemType e, Status(*compareptr)(ElemType, ElemType) = compare)
{
	if (L.head)
	{
		int counter = 1;
		L.current = L.head->next;
		while (L.current != NULL)
		{
			if (compareptr(L.current->data, e))
			{
				return counter;
				break;
			}
			else
			{
				++counter;
				L.current = L.current->next;
			}
		}
		if (counter > ListLength(L))
			return FALSE;
	}
	else
		return ERROR;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType& pre_e)
{
	if (L.head)
	{
		L.current = L.head->next;
		ListPtr prior = L.head;
		if (cur_e == L.current->data)
			return ERROR;
		while (L.current != NULL)
		{
			if (cur_e == L.current->data)
			{
				pre_e = prior->data;
				return OK;
				break;
			}
			else
			{
				prior = prior->next;
				L.current = L.current->next;
			}
		}
		if (L.current == NULL)
		{
			return ERROR;
		}
	}
	else
		return ERROR;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType& next_e)
{
	if (L.head)
	{
		L.current = L.head->next;
		while (L.current != L.rear)
		{
			if (cur_e == L.current->data)
			{
				next_e = L.current->next->data;
				return OK;
				break;
			}
			else
			{
				L.current = L.current->next;
			}
		}
		if (L.current == L.rear)
			return ERROR;
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

int GetTurningPoint(LinkList L, int total)
{
	if (!L.head)
		return ERROR;
	ElemType pre_e, turningpoint = 0, next_e;
	ListPtr p = L.head->next->next;
	for (; p->next != NULL; p = p->next)
	{
		PriorElem(L, p->data, pre_e);
		NextElem(L,p->data, next_e);
		if ((p->data < pre_e && p->data < next_e) || (p->data > pre_e&& p->data > next_e))
		{
			++turningpoint;
		}
	}
	return turningpoint;
}

int main()
{
	LinkList L;
	InitList(L);
	int total,num,turningpoint;
	scanf("%d", &total);
	for (int i = 1; i <= total; ++i)
	{
		scanf("%d", &num);
		ListInsert(L, i, num);
	}
	turningpoint=GetTurningPoint(L, total);
	printf("%d", turningpoint);
	return 0;
}