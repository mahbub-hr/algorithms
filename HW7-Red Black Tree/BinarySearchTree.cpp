#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1
#define RED 255
#define BLACK 256

struct treeNode
{
    int item;
    int color;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;


void initializeTree()
{
    root = 0;
}


struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};


struct treeNode * makeTreeNode(int item,int color)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    node->color = color;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item,BLACK);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}



int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
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
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
	//write your codes here
	if (node == 0 ) return 0;
	else return 1 + getSize(node->right) + getSize(node->left) ;
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    // write your codes here
    if (node == 0 ) return -1;
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
    if(node==0) return -1; //not found
    else return calcNodeDepth(node);
}

// Replace a tree of node u with a tree of node v
Transplant(struct treeNode*p, struct treeNode*u,struct treeNode*v)
{
    if (p == 0) root = v;
    else if( u == p->left) p->left = v;
    else p->right = v;
}

int deleteItem(struct treeNode * node, int item)
{
    // write your code here, return TRUE, FALSE
    if (node == 0 ) return FALSE_VALUE;
    struct treeNode *temp,*prev=0;
	temp = node;

	while (temp!=0 )
	{
	    if(item == temp->item) break;
	     prev = temp;
		if ( item < temp->item)
        {
            temp = temp->left;
        }
        else if(item > temp->item)
        {
            temp = temp->right;
        }
	}

	node = temp;

    if (temp == 0 ) return FALSE_VALUE;

    else if(temp->left ==0 )
    {
        struct treeNode *p = temp;
        Transplant(prev,temp,temp->right);
        free(p);
    }
    else if(temp->right == 0)
    {

        struct treeNode *p=temp;
        Transplant(prev, temp,temp->left);
        free(p);
    }
    else
    {
        struct treeNode*parent = temp;
        temp = temp->right;
        while(temp->left != 0)
        {
            parent = temp;
            temp = temp->left;
        }
        node->item = temp->item;
        struct treeNode *p=temp;
        Transplant(parent,temp,temp->right);
        free(temp);
    }

    return TRUE_VALUE;
}



int getMinItem() //returns the minimum item in the tree
{
    // write your codes here
    struct treeNode *node = root;
    if (node == 0) return -1;

     while(node->left != 0) node = node->left;

     return node->item;
}

int getMaxItem() //returns the maximum item in the tree
{
   // write your codes here
     struct treeNode *node = root;
     if (node == 0) return -1;

     while(node->right != 0) node = node->right;

     return node->item;

}

 int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
 {
   // write your codes here

   if (node == 0 ) return 0;
   if (leftBound>rightBound)
   {
       printf("Invalid Range\n");
       return 0;
   }
   else if (node->item == leftBound ) return   1+rangeSearch(node->right,leftBound,rightBound);
   else if (node->item  < leftBound ) return   rangeSearch(node->right,leftBound,rightBound);
   else if (node->item == rightBound) return   1+rangeSearch(node->left,leftBound,rightBound);
   else if (node->item  > rightBound) return   rangeSearch(node->left,leftBound,rightBound);

   return 1+ rangeSearch(node->left,leftBound,rightBound) + rangeSearch(node->right,leftBound,rightBound);
 }


void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0;i<height;i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}



int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item.    2. Delete item.       3. Search item. \n");
        printf("4. height of tree. 5. height of an item. 6. PrintInOrder.\n");
        printf("7. size            8. Depth of Node      9. Depth of an item\n");
        printf("10.Get Min         11.Get Max            12.Range Search\n");
        printf("0. exit.\n");

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
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
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
            printf("MIN : %d\n",getMinItem());
        }
        else if(ch == 11)
        {
            printf("MAX : %d\n",getMaxItem());
        }
        else if(ch == 12)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("Found %d items\n",rangeSearch(root,l,r));
        }
        else if(ch==0)
        {
            break;
        }
    }

}
