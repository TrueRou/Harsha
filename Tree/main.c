#include<stdio.h>
#include<stdlib.h>

struct Node {
	struct Node* left;
	struct Node* right;
	int value;
};

struct Node* CreateNode(int value) {
	struct Node* node = malloc(sizeof(struct Node));
	node->left = NULL;
	node->right = NULL;
	node->value = value;
}

void Insert(struct Node** treePtr, int value) {
	struct Node* newNode = CreateNode(value);
	if (*treePtr == NULL) { *treePtr = newNode; return; }
	struct Node* tree = *treePtr;
	if (value <= tree->value) Insert(&tree->left, value);
	else Insert(&tree->right, value);
}

int Search(struct Node* tree, int value) {
	if (tree == NULL) return 0;
	if (tree->value == value) return 1;
	if (value <= tree->value) return Search(tree->left, value);
	else return Search(tree->right, value);
}

int Min(struct Node* tree) {
	if (tree == NULL) return -1;
	if (tree->left == NULL) return tree->value;
	return Min(tree->left);
}

int Max(struct Node* tree) {
	if (tree == NULL) return -1;
	if (tree->right == NULL) return tree->value;
	return Min(tree->right);
}

int Height(struct Node* node) {
	if (node == NULL) return -1;
	int leftHeight = Height(node->left);
	int rightHeight = Height(node->right);
	return max(leftHeight, rightHeight) + 1;
}

void main() {
	struct Node* tree = NULL;
	Insert(&tree, 16);
	Insert(&tree, 14);
	Insert(&tree, 12);
	Insert(&tree, 10);
	Insert(&tree, 2);
	Insert(&tree, 7);
	Insert(&tree, 6);
	Insert(&tree, 9);
	printf("Max value: %d\n", Max(tree));
	printf("Min value: %d\n", Min(tree));
	printf("Search 6: %d\n", Search(tree, 6));
	printf("Search 100: %d\n", Search(tree, 100));
	printf("Height: %d\n", Height(tree));
}