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
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
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
Status ClearList(SqList& L)
{
	if (L.elem)
	{
		L.length = 0;
		printf("线性表已清空！\n");
		return OK;
	}
	else
	{
		printf("线性表清除失败！\n");
		return ERROR;
	}
}
Status ListEmpty(SqList L)
{
	if (L.elem)
	{
		if (L.length == 0)
			return TRUE;
		else
			return FALSE;
	}
	else
		return ERROR;
}
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	else
		return ERROR;
}
Status GetElem(SqList L, int i, ElemType& e)
{
	if (L.elem)
	{
		if (i <= 0 || i > L.length) return ERROR;
		e = L.elem[i - 1];
		return OK;
	}
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
int LocateElem(SqList L, ElemType e, Status (*compareptr)(ElemType, ElemType)=compare)//使用带有默认参数的函数指针
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
Status PriorElem(SqList L, ElemType cur_e, ElemType& pre_e)
{
	if (L.elem)
	{
		for (int i = 0; i < L.length; ++i)
		{
			if (i == 0 && L.elem[i] == cur_e)
			{
				return ERROR;
			}
			else if (L.elem[i] == cur_e)
			{
				pre_e = L.elem[i - 1];
				return OK;
				break;
			}
		}
	}
	else
		return ERROR;
}
Status NextElem(SqList L, ElemType cur_e, ElemType& next_e)
{
	if (L.elem)
	{
		for (int i = 0; i < L.length; ++i)
		{
			if (i == L.length-1 && L.elem[i] == cur_e)
			{
				return ERROR;
			}
			else if (L.elem[i] == cur_e)
			{
				next_e = L.elem[i - 1];
				return OK;
				break;
			}
		}
	}
	else
		return ERROR;
}
Status ListInsert(SqList& L, int i, ElemType e)
{
	if (L.elem)
	{
		if (i<0 || i>ListLength(L)+1) return ERROR;
		if (ListLength(L) >= L.listsize)
		{
			ElemType* newbase = (ElemType*)realloc(L.elem, INCREMENTSIZE*sizeof(ElemType));
			if (!newbase) exit(OVERFLOW);
			L.listsize += INCREMENTSIZE;
			L.elem = newbase;
		}
		ElemType* q = &(L.elem[i - 1]);
		ElemType* p = &(L.elem[ListLength(L) - 1]);
		for (; p >= q ; --p)
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
Status visit(SqList L,int i)
{
	printf("%d ", L.elem[i]);
	return OK;
}
Status ListTraverse(SqList L,Status(*visitptr)(SqList,int)=visit)
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

int main()
{
	SqList L;
	InitList(L);
	int n;
	for (int i = 0; i < 10; i++)
	{
		ListInsert(L, 1, i);
	}
	//遍历：
	ListTraverse(L);
	//插入：
	int e = 66;
	ListInsert(L, 3, e);
	ListTraverse(L);
	//删除：
	ListDelete(L, 5, e);
	printf("删去的数字为：%d\n删除之后的线性表：",e);
	ListTraverse(L);
	printf("%d\n", ListEmpty(L));//非空输出0
	//清空：
	ClearList(L);
	printf("%d\n", ListEmpty(L));//空输出1
	//销毁：
	DestoryList(L);
	return 0;
}