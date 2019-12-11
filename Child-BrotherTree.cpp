#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
typedef char ElemType;

typedef struct CBTNode
{
	ElemType data;
	CBTNode* child, * brother;
}CBTNode,*CBTree;

Status InitCBTree(CBTree& T)
{
	T = (CBTNode*)malloc(sizeof(CBTNode));
	if (!T) exit(OVERFLOW);
	T->child = T->brother = NULL;
	return OK;
}

Status CreateCBTree(CBTree& T)
{
	ElemType ch;
	scanf_s("%c", &ch);
	if (ch == ' ')
	{
		T = NULL;
		return OK;
	}
	else
	{
		T = (CBTNode*)malloc(sizeof(CBTNode));
		T->data = ch;
		CreateCBTree(T->child);
		CreateCBTree(T->brother);
	}
	return OK;
}

int count = 0, remember = 1;;
int Leftmove(CBTree T, ElemType data)
{
	if (T)
	{
		if (T->data == data)
		{
			remember = count;
			return remember;
		}
		if (T->child)
		{
			++count;
		}
		Leftmove(T->child, data);
		if (Leftmove(T->brother, data))
			--count;
	}
	else
		return ERROR;
	return remember;
}

Status LevelOutput(CBTree T, int i)
{
	std::queue<CBTNode*> Q;
	Q.push(T);
	CBTNode* ptr;
	while (!Q.empty())
	{
		ptr = Q.front();
		Q.pop();
		if (ptr->child != NULL)
		{
			Q.push(ptr->child);
		}
		count = 0;
		if (i-1 == Leftmove(T,ptr->data))
		{
			printf("%c ", ptr->data);
		}
		for (ptr=ptr->brother; ptr != NULL; ptr = ptr->brother)
		{
			if (ptr->child != NULL)
			{
				Q.push(ptr->child);
			}
			count = 0;
			if (i-1 == Leftmove(T,ptr->data))
			{
				printf("%c ", ptr->data);
			}
		}
	}
	return OK;
}

int main()
{
	CBTree T;
	InitCBTree(T);
	CreateCBTree(T);
	//Leftmove(T, 'F');
	LevelOutput(T, 4);
	return 0;
}