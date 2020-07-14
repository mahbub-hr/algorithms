#include<iostream>
#include<ctime>
#include<cstdlib>
#include<ctime>
#include<string>
#include<list>
#include"hashFunction.h"
#define NOT_FOUND -2
#define NOT_ASSIGNED -1
using namespace std;


string RandomWord(int l=5)
{
    string result="";
    string str="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int pos ;
    //cout <<str.size()<<endl;
    for(int i=1; i<=l; i++)
    {
        pos = rand()%26;
        // cout << pos << endl;
        result= result+str[pos];
    }

    return result;
}

class HashItem
{
public:

    string word;
    int serial;
    HashItem *next;
    HashItem *prev;
    HashItem(string str="", int i = NOT_ASSIGNED)
    {
        word = str;
        serial = i;
        next=0;
        prev = 0;
    }
};

class Hash
{
    HashItem *table;
    int tableSize;
    int itemCount;
    int collisionCount;
    int choice;
public:

    Hash()
    {
        itemCount =0;
        tableSize = 0;
        collisionCount = 0;
        choice=0;
        table = NULL;
    }
    ~Hash()
    {
        if(table) delete[] table;
    }

    void SetHash(int choice)
    {
        this->choice = choice;
    }

    int initialize(int Size=100)
    {
        tableSize = Size;
        table = new HashItem[tableSize];
        return tableSize;
    }

    bool ChainInsert(string str)
    {
        if(ChainSearch(str)!= false) return false;

        int hashVal;
        if(choice==1) hashVal = FNVHash(str)%tableSize;
        else if(choice==2) hashVal=APHash(str)%tableSize;
        else if(choice==3) hashVal=ELFHash(str)%tableSize;
        else
        {
            cout << "Please choose between 1 to 3";
            return false;
        }

        HashItem *item = new HashItem(str,++itemCount);
        item->next = 0;

        if( table[hashVal].serial == NOT_ASSIGNED)
        {
            item->prev=0;
            table[hashVal] = *item ;
        }
        else
        {
            collisionCount++;
            HashItem *head = &table[hashVal];
            while(head->next != 0) head = head->next;
            head->next = item;
            item->prev = head;
        }

        return true;
    }

    bool LPInsert(string str)
    {

        if (LPSearch(str) != NOT_FOUND) return false;
        if(itemCount >= tableSize || tableSize==0) return false;
        int hashVal ;

        if(choice==1) hashVal = FNVHash(str)%tableSize;
        else if(choice==2) hashVal=APHash(str)%tableSize;
        else if(choice==3) hashVal=ELFHash(str)%tableSize;
        else
        {
            cout << "Please choose between 1 to 3";
            return false;
        }

        HashItem item;
        item.word=str;

        item.serial=++itemCount;

        if(table[hashVal].serial != NOT_ASSIGNED) collisionCount++;
        while(table[hashVal].serial != NOT_ASSIGNED)
        {
            ++hashVal;
            if(hashVal >= tableSize ) hashVal=0;
        }
        table[hashVal] = item;

        return true;
    }

    HashItem* ChainSearch(const string str)
    {
        if(tableSize == 0) return NULL;

        int hashVal;

        if(choice==1)      hashVal = FNVHash(str)%tableSize;
        else if(choice==2) hashVal =APHash(str)%tableSize;
        else if(choice==3) hashVal=ELFHash(str)%tableSize;
        else
        {
            cout << "Please choose between 1 to 3";
            return NULL;
        }

        HashItem *item = &table[hashVal];
        while(item != 0 && item->word != str) item = item->next;

        if(item != 0) return item;

        else
        {
            HashItem *null=0;
            return null;
        }
    }

    int LPSearch(const string str)
    {
        if(tableSize == 0) return false;

        int hashVal;

        if(choice==1) hashVal = FNVHash(str)%tableSize;
        else if(choice==2) hashVal=APHash(str)%tableSize;
        else if(choice==3) hashVal=ELFHash(str)%tableSize;
        else
        {
            cout << "Please choose between 1 to 3";
            return false;
        }

        int markHashVal=hashVal;
        //cout << hashVal <<endl;
//        while(table[hashVal].word != str)
//        {
//            hashVal++;
//            if(hashVal >= tableSize ) hashVal=0;
//
//        }
        for(int i=0; i< tableSize; i++)
        {
            if(table[hashVal].serial==-1)
            {
                hashVal++;
                if(hashVal >= tableSize ) hashVal=0;
                continue;
            }
            if(table[hashVal].word==str) return hashVal;
            hashVal++;
            if(hashVal >= tableSize ) hashVal=0;
        }
        return NOT_FOUND;
    }

    bool ChainDelete(string str)
    {

        HashItem *item = ChainSearch(str);

        if(item==0) return false;
        if(item->prev == 0) item->serial = -1;

        else
        {
            item->prev->next = item->next;
            if(item->next != 0)
                item->next->prev = item->prev;
        }

        delete item;
        return true;
    }

    bool LPDelete(string str)
    {
        int hashVal =LPSearch(str);
        if(hashVal == -1) return false;
        table[hashVal].serial = NOT_ASSIGNED;
        return true;
    }

    int getCollision()
    {
        return collisionCount;
    }

    void setCollision(int num)
    {
        collisionCount=num;
    }
    int getItemCount()
    {
        return itemCount;
    }
    void printList(HashItem *head)
    {
        while(head!= 0)
        {
            cout <<" => " << head->word;
            head=head->next;

        }
    }

    void printTable()
    {
        HashItem *head;
        for(int i=0; i<tableSize; i++)
        {
            cout << table[i].word;
            head = &table[i];
            if(head->next!=0) printList(head->next);
            cout << endl;
        }
    }
};

int main()
{
    clock_t Start,End;
    int i=0;
    string str;
    list<string> words;
    double result[2][6];
    srand(time(NULL));

    Hash hashTable1,hashTable2,hashTable3,hashTable4,hashTable5,hashTable6;
    hashTable1.initialize(10000);
    hashTable2.initialize(10000);
    hashTable3.initialize(10000);
    hashTable4.initialize(10000);
    hashTable5.initialize(10000);
    hashTable6.initialize(10000);

    hashTable1.SetHash(1);
    hashTable2.SetHash(2);
    hashTable3.SetHash(3);
    hashTable4.SetHash(1);
    hashTable5.SetHash(2);
    hashTable6.SetHash(3);

    for( i =0; i<10000; i++)
    {
        str = RandomWord(5);

        if (hashTable4.ChainInsert(str)== false)
        {
            i--;
            cout << "insert discarded"<<endl;
            continue;
        }

        hashTable1.LPInsert(str);
        hashTable2.LPInsert(str);
        hashTable3.LPInsert(str);
        hashTable4.ChainInsert(str);
        hashTable5.ChainInsert(str);
        hashTable6.ChainInsert(str);
    }

    for(int i=0; i<10000; i++)
    {
        words.push_back(RandomWord());
    }
    //hashTable.printTable();
    // cout << "List size: "<< words.size()<<endl;
    //cout <<"Item: "<<hashTable.getItemCount()<<endl;
    //cout <<"Collision: "<<hashTable.getCollision()<<endl;
    cout<<endl;

    list<string>:: iterator p = words.begin();

    Start = clock();
    while(p != words.end())
    {
        hashTable1.LPSearch(*p);
        p++;
    }
    End = clock();

    result[0][0] = End-Start;
    result[0][1] = hashTable1.getCollision();

    p = words.begin();
    Start = clock();
    while(p != words.end())
    {
        hashTable2.LPSearch(*p);
        p++;
    }
    End = clock();

    result[0][2] = End-Start;
    result[0][3] = hashTable2.getCollision();

    p = words.begin();
    Start = clock();
    while(p != words.end())
    {
        hashTable3.LPSearch(*p);
        p++;
    }
    End = clock();

    result[0][4] = End-Start;
    result[0][5] = hashTable3.getCollision();

    p = words.begin();
    Start = clock();
    while(p != words.end())
    {
        hashTable4.ChainSearch(*p);
        p++;
    }
    End = clock();

    result[1][0] = End-Start;
    result[1][1] = hashTable4.getCollision();

    p = words.begin();
    Start = clock();
    while(p != words.end())
    {
        hashTable5.ChainSearch(*p);
        p++;
    }
    End = clock();

    result[1][2] = End-Start;
    result[1][3] = hashTable5.getCollision();

    p = words.begin();
    Start = clock();
    while(p != words.end())
    {
        hashTable6.ChainSearch(*p);
        p++;
    }
    End = clock();

    result[1][4] = End-Start;
    result[1][5] = hashTable6.getCollision();

    cout << "            Hash1"<<"             Hash2" <<"             Hash3 "<< endl << endl;
    cout << "LP:       ";
    for(int i =0; i<6; i+=2)
    {
        cout <<result[0][i]<<", "<<result[0][i+1]<<"        ";

    }

    cout << endl<<endl<<"Chaning:   ";
    for(int i =0; i<6; i+=2)
    {
        cout <<result[1][i]<<", "<<result[1][i+1]<<"           ";

    }

    cout<<endl<<endl;

    return 0;
}
