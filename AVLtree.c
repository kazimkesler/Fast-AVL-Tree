#include <stdio.h>
#include <stdlib.h>
struct treeNode_
{
	int data;
	struct treeNode_* left, * right, * prev;
	char balance;
};
typedef struct treeNode_ treeNode;
void rotate_right(treeNode** root, treeNode* iter)
{
	if (iter->prev != NULL)
	{
		if (iter->prev->left == iter)
			iter->prev->left = iter->left;
		else
			iter->prev->right = iter->left;
		iter->left->prev = iter->prev;
	}
	else
	{
		iter->left->prev = NULL;
		*root = iter->left;
	}
	treeNode* temp = iter->left->right;
	iter->left->right = iter;
	iter->prev = iter->left;
	if (temp != NULL)
	{
		iter->left = temp;
		temp->prev = iter;
	}
	else
		iter->left = NULL;
}
void rotate_left(treeNode** root, treeNode* iter)
{
	if (iter->prev != NULL)
	{
		if (iter->prev->left == iter)
			iter->prev->left = iter->right;
		else
			iter->prev->right = iter->right;
		iter->right->prev = iter->prev;
	}
	else
	{
		iter->right->prev = NULL;
		*root = iter->right;
	}
	treeNode* temp = iter->right->left;
	iter->right->left = iter;
	iter->prev = iter->right;
	if (temp != NULL)
	{
		iter->right = temp;
		temp->prev = iter;
	}
	else
		iter->right = NULL;
}
void left_left(treeNode** root, treeNode* iter)
{
	rotate_right(root, iter);
	iter->balance = 0;
	iter->prev->balance = 0;
}
void left_right(treeNode** root, treeNode* iter)
{
	rotate_left(root, iter->left);
	rotate_right(root, iter);
	if (iter->prev->balance < 0)
	{
		iter->balance = 1;
		iter->prev->left->balance = 0;
	}
	else if (iter->prev->balance > 0)
	{
		iter->balance = 0;
		iter->prev->left->balance = -1;
	}
	else
	{
		iter->balance = 0;
		iter->prev->left->balance = 0;
	}
	iter->prev->balance = 0;
}
void right_left(treeNode** root, treeNode* iter)
{
	rotate_right(root, iter->right);
	rotate_left(root, iter);
	if (iter->prev->balance < 0)
	{
		iter->balance = 0;
		iter->prev->right->balance = 1;
	}
	else if (iter->prev->balance > 0)
	{
		iter->balance = -1;
		iter->prev->right->balance = 0;
	}
	else
	{
		iter->balance = 0;
		iter->prev->right->balance = 0;
	}
	iter->prev->balance = 0;
}
void right_right(treeNode** root, treeNode* iter)
{
	rotate_left(root, iter);
	iter->balance = 0;
	iter->prev->balance = 0;
}
void rebalance(treeNode** root, treeNode* iter)
{
	if (iter != NULL && iter->prev != NULL)
	{
		do
		{
			if (iter->prev->left == iter)
				iter->prev->balance--;
			else
				iter->prev->balance++;
			iter = iter->prev;
		} while (abs(iter->balance) == 1 && iter->prev != NULL);
		if (iter->balance == -2)
			if (iter->left->balance < 0)//leftleft
				left_left(root, iter);
			else//leftright
				left_right(root, iter);
		else if (iter->balance == 2)
			if (iter->right->balance < 0)//rightleft
				right_left(root, iter);
			else//rightright
				right_right(root, iter);
	}
}
bool insert_node(treeNode** root, int x)
{
	if (*root == NULL)
	{
		*root = (treeNode*)malloc(sizeof(treeNode));
		(*root)->data = x;
		(*root)->left = NULL;
		(*root)->right = NULL;
		(*root)->prev = NULL;
		(*root)->balance = 0;
		return true;
	}
	treeNode* iter = *root;
	while (x != iter->data)
		if (x > iter->data)
			if (iter->right != NULL)
				iter = iter->right;
			else
			{
				iter->right = (treeNode*)malloc(sizeof(treeNode));
				iter->right->data = x;
				iter->right->left = NULL;
				iter->right->right = NULL;
				iter->right->prev = iter;
				iter->right->balance = 0;
				rebalance(root, iter->right);
				return true;
			}
		else
			if (iter->left != NULL)
				iter = iter->left;
			else
			{
				iter->left = (treeNode*)malloc(sizeof(treeNode));
				iter->left->data = x;
				iter->left->left = NULL;
				iter->left->right = NULL;
				iter->left->prev = iter;
				iter->left->balance = 0;
				rebalance(root, iter->left);
				return true;
			}
	return false;
}
treeNode* search_node(treeNode* iter, int x)
{
	if (iter != NULL)
		while (true)
			if (x > iter->data)
				if (iter->right != NULL)
					iter = iter->right;
				else
					break;
			else if (x < iter->data)
				if (iter->left != NULL)
					iter = iter->left;
				else
					break;
			else
				return iter;
	return NULL;
}
int main() //Test the program
{
	treeNode* avl = NULL;
	insert_node(&avl, 20);
	insert_node(&avl, 9);
	insert_node(&avl, 26);
	insert_node(&avl, 4);
	insert_node(&avl, 11);
	insert_node(&avl, 21);
	insert_node(&avl, 30);
	insert_node(&avl, 3);
	insert_node(&avl, 7);
	insert_node(&avl, 2);
	insert_node(&avl, 8);
	printf("3 %s\n", search_node(avl, 3) ? "found": "not found");
	printf("10 %s\n", search_node(avl, 10) ? "found": "not found");
}
