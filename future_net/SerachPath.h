#ifndef SERACHPATH_H
#define SERACHPATH_H
#include<iostream>
#include<map>
#include"Init.h"
using namespace std;
//

int Cond(int path[], int d)
{
	int flag1 = 0, f1,  i, j;
	for (i = 0; i < vn; i++)
	{
		f1 = 1;
		for (j = 0; j <= d; j++)
		if (path[j] == V1[i])
		{
			f1 = 0;
			break;
		}
		flag1 += f1;
	}
	if (flag1 == 0)
		return 1;
	else
		return 0;
}

int weight(int xPoint, int yPoint)
{
	Node *ptr = &(head[xPoint]);
	int num=0;
	while (ptr!= NULL)
	{
		if (ptr->val == yPoint)
		{
			num = ptr->info;
			return num;
		}
		ptr = ptr->next;
	}
	return num;

}

void CovertToPath(int path[],int d,int edge_path[])
{
    for(int i=0;i<d;i++)
    {
        int xPoint=path[i];
        int yPoint=path[i+1];
     Node *ptr = &(head[xPoint]);
     while (ptr!= NULL)
      {
        if (ptr->val == yPoint)
        {
            edge_path[i] = ptr->edge_num;
        }
        ptr = ptr->next;
      }

    }

}

int computeWeight(int path[],int d)
{
	int weightTotal = 0;
	for (int i = 0; i < d; i++)
	{
		weightTotal+= weight(path[i], path[i + 1]);
	}

	return weightTotal;
}

void TravPath(int u, int v, int d)
{
	int w, i;
	Node *p;
	visited[u] = 1;
	d++; path[d] = u;
	if (u == v&&Cond(path, d))
	{

		for (i = 0; i <= d; i++)
			cout << path[i] << " ";
		int weight=computeWeight(path,d);//计算权值
		if (foreWeight == -1)//初始化
		{
			foreWeight = weight;
			for (i = 0; i <= d; i++)
				pathMin[i] = path[i];
			dMin = d;
            CovertToPath(pathMin,dMin,pathEdgeMin);
            route.clear();
            route.insert(make_pair(dMin, pathEdgeMin));

		}
		//如果该权值小于上次权值，则更新最短路径
		if (weight < foreWeight)
		{
			foreWeight = weight;
			for (i = 0; i <= d; i++)
				pathMin[i] = path[i];
			dMin = d;
            CovertToPath(pathMin,dMin,pathEdgeMin);
            route.clear();
            route.insert(make_pair(dMin, pathEdgeMin));
		}

		cout << "    权值 " << weight;
		cout << endl;
       // flag=1;
   // return;
	}
	p = head[u].next;
    while (p != NULL)
	{
        if(flag==1)
            break;
		w = p->val;
		if (visited[w] == 0)
            TravPath(w, v, d);
        p = p->next;

	}
    visited[u] = 0;

}





#endif
