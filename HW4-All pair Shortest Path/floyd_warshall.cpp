#include<iostream>
#include<fstream>
#include"GraphAdjMatrix.h"

using namespace std;

int **d,**p;

void floyd_warshall(int n)
{
	int i, j ,k;
	
	for(k = 1; k <= n; k++)
	{
	    for(i = 1; i <= n; i++)
		{
			for(j = 1; j <= n; j++)
			{
				if(d[i][k] + d[k][j] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					p[i][j] = p[k][j];
				}
			}
		}			
	}
}

void printGraph(int **mat,int nVertices, int nEdges)
{
   // printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=1;i<=nVertices;i++)
    {
        for(int j=1; j<=nVertices;j++)
        {
            if(mat[i][j] == INFINITY) printf("inf      ");
            else    printf(" %d       ", mat[i][j]);
        }
        printf("\n\n");
    }
}

int main()
{
	
	int n,nEdges,u,v,w;
	bool f = false;
	d=0; p =0;
	ifstream fin("input2.txt");
	
	fin >> n >> nEdges;
	d = new int*[n+1];
	p = new int*[n+1];
	
	for(int i=1;i<=n;i++)
    {
        d[i] = new int[n+1];
		p[i] = new int[n+1];
		
        for(int j=1;j <= n; j++)
        {    
			if(i==j) d[i][j] = 0; //initialize the d cells to 0
			else d[i][j]= INFINITY;
		}
    }
	
	for(int i =0 ; i<nEdges; i++) 
	{
		fin >> u >> v >> w;
		d[u][v] = w;
		//cout << u<<v<<w<<endl;
	}		
	
	for(int i=1;i<=n;i++)
    {
        for(int j=1;j <= n; j++)
        {    
			if(i==j || d[i][j] == INFINITY) p[i][j] = INFINITY;
			else p[i][j] = i;
		}
    }
	
	printGraph(d,n, nEdges);
	floyd_warshall(n);
	cout<<endl;
	printGraph(d,n, nEdges);
	cout<<endl<<endl;
	printGraph(p,n, nEdges);
	cout<<endl;
	
	for(int i = 1; i<=n;i++) 
	{
		if(d[i][i]<0) {
			f= true;
			break;
		}
		
	}
	cout <<"Negative Edge Cycle? ";
	if(f) cout <<"YES"<<endl;
	else cout << "NO"<<endl;
	
	for (int i=1; i<=n; i++)
    {
       if(d[i]) delete []d[i];
	   if(p[i]) delete []p[i];
    }

    if(d) delete []d;
    if(p) delete []p;
   
	return 0;
}

