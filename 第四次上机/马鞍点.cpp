#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXSIZE 12500

typedef int Status;
typedef int ElemType;
typedef struct Triple
{
	ElemType data=0;
	int i=0;
	int j=0;
}Triple;

typedef struct SMatrix
{
	Triple data[MAXSIZE+1];
	int mu = 0, nu = 0, tu = 0;
}SMatrix;

Status ElemSort(SMatrix& M)
{
	Triple Elem;
	int min;
	for (int i = 1; i <= M.tu; ++i)
	{
		Elem = M.data[i];
		min = i;
		for (int j = i; j <= M.tu; ++j)
		{
			if (Elem.i > M.data[j].i)
			{
				Elem = M.data[j];
				min = j;
			}
			else if (Elem.i == M.data[j].i)
			{
				if (Elem.j > M.data[j].j)
				{
					Elem = M.data[j];
					min = j;
				}
			}
		}
		Elem = M.data[i];
		M.data[i] = M.data[min];
		M.data[min] = Elem;
	}
	return OK;
}

Status CreateSMatrix(SMatrix& M)
{
	printf("Input row and column and total element:\n");
	scanf_s("%d%d%d", &M.mu, &M.nu, &M.tu);
	printf("Input each element:\n");
	for (int i = 1; i <= M.tu; ++i)
	{
		scanf_s("%d%d%d", &M.data[i].i, &M.data[i].j, &M.data[i].data);
	}
	ElemSort(M);
	return OK;
}

Status DestorySMatrix(SMatrix& M)
{
	if (M.tu == 0) return ERROR;
	for (int i = 0; i <= M.tu; ++i)
	{
		M.data[i].i = 0;
		M.data[i].j = 0;
		M.data[i].data = 0;
	}
	M.mu = 0;
	M.nu = 0;
	M.tu = 0;
	return OK;
}

Status TransposeSMatrix(SMatrix M, SMatrix& T)
{
	if (M.tu == 0) return ERROR;
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	for (int i = 1; i <= M.tu; ++i)
	{
		T.data[i].i = M.data[i].j;
		T.data[i].j = M.data[i].i;
		T.data[i].data = M.data[i].data;
	}
	ElemSort(T);
	return OK;
}

Status GetSaddlePoint(SMatrix M)
{
	SMatrix T;
	TransposeSMatrix(M, T);
	int min_in_row[MAXSIZE + 1];
	int max_in_column[MAXSIZE + 1];
	int m_temp = 1;
	for (int i = 1; i <= M.mu; ++i)
	{
		min_in_row[i] = M.data[m_temp].data;
		for (m_temp; m_temp <= M.tu; ++m_temp)
		{
			if (M.data[m_temp].i == i)
			{
				if (M.data[m_temp].data <= min_in_row[i])
				{
					min_in_row[i] = M.data[m_temp].data;
				}
			}
			else
			{
				if (m_temp >= 2 && M.data[m_temp - 1].i != M.data[m_temp].i)
				{
					break;
				}
				else
				{
					min_in_row[i] = 0;
					break;
				}
			}
		}	
	}
	m_temp = 1;
	for (int i = 1; i <= T.mu; ++i)
	{
		max_in_column[i] = T.data[m_temp].data;
		for (m_temp; m_temp <= T.tu; ++m_temp)
		{
			if (T.data[m_temp].i == i)
			{
				if (T.data[m_temp].data >= max_in_column[i])
				{
					max_in_column[i] = T.data[m_temp].data;
				}
			}
			else
			{
				if (m_temp >= 2 && T.data[m_temp - 1].i != T.data[m_temp].i)
				{
					break;
				}
				else
				{
					max_in_column[i] = 0;
					break;
				}
			}
		}
	}
	for (int i = 1; i <= M.mu; ++i)
	{
		for (int j = 1; j <= M.nu; ++j)
		{
			if (min_in_row[i] == max_in_column[j])
			{
				printf("%d\n", min_in_row[i]);
			}
		}
	}
	return OK;
}

int main()
{
	SMatrix M;
	CreateSMatrix(M);
	GetSaddlePoint(M);
	DestorySMatrix(M);
	return 0;
}