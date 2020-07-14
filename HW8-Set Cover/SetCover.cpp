#include<iostream>
#include<queue>
#include<fstream>
using namespace std;

class result{
public :
    int numberOfSet;

};

double **arr,*Union;
int *size_array;
int row,column;
float EleUni;

void printArr(int row, int column )
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<column;j++)
            cout << arr[i][j]<<" ";
        cout <<endl;
    }
}
void scanInput(int &m, int &n)
{
    int s;
   ifstream fin("input4.txt");
   fin >>m>>n;
   row = n;
   column = m;
   EleUni = m;
   arr = new double*[n];

   for(int i=0;i<n;i++)
   {
       arr[i] = new double[m];
       for(int j=0;j<m;j++) arr[i][j]=-1;
   }


   size_array = new int[n];

   int k=0,c=0;
   while(fin)
   {

       fin >> size_array[k];

       for(int l=0;l<size_array[k];l++) fin >> arr[k][l];
      // cout << arr[k][c];

       k++;

       if(k == n) break;
   }
}

class node{
 public:
    float bound;
    float ElementCovered;
    int *index;
    int level;
    float SetPicked;
};

class myComparator
{
public:
    int operator()(const node& a, const node& b)
    {
        return a.bound > b.bound;
    }
};

float getBound(float SetPicked, float NotCovered,float MaxCardinality)
{
   // cout << SetPicked <<NotCovered<<MaxCardinality<< endl;
    float bound = SetPicked+ (float)(NotCovered/(MaxCardinality));
   // cout<<"haha"<< bound<<endl;
    return bound;
}

int getMaxCardinality(int *a, int n)
{
    int high =0;

    for(int i = 0; i<n; i++)
    {
        if(a[i] == 0 && size_array[i] > high)
            high = size_array[i];
    }

    return high;
}
void SetCopy( int n, double *a1, double *a2)
{
    for(int i =0; i< n; i++) a1[i] = a2[i];
}
void SetCopyInt( int n, int *a1, int *a2)
{
    for(int i =0; i< n; i++) a1[i] = a2[i];
}
int MakeUnion(int m, int n,double *a1, double *a2)
{
    int r=m;
    int found =0;

 //   for(int i=0;i<n;i++) cout<<a2[i] <<" ";
//        cout << endl;
//    for(int i=0;i<m;i++) cout<<a1[i] <<" ";
//        cout << endl;

    for(int i =0 ;i <n; i++)
    {
        for(int j=0;j<m;j++)
        {
            found =0;
            if(a2[i] == a1[j]) {
                    found=1;
                    //cout << "found"<<endl;
                    break;

            }

        }

        if(found==0){
            a1[r] = a2[i];
            r++;
        }
    }

    return r;
}

void printNode(node n)
{
    cout<<n.SetPicked<<endl;
    for(int i=0;i<row;i++)
    {
        if(n.index[i]==1)
        {
            for(int j=0;j<size_array[i];j++) cout<<arr[i][j]<<" ";
            cout<<endl;
        }

    }
}

void SetCover( int m, int n)
{
    Union = new double[m];
    priority_queue <node, vector<node>, myComparator > pq;

    node u;
    u.level=0;

    u.ElementCovered = 0;
    u.SetPicked = 0;

   // for(int c=0;c<n;c++) cout <<size_array[c]<<" ";

    int mark[n]={};
    u.index =mark;
    u.bound = getBound(0,EleUni,getMaxCardinality(u.index,n));
    // cout <<endl <<u.bound;
    pq.push(u);
    int k=0;

    while(pq.empty() == false)
    {
        node v = pq.top();
        pq.pop();
        node left,right;

        //cout << endl<<v.bound<<endl;
//----------------------------------------
//Prepare right child of v
        right.index = new int[n];  for(int i=0;i<n;i++) right.index[i]=0;
        right.level = v.level+1;
        right.SetPicked = v.SetPicked+1;
        SetCopyInt(n,right.index,v.index);
        right.index[v.level] =1;
//     if(v.bound==2.0)
//     {
//         for(int i=0;i<n;i++) cout <<right.index[i]<<" ";
//        cout <<endl;
//     }

        if(v.ElementCovered == 0)
        {
            right.ElementCovered = size_array[v.level];
           // cout << endl<<right.ElementCovered<<endl;
            right.bound = getBound(right.SetPicked,EleUni-right.ElementCovered,getMaxCardinality(right.index,n));
            //cout << endl<<right.bound<<endl;

        }
        else{

            int l=0;
            for(int i=0;i<row;i++)
            {
                if(right.index[i]==1)
                {
                    l = MakeUnion(l,size_array[i],Union,arr[i]);
                }

            }

            right.ElementCovered =l;
            right.bound = getBound(right.SetPicked,EleUni-right.ElementCovered,getMaxCardinality(right.index,n));

            //cout <<right.SetPicked<<" "<<right.ElementCovered<<" "<<right.bound<<endl;
        }


        if(right.ElementCovered == EleUni)
        {
            printNode(right);
            break;
        }
        pq.push(right);
//--------------------------------
//Prepare left child of v

        left.index = new int[n];  for(int i=0;i<n;i++) left.index[i]=0;
        SetCopyInt(n,left.index,v.index);
        left.level = v.level+1;
        left.SetPicked = v.SetPicked;
        left.index[v.level] =-1;

//        if(v.bound==2.0)
//         {
//            for(int i=0;i<n;i++) cout <<left.index[i]<<" ";
//            cout <<endl;
//         }

        if(v.ElementCovered == 0)
        {
            left.ElementCovered = 0;
           // cout << endl<<right.ElementCovered<<endl;
            left.bound = getBound(left.SetPicked,EleUni,getMaxCardinality(left.index,n));
            //cout << endl<<"hhh"<<left.bound<<endl;
           // cout <<endl<<getMaxCardinality(left.index,n)<<endl;
        }
        else{
            int l=0;
            for(int i=0;i<row;i++)
            {
                if(left.index[i]==1)
                {
                    l = MakeUnion(l,size_array[i],Union,arr[i]);
                }

            }

            left.ElementCovered =l;
            left.bound = getBound(left.SetPicked,EleUni-left.ElementCovered,getMaxCardinality(left.index,n));

           //cout <<left.SetPicked<<" " <<left.ElementCovered<<" "<<left.bound<<endl;
        }

        if(left.ElementCovered == EleUni)
        {
            printNode(left);
            break;
        }
        pq.push(left);
        k++;
    }
}

int main()
{
    int m,n;
//    ifstream fin("input.txt");

   //cin >> column;
    scanInput(m,n);

   // printArr(n,m);
    SetCover( m,n);

    return 0;
}
