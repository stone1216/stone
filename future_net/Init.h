#ifndef INIT_H__
#define INIT_H__
#include<map>

struct Node//��㶨��
{
	int  val;
	int info;//���Ȩֵ��
    int edge_num;//
	struct Node *next;
};
Node *head;//ͼ���ڽӱ��ʾ
int *visited;//���ʱ��
int *path;//��ʱ·���洢
int *V1;//�ؾ��ڵ�
int vn;//�ؾ��ڵ������
int *pathMin;//����·���洢
int *pathEdgeMin;//����·���洢
int dMin;//����·������
int foreWeight = -1;
int flag=0;
map<int, int * > route;




#endif
