#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
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

Status compare(ElemType a, ElemType b)
{
	if (a == b)
		return TRUE;
	else
		return FALSE;
}

int LocateElem(SqList L, ElemType e, Status(*compareptr)(ElemType, ElemType) = compare)//使用带有默认参数的函数指针
{
	if (L.elem)
	{
		for (int i = 0; i < L.length; ++i)
		{
			if (compare(e, L.elem[i]))
			{
				return i + 1;
				break;
			}
			if (i == L.length - 1)
				return ERROR;//不存在
		}
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

Status ListDelete(SqList& L, int i, ElemType& e)
{
	if (L.elem)
	{
		if (i < 0 || i>ListLength(L)) return ERROR;
		ElemType* p = &(L.elem[i - 1]);
		ElemType* q = &(L.elem[ListLength(L) - 1]);
		e = L.elem[i - 1];
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

Status CreateList(SqList& L, ElemType total, ...)
{
	if (L.elem)
	{
		va_list ap;
		va_start(ap, total);
		for (int i = 1; i <= total; ++i)
		{
			ListInsert(L, i, va_arg(ap, ElemType));
		}
		va_end(ap);
		return OK;
	}
	else
	{
		return ERROR;
	}
}

Status ListUnion(SqList& A, SqList B)
{
	int num;
	if (!A.elem || !B.elem)//保证两个线性表存在
		return ERROR;
	for (int i = 0; i < ListLength(A);)//遍历表A
	{
		if (!LocateElem(B, A.elem[i]))//如果当前的值不存在于表B中
		{
			ListDelete(A, LocateElem(A, A.elem[i]), num);//将该值从表A中删除
		}
		else
		{
			++i;//如果存在则指针加一
		}
	}
	return OK;
}

int main()
{
	//创建两个线性表
	SqList L1, L2;
	//初始化
	InitList(L1);
	InitList(L2);
	//创建两个有序的顺序表
	CreatList(L1, 5, 1, 2, 3, 4, 5);
	CreatList(L2, 6, 4, 5, 6, 7, 8, 9);
	//分别打印出两个线性表的内容 
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