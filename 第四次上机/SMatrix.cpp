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
	ElemType data = 0;
	int i=0, j=0;
}Triple;

typedef struct SMatrix
{
	Triple data[MAXSIZE + 1];
	int mu=0, nu=0, tu=0;
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

Status PrintSMatrix(SMatrix M)
{
	if (M.tu == 0) return ERROR;
	bool judge;
	for (int i = 1; i <= M.mu; ++i)
	{
		printf("[ ");
		for (int j = 1; j <= M.nu; ++j)
		{
			judge = FALSE;
			for (int k = 1; k <= M.tu; ++k)
			{
				if (i == M.data[k].i && j == M.data[k].j)
				{
					printf("%d ", M.data[k].data);
					judge = TRUE;
					break;
				}
			}
			if (!judge)
			{
				printf("0 ");
			}
		}
		printf("]\n");
	}
	printf("\n");
	return OK;
}

Status CopySMatrix(SMatrix M, SMatrix& T)
{
	if (M.tu == 0) return ERROR;
	T.mu = M.mu;
	T.nu = M.nu;
	T.tu = M.tu;
	for (int i = 1; i <= M.tu; ++i)
	{
		T.data[i].i = M.data[i].i;
		T.data[i].j = M.data[i].j;
		T.data[i].data = M.data[i].data;
	}
	return OK;
}

Status AddSMatrix(SMatrix M, SMatrix N, SMatrix& Q)
{
	if (M.mu != N.mu || M.nu != N.nu) return ERROR;
	Q.mu = M.mu;
	Q.nu = M.nu;
	int m_temp = 1, n_temp = 1, q_len = 1;
	for (; m_temp <= M.tu && n_temp <= N.tu; ++q_len)
	{
		if (M.data[m_temp].i < N.data[n_temp].i)
		{
			Q.data[q_len].i = M.data[m_temp].i;
			Q.data[q_len].j = M.data[m_temp].j;
			Q.data[q_len].data = M.data[m_temp].data;
			++m_temp;
		}
		else if (M.data[m_temp].i > N.data[n_temp].i)
		{
			Q.data[q_len].i = N.data[n_temp].i;
			Q.data[q_len].j = N.data[n_temp].j;
			Q.data[q_len].data = N.data[n_temp].data;
			++n_temp;
		}
		else if (M.data[m_temp].i == N.data[n_temp].i)
		{
			if (M.data[m_temp].j < N.data[n_temp].j)
			{
				Q.data[q_len].i = M.data[m_temp].i;
				Q.data[q_len].j = M.data[m_temp].j;
				Q.data[q_len].data = M.data[m_temp].data;
				++m_temp;
			}
			else if (M.data[m_temp].j > N.data[n_temp].j)
			{
				Q.data[q_len].i = N.data[n_temp].i;
				Q.data[q_len].j = N.data[n_temp].j;
				Q.data[q_len].data = N.data[n_temp].data;
				++n_temp;
			}
			else if (M.data[m_temp].j == N.data[n_temp].j)
			{
				Q.data[q_len].i = M.data[m_temp].i;
				Q.data[q_len].j = M.data[m_temp].j;
				Q.data[q_len].data = M.data[m_temp].data + N.data[n_temp].data;
				++n_temp;
				++m_temp;
			}
		}
	}
	for (; m_temp <= M.tu; ++m_temp,++q_len)
	{
		Q.data[q_len].i = M.data[m_temp].i;
		Q.data[q_len].j = M.data[m_temp].j;
		Q.data[q_len].data = M.data[m_temp].data;
	}
	for (; n_temp <= N.tu; ++n_temp, ++q_len)
	{
		Q.data[q_len].i = N.data[n_temp].i;
		Q.data[q_len].j = N.data[n_temp].j;
		Q.data[q_len].data = N.data[n_temp].data;
	}
	Q.tu = q_len-1;
	return OK;
}

Status SubtMatrix(SMatrix M, SMatrix N, SMatrix& Q)
{
	if (M.mu != N.mu || M.nu != N.nu) return ERROR;
	Q.mu = M.mu;
	Q.nu = M.nu;
	int m_temp = 1, n_temp = 1, q_len = 1;
	for (; m_temp <= M.tu && n_temp <= N.tu; ++q_len)
	{
		if (M.data[m_temp].i < N.data[n_temp].i)
		{
			Q.data[q_len].i = M.data[m_temp].i;
			Q.data[q_len].j = M.data[m_temp].j;
			Q.data[q_len].data = M.data[m_temp].data;
			++m_temp;
		}
		else if (M.data[m_temp].i > N.data[n_temp].i)
		{
			Q.data[q_len].i = N.data[n_temp].i;
			Q.data[q_len].j = N.data[n_temp].j;
			Q.data[q_len].data = -N.data[n_temp].data;
			++n_temp;
		}
		else if (M.data[m_temp].i == N.data[n_temp].i)
		{
			if (M.data[m_temp].j < N.data[n_temp].j)
			{
				Q.data[q_len].i = M.data[m_temp].i;
				Q.data[q_len].j = M.data[m_temp].j;
				Q.data[q_len].data = M.data[m_temp].data;
				++m_temp;
			}
			else if (M.data[m_temp].j > N.data[n_temp].j)
			{
				Q.data[q_len].i = N.data[n_temp].i;
				Q.data[q_len].j = N.data[n_temp].j;
				Q.data[q_len].data = -N.data[n_temp].data;
				++n_temp;
			}
			else if (M.data[m_temp].j == N.data[n_temp].j)
			{
				Q.data[q_len].i = M.data[m_temp].i;
				Q.data[q_len].j = M.data[m_temp].j;
				Q.data[q_len].data = M.data[m_temp].data - N.data[n_temp].data;
				if (Q.data[q_len].data == 0)
					--q_len;
				++n_temp;
				++m_temp;
			}
		}
	}
	for (; m_temp <= M.tu; ++m_temp, ++q_len)
	{
		Q.data[q_len].i = M.data[m_temp].i;
		Q.data[q_len].j = M.data[m_temp].j;
		Q.data[q_len].data = M.data[m_temp].data;
	}
	for (; n_temp <= N.tu; ++n_temp, ++q_len)
	{
		Q.data[q_len].i = N.data[n_temp].i;
		Q.data[q_len].j = N.data[n_temp].j;
		Q.data[q_len].data = -N.data[n_temp].data;
	}
	Q.tu = q_len-1;
	return OK;
}

Status MultSMatrix(SMatrix M, SMatrix N, SMatrix& Q)
{
	if (M.nu != N.mu) return ERROR;
	Q.mu = M.mu;
	Q.nu = N.nu;
	int m_temp = 1, n_temp = 1, q_len = 1, count = 0;
	for (; m_temp <= M.tu;)
	{
		n_temp = 1, count = 0;
		for (; n_temp <= N.tu; ++n_temp)
		{
			if (M.data[m_temp].j == N.data[n_temp].i)
			{
				Q.data[q_len].i = M.data[m_temp].i;
				Q.data[q_len].j = N.data[n_temp].j;
				Q.data[q_len].data = M.data[m_temp].data * N.data[n_temp].data;
				if (q_len >= 2 && Q.data[q_len].i == Q.data[q_len - 1].i && Q.data[q_len].j == Q.data[q_len - 1].j)
					Q.data[q_len - 1].data += Q.data[q_len].data;
				++q_len;
			}
		}
		++m_temp;
	}
	Q.tu = q_len-2;
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

int main()
{
	SMatrix M, N, Q;
	//创建矩阵：
	CreateSMatrix(M);
	CreateSMatrix(N);
	//打印创建的矩阵：
	PrintSMatrix(M);
	PrintSMatrix(N);
	//矩阵相加：
	AddSMatrix(M, N, Q);
	//打印相加后的结果
	PrintSMatrix(Q);
	//矩阵相减：
	SubtMatrix(M, N, Q);
	//打印相减后的结果：
	PrintSMatrix(Q);
	//矩阵相乘：
	MultSMatrix(M, N, Q);
	//打印矩阵相乘后的结果：
	PrintSMatrix(Q);
	//矩阵转置：
	TransposeSMatrix(M, Q);
	//打印矩阵转置后的结果：
	PrintSMatrix(Q);
	//测试销毁矩阵的操作是否成功：
	printf("%d %d %d", DestorySMatrix(M),DestorySMatrix(N),DestorySMatrix(Q));
	return 0;
}