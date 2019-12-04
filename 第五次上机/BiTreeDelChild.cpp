#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char ElemType;

typedef struct BiTNode
{
	ElemType data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

Status InitBiTree(BiTree& T)
{
	T = (BiTNode*)malloc(sizeof(BiTNode));
	if (!T->lchild) exit(OVERFLOW);
	T->lchild = T->rchild = NULL;
	return OK;
}

Status DestoryBiTree(BiTree& T)
{
	if (T)
	{
		if (DestoryBiTree(T->lchild))
		{
			if (DestoryBiTree(T->rchild))
			{
				free(T);
				T = NULL;
				if (!T)
					return OK;
				else
					return ERROR;
			}
		}
	}
	else
		return OK;
}

Status CreateBiTree(BiTree& T)
{
	ElemType ch;
	ch = getchar();
	if (ch == ' ')
		T = NULL;
	else
	{
		T = (BiTNode*)malloc(sizeof(BiTNode));
		if (!T) exit(OVERFLOW);
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

BiTNode* Value(BiTree T, BiTNode e)
{
	static BiTNode* ptr;
	if (!T) return ERROR;
	if (T->data == e.data)
	{
		ptr = T;
		return ptr;
	}
	if (Value(T->lchild, e)) return ptr;
	if (Value(T->rchild, e)) return ptr;
}

Status DeleteChild(BiTree T, BiTNode* p)
{
	if (!T) return ERROR;
	if (T->data == p->data)
	{
		DestoryBiTree(T->lchild);
		DestoryBiTree(T->rchild);
		return OK;
	}
	DeleteChild(T->lchild, p);
	DeleteChild(T->rchild, p);
	return OK;
}

Status Visit(BiTNode* p)
{
	if (!p) return ERROR;
	printf("%c ", p->data);
	return OK;
}

Status PreOrderTraverse(BiTree T)
{
	if (T)
	{
		Visit(T);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
		return OK;
	}
	else
		return OK;
}

int main()
{
	BiTree T;
	BiTNode* p=(BiTNode*)malloc(sizeof(BiTNode));
	p->data = 'D';
	printf("%d\n", InitBiTree(T));
	CreateBiTree(T);
	PreOrderTraverse(T);
	printf("\n");
	DeleteChild(T, p);
	PreOrderTraverse(T);
	printf("\n");
	printf("%d\n", DestoryBiTree(T));
	return 0;
}