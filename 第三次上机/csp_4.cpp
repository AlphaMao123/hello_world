#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0;
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

int StackLength(SqStack S)
{
	if (!S.base) return ERROR;
	return S.stacklength;
}

Status StackEmpty(SqStack S)
{
	if (!S.base) return ERROR;
	if (S.top == S.base) return TRUE;
	else return FALSE;
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

int main()
{
	SqStack S;
	InitStack(S);
	int m,nums[100];
	scanf_s("%d", &m);
	for (int i = 0; i < m; ++i)
	{
		scanf_s("%d", &nums[i]);
	}
	int key,change;
	for (int i = 0; i < m; ++i)
	{
		key = i;
		for (int j = i; j < m; ++j)
		{
			if (nums[key] >= nums[j])
			{
				key = j;
			}
		}
		Push(S, nums[key]);
		change = nums[i];
		nums[i] = nums[key];
		nums[key] = change;
	}
	int high = 0, low = 0, num1, num2 = S.base[StackLength(S) / 2];
	for (; !StackEmpty(S);)
	{
		Pop(S, num1);
		if (num1 > num2)
			++high;
		else if (num1 < num2)
			++low;
	}
	if (high == low)
		printf("%d", num2);
	else
		printf("-1");
	return 0;
}