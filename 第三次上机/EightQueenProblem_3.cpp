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

int count = 0;
int total = 0;
typedef int Status;
class Queen
{
public:
	int row;
	int column;
	Queen(int r = 0, int c = 0)
	{
		row = r;
		column = c;
	}
};
typedef Queen ElemType;
typedef struct SqStack
{
	ElemType* base;
	ElemType* top;
	int stacksize;
	int stacklength;
}SqStack;

Status InitStack(SqStack& S)
{
	S.base = (ElemType*)malloc(STACK_INIT_SIZE * sizeof(Queen));
	if (!S.base) exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	S.stacklength = 0;
	return OK;
}

Status ClearStack(SqStack& S)
{
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacklength = 0;
	return OK;
}

Status DestroyStack(SqStack& S)
{
	if (!S.base) return ERROR;
	S.top = S.base;
	free(S.base);
	S.stacksize = 0;
	S.stacklength = 0;
	return OK;
}

Status StackEmpty(SqStack S)
{
	if (!S.base) return ERROR;
	if (S.base == S.top)
		return TRUE;
	else
		return FALSE;
}

int StackLength(SqStack S)
{
	if (!S.base) return ERROR;
	return S.stacklength;
}

Status Pop(SqStack& S, ElemType& q)
{
	if (!S.base || StackEmpty(S)) return ERROR;
	q = *(--S.top);
	--S.stacklength;
	return OK;
}

Status Push(SqStack& S, ElemType q)
{
	if (!S.base) return ERROR;
	if (StackLength(S) >= S.stacksize)
	{
		ElemType* newbase = (ElemType*)realloc(S.base, STACKINCREMENT * sizeof(ElemType));
		if (!newbase) exit(OVERFLOW);
		S.stacksize += STACKINCREMENT;
		S.base = newbase;
	}
	*(S.top++) = q;
	++S.stacklength;
	return OK;
}

Status StackTraverse(SqStack S)
{
	if (!S.base) return ERROR;
	for (int i = 0; i < StackLength(S); ++i)
	{
		printf("(%d,%d) ", S.base[i].row, S.base[i].column);
	}
	printf("\n");
	return OK;
}

Status Compare(ElemType p1, ElemType p2)
{
	if (p1.row == p2.row && p1.column == p2.column)
		return TRUE;
	else
		return FALSE;
}

Status IfInStack(SqStack S, ElemType q, Status(*compareptr)(ElemType, ElemType) = Compare)
{
	if (!S.base) return ERROR;
	for (int i = 0; i < StackLength(S); ++i)
	{
		if (compareptr(q, S.base[i]))
		{
			return TRUE;
		}
	}
	return FALSE;
}

int EmptyRow(SqStack S)
{
	int nums[8];
	int EmptyRow[8] = { 0 }, row;
	for (int i = 0; i < 8; ++i)//8
	{
		nums[i] = i;
	}
	for (int i = 0; i < 8; ++i)//8
	{
		bool Flag = FALSE;
		for (int j = 0; j < StackLength(S); ++j)
		{
			if (nums[i] == S.base[j].row)
			{
				Flag = TRUE;
				break;
			}
		}
		if (!Flag)
		{
			EmptyRow[i] = i;
		}
	}
	row = EmptyRow[0];
	for (int i = 0; i < 8; ++i)
	{
		if (row <= EmptyRow[i])
			row = EmptyRow[i];
	}
	return row;
}

Status IfFirstLineEmpty(SqStack S)
{
	if (!S.base) return ERROR;
	for (int i = 0; i < StackLength(S); ++i)
	{
		if (S.base[i].row == 0)
		{
			return FALSE;
		}
	}
	return TRUE;
}

Status IfAttacked(SqStack S)
{
	for (int i = 0; i < StackLength(S); ++i)
	{
		for (int j = 0; j < StackLength(S); ++j)
		{
			if (i != j && (S.base[i].row == S.base[j].row || S.base[i].column == S.base[j].column))
				return TRUE;
			for (int n = 0; n < 8; ++n)//8
			{
				if (i != j && (S.base[i].row + n == S.base[j].row && S.base[i].column + n == S.base[j].column))
					return TRUE;
				if (i != j && (S.base[i].row - n == S.base[j].row && S.base[i].column + n == S.base[j].column))
					return TRUE;
			}
		}
	}
	return FALSE;
}

Status EightQueen(SqStack& S, int i, int j, int n)
{
	++total;
	Queen Q(i, j);
	for (int r = Q.row; r < 8; ++r)//8
	{
		for (int c = Q.column; c < 8; ++c)//8
		{
			Queen p(r, c);
			Push(S, p);
			Queen q(0, n);
			if (!IfInStack(S, q))
			{
				if (IfAttacked(S))
					Pop(S, p);
				else
				{
					break;
				}
			}
			else
			{
				ClearStack(S);
				return OK;
			}
		}
		Q.column = 0;
	}
	if (!IfFirstLineEmpty(S))
	{
		if (StackLength(S) < 8)//8
		{
			Queen p;
			int m = EmptyRow(S);
			for (int i = 0; i < 8 - m; ++i)//8
			{
				Pop(S, p);
			}
			EightQueen(S, p.row, ++p.column, n);
		}
		else
		{
			++count;
			StackTraverse(S);
			Queen p;
			Pop(S, p);
			EightQueen(S, p.row, ++p.column, n);
		}
	}
	ClearStack(S);
	return OK;
}

int main()
{
	SqStack S;
	InitStack(S);
	for (int i = 1; i <= 8; ++i)//8
	{
		EightQueen(S, 0, i-1, i);
		//printf("%d\n", total);
	}
	printf("解的总数：%d", count);
	DestroyStack(S);
	return 0;
}