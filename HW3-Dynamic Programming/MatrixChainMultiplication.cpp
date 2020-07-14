#include<iostream>
#include<fstream>

#define INFINITY 99999

using namespace std;

int **m,**s;

void Matrix_Chain(int n, int *p)
{
	for(int i=1; i<=n; i++ ) m[i][i] = 0;   
    //m[1][2] = INFINITY;
	for(int l =2; l<=n; l++)
	{
		
		for(int i = 1; i<= n-l+1; i++)
		{
			int j = i+l-1;
			m[i][j] = INFINITY;
			
			for(int k = i; k< j; k++)
			{
				int q = m[i][k] + m[k+1][j]+p[i-1]*p[k]*p[j];
				
				if(q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}
}

void printSequence(int i, int j)
{
	if(i == j)
	{
		cout << " A"<<i<<" ";
		return;
	}
	
	cout <<"(";
	printSequence(i,s[i][j]);
	printSequence(s[i][j]+1,j);
	cout<<")";
}

int main()
{
   int n,dim1,dim2;

   ifstream  fin("input.txt");
   if(!fin)
   {
	   cout<<"can't open file";
	   return 0;
   }
   fin >> n;
   
   int *dim = new int[n+1];
   m = new int*[n+1];
   s = new int*[n+1];

   for(int i = 1; i<=n ; i++) 
   {
	   m[i] = new int[n+1];
	   s[i] = new int[n+1];
   }
	
   
   fin >> dim[0] >> dim[1];

   for(int i =2; i<=n; i++) 
   {
	   fin >> dim1 >> dim[i];
	   if( dim1 != dim[i-1])
	   {
		   cout << "Not Multiplicable!";
		   return 0;
	   }
   }
  // for(int i =0; i<=n; i++) cout << dim[i];
  
   Matrix_Chain(n,dim);
   cout<<"result: "<< m[1][n]<<endl;
   cout<<endl;
   printSequence(1,n);
  
   if(dim) delete[] dim;
   for(int i = 1; i<=n ; i++) 
   {
	  if(m[i]) delete[] m[i];
	  if(s[i]) delete[] s[i];
   }
   if(m) delete m;
   if(s) delete s;
   
   return 0;
}