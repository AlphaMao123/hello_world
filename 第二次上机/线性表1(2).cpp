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
	L.head->next=NULL;
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

Status ListInsert(LinkList& L, ListPtr p, ElemType e)
{
	if (L.head)
	{
		ListPtr new_node = (LNode*)malloc(sizeof(LNode));
		new_node->data = e;
		ListPtr prior = L.head;
		L.current = L.head->next;
		if (p==NULL)
		{
			L.rear->next = new_node;
			L.rear = new_node;
			new_node->next = NULL;
			return OK;
		}
		else
		{
			for (;L.current!=p;)
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

Status ListDelete(LinkList& L, ListPtr p, ElemType& e)
{
	if (L.head)
	{
		L.current = L.head->next;
		ListPtr prior = L.head;
		for (;p!=L.current;)
		{
			L.current = L.current->next;
			prior = prior->next;
		}
		if (L.rear==p)
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

Status CreatList(LinkList& L,ElemType total,...)
{
	if (L.head)
	{
		va_list(ap);
		va_start(ap, total);
		ListPtr p=L.head->next;
		for (int i = 1; i <= total; ++i)
		{
			ListInsert(L, p, va_arg(ap, ElemType));
		}
		return OK;
	}
	else
		return ERROR;
}

Status Insert_sorted(LinkList& L)
{
	int num;
	if(L.head)
	{
		ListPtr p=L.head->next->next;
		ListPtr pior=L.head->next;
		bool Flag;
		for(;p;p=p->next)
		{
			Flag=TRUE;
			for(ListPtr q=L.head->next;q!=p;q=q->next)
			{
				if(q->data>=p->data)
				{
					ListInsert(L,q,p->data);
					Flag=FALSE;
					ListDelete(L,p,num);
					p=pior;
					break;
				}
			}
			if(Flag)
				pior=pior->next;
		}
		return OK;
	}
	else
	{
		return ERROR;
	}
	
}

int main()
{
	LinkList L;
	InitList(L);
	//创建一个未排序了链表
	CreatList(L, 5, 1, 3, 2, 5, 4);
	//打印出排序之前的链表
	ListTraverse(L);
	//插入法排序
	Insert_sorted(L);
	//打印出排序之后的链表
	ListTraverse(L);
	//销毁链表
	DestoryList(L);
	system("pause");
	return 0;
}