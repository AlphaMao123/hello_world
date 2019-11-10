#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int Status;
typedef int ElemType;
typedef struct SqStack
{
	ElemType* base;
	ElemType* top;
	int stacksize;
	int stacklength;
}SqStack;

Status InitStack(SqStack& S)
{
	S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(ElemType));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	S.stacklength = 0;
	return OK;
}

Status DestroyStack(SqStack& S)
{
	if (!S.base) return ERROR;
	free(S.base);
	S.stacksize = 0;
	S.stacklength = 0;
	printf("Stack destroy succeed!\n");
	return OK;
}

Status ClearStack(SqStack& S)
{
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacklength = 0;
	printf("Stack clear succeed!\n");
	return OK;
}

Status StackEmpty(SqStack S)
{
	if (!S.base) return ERROR;
	if (S.top == S.base) return TRUE;
	else return FALSE;
}

int StackLength(SqStack S)
{
	if (!S.base) return ERROR;
	return S.stacklength;
}

Status GetTop(SqStack S, ElemType& e)
{
	if (!S.base || StackEmpty(S)) return ERROR;
	e = *(--S.top);
	return OK;
}

Status Push(SqStack& S, ElemType e)
{
	if (!S.base) return ERROR;
	if (StackLength(S) >= S.stacksize)
	{
		ElemType* newbase = (ElemType*)realloc(S.base, STACKINCREMENT * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		S.stacksize += STACKINCREMENT;
		S.base = newbase;
	}
	*(S.top++) = e;
	++S.stacklength;
	return OK;
}

Status Pop(SqStack& S, ElemType& e)
{
	if (!S.base || StackEmpty(S)) return ERROR;
	e = *(--S.top);
	--S.stacklength;
	return OK;
}

Status visit(ElemType * p)
{
	printf("%d ", *p);
	return OK;
}

Status StackTraverse(SqStack S, Status(*visitptr)(ElemType*)=visit)
{
	if (!S.base || StackEmpty(S)) return ERROR;
	ElemType* p = S.base;
	for (int i = 1; i <= StackLength(S); ++i,++p)
	{
		visitptr(p);
	}
	printf("\n");
	return OK;
}

int main()
{
	SqStack S;
	int num;
	//³õÊ¼»¯£º
	InitStack(S);
	//²âÊÔStackEmptyº¯Êý£º
	printf("%d\n\n", StackEmpty(S));
	//²âÊÔPushº¯Êý£º
	for (int i = 1; i < 10; ++i)
	{
		Push(S, i);
	}
	//²âÊÔStackTraverseº¯Êý£º
	StackTraverse(S);
	printf("%d\n\n", StackEmpty(S));
	//²âÊÔStackLengthº¯Êý£º
	printf("%d\n\n", StackLength(S));
	//²âÊÔPopº¯Êý£º
	Pop(S, num);
	printf("%d\n", num);
	printf("%d\n\n", StackLength(S));
	//²âÊÔGetTopº¯Êý£º
	GetTop(S, num);
	printf("%d\n\n", num);
	//²âÊÔClearStackº¯Êý£º
	ClearStack(S);
	printf("%d\n\n", StackEmpty(S));
	//²âÊÔDestroyStackº¯Êý£º
	DestroyStack(S);
	return 0;
}

