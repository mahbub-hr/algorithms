#include<iostream>
#include<fstream>
#include<vector>

#define INFINTY 999999

using namespace std;

typedef pair<int,int> iPair;
vector<pair<iPair, int> > graph;
vector<pair<iPair, int> >::iterator it;
int u,v;

int bellman_ford(int n, int *d, int *p)
{
	int source;
	cout << "Source? ";
	cin >> source;
	
	d[source] = 0;
	
	for( int i =1 ; i<= n-1; i++)
	{
		for(it = graph.begin(); it != graph.end(); it++)
		{
			u = it->first.first;
			v = it->first.second;
			//cout<<u<<" "<<v<<endl;
			if( d[v] > (d[u]+ it->second))
			{
				d[v] = d[u] + it->second;
				p[v] = u;
			}
		}
	}
	
	for(it = graph.begin(); it != graph.end(); it++)
	{
		u = it->first.first;
		v = it->first.second;
		
		if( d[v] > (d[u]+ it->second))
			return 0;
	}
	
	return 1;
}	

int main()
{
	
	int n, nEdge,u ,v;
	int w;
	ifstream fin("input2.txt");
	if(!fin)
	{
		cout<<"file error"<<endl;
		return 0;
	}
	
	fin >> n >> nEdge;
	
	int *d = new int[n+1];
	int *p = new int[n+1];
	for(int i = 1; i <= n; i++) 
	{
		d[i] = INFINTY;
		p[i] = -1;
	}
	
	for(int i = 0; i < nEdge; i++)
	{
		fin >> u >> v >> w;
		graph.push_back( {{u,v},w} );
	}
	
	int haveSolution = bellman_ford(n,d,p);
	
	if(haveSolution)
	{
		for(int i = 1; i<=n; i++)
		{
			cout<<i<<"    "<<d[i]<<"    "<<p[i]<<endl;
		}
	}
	else cout<<"no solution"<<endl;
	
	return 0;
}