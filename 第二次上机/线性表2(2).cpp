#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
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
	struct LNode* current;
	struct LNode* rear;
}LinkList;

Status InitList(LinkList& L)
{
	L.head = (ListPtr)malloc(sizeof(LNode));
	if (!L.head) exit(OVERFLOW);
	L.head->next = L.current = NULL;
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

Status CreateList(LinkList L, int total, ElemType ...)
{
	if (!L.head)
		return ERROR;
	va_list ap;
	va_start(ap, total);
	for (int i = 1; i <= total; ++i)
	{
		ListInsert(L, i, va_arg(ap, ElemType));
	}
	va_end(ap);
	return OK;
}

Status ListUnion(LinkList& L1, LinkList L2)
{
	int num;
	if (!L1.head || !L2.head)
		return ERROR;
	for (ListPtr p = L1.head->next; p;)
	{
		if (!LocateElem(L2, p->data))
		{
			ListPtr q = p;
			p = p->next;
			ListDelete(L1, LocateElem(L1, q->data),num);
		}
		else
		{
			p = p->next;
		}
	}
	return OK;
}

int main()
{
	//创建两个链表
	LinkList L1,L2;
	//初始化
	InitList(L1);
	InitList(L2);
	//创建两个有序的线性链表
	CreateList(L1, 5, 1, 2, 3, 4, 5);
	CreateList(L2, 6, 2, 4, 5, 7, 8, 9);
	//分别打印出两个链表的内容
	ListTraverse(L1);
	ListTraverse(L2);
	//求交集
	ListUnion(L1, L2);
	//打印出求交集之后的值
	ListTraverse(L1);
	//销毁线性表
	DestoryList(L1);
	DestoryList(L2);
	return 0;
}