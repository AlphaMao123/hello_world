#include<stdio.h>
#include<stdlib.h>
#include<queue>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define INFINITY INT_MAX;
#define MAX_VERTEX_NUM 20

typedef int Status;
typedef int VertexType;
typedef int VRType;
typedef char InfoType;

typedef enum { DG, DN, UDG, UDN }GraphKind; 
typedef struct ArcCell
{
	VRType adj;
	InfoType* info=NULL;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct MGraph
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum=0, arcnum=0;
	GraphKind kind;
}MGraph;
int LocateVex(MGraph G, VertexType u)
{
	if (G.vexnum == 0) return ERROR;
	bool flag = FALSE;
	int i;
	for ( i = 0; i < G.vexnum; ++i)
	{
		if (G.vexs[i] == u)
		{
			flag = TRUE;
			break;
		}
	}
	if (flag)
		return i;
	else
		return INT_MAX;
}

Status CreateDG(MGraph& G)
{
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	VertexType v1, v2;
	int i, j, k;
	for (i = 0; i < G.vexnum; ++i)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i)
	{
		for (j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	for (k = 0; k < G.arcnum; ++k)
	{
		scanf_s("%d%d", &v1, &v2);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
	}
	return OK;
}

Status CreateDN(MGraph& G)
{
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	VertexType v1, v2;
	VRType w;
	int i, j, k;
	for (i = 0; i < G.arcnum; ++i)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i)
	{
		for (j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	for (k = 0; k < G.arcnum; ++k)
	{
		scanf_s("%d%d%d", &v1, &v2, &w);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
	}
	return OK;
}

Status CreateUDG(MGraph& G)
{
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	VertexType v1, v2;
	int i, j, k;
	for (i = 0; i < G.vexnum; ++i)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i)
	{
		for (j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	for (k = 0; k < G.arcnum; ++k)
	{
		scanf_s("%d%d", &v1, &v2);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
	return OK;
}

Status CreateUDN(MGraph& G)
{
	scanf_s("%d%d", &G.vexnum, &G.arcnum);
	VertexType v1, v2;
	VRType w;
	int i, j, k;
	for (i = 0; i < G.vexnum; ++i)
	{
		scanf_s("%d", &G.vexs[i]);
	}
	for (i = 0; i < G.vexnum; ++i)
	{
		for (j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	for (k = 0; k < G.arcnum; ++k)
	{
		scanf_s("%d%d%d", &v1, &v2, &w);
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);
		G.arcs[i][j].adj = w;
		G.arcs[j][i].adj = G.arcs[i][j].adj;
	}
	return OK;
}

Status CreateGraph(MGraph& G)
{
	scanf_s("%d", &G.kind);
	switch (G.kind)
	{
	case DG: return CreateDG(G);
	case DN: return CreateDN(G);
	case UDG: return CreateUDG(G);
	case UDN: return CreateUDN(G);
	default:
		break;
	}
}

Status DestroyGraph(MGraph& G)
{
	if (G.vexnum == 0) return ERROR;
	for (int i=0; i < G.vexnum; ++i)
	{
		G.vexs[i] = INFINITY;
	}
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
		{
			G.arcs[i][j].adj = INFINITY;
		}
	}
	G.vexnum = 0;
	G.arcnum = 0;
}

VertexType GetVex(MGraph G, VertexType v)
{
	if (G.vexnum == 0) return ERROR;
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (G.vexs[i] == v)
		{
			return G.vexs[i];
			break;
		}
	}
	return INFINITY;
}

Status PutVex(MGraph& G, VertexType v, VertexType value)
{
	if (G.vexnum == 0) return ERROR;
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (G.vexs[i] == v)
		{
			G.vexs[i] = value;
			return OK;
			break;
		}
	}
	return ERROR;
}

int FirstAdjVex(MGraph G, VertexType v)
{
	if (G.vexnum == 0) return -1;
	int i, j;
	bool flag = FALSE;
	for (i = 0; i < G.vexnum; ++i)
	{
		if (G.vexs[i] == v)
		{
			flag = TRUE;
			break;
		}
	}
	if (!flag)
		return -1;
	flag = FALSE;
	for (j = 0; j < G.vexnum; ++j)
	{
		if (G.arcs[i][j].adj!=INT_MAX)
		{
			flag = TRUE;
			break;
		}
	}
	if (flag)
		return j;
	else
		return -1;
}

int NextAdjVex(MGraph& G, VertexType v, VertexType w)
{
	if (G.vexnum == 0) return -1;
	int i = LocateVex(G, v), j = LocateVex(G, w);
	bool flag=FALSE;
	if (i == INT_MAX || j == INT_MAX) return INFINITY;
	for (++j; j < G.vexnum; ++j)
	{
		if (G.arcs[i][j].adj != INT_MAX)
		{
			flag = TRUE;
			break;
		}
	}
	if (flag)
		return j;
	else
		return -1;
}

Status InsertVex(MGraph& G, VertexType v)
{
	if (G.vexnum == 0) return ERROR;
	if (G.vexnum + 1 > MAX_VERTEX_NUM) return ERROR;
	++G.vexnum;
	G.vexs[G.vexnum - 1] = v;
}

Status DeleteVex(MGraph& G, VertexType v)
{
	if (G.vexnum == 0) return ERROR;
	if (LocateVex(G, v) == INT_MAX) return ERROR;
	int locate=LocateVex(G,v);
	for (int i = locate; i < G.vexnum - 1; ++i)
	{
		G.vexs[i] = G.vexs[i + 1];
	}
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = locate; j < G.vexnum - 1; ++j)
		{
			G.arcs[i][j] = G.arcs[i][j + 1];
		}
	}
	for (int j = 0; j < G.vexnum - 1; ++j)
	{
		for (int i = locate; i < G.vexnum - 1; ++i)
		{
			G.arcs[i][j] = G.arcs[i + 1][j];
		}
	}
	--G.vexnum;
	G.arcnum = 0;
	for (int i = 0; i < G.vexnum; ++i)
	{
		for (int j = 0; j < G.vexnum; ++j)
		{
			if (G.arcs[i][j].adj != INT_MAX)
				++G.arcnum;
		}
	}
	return OK;
}

Status InsertArc(MGraph& G, VertexType v, VertexType w, VRType weight=1)
{
	if (G.vexnum == 0) return ERROR;
	if (LocateVex(G, v) == INT_MAX || LocateVex(G, w) == INT_MAX) return ERROR;
	int i = LocateVex(G, v), j = LocateVex(G, w);
	if (G.kind == DG)
	{
		G.arcs[i][j].adj = weight;
	}
	else if(G.kind==DN)
	{
		G.arcs[i][j].adj = weight;
	}
	else if (G.kind==UDG)
	{
		G.arcs[j][i].adj = G.arcs[i][j].adj = weight;
	}
	else if (G.kind == UDN)
	{
		G.arcs[j][i].adj = G.arcs[i][j].adj = weight;
	}
	return OK;
}

Status DeleteArc(MGraph& G, VertexType v, VertexType w)
{
	if (G.vexnum == 0) return ERROR;
	if (LocateVex(G, v) == INT_MAX || LocateVex(G, w) == INT_MAX) return ERROR;
	int i = LocateVex(G, v), j = LocateVex(G, w);
	if (G.kind == DG || G.kind == DN)
	{
		G.arcs[i][j].adj = INFINITY;
	}
	else if (G.kind == UDG || G.kind == UDN)
	{
		G.arcs[i][j].adj = G.arcs[j][i].adj = INFINITY;
	}
	return OK;
}

bool visited[MAX_VERTEX_NUM];
Status Visit(VertexType v)
{
	if (v != INT_MAX) return ERROR;
	printf("%d", v);
	return OK;
}

Status DFS(MGraph G, int i)
{
	visited[i] = TRUE;
	Visit(G.vexs[i]);
	int w;
	for (w = FirstAdjVex(G, i); w >= 0; w = NextAdjVex(G, i, w))
	{
		if (!visited[w])
			DFS(G, w);
	}
}

Status DFSTraverse(MGraph G)
{
	if (G.vexnum == 0) return ERROR;
	for (int i = 0; i < G.vexnum; ++i)
	{
		visited[i] = FALSE;
	}
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
		{
			DFS(G,i);
		}
	}
	return OK;
}

Status BFSTraverse(MGraph G)
{
	if (G.vexnum == 0) return ERROR;
	for (int i = 0; i < G.vexnum; ++i)
	{
		visited[i] = FALSE;
	}
	std::queue<int> Q;
	for (int i = 0; i < G.vexnum; ++i)
	{
		if (!visited[i])
		{
			visited[i] = TRUE;
			Visit(G.vexs[i]);
			Q.push(i);
		}
		while (!Q.empty())
		{
			int v = Q.front();
			Q.pop();
			for (int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
			{
				if (!visited[w])
				{
					visited[w] = TRUE;
					Visit(w);
					Q.push(w);
				}
			}
		}
	}
}

int main()
{
	return 0;
}