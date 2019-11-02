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
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	else
		return ERROR;
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
		printf("���Ա����ٳɹ���\n");
		return OK;
	}
	else
	{
		printf("�������Ա�ʧ�ܣ�\n");
		return ERROR;
	}
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

Status compare(ElemType a, ElemType b)
{
	if (a == b)
		return TRUE;
	else
		return FALSE;
}
int LocateElem(SqList L, ElemType e, Status(*compareptr)(ElemType, ElemType) = compare)//ʹ�ô���Ĭ�ϲ����ĺ���ָ��
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
				return ERROR;//������
		}
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

Status CreateList(SqList& L,ElemType e,...)
{
	if (L.elem)
	{
		if (L.listsize <= e)
		{
			ElemType* new_base = (ElemType*)realloc(L.elem,INCREMENTSIZE * sizeof(ElemType));
			if (!new_base) exit(OVERFLOW);
			L.elem = new_base;
		}
		va_list ap;
		va_start(ap,e);
		for (int i = 0; i < e; ++i)
		{
			L.elem[i] = va_arg(ap, ElemType);
			++L.length;
		}
		return OK;
	}
	else
		return ERROR;
}

Status Insert_sorted(SqList& L)
{
	int num;
	if (L.elem)
	{
		for (int i = 1; i < ListLength(L); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (L.elem[j] >= L.elem[i])
				{
					ListInsert(L, j+1, L.elem[i]);
					ListDelete(L, LocateElem(L,L.elem[i])+1, num);
					break;
				}
			}
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
	//����һ��δ��������Ա�
	CreatList(L, 8, 4, 8, 3, 3, 5, 7, 6, 1);
	//��ӡ������֮ǰ��ֵ
	ListTraverse(L);
	//��������
	Insert_sorted(L);
	//��ӡ������֮���ֵ
	ListTraverse(L);
	//�������Ա�
	DestoryList(L);
	return 0;
}