#include <stdio.h>
#include <stdlib.h>
#include<time.h>


//struct node *root = NULL;
long *B[10000];


struct node {
    long key;
	struct node *left;
	struct node *right;
	int height;
};

struct node* newNode(long item)
{
	struct node* temp;
	temp = (struct node*) malloc(sizeof(struct node));
	temp->key = item;
	temp->left = NULL;
	temp->right = NULL;
	temp->height = 1;
	return (temp);

}

//BST
struct node* InsertBST(struct node* node, long key)
{
	if (node == NULL)
		return newNode(key);
	else if (key < node->key)
		node->left = InsertBST(node->left, key);
	else
		node->right = InsertBST(node->right, key);
	return node;

}

struct node* Search(struct node* root, long key)
{
	if (root == NULL || root->key == key) 
		return root;
	if (root->key < key)
		return Search(root->right, key);
	return Search(root->left, key);
}

int findHeight(struct node* temp)
{
	if (temp == NULL)
	{
		printf("Tree is empty...");
		return 0;
	}
	else
	{
		long leftHeight = 0; long rightHeight = 0;
		if (temp->left != NULL)
			leftHeight = findHeight(temp->left);
		if (temp->right != NULL)
			rightHeight = findHeight(temp->right);

		long max = (leftHeight > rightHeight) ? leftHeight : rightHeight;
		
		return(max + 1);
	}
}

int cmpfunc(const void * a, const void * b) {
	return (*(long*)a - *(long*)b);
}

void RandEveryRand(long Arr[])
{
	long x, p;
	long count;
	long i = 0;

	srand(time(NULL));

	for (count = 0; count < 10000; count++) {
		Arr[count] = rand() % 100000 << 1;
	}

	while (i < 10000) {
		long r = rand() % 100000 << 1;

		for (x = 0; x < i; x++)
		{
			if (Arr[x] == r) {
				break;
			}
		}
		if (x == i) {
			Arr[i++] = r;
		}
	}
	return Arr;
}

void swap(long *xp, long *yp)
{
	long temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubblesort(long arr[], long n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		//printf("%d \n", B[i]);
	}
	return arr;
}


void InsertInTreeBST(long *Arr[], int n)
{
	struct node *root = NULL;
	
	
	for (int i = 0; i < n; i++)
	{

		root = InsertBST(root, Arr[i]);
		//printf(" %d \n",Arr[i]);
	}


	printf("|     %2d      ", findHeight(root));

}

//AVL

int height(struct node *N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

int maxx(long a, long b)
{
	return (a > b) ? a : b;
}

struct node *rightRotate(struct node *y)
{
	struct node *x = y->left;
	struct node *T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = maxx(height(y->left), height(y->right)) + 1;
	x->height = maxx(height(x->left), height(x->right)) + 1;
	return x;
}

struct node *leftRotate(struct node *x)
{
	struct node *y = x->right;
	struct node *T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = maxx(height(x->left), height(x->right)) + 1;
	y->height = maxx(height(y->left), height(y->right)) + 1;
	return y;
}

int getBalance(struct node *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

struct node* insertAVL(struct node* node, long key)
{
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insertAVL(node->left, key);
	else if (key > node->key)
		node->right = insertAVL(node->right, key);
	else
		return node;


	node->height = 1 + maxx(height(node->left),
		height(node->right));
	int balance = getBalance(node);
	if (balance > 1 && key < node->left->key)
		return rightRotate(node);
	if (balance < -1 && key > node->right->key)
		return leftRotate(node);
	if (balance > 1 && key > node->left->key)
	{
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}
	if (balance < -1 && key < node->right->key)
	{
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}
	return node;
}

void preOrder(struct node *root)
{
	if (root != NULL)
	{
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

int heightAVL(struct node* T)
{
	int lh, rh;
	if (T == NULL)
		return(0);

	if (T->left == NULL)
		lh = 0;
	else
		lh = 1 + T->left->height;

	if (T->right == NULL)
		rh = 0;
	else
		rh = 1 + T->right->height;

	if (lh > rh)
		return(lh);

	return(rh);
}

void InsertInTreeAVL(long Arr[], int n)
{
	//RandEveryRand(B);

	//qsort(B, 10000, sizeof(long), cmpfunc);


	struct node *root = NULL;


	for (int i = 0; i < n; i++)
	{

		root = insertAVL(root, Arr[i]);
	//printf("%d. %d \n", i, Arr[i]);
	}


	printf("|      %2d      |\n", root->height);

//	preOrder(root);
}





int main()
{
	printf("I. Vzestupne BST | -- || \n");
	printf("I. Vzestupne AVL");
	RandEveryRand(B);
	bubblesort(B, 10000);
	InsertInTreeAVL(B, 10000);
	//InsertInTreeBST(B, 10000);
   
	printf("II. \n ");
	printf("___________BST_____________AVL_____\n");
	for (int i = 0; i < 100; i++)
	{
		printf("| %3d ", i+1);
		RandEveryRand(B);		
		InsertInTreeBST(B, 10000);
		InsertInTreeAVL(B, 10000);
	}


	printf("\n");
	

	
	



	return 0;

}