#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<queue>
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

Status ClearBiTree(BiTree& T)
{
	BiTNode* p = T->lchild;
	BiTNode* q = T->rchild;
	T->lchild = NULL;
	T->rchild = NULL;
	if (DestoryBiTree(p) && DestoryBiTree(q))
		return OK;
	else
		return ERROR;
}

Status BiTreeEmpty(BiTree T)
{
	if (T->lchild == NULL && T->rchild == NULL)
		return OK;
	else
		return ERROR;
}

int BiTreeDepth(BiTree T)
{
	static int count = 0;
	static int max_depth = 0;
	if (!T) return OK;
	++count;
	if (count > max_depth)
		max_depth = count;
	BiTreeDepth(T->lchild);
	BiTreeDepth(T->rchild);
	--count;
	return max_depth;
}

BiTNode* Root(BiTree T)
{
	if (!T) return ERROR;
	return T;
}

BiTNode* Value(BiTree T,  BiTNode e)
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

Status Assign(BiTree T, BiTNode& e, ElemType value)
{
	if (!T) return ERROR;
	T = Value(T, e);
	if (T)
	{
		T->data = value;
	}
	return OK;
}

BiTNode* Parent(BiTree T, BiTNode e)
{
	static BiTNode* ptr;
	if (!T) return NULL;
	static std::stack<BiTNode*> S;
	if (T->data == e.data)
	{
		if (!S.empty())
		{
			ptr = S.top();
			return ptr;
		}
		else
		{
			ptr = NULL;
			return ptr;
		}
	}
	S.push(T);
	Parent(T->lchild, e);
	Parent(T->rchild, e);
	S.pop();
	return ptr;
}

BiTNode* LeftChild(BiTree T, BiTNode e)
{
	if (!T) return NULL;
	BiTNode* ptr = Value(T, e);
	if (ptr->lchild)
		return ptr->lchild;
	else
	{
		ptr = (BiTNode*)malloc(sizeof(BiTNode));
		ptr->data = '0';
		return ptr;
	}
}

BiTNode* RightChild(BiTree T, BiTNode e)
{
	if (!T) return NULL;
	BiTNode* ptr = Value(T, e);
	if (ptr->rchild)
		return ptr->rchild;
	else
	{
		ptr = (BiTNode*)malloc(sizeof(BiTNode));
		ptr->data = '0';
		return ptr;
	}
}

BiTNode* LeftSibling(BiTree T, BiTNode e)
{
	if (!T) return NULL;
	BiTNode* ptr = Parent(T, e);
	if (ptr && ptr->lchild && ptr->lchild->data!=e.data)
	{
		
		return ptr->lchild;
	}
	else
	{
		ptr = (BiTNode*)malloc(sizeof(BiTNode));
		ptr->data = '0';
		return ptr;
	}
}

BiTNode* RightSibling(BiTree T, BiTNode e)
{
	if (!T) return NULL;
	BiTNode* ptr = Parent(T, e);
	if (ptr && ptr->rchild && ptr->rchild->data != e.data)
	{

		return ptr->rchild;
	}
	else
	{
		ptr = (BiTNode*)malloc(sizeof(BiTNode));
		ptr->data = '0';
		return ptr;
	}
}

Status InsertChild(BiTree T, BiTNode* p, int LR, BiTNode* c)
{
	if (!T) return ERROR;
	if (c->rchild) return ERROR;
	BiTNode* ptr;
	if (LR == 0)
	{
		ptr = p->lchild;
		p->lchild = c;
		c->rchild = ptr;
	}
	else if (LR == 1)
	{
		ptr = p->rchild;
		p->rchild = c;
		c->rchild = ptr;
	}
	return OK;
}

Status DeleteChild(BiTree T, BiTNode* p, int LR)
{
	if (!T) return ERROR;
	if (LR == 0)
	{
		DestoryBiTree(p->lchild);
	}
	else if (LR == 1)
	{
		DestoryBiTree(p->rchild);
	}
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

Status InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);
		Visit(T);
		InOrderTraverse(T->rchild);
		return OK;
	}
	else
		return OK;
}

Status PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		Visit(T);
		return OK;
	}
	else
		return OK;
}

Status LevelOrderTraverse(BiTree T)
{
	if (!T) return ERROR;
	std::queue<BiTNode*> Q;
	BiTNode* p;
	Q.push(T);
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		Visit(p);
		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);
	}
	return OK;
}

int main()
{
	BiTree T;
	//初始化：
	printf("%d\n",InitBiTree(T));
	//创建：
	CreateBiTree(T);
	//销毁：
	printf("%d\n", DestoryBiTree(T));
	return 0;
}