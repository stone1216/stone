
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include<string>
#include<algorithm>
using namespace std;
#define INF 1000

/* Split a string given by parameter str with the symbol specified by parameter
 *  deli, and convert the splited string to integer and save into a vector.
 */
vector<int> split(const char *str, const char *deli)
{
	char buff[100];
	strcpy(buff, str);
	char *p = strtok(buff, deli);
	vector<int> result;
	while(p != NULL)
	{
		result.push_back(atoi(p));
		p = strtok(NULL, deli);
	};
	return result;
}

/* Get the topology matrix by simplified the array of char which is read
 *  from the given file.
 */
vector<vector<int> > topoMatrix(char *graph[], int edge_num)
{
	vector<vector<int> > matrix;
	for( int i = 0; i < edge_num; i++ )
		matrix.push_back(split(*(graph + i), ","));
	return matrix;
}

/* Compute the number of vertex via  the topology matrix */
int numOfVertex(vector<vector<int> > topo)
{
	int num = 0;
	for(unsigned int i = 0; i < topo.size(); i++ )
		num = max(num, max(topo[i][1], topo[i][2]));
	return num + 1;
}

/* Compute the adjacency matrix of this graph */
int* adjacencyMatrix(vector<vector<int> > topo, int vertex_num)
{
	int *result = new int[vertex_num * vertex_num];
	for( int i = 0; i < vertex_num; i++ )
		for( int j = 0; j < vertex_num; j++ )
			*(result + j + i * vertex_num) = (i == j ? 0 : INF);
	
	for(unsigned int i = 0; i < topo.size(); i++ )
	{
		int pos_i = topo[i][1], pos_j = topo[i][2];
		if( topo[i][3] < *(result + pos_j + vertex_num * pos_i) )
			*(result + pos_j + vertex_num * pos_i) = topo[i][3];
	}
	return result;
}

/* Get the constraints for the vertex the optimal path should be through */
vector<int> getConstraints(char *demand, int &src, int &des)
{
	vector<int> constaints = split(demand, ",|");
	src = constaints[0]; des = constaints[1];
	return vector<int>(constaints.begin() + 2, constaints.end());
}


/* Display adjacency matrix order by rows */
void display(int *adjacencyMatrix, int vertices)
{
	for( int i = 0; i < vertices; i++ )
	{
		   for( int j = 0; j < vertices; j++ )
			  cout<<*(adjacencyMatrix + j + i * vertices)<<"  ";
		   cout<<endl;
	}
}

/* Display the shortest path recursively */
void displayPath(int *path, int length, int des)
{
	if( path[des] == -1 )
		cout<<"No any path to "<<des<<endl;
	else if( path[des] == des )
		cout<<"Path: "<<des;
	else
	{
		displayPath(path, length, path[des]);
		cout<<"=>"<<des;
	}
}

/* Dijkstra algorithm */
int dijkstra(int *adjacency, int vertices, int src, int des, int *path)
{
	int *minDis = new int[vertices]; // length of the shortest path from src to each vertex
	int *S2 = new int[vertices];
	for( int i = 0; i < vertices; i++ )
		S2[i] = 1;
	S2[src] = 0; // vertex src is not of S2

	for( int i = 0; i < vertices; i++ )
	{
		// initialize the shortest distance from src to others vertex
		minDis[i] = *(adjacency + i + src * vertices);//src=>i
		path[i] = minDis[i] < INF ? src : -1;
	}

	// while the destination vertex is still of S2, then proceed
	while(S2[des])
	{
		int minLen = INF, index = -1;
		for( int i = 0; i < vertices; i++ )
			if( S2[i] && ( minDis[i] < minLen ) )
			{
				minLen = minDis[i];
				index = i;
			}
		if( minLen == INF )
			break;
		S2[index] = 0;
		for( int i = 0; i < vertices; i++ )
			if( S2[i] && (*(adjacency + i + index * vertices) < INF) )
			{
				int newLen = minLen + *(adjacency + i + index * vertices);
				if( newLen < minDis[i] )
				{
					path[i] = index;
					minDis[i] = newLen;
				}
			}
	}
	return minDis[des];
}

/*
void demandMatrix(string demand, vector<int> &startEndpoint, vector<int> &demandPoint)
{
	string::size_type index = demand.find_last_of(',');
	string s1(demand.begin(), demand.begin() + index);//input output
	string s2(demand.begin() + index+1, demand.end());//demand
	startEndpoint=split(s1.c_str(), ',');
	demandPoint=split(s1.c_str(), '|');

}
*/

void main()
{
	char *graph[] = {{"0,0,1,1\n"}, {"1,0,2,2\n"},{"2,0,3,1\n"},
		{"3,2,1,3\n"}, {"4,3,1,1\n"},{"5,2,3,1\n"}, {"6,3,2,1\n"}};
	char *demand = "0,5,2|3\n";
	vector<vector<int>> topo = topoMatrix(graph, 7);

	
	vector<int> demandPoint; 
	demandPoint.reserve(50);
	int start, end;
	demandPoint=getConstraints(demand, start, end);

	int *adj = adjacencyMatrix(topo, numOfVertex(topo));
	display(adj, numOfVertex(topo));
	system("pause");
}