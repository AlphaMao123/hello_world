	#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;

typedef struct HfTNode
{
	int weight;
	HfTNode* lchild,* rchild,* next;
}HfTNode,*HfTree;

Status InitHfTree(HfTree& T,int n)
{
	T = (HfTNode*)malloc(sizeof(HfTNode));
	scanf_s("%d", &(T->weight));
	T->lchild = T->rchild = NULL;
	HfTNode* p = T,* q;
	for (int i = 0; i < n-1; ++i)
	{
		q = (HfTNode*)malloc(sizeof(HfTNode));
		scanf_s("%d", &(q->weight));
		q->lchild= q->rchild = NULL;
		p->next = q;
		p = p->next;
	}
	p->next = NULL;
	return OK;
}

Status InsertHfTNode(HfTree& T,int i, HfTNode* p)//该函数不能在链表的末尾插入
{
	HfTNode* ptr_1 = T, * ptr_2 = T->next;
	if (i == 0)
	{
		p->next = T;
		T = p;
	}
	else
	{
		for (int n = 1; n < i; ++n)
		{
			ptr_1 = ptr_1->next;
			ptr_2 = ptr_2->next;
		}
		ptr_1->next = p;
		p->next = ptr_2;
	}
	return OK;
}

Status DeleteHfNode(HfTree& T, int i, HfTNode* p)
{
	HfTNode* ptr_1=T, * ptr_2=T->next;
	if (i == 0)
	{
		p = T;
		T = T->next;
	}
	for (int n = 1; n < i; ++n)
	{
		ptr_1 = ptr_1->next;
		ptr_2 = ptr_2->next;
	}
	if (ptr_2->next == NULL)
	{
		p = ptr_2;
		ptr_1->next = NULL;
	}
	else
	{
		p = ptr_2;
		p->next = NULL;
		ptr_1->next = ptr_2->next;
	}
	return OK;
}

Status HfTNode_sort(HfTree& T)
{
	
	int mark, weight, i, j;
	HfTNode*ptr_1=T,* ptr_2,* min;
	for ( i = 0; ptr_1 != NULL; ptr_1 = ptr_1->next,++i)
	{
		ptr_1 = T;
		for (int j = 0; j < i; ++j)
		{
			ptr_1 = ptr_1->next;
		}
		min = ptr_2 = ptr_1;
		weight = ptr_2->weight;
		for ( j = i; ptr_2 != NULL; ptr_2 = ptr_2->next,++j)
		{
			if (weight >= ptr_2->weight)
			{
				mark = j;
				weight = ptr_2->weight;
				min = ptr_2;
			}
		}
		DeleteHfNode(T, mark, min);
		InsertHfTNode(T, i, min);
	}
	return OK;
}

Status HuffmanCoding(HfTree& T)
{
	HfTNode_sort(T);
	HfTNode* ptr_1 = T, * ptr_2 = T->next,* p;
	p = (HfTNode*)malloc(sizeof(HfTNode));
	p->lchild = ptr_1;
	p->rchild = ptr_2;
	p->weight = ptr_1->weight + ptr_2->weight;
	p->next = NULL;
	if (ptr_2->next != NULL)
	{
		DeleteHfNode(T, 0, ptr_1);
		DeleteHfNode(T, 0, ptr_2);
		InsertHfTNode(T, 0, p);
	}
	else
	{
		ptr_1->next = NULL;
		T = p;
	}
	if (T->next == NULL)
	{
		return OK;
	}
	HuffmanCoding(T);
}

int main()
{
	HfTree T;
	int n;
	scanf_s("%d", &n);
	InitHfTree(T, n);
	HuffmanCoding(T);
	return 0;
}