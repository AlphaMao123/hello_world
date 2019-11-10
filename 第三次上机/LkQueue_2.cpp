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
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode,*QueuePtr;

typedef struct LKQueue
{
	QueuePtr front;
	QueuePtr rear;
}LKQueue;

Status InitQueue(LKQueue& Q)
{
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LKQueue& Q)
{
	if (!Q.front) return ERROR;
	while (Q.front)
	{
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	printf("¶ÓÁÐÏú»Ù³É¹¦£¡\n");
	return OK;
}

Status ClearQueue(LKQueue& Q)
{
	if (!Q.front) return OK;
	QueuePtr p = Q.front->next,q;
	Q.front->next = NULL;
	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	Q.rear = Q.front;
	printf("¶ÓÁÐÇå¿Õ³É¹¦£¡\n");
	return OK;
}

Status QueueEmpty(LKQueue& Q)
{
	if (!Q.front) return OK;
	if (Q.front == Q.rear)
		return TRUE;
	else
		return FALSE;
}

int QueueLength(LKQueue Q)
{
	if (!Q.front) return ERROR;
	int count=0;
	QueuePtr p = Q.front->next;
	while (p != NULL)
	{
		++count;
		p = p->next;
	}
	return count;
}

Status GetHead(LKQueue Q, ElemType& e)
{
	if (!Q.front) return ERROR;
	e = Q.front->next->data;
	return OK;
}

Status EnQueue(LKQueue& Q, ElemType e)
{
	if (!Q.front) return ERROR;
	QueuePtr new_node = (QueuePtr)malloc(sizeof(QNode));
	new_node->data = e;
	new_node->next = NULL;
	Q.rear->next = new_node;
	Q.rear = new_node;
	return OK;
}

Status DeQueue(LKQueue& Q, ElemType& e)
{
	if (!Q.front) return ERROR;
	QueuePtr p = Q.front->next;
	Q.front->next = Q.front->next->next;
	e = p->data;
	free(p);
	return OK;
}

Status visit(QueuePtr p)
{
	if (p)
	{
		printf("%d ", p->data);
		return OK;
	}
	else
		return ERROR;
}

Status QueueTraverse(LKQueue Q, Status(*visitptr)(QueuePtr) = visit)
{
	if (!Q.front) return ERROR;
	QueuePtr p = Q.front->next;
	for (p; visitptr(p); p = p->next);
	printf("\n");
	return OK;
}

int main()
{
	LKQueue Q;
	int num;
	//³õÊ¼»¯
	InitQueue(Q);
	//²âÊÔQueueEmptyº¯Êý£º
	printf("%d\n\n", QueueEmpty(Q));
	//²âÊÔEnQueueº¯Êý£º
	for (int i = 1; i < 10; ++i)
	{
		EnQueue(Q, i);
	}
	//²âÊÔQueueTraverseº¯Êý£º
	QueueTraverse(Q);
	printf("%d\n\n", QueueEmpty(Q));
	//²âÊÔQueueLengthº¯Êý£º
	printf("%d\n\n", QueueLength(Q));
	//²âÊÔDeQueueº¯Êý£º
	DeQueue(Q, num);
	printf("%d\n", num);
	printf("%d\n\n", QueueLength(Q));
	//²âÊÔGetHeadº¯Êý£º
	GetHead(Q, num);
	printf("%d\n\n", num);
	//²âÊÔClearQueueº¯Êý£º
	ClearQueue(Q);
	printf("%d\n\n", QueueEmpty(Q));
	//²âÊÔDestroyQueueº¯Êý:
	DestroyQueue(Q);
	return 0;
}