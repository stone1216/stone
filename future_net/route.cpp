
#include "route.h"
#include "lib_record.h"
#include <stdio.h>
#include<vector>
#include<list>
#include<map>
using namespace std;
#include"Init.h"
#include"SerachPath.h"
#include"read.h""

//Ϊ����Vertex��������
void Create(const vector<vector<int> > EdgeData,int pointNum,int EdgeNum)
{ //Vertex������,EdgeNum�������

    for(int Vertex=0;Vertex<pointNum;Vertex++)
    {
    int j;
    Node *ptr, *newnode;
    head[Vertex].val = Vertex;//��������Vertex��ͷ���
    head[Vertex].info=0;
    head[Vertex].next = NULL;
    ptr = &(head[Vertex]); //̽��ָ��ָ��ͷ���
    for (j = 0; j<EdgeNum; j++)//����ͼ�ı߼���
    {
        if (EdgeData[j][1] == Vertex)//�������ֵΪi
        {//��������������½��
            newnode = new Node;
            newnode->edge_num=EdgeData[j][0];
            newnode->val = EdgeData[j][2];//�붥��i���ӵĶ���ֵ
            newnode->info = EdgeData[j][3];//�붥��i���ӵĶ���ֵ��Ȩֵ
            newnode->next = NULL;
            ptr->next = newnode;//�½������
            ptr = newnode;//ptr������β
        }
    }
    }
}
//�����Vertex������
void Display(int Vertex)
{
    Node *ptr;
    ptr = &(head[Vertex]); //̽��ָ��ָ�������ͷ���
    cout << "Point" << Vertex << "=>";//�������
    while (ptr->next != NULL)
    {
        ptr = ptr->next;
        cout << "[" << ptr->val << "]";
    }
    cout << endl;
}
/*
bool comp(Node *x,Node *y)
{
    return x->info<y->info;
}
void sortByWeight(int numPoint)
{
    for(int i=0;i<numPoint;i++)
    {
        Node *ptr=&head[i];
        list<Node *> temp;
        while(ptr!=NULL)
        {
            temp.push_back(ptr);
            ptr=ptr->next;
        }
        temp.sort(comp);
        int kk=0;
        for(list<Node *>::iterator ite=temp.begin();ite!=temp.end();ite++)
             {
                 (&head[i]+kk)->edge_num=(*ite)->edge_num;
                 (&head[i]+kk)->info=(*ite)->info;
                 (&head[i]+kk)->val=(*ite)->val;
            kk++;
             }

    }

}
*/

void disRoute(map<int, int *> v)
{
    map<int, int *>::iterator ite;
    cout << "The Best Path:  " ;
    for (ite = v.begin(); ite != v.end(); ite++)
    for (int j = 0; j < ite->first; j++)
        cout << (ite->second)[j] << " ";
    cout << endl;

}
bool minWeight(vector<int> v1,vector<int> v2)
{
    return v1[3]<v2[3];
}

//��Ҫ��ɵĹ��������
void search_route(char *graph[5000], int edge_num, char *condition)
{

//    vector<vector<int> > topo = topoMatrix(graph, edge_num);
//      int point_num=numOfVertex(topo);
//        vector<int> demandPoint;
//        demandPoint.reserve(50);
//       int start, end;
//     cout<<"55";
//        //initial parameter
//        demandPoint=getConstraints(condition, start, end);

    vector<vector<int> > topo = topoMatrix(graph, edge_num);
    int point_num=numOfVertex(topo);
    head=new Node[point_num];
    vector<int> demandPoint;
    demandPoint.reserve(50);
    int start, end;

    //initial parameter
    demandPoint=getConstraints(condition, start, end);
    vn=demandPoint.size();
    V1=new int[vn];
    visited=new int[point_num];
    path=new int[point_num];
    pathMin=new int[point_num];
    pathEdgeMin=new int[point_num];
    for(int i=0;i<point_num;i++)
    {
        visited[i]=0;
        path[i]=0;
        pathMin[i]=0;
        pathEdgeMin[i]=0;
    }

    for(int i=0;i<vn;i++)
        V1[i]=demandPoint.at(i);


    sort(topo.begin(),topo.end(),minWeight);
    Create(topo,point_num,edge_num);//��������
    cout << "the Graphic information:" << endl;
    for (int i = 0; i < point_num; i++)
        Display(i);
    vn=demandPoint.size();
    TravPath(start, end, -1);
    disRoute(route);
      for (int i = 0; i <= route.begin()->first; i++)
          record_result(route.begin()->second[i]);


}
