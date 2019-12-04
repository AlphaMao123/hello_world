#include<stdio.h>
#include<stdlib.h>
#include<queue>
#include<vector>
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

Status If_CompleteBiTree(BiTree T)
{
	if (!T) return ERROR;
	std::queue<std::pair<BiTNode*, int>> Q;
	std::vector<int> L;
	int n = 0;
	Q.push(std::make_pair(T, ++n));
	for (; !Q.empty();)
	{
		T = Q.front().first;
		L.push_back(Q.front().second);
		Q.pop();
		if (T->lchild)
			Q.push(std::make_pair(T->lchild, ++n));
		else
			++n;
		if (T->rchild)
			Q.push(std::make_pair(T->rchild, ++n));
		else
			++n;
	}
	for (int i = 0; i < L.size(); ++i)
	{
		if (L[i] == i + 1)
			continue;
		else
		{
			return FALSE;
		}
	}
	return OK;
}

int main()
{
	BiTree T;
	printf("%d\n", InitBiTree(T));
	CreateBiTree(T);
	printf("%d\n", If_CompleteBiTree(T));
	printf("%d\n", DestoryBiTree(T));
	return 0;
}