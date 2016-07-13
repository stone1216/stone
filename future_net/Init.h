#ifndef INIT_H__
#define INIT_H__
#include<map>

struct Node//结点定义
{
	int  val;
	int info;//存放权值；
    int edge_num;//
	struct Node *next;
};
Node *head;//图的邻接表表示
int *visited;//访问标记
int *path;//临时路径存储
int *V1;//必经节点
int vn;//必经节点个数；
int *pathMin;//最优路径存储
int *pathEdgeMin;//最优路径存储
int dMin;//最优路径长度
int foreWeight = -1;
int flag=0;
map<int, int * > route;




#endif
