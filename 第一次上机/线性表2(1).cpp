#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define INCREMENTSIZE 10

typedef int Status;
typedef int ElemType;
typedef struct SqList
{
	ElemType* elem;
	int length;
	int listsize;
}SqList;

Status InitList(SqList& L)
{
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
Status DestoryList(SqList& L)
{
	if (L.elem)
	{
		free(L.elem);
		L.elem = NULL;
	}
	else
		return ERROR;
	if (!L.elem)
	{
		printf("线性表销毁成功！\n");
		return OK;
	}
	else
	{
		printf("销毁线性表失败！\n");
		return ERROR;
	}
}
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	else
		return ERROR;
}
Status ListInsert(SqList& L, int i, ElemType e)
{
	if (L.elem)
	{
		if (i<0 || i>ListLength(L) + 1) return ERROR;
		if (ListLength(L) >= L.listsize)
		{
			ElemType* newbase = (ElemType*)realloc(L.elem, INCREMENTSIZE * sizeof(ElemType));
			if (!newbase) exit(OVERFLOW);
			L.listsize += INCREMENTSIZE;
			L.elem = newbase;
		}
		ElemType* q = &(L.elem[i - 1]);
		ElemType* p = &(L.elem[ListLength(L) - 1]);
		for (; p >= q; --p)
		{
			*(p + 1) = *p;
		}
		L.elem[i - 1] = e;
		++L.length;
		return OK;
	}
	else
		return ERROR;
}
Status visit(SqList L, int i)
{
	printf("%d ", L.elem[i]);
	return OK;
}
Status ListTraverse(SqList L, Status(*visitptr)(SqList, int) = visit)
{
	if (L.elem)
	{
		for (int i = 0; i <= ListLength(L) - 1; ++i)
		{
			visitptr(L, i);
		}
		printf("\n");
		return OK;
	}
	else
		return ERROR;
}
//实现就地置逆的函数
Status ListReverse(SqList& L)
{
	if (L.elem)
	{
		ElemType* p = &(L.elem[0]);
		ElemType* q = &(L.elem[ListLength(L) - 1]);
		ElemType num;
		for (int i = 0; i < ListLength(L) / 2; ++i)
		{
			num = *p;
			*p = *q;
			*q = num;
			++p;
			--q;
		}
		return OK;
	}
	else
		return ERROR;
}
int main()
{
	SqList L;
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