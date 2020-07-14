#include<iostream >
#include<fstream>
#include"GraphAdjMatrix.h"

using namespace std;

void initialize(int **&A, int n)
{
    A = new int*[n+1];
    for(int i =1; i<=n; i++)
    {
        A[i] = new int[n+1];
        for(int j =1; j<=n; j++) A[i][j] = 0;
    }
}

int FordFulkerson(Graph &g, int **flow, int n, int source, int target)
{

    int **rGraph = 0;
    initialize(rGraph,n);

    g.Copy(rGraph);
    int maxFlow = 0;
    int min_capacity;
    while (g.bfs(rGraph,source, target) == true)
    {
        min_capacity= g.minValue(rGraph, source, target);
        g.update(rGraph,flow,source,target);
        maxFlow += min_capacity;
    }

	g.printMinCut();
	for (int i = 1; i <= n; i++)
	{
		if (rGraph[i])
			delete[]rGraph[i];
	}

	if (rGraph)
		delete[]rGraph;

    return maxFlow;
}

int main()
{
	Graph g(true);
	ifstream fin("input.txt");
	int n,nEdge;
	int u,v,w;
	int source,target;
	int **flow;
	flow = 0;

	fin >> n >> nEdge;
	//cin >> n;
	g.setnVertices(n);

    initialize(flow, n);

	for(int i = 1; i <= nEdge; i++)
	{
	    fin >> u >> v >> w;
		g.addEdge(u,v,w);
	}
//    g.inputGraph();

	g.printGraph(0);
	cin >> source >> target;

    cout << FordFulkerson(g,flow,n,source,target)<<endl;
	g.printGraph(flow);
	for (int i = 1; i <= n; i++)
		delete[]flow[i];

	delete[]flow;
    return 0;
}
