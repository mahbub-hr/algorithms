#include"array_list.h"
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

class vertex
{
    public:
    int u,w;
};
//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  *adjList, edges, mst_edges ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * rnk;
    int * parent, *dist,*start,*finish;
    char *color;
    int time ;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int isConnected();
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void printMST();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	void DFSVisit(int u);
	void printParent();
	void printDist();
	void printStartAndFinish();

    int find(int u);
    int Union(int x, int y);
    int Kruskal();
    int SBMST();
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    rnk = 0;
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
    if(adjList!=0) delete[] adjList ;
    if(rnk != 0) delete[]rnk;
    if(parent != 0) delete []parent;
    if(color != 0) delete[]color;
	if(dist != 0) delete []dist;
	if(start != 0) delete []start;
	if(finish != 0) delete []finish;

	adjList = new ArrayList[n+1];
    rnk = new int[n+1];
    color = new char[n+1];
	parent = new int[n+1];
	dist = new int[n+1];
	start = new int[n+1];
	finish = new int[n+1];

    for(int i=1; i<=n; i++)
    {
        rnk[i] = 0;
        parent[i]= i;
    }
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<1 || v<1 || u>=nVertices+1 || v>=nVertices+1) return; //u out of range
    this->nEdges++ ;

    element e;
    e.u = u;
    e.v = v;
    e.weight = w;
    edges.insertItem(e) ;

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

	U.v = v;
	edges.removeItem(U);
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

int Graph::isConnected()
{
    bfs(1);
    for(int i =1; i<=nVertices; i++)
    {
        if(color[i] == 'W') return 0;
    }

    return 1;
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

void Graph::printDist()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d ",dist[i]);
    printf("\n");
     cout << "color\n";
    for (int i = 1; i <= nVertices; i++)
        printf("%c ",color[i]);
    printf("\n");
}

void Graph::printStartAndFinish()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d:(%d,%d),",i,start[i],finish[i]);
    printf("\n");
}

int Graph::find(int u)
{
    if(u != parent[u])
        parent[u] = find(parent[u]);
    return parent[u];
}

Graph::Union(int x, int y)
{
    int xroot = find(x);
    int yroot = find(y);

    if(rnk[xroot] > rnk[yroot]) parent[yroot] = xroot;
    else parent[xroot] = yroot;

    if(rnk[xroot] == rnk[yroot]) rnk[yroot]++;

}

int Graph::Kruskal()
{
    for(int i=1; i<=nVertices; i++)
    {
        rnk[i] = 0;
        parent[i]= i;
    }

    int mst_wt = 0;

    edges.Sort();

    for(int i = 0; i<edges.getLength(); i++)
    {
        element e = edges.getItem(i);
        int x = find(e.u);
        int y = find(e.v);
        if(x != y)
        {
         //   cout<<e.u<<" "<<e.v<<endl;
            mst_edges.insertItem(e);
            mst_wt+=e.weight;
            Union(x,y);

        }
    }

    return mst_wt;
}

int Graph::SBMST()
{
    ArrayList sbmst_edges, temp_edges;
    element e;
    int sbmst_wt= INFINITY;
    int wt = 0;

    temp_edges.Copy(mst_edges);

    for(int i =0 ; i<temp_edges.getLength(); i++)
    {
        e = temp_edges.getItem(i);

        if( true)
        {
            removeEdge(e.u,e.v);

            if(!isConnected())
            {
                addEdge(e.u,e.v,e.weight);
                continue;
            }
            else
            {
                mst_edges.setLength(0);
                wt = Kruskal();

                if(sbmst_wt > wt)
                {
                    sbmst_wt =  wt;
                    sbmst_edges.Copy(mst_edges);
                }

                addEdge(e.u,e.v,e.weight);
            }
        }
    }

    sbmst_edges.printList();

    return sbmst_wt;
}

void Graph::printMST()
{
   // printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);


    for(int j=0; j<mst_edges.getLength(); j++)
    {
        printf("%d %d\n", mst_edges.getItem(j).u, mst_edges.getItem(j).v);
    }
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
    if(rnk)  delete []rnk;
    if(color) delete []color;
    if(dist) delete[]dist;
    if(start) delete[]start;
    if(finish) delete[]finish;
}


//**********************Graph class ends here******************************

int main()
{
    int n, nEdge;
    Graph g;
    ifstream fin("input.txt");
    if(!fin)
    {
        cout << "can't open file";
        return 0;
    }

    fin >> n >> nEdge;
    g.setnVertices(n);

    int u,v,w;

    for(int i=0; i<nEdge; i++)
    {
        fin >> u >> v >> w;
        g.addEdge(u,v,w);
    }

//    g.printGraph();
//    cout << endl;
    int wt = g.Kruskal();
    g.printMST();

    cout << wt << endl<<endl;

    int wt2 = g.SBMST();
    cout << wt2 <<endl;

//    while(1)
//    {
//        printf("1. Add edge. 2. Remove edge 3. is Connected\n");
//        printf("4. Has Common Edge. 5. Print Graph 6. BFS\n");
//        printf("7. DFS 8. Get Dist 9. Parent\n");
//        printf("10.Start Time & Finish Time  0. Exit.\n");
//
//        int ch;
//        scanf("%d",&ch);
//        if(ch==2)
//        {
//            int u, v;
//            scanf("%d%d", &u, &v);
//            g.removeEdge(u, v);
//        }
//        else if(ch==3)
//        {
//            printf("Connected %d\n",g.isConnected());
//        }
//        else if (ch == 4)
//        {
//            int u,v;
//            scanf("%d%d",&u,&v);
//            printf("%s\n",g.hasCommonAdjacent(u,v) ? "true" : "false");
//        }
//        else if(ch==5)
//        {
//            g.printGraph();
//        }
//        else if(ch==6)
//        {
//            int s;
//            scanf("%d",&s);
//            g.bfs(s);
//            printf("---------------------------------------------------\n");
//            printf("Dist: ");
//            g.printDist();
//            printf("Parent: ");
//            g.printParent();
//            printf("---------------------------------------------------\n");
//        }
//        else if(ch==7)
//        {
//            g.dfs();
//            printf("---------------------------------------------------\n");
//            printf("Parent: ");
//            g.printParent();
//            printf("(Start,Finish): ");
//            g.printStartAndFinish();
//            printf("---------------------------------------------------\n");
//        }
//        else if(ch==8)
//        {
//            int u,v;
//            scanf("%d%d",&u,&v);
//            printf("---------------------------------------------------\n");
//            printf("Distance between %d and %d = %d\n",u,v,g.getDist(u,v));
//            printf("---------------------------------------------------\n");
//        }
//        else if(ch==9)
//        {
//            g.printParent();
//        }
//        else if(ch==10)
//        {
//           g.printStartAndFinish();
//        }
//        else
//        {
//            break;
//        }
//    }
//
//    return 0;
}
