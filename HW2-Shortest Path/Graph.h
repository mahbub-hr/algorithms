#define _CRT_SECURE_NO_WARNINGS
#include"array_list.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges, a, b ;
    bool directed ;
    ArrayList  *adjList ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * parent, *dist,*start,*finish;
    char *color;
    int time ;

public:
	
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, float w);
    void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
	int getLength(int u);
	element getItem(int u,int i);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	void DFSVisit(int u);
	void printParent();
	void printDist();
	void printStartAndFinish();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    adjList = 0;
    parent = 0;
    color =0;
    start = 0;
    finish = 0;
    dist = 0;
    time = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
       cout << n;
    if(adjList!=0) delete[] adjList ;
    if(parent != 0) delete []parent;
    if(color != 0) delete[]color;
	if(dist != 0) delete []dist;
	if(start != 0) delete []start;
	if(finish != 0) delete []finish;

	adjList = new ArrayList[n+1];
    color = new char[n+1];
	parent = new int[n+1];
	dist = new int[n+1];
	start = new int[n+1];
	finish = new int[n+1];

    for(int i=1; i<=n; i++)
    {
        parent[i]= i;
    }
}

void Graph::addEdge(int u, int v, float w)
{
    if(u<1 || v<1 || u>=nVertices+1 || v>=nVertices+1) return; //u out of range
    this->nEdges++ ;
    cout << u;
    element U,V;
    U.u = u;
    U.v = -1;
    U.weight = w;
    V.u = v;
    V.v = -1;
    V.weight = w;

    adjList[u].insertItem(V) ;
	if(!directed) adjList[v].insertItem(U) ;
}

void Graph::removeEdge(int u, int v)
{
    //write this function

    if(u<1 || v<1 || u>nVertices || v>nVertices) return; //vertex out of range
    this->nEdges-- ;

    element U,V;
    U.u = u; U.v =-1;
    V.u = v; V.v = -1;
	adjList[u].removeItem(V) ;
	if(!directed) adjList[v].removeItem(U) ;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<1 || v<1 || u>nVertices || v>nVertices) return false; //vertex out of range
    element V;
    V.u = v;
    V.v =-1;

    if(adjList[u].searchItem(V) != NULL_VALUE) return true;
    else return false;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<1 || v<1 || u>nVertices || v>nVertices) return false;

    for (int i =0 ; i< adjList[u].getLength(); i++)
    {
         if (adjList[v].searchItem(adjList[u].getItem(i)) != NULL_VALUE) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    if(source<1 || source>nVertices) return ;
    //complete this function
    //initialize BFS variables
    for(int i=1; i<=nVertices; i++)
    {
        color[i] = 'W' ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = 'G';
    dist[source] = 0 ;
    q.enqueue(source) ;
    element v;

    while( !q.empty() )
    {
        //complete this part
       int u = q.dequeue();

        for (int i =0; i < adjList[u].getLength(); i++)
        {

            v = adjList[u].getItem(i);
            if ( color[v.u] == 'W')
            {
                parent[v.u] = u;
                dist[v.u] = dist[u] + 1;
                color[v.u] = 'G';
                q.enqueue(v.u);
            }
        }

        color[u] = 'B' ;
    }
}

void Graph::dfs()
{
    //write this function
    for(int i=1; i<=nVertices; i++)
    {
        color[i] = 'W' ;
        parent[i] = -1 ;
        start[i] = 0;
        finish[i] =0;
    }

    time = 0;
    for (int i =1 ; i<= nVertices ; i++)
    {
        if (color[i] == 'W')
            DFSVisit(i);
    }

}

void Graph::DFSVisit(int u)
{
    time++;
    start[u] = time;
    color[u] = 'G';
    element v;
    for(int i = 0; i < adjList[u].getLength(); i++)
    {
        v = adjList[u].getItem(i);
        if( color[v.u] == 'W')
        {
            parent[v.u] = u;
            DFSVisit(v.u);
        }
    }
    time++;
    finish[u] = time;
    color[u] = 'B';
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return INFINITY ;
    bfs(u);
    return dist[v];
}

int Graph::getLength(int u)
{
	return adjList[u].getLength();
}

element Graph::getItem(int u,int i)
{
	return adjList[u].getItem(i);
}

void Graph::printDist()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d ",dist[i]);
    printf("\n");
}

void Graph::printStartAndFinish()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d:(%d,%d),",i,start[i],finish[i]);
    printf("\n");
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=1;i<=nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j).u);
        }
        printf("\n");
    }
}

void Graph::printParent()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d->%d, ",i,parent[i]);
    printf("\n");
}

Graph::~Graph()
{
    //write your destructor here
    if(parent)  delete []parent;
    if(color) delete []color;
    if(dist) delete[]dist;
    if(start) delete[]start;
    if(finish) delete[]finish;
}

//**********************Graph class ends here******************************
