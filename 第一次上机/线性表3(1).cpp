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

Status ListDelete(SqList& L, ElemType* m, ElemType& e)
{
	if (L.elem)
	{
		ElemType* p = m;
		ElemType* q = &(L.elem[ListLength(L) - 1]);
		e = *m;
		for (; p < q; ++p)
		{
			*p = *(p + 1);
		}
		--L.length;
		return OK;
	}
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

Status circular_count(SqList& L,int n,int m)
{
	int num;
	int index = 0;
	ElemType* p=&(L.elem[0]);
	for (int i = 1; i <= n; ++i)
	{
		ListInsert(L,i, i);
	}
	if (ListLength(L) <= 1)
		return ERROR;
	while (ListLength(L) > 1)
	{	
		index = (index + m) % ListLength(L) - 1;
		if (index < 0)
			index += ListLength(L);
		p = &(L.elem[index]);
		ListDelete(L,p,num);
		printf("%d ", num);
	}
	printf("%d", L.elem[0]);
	return OK;
}


int main()
{
	SqList L;
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