#include<stdio.h>
#include<stdlib.h>

struct Node* queue[16];
int front = 0;
int rear = 0;

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
	return node;
}

void Enqueue(struct Node* node) {
	queue[rear] = node;
	rear = rear + 1;
}

struct Node* Dequeue() {
	struct Node* value = queue[front];
	front = front + 1;
	return value;
}

int IsEmpty() {
	return front == rear;
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

// use queue to keep track on nodes
void Levelorder(struct Node* tree) {
	if (tree == NULL) return;
	Enqueue(tree); // the root node.
	while (!IsEmpty()) {
		struct Node* current = Dequeue();
		if (current->left != NULL) Enqueue(current->left);
		if (current->right != NULL) Enqueue(current->right);
		printf("%d ", current->value);
	}
}

// DLR
void Preorder(struct Node* tree) {
	printf("%d ", tree->value);
	if (tree->left != NULL) Preorder(tree->left);
	if (tree->right != NULL) Preorder(tree->right);
}

//LRD
void Postorder(struct Node* tree) {
	if (tree->left != NULL) Postorder(tree->left);
	if (tree->right != NULL) Postorder(tree->right);
	printf("%d ", tree->value);
}

//LDR
void Inorder(struct Node* tree) {
	if (tree->left != NULL) Inorder(tree->left);
	printf("%d ", tree->value);
	if (tree->right != NULL) Inorder(tree->right);
}

// 只检查了所有左子树的节点是否小于当前节点
int IsSubtreeLesser(struct Node* tree, int value) {
	if (tree == NULL) return 1;
	if (tree->value >= value) return 0;
	return IsSubtreeLesser(tree->left, value) && IsSubtreeLesser(tree->right, value);
}

int IsSubtreeBigger(struct Node* tree, int value) {
	if (tree == NULL) return 1;
	if (tree->value <= value) return 0;
	return IsSubtreeBigger(tree->left, value) && IsSubtreeBigger(tree->right, value);
}

// time costly function: O(n2)
// node calculation results are not being reused when calculating for upper layer.
int IsBst(struct Node* tree) {
	if (tree == NULL) return 1;
	if (IsSubtreeLesser(tree->left, tree->value) && IsSubtreeBigger(tree->right, tree->value)
		&& IsBst(tree->left) && IsBst(tree->right)) return 1;
	return 0;
}

int IsBstFastInternal(struct Node* tree, int allowedMax, int allowedMin) {
	if (tree == NULL) return 1;
	if (tree->value > allowedMax || tree->value < allowedMin) return 0;
	if (IsBstFastInternal(tree->left, tree->value, allowedMin) && IsBstFastInternal(tree->right, allowedMax, tree->value)) return 1;
	return 0;
}

int IsBstFast(struct Node* tree) {
	IsBstFastInternal(tree, INT_MAX, INT_MIN);
}

// third method: Bst Inorder + Check arrangement

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
	printf("Inorder: ");
	Inorder(tree);
	printf("\nLevelorder: ");
	Levelorder(tree);
	// tree->left->left->value = 812793049;
	printf("\nIsBst: %d", IsBst(tree));
	printf("\nIsBstFast: %d", IsBstFast(tree));
}