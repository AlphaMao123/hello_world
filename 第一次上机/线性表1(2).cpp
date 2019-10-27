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
			printf("�����������ٳɹ���\n");
			return OK;
		}
		else
		{
			printf("������������ʧ�ܣ�\n");
			return ERROR;
		}
	}
	else
		return ERROR;
}

Status ClearList(LinkList& L)
{
	if (L.head)
	{
		L.current = L.head->next;
		ListPtr post = L.current->next;
		while (L.current != L.rear)
		{
			free(L.current);
			L.current = post;
			post = post->next;
		}
		free(L.current);
		L.current = L.head;
		L.rear = L.head;
		post = NULL;
		printf("����������ճɹ���\n");
		return OK;
	}
	else
		return ERROR;
}

Status ListEmpty(LinkList L)
{
	if (L.head)
	{
		if (L.head == L.rear)
			return TRUE;
		else
			return FALSE;
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

Status compare(ElemType m,ElemType n)
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
		int counter=1;
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

int main()
{
	//�������ܲ��ԣ�
	LinkList L;
	//�����ʼ����
	InitList(L);
	//ʹ�ò���������ɷ�ΧΪ9~0������
	for (int i = 0; i < 10; ++i)
	{
		ListInsert(L, 1, i);
	}
	//�����������ԣ�
	ListTraverse(L);//��������
	//��������Ĳ��ԣ�
	ListInsert(L, 3, 66);
	ListTraverse(L);
	//ɾ�������Ĳ��ԣ�
	int num;
	ListDelete(L, 3, num);
	ListTraverse(L);
	printf("ɾ�������ǣ�%d\n", num);
	//����ǰ����
	PriorElem(L, 6, num);
	printf("ǰ��Ϊ��%d\n", num);
	//���غ�̣�
	NextElem(L, 6, num);
	printf("���Ϊ��%d\n", num);
	//Ԫ�ض�λ��
	printf("Ԫ��%d�������е�λ��Ϊ��%d\n", num, LocateElem(L, num));
	//��������ȡ����Ӧλ�õ�Ԫ�أ�
	GetElem(L, 5, num);
	printf("��5λ��Ԫ���ǣ�%d\n", num);
	//�������
	printf("�����Ƿ�Ϊ�գ�%d\n", ListEmpty(L));
	ClearList(L);
	printf("�����Ƿ�Ϊ�գ�%d\n", ListEmpty(L));
	//��������
	DestoryList(L);
	return 0;
}