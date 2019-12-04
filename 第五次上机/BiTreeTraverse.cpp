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

Status Visit(BiTNode* p)
{
	if (!p) return ERROR;
	printf("%c ", p->data);
	return OK;
}
//����������ݹ飩
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
//����������ݹ飩
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
//����������ݹ飩
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
//����������ǵݹ飩
Status PreOrderTraverse_non_recursive(BiTree T)
{
	if (!T) return ERROR;
	std::stack<std::pair<BiTNode*, bool>> S;
	BiTNode* root;
	bool visited;
	S.push(std::make_pair(T, false));
	while (!S.empty())
	{
		root = S.top().first;
		visited = S.top().second;
		S.pop();
		if (root == NULL)
			continue;
		if (visited)
			Visit(root);
		else
		{
			S.push(std::make_pair(root->rchild, false));
			S.push(std::make_pair(root->lchild, false));
			S.push(std::make_pair(root,true));
		}
	}
	return OK;
}
//����������ǵݹ飩
Status InOrderTraverse_non_recursive(BiTree T)
{
	if (!T) return ERROR;
	std::stack<std::pair<BiTNode*, bool>> S;
	BiTNode* root;
	bool visited;
	S.push(std::make_pair(T, false));
	while (!S.empty())
	{
		root = S.top().first;
		visited = S.top().second;
		S.pop();
		if (root == NULL)
			continue;
		if (visited)
			Visit(root);
		else
		{
			S.push(std::make_pair(root->rchild, false));
			S.push(std::make_pair(root, true));
			S.push(std::make_pair(root->lchild, false));
		}
	}
	return OK;
}
//����������ǵݹ飩
Status PostOrderTraverse_non_recursive(BiTree T)
{
	if (!T) return ERROR;
	std::stack<std::pair<BiTNode*, bool>> S;
	BiTNode* root;
	bool visited;
	S.push(std::make_pair(T, false));
	while (!S.empty())
	{
		root = S.top().first;
		visited = S.top().second;
		S.pop();
		if (root == NULL)
			continue;
		if (visited)
			Visit(root);
		else
		{
			S.push(std::make_pair(root, true));
			S.push(std::make_pair(root->rchild, false));
			S.push(std::make_pair(root->lchild, false));
		}
	}
	return OK;
}
//��α���
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
	printf("%d\n", InitBiTree(T));
	CreateBiTree(T);
	//���������
	PreOrderTraverse(T);
	printf("\n");
	PreOrderTraverse_non_recursive(T);
	printf("\n");
	//���������
	InOrderTraverse(T);
	printf("\n");
	InOrderTraverse_non_recursive(T);
	printf("\n");
	//���������
	PostOrderTraverse(T);
	printf("\n");
	PostOrderTraverse_non_recursive(T);
	printf("\n");
	//��α�����
	LevelOrderTraverse(T);
	printf("\n");
	printf("%d\n", DestoryBiTree(T));
	return 0;
}