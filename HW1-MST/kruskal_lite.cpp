#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

//****************Dynamic ArrayList class based************************

class element
{
public:
    int u;
    int v;
    int weight;
};

class ArrayList
{
    element *list;
    element null;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(element item) ;
    void insertItem(element item) ;
    void removeItem(element item) ;
    void removeItemAt(int pos);
    element getItem(int position) ;
    int getLength();
    void setLength(int l);
    bool empty();
    void printList();
    void MergeSort(element *A,int lo,int hi);
    void Merge(element *A,int lo,int q,int hi);
    void Sort();
    void Copy(ArrayList &list2);
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new element[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(element newitem)
{
    element * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new element[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(element item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( (list[i].u == item.u) && (list[i].v == item.v) ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(element item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


element ArrayList::getItem(int position)
{
    if(position < 0 || position >= length)
    {
        null.u = NULL_VALUE;
        null.weight = NULL_VALUE;
        return null ;
    }
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

void ArrayList::setLength(int l)
{
    length = l;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d %d\n", list[i].u, list[i].v);
    //printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

void ArrayList::Copy(ArrayList &list2)
{
    if(list) delete []list;
    list = new element[list2.length];
    int i;
    for( i = 0; i < list2.length ; i++ )
    {
        list[i] = list2.list[i] ; //copy all items from list to tempList
    }

    length = list2.length;
    listMaxSize = list2.listMaxSize;
}
void ArrayList::Sort()
{
    MergeSort(list,0,length-1);
}

void ArrayList::MergeSort(element *A,int lo,int hi)
{
    int q;

    if( hi > lo)
    {
        q = (hi+lo)/2;
        MergeSort(A,lo,q);
        MergeSort(A,q+1,hi);
        Merge(A,lo,q,hi);
    }


}

void ArrayList::Merge(element *A,int lo,int q,int hi)
{
    int n1 = q-lo+1+1;
    int n2 = hi - q+1;

    element L[100],R[100];

    for(int i =0 ; i<n1-1; i++) L[i] = A[lo+i];
    for(int i =0 ; i<n2-1; i++) R[i] = A[q+1+i];

    element check;
    check.weight = INFINITY;
    L[n1-1] = check;
    R[n2-1] = check;

    int i =0, j=0;

    for(int k = lo ; k <= hi; k++)
    {
        if(L[i].weight <= R[j].weight)
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }

}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  adjList, mst_edges ;
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation
    int * rnk;
    int * parent, *deg;

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v, int w);
    int find(int u);
    int Union(int x, int y);
    void printGraph();
    void printParent();
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
    deg = 0;
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    if(rnk != 0) delete[]rnk;
    if(parent != 0) delete []parent;
    if(deg != 0) delete []deg;

    rnk = new int[n+1];
    parent = new int[n+1];
    deg = new int[n+1];

    for(int i=1; i<=n; i++)
    {
        rnk[i] = 0;
        deg[i] = 0;
        parent[i]= i;
    }
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<1 || v<1 || u>=nVertices+1 || v>=nVertices+1) return; //u out of range
    this->nEdges++ ;
    deg[u]++;
    deg[v]++;

    element U;
    U.u = u;
    U.v = v;
    U.weight = w;

    adjList.insertItem(U) ;
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
    int mst_wt = 0;

    adjList.Sort();

    for(int i = 0; i<adjList.getLength(); i++)
    {
        element e = adjList.getItem(i);
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
        for(int j =1 ; j<=nVertices; j++)
        {
            parent[j] = j;
            rnk[j] = 0;
        }

        e = temp_edges.getItem(i);

        if( deg[e.u] > 1 && deg[e.v] > 1)
        {
            adjList.removeItem(e);

            mst_edges.setLength(0);
            wt = Kruskal();

            if(sbmst_wt > wt)
            {
                sbmst_wt =  wt;
                sbmst_edges.Copy(mst_edges);
            }

            adjList.insertItem(e);
        }
    }

    sbmst_edges.printList();

    return sbmst_wt;
}

void Graph::printGraph()
{
   // printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);


    for(int j=0; j<mst_edges.getLength(); j++)
    {
        printf("%d %d\n", mst_edges.getItem(j).u, mst_edges.getItem(j).v);
    }
}

void Graph::printParent()
{
    for (int i = 1; i <= nVertices; i++)
        printf("%d->%d, ",i,deg[i]);
    printf("\n");
}

Graph::~Graph()
{
    //write your destructor here
    if(parent)  delete []parent;
    if(rnk)  delete []rnk;
    if(deg) delete []deg;
}


//**********************Graph class ends here******************************

int main()
{
    int n, nEdge;
    Graph g;
    ifstream fin("input2.txt");
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

    int wt = g.Kruskal();
    g.printGraph();

    cout << wt << endl<<endl;

    int wt2 = g.SBMST();
    cout << wt2 <<endl;

    return 0;
}
