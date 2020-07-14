#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define FALSE_VALUE 0
#define TRUE_VALUE 1
#define RED 255
#define BLACK 256
#define NULL -99999
using namespace std;
struct treeNode
{
    int item;
    int color;
    struct treeNode * p; //points to parent
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root,*nil=0;
struct treeNode * makeTreeNode(int item);
void printInOrder(struct treeNode* node,int h);
int calcNodeHeight(struct treeNode*node);

void initializeTree()
{
    nil = (struct treeNode *)malloc(sizeof(struct treeNode));
    nil->item = NULL;
    nil->p = 0;
    nil->left = 0;
    nil->right = 0;
    nil->color = BLACK;
    root = nil;
}

struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==nil) return nil;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = nil;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};

void Left_Rotate(struct treeNode* x)
{
    struct treeNode * y = x->right;
    x->right = y->left;
    y->left->p = x;
    y->p = x->p;

    if(x->p == nil){
        root = y;
    }
    else if(x == x->p->right){
        x->p->right = y;
    }
    else x->p->left = y;

    y->left = x;
    x->p = y;

}

void Right_Rotate(struct treeNode *y){
    struct treeNode * x = y->left;
    y->left = x->right;
    x->right->p = y;
    x->p = y->p ;

    if(y->p == nil){
        root = x;
    }
    else if(y == y->p->right){
        y->p->right = x;
    }
    else y->p->left = x;

    x->right = y;
    y->p = x;
}

struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->p = nil;
    node->left = nil;
    node->right = nil;
    node->color = RED;
    return node;
};

void RB_Insert_Fixup(struct treeNode *z)
{
    while(z->p->color == RED)
    {
        if(z->p == z->p->p->left)
        {
            struct treeNode * y = z->p->p->right;

            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;

            }
            else
            {
                if(z == z->p->right)
                {
                    z = z->p;
                    Left_Rotate(z);
                }

                z->p->color = BLACK;
                z->p->p->color = RED;
                cout << z->p->p->item<<endl;
                Right_Rotate(z->p->p);
            }
        }
        else
        {
            struct treeNode * y = z->p->p->left;
            if(y->color == RED)
            {
                z->p->color = BLACK;
                y->color = BLACK;
                z->p->p->color = RED;
                z = z->p->p;
            }
            else
            {
                if(z == z->p->left)
                {
                    z= z->p;
                    Right_Rotate(z);
                }

                z->p->color = BLACK;
                z->p->p->color = RED;
                Left_Rotate(z->p->p);
            }
        }
    }

    root->color = BLACK;
}

struct treeNode * insertItem(struct treeNode * node, int item)
{
    struct treeNode * y =nil;
    while(node != nil ){
        y = node;
        if(item < node->item ) node = node->left;
        else node = node->right;
    }

    struct treeNode * z = makeTreeNode(item);

    z->p = y;

    if (y == nil) root = z;
    else if(item < y->item )
    {
        y->left = z;

    }
    else {
            y->right = z;

    }


    RB_Insert_Fixup(z);

//    int h = calcNodeHeight(root);
//    printInOrder(root,h);
}

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==nil) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}


int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==nil) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
	//write your codes here
	if (node==nil ) return 0;
	else return 1 + getSize(node->right) + getSize(node->left) ;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    // write your codes here
    if (node==nil ) return -1;
    struct treeNode *temp = root;
    int counter =0;
    while(temp != node)
    {
        if(temp->item > node->item)
        {
            temp = temp->left;
            counter++;
        }
        else if( temp->item < node->item)
        {
             temp = temp->right;
             counter++;
        }
    }

    return counter;
}


int calcDepth(int item)//return depth of an item in the tree
{
    // write your codes here
    struct treeNode * node = searchItem(root,item);
    if(node==nil) return -1; //not found
    else return calcNodeDepth(node);
}

// Replace a tree of node u with a tree of node v
void RB_Delete_Fixup(struct treeNode * x)
{
    while(x->color == BLACK && x != root)
    {
        if(x == x->p->left)
        {//cout <<"here";
            struct treeNode * w = x->p->right;
            if(w->color == RED)
            {
               // cout << "hi";
                w->color = BLACK;
                x->p->color = RED;
                Left_Rotate(x->p);
                w = x->p->right;
                //cout << "hello";
            }

            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    Right_Rotate(w);
                    w = x->p->right;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->right->color = BLACK;
                Left_Rotate(x->p);
                x = root;
            }
        }
        else
        {
            struct treeNode * w = x->p->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->p->color = RED;
                Right_Rotate(x->p);
                w = x->p->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                x = x->p;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    Left_Rotate(w);
                    w = x->p->left;
                }
                w->color = x->p->color;
                x->p->color = BLACK;
                w->left->color = BLACK;
                Right_Rotate(x->p);
                x = root;
            }
        }
    }

    x->color = BLACK;
}

Transplant(struct treeNode*p, struct treeNode*u,struct treeNode*v)
{
    if (p == nil) root = v;
    else if( u == p->left) p->left = v;
    else p->right = v;
    v->p = u->p;
}

int deleteItem(struct treeNode * node, int item)
{
    // write your code here, return TRUE, FALSE
    if (node == nil) return FALSE_VALUE;
    struct treeNode *x,*z = searchItem(root,item);
	if(z == nil) return FALSE_VALUE;

	struct treeNode * y= z;

    if(z->left ==nil )
    {
        Transplant(z->p,z,z->right);
    }
    else if(z->right == nil)
    {
        Transplant(z->p, z,z->left);
    }
    else
    {
        y = y->right;
        while(y->left != nil)
        {
            y = y->left;
        }
        z->item = y->item;
        Transplant(y->p,y,y->right);
    }

    if(y->left != nil) x = y->left;
    else x = y->right;

    if (y->color == BLACK) RB_Delete_Fixup(x);
    free(y);
    return TRUE_VALUE;
}

int getMinItem() //returns the minimum item in the tree
{
    // write your codes here
    struct treeNode *node = root;
    if (node->item == NULL) return -1;

     while(node->left->item != NULL) node = node->left;

     return node->item;
}

int getMaxItem() //returns the maximum item in the tree
{
   // write your codes here
     struct treeNode *node = root;
     if (node->item == NULL) return -1;

     while(node->right->item != NULL) node = node->right;

     return node->item;

}

void printInOrder(struct treeNode * node, int height)
{

    if(node==nil) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}

void print(struct treeNode * node)
{

    if(node==nil) return ;

    //print left sub-tree
    print(node->left);

    //print item

    printf("%d  ",node->item);

    //print right sub-tree
    print(node->right);
}

int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item.    2. Delete item.       3. Search item. \n");
        printf("4. Print           5. height of an item. 6. PrintInOrder.\n");
        printf("7. size            8. Depth of Node      9. Depth of an item\n");
        printf("10.Get Min         11.Get Max            12.Range Search\n");
        printf("0. exit.\n");
        printf("\n");
        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);

        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(root, item);
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch==3)
        {
            int item;
            scanf("%d\n", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=nil) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            printf("--------------------------------\n");
            print(root);
            printf("\n--------------------------------\n");
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            //cout <<h<<endl;
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch == 7)
            printf("Size of Tree: %d\n",getSize(root));

        else if(ch == 8)
        {
            int item;
            scanf("%d",&item);
            struct treeNode * node = searchItem(root,item);
            printf("%d\n",calcNodeDepth(node));
        }
        else if(ch==9)
        {
            int item;
            scanf("%d", &item);
            int depth = calcDepth(item);
            printf("Depth of %d = %d\n", item, depth);
        }
        else if(ch == 10)
        {
            printf("MIN : %d\n\n",getMinItem());
        }
        else if(ch == 11)
        {
            printf("MAX : %d\n\n",getMaxItem());
        }
        else if(ch==0)
        {
            break;
        }
    }

}
