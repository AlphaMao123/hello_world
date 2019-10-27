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
}//InitList
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
}//DestoryList
int ListLength(SqList L)
{
	if (L.elem)
		return L.length;
	else
		return ERROR;
}//ListLength

Status compare(ElemType a, ElemType b)
{
	if (a == b)
		return TRUE;
	else
		return FALSE;
}//compare
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
}//LocateElem

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
}//ListInsert
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
}//ListDelete

Status visit(SqList L, int i)
{
	printf("%d ", L.elem[i]);
	return OK;
}//visit
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
}//ListTraverse

Status change_sort(SqList& L, int n)
{
	int num;//��Ҫ������ѧ��
	int locate;//��Ӧѧ�������Ա��е�λ��
	int change; //ǰ�ƻ���Ƶĳ���
	int m;
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d%d", &num,&change);
		locate = LocateElem(L, num);
		if (-(locate - 1) > change || change > ListLength(L) - locate)
			return ERROR;
		ListDelete(L, locate, m);
		ListInsert(L, locate + change, m);
	}
	return OK;
}//change_sort

int main()
{
	SqList L;
	InitList(L);
	int m;
	int n;
	printf("������ѧ����������");
	scanf("%d", &m);
	printf("������Ҫ�����Ĵ�����");
	scanf("%d", &n);
	for (int i = 1; i <= 8; ++i)
	{
		ListInsert(L, i, i);
	}
	ListTraverse(L);//��ӡ����λ��ǰ������
	change_sort(L, n);//�������еĺ���
	ListTraverse(L);//��ӡ����λ��֮�������
	DestoryList(L);
	return 0;
}