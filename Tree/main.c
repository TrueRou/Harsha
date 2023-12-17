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

// return the next connection cursor.
struct Node* Delete(struct Node* root, int value) {
	if (root == NULL) return NULL;

	// route to the position of the value, this may change the connection
	if (value < root->value) root->left = Delete(root->left, value);
	if (value > root->value) root->right = Delete(root->right, value);

	// we are now at the position of the value
	if (value == root->value) {
		// case: it's a leaf node
		if (root->left == NULL && root->right == NULL) {
			// simply delete it and set NULL to the connection
			free(root);
			return NULL;
		}
		// case: left and right
		if (root->left != NULL && root->right != NULL) {
			// find the minimal value in the right subtree (min value doesn't have right node)
			int minValue = Min(root->right);
			root->value = minValue;
			root->right = Delete(root->right, minValue);
			return root;
		}
		// case: left or right
		if (root->left == NULL || root->right == NULL) {
			struct Node* next = (root->left != NULL) ? root->left : root->right;
			free(root);
			return next;
		}
	}

	return root; // we're not in the case (in the router path), don't change the connection.
}

struct Node* FindSuccessor(struct Node* target, int value) {
	// find the node of the value (keep track on parent)
	struct Node* parent = target;
	while (value != target->value) {
		if (target == NULL) break; // the value is not exist.
		parent = target;
		if (value < target->value) target = target->left;
		if (value > target->value) target = target->right;
	}

	if (target == NULL) return NULL;

	// case: have right subtree: go to find the leftmost node (min value in the right subtree)
	if (target->right != NULL) {
		// target: LD (R)
		target = target->right;
		while (target->left != NULL) {
			target = target->left;
		}
		return target; // we got the leftmost node in the right subtree
	}
	// case: don't have right subtree: go to find the parent node (we keep track on parent in the loop)
	else return parent;
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
	tree = Delete(tree, 9);
	tree = Delete(tree, 16);
	printf("\nLevelorder: ");
	Levelorder(tree);
	tree = FindSuccessor(tree, 10); // we cut out part of the bst tree
	printf("\nLevelorder: ");
	Levelorder(tree);
}