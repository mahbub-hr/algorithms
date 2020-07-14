#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999


class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

    char *color;
    int *parent;
    int *dist;
    int *start;
    int *finish;
    int time;

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs();
	void DFSVisit(int s);
	void printParent();
	void printDist();
	void printStartAndFinish();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	parent = 0;
	color  = 0;
	dist = 0;
	start = 0;
	finish = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(color != 0) delete[]color;
	if(dist != 0) delete []dist;
	if(parent != 0) delete []parent;
	if(start != 0) delete []start;
	if(finish != 0) delete []finish;

    parent = new int[n];
    color = new char[n];
    dist = new int[n];
    start = new int[n];
    finish = new int[n];

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v, int w)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = w;
    if(!directed) matrix[v][u] = w;
    nEdges++;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    nEdges--;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    if(matrix[u][v]==1) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
     if(u<0 || u>=nVertices) return NULL_VALUE;

    int degree =0;

    for (int i=0; i <nVertices;i++)
    {
        if (matrix[u][i] == 1)  degree++;
    }

    return degree;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;

    for (int i =0; i<nVertices ; i++)
        if (matrix[u][i] == 1 && matrix[v][i] == 1) return true;
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    if(source<0 || source>=nVertices ) return;

    for(int i=0; i<nVertices; i++)
    {
        color[i] = 'W';
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = 'G';
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        int u = q.dequeue();

        for (int i =0 ; i< nVertices; i++)
        {
            if ( matrix[u][i] && color[i] == 'W')
            {
                parent[i] = u;
                color[i] = 'G';
                dist[i] = dist[u] + 1;
                q.enqueue(i);
            }
        }

        color[u] = 'B';

    }

}

void Graph::dfs()
{
    //write this function
     for(int i=0; i<nVertices; i++)
    {
        color[i] = 'W';
        parent[i] = -1 ;
    }
    time =0 ;
    for (int i =0 ; i< nVertices ; i++)
    {
        if (color[i] == 'W')
            DFSVisit(i);
    }
}

void Graph::DFSVisit(int u)
{
    time++ ;
    start[u] = time;
    color[u] = 'G';
    for (int i =0;i < nVertices; i++)
    {
        if(matrix[u][i] && color[i] == 'W')
        {
            parent[i] = u;
            DFSVisit(i);
        }
    }

    time++ ;
    finish[u] = time;
    color[u] = 'B';

}
int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return INFINITY;

    bfs(u);

    if (dist[v] != INFINITY) return dist[v];

    return INFINITY ;
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

void Graph::printParent()
{
     for (int i = 0; i < nVertices; i++)
        printf("%d->%d, ",i,parent[i]);
     printf("\n");
}

void Graph::printDist()
{
    for (int i = 0; i < nVertices; i++)
        printf("%d ",dist[i]);
    printf("\n");
}

void Graph::printStartAndFinish()
{
    for (int i = 0; i < nVertices; i++)
        printf("%d:(%d,%d),",i,start[i],finish[i]);
    printf("\n");
}

Graph::~Graph()
{
    //write your destructor here
    if(parent) delete []parent;
    if(color) delete []color;
	if(dist) delete []dist;
	if(start) delete []start;
	if(finish) delete []finish;

    for (int i=0; i<nVertices; i++)
    {
        if(matrix[i])
           delete []matrix[i];
    }

    if(matrix)
       delete []matrix;
}


//**********************Graph class ends here******************************
