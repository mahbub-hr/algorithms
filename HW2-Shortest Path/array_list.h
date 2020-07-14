#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999

using namespace std;

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

//****************Dynamic ArrayList class based************************

class element
{
public:
    int u;
    int v;
    float weight;
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
