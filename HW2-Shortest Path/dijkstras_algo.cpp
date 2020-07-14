#define _CRT_SECURE_NO_WARNINGS
#include"Graph.h"
#include"MinHeap.h"
#include<iostream>
#include<fstream>
#define MAXREAL 999999.0

using namespace std;


void Dijkstra(Graph &g, int n, int source, int *dist, int *parent)
{
	int j = 0;
	float value;// value = d[u]+w(u,v)
	MinHeap heap;

	for (int i = 1; i <= n; i++)
	{
	if (i == source) heap.insertItem(i, 0);
	else heap.insertItem(i, MAXREAL);
	}

	dist[source] = 0;
	parent[source] = -1;

	HeapItem item;

	while (!heap.Empty())
	{
		item = heap.removeMin();

		for (int i = 0; i < g.getLength(item.data); i++)
		{
			element v = g.getItem(item.data, i);
			value = item.key + v.weight;
			//cout << heap.getKey(v.u) << endl;
			if (dist[v.u] > value)
			{
				heap.updateKey(v.u, value);
				dist[v.u] = value;
				parent[v.u] = item.data;
			}

		}
	}
}

int main()
{

	Graph g(true);
	int n, nEdge, u, v;
	float w;
	int *d=0, *p=0;
	int *s=new int[10];
	ifstream fin("input.txt");

	if (!fin)
	{
		cout << "can't open file" << endl;
		return 0;
	}

	fin >> n >> nEdge;
	d = new int[n + 1];
	p = new int[n + 1];
	//s = new int[n + 1];

	g.setnVertices(n);

	for (int i = 0; i < nEdge; i++)
	{
		fin >> u >> v >> w;
		if(w<0)
        {
            printf("Invalid weight");
            return 0;
        }
		g.addEdge(u, v, w);

	}

	g.printGraph();
	int source;
	cout << "The source?";
	cin >> source;

	for (int i = 1; i <= n; i++)
	{
		d[i] = MAXREAL;
		p[i] = -1;
	}

	Dijkstra(g, n, source, d, p);

	//cout <<endl<<"V    d    p"<<endl;
	for (int i = 1; i <= n; i++)
	{
		cout << i << "    " << d[i] << "    " << p[i] << endl;
	}

	if (d != 0 ) delete[] d;
	if (p != 0 ) delete[] p;
	if ( s!= 0 ) delete[] s;

	return 0;
}
