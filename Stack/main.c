#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int index = -1;
int array[16];
struct Node* list;

struct Node
{
	int value;
	struct Node* next;
};

struct Node* CreateNode(int value) {
	struct Node* node = malloc(sizeof(struct Node));
	node->value = value;
	node->next = NULL;
}

void PushArray(int value) {
	index = index + 1;
	array[index] = value;
}

void Push(int value) {
	if (list == NULL) {
		list = CreateNode(value);
		return;
	}

	struct Node* newNode = CreateNode(value);
	newNode->next = list;
	list = newNode;
}

int PopArray() {
	index = index - 1;
	return array[index + 1];
}

int Pop() {
	int value = list->value;
	struct Node* next =  list->next;
	free(list);
	list = next;
	return value;
}

int SizeArray() {
	return index;
}

int Size() {
	int size = 0;
	struct Node* copy = list;

	while (copy != NULL) {
		copy = copy->next;
		size = size + 1;
	}

	return size;
}

int IsEmptyArray() {
	return index == -1;
}

int IsEmpty() {
	return list == NULL;
}

int CalcReversePolish(char expression[]) {
	int length = strlen(expression);
	for (int i = 0; i < length; i++) {
		if (expression[i] >= '0' && expression[i] <= '9') Push(expression[i] - '0');
		if (expression[i] == '+') Push((int) (Pop() + Pop()));
		if (expression[i] == '-') Push((int) (-(Pop() - Pop())));
		if (expression[i] == '*') Push((int) (Pop() * Pop()));
		if (expression[i] == '/') Push((int) (1 / (Pop() / Pop())));
	}
	return Pop();
}

void main() {
	PushArray(8);
	PushArray(2);
	PushArray(3);
	printf("Using array (size: %d): ", SizeArray());
	while (!IsEmptyArray()) {
		printf("%d, ", PopArray());
	}

	Push(8);
	Push(2);
	Push(3);
	printf("\nUsing list (size: %d): ", Size());
	while (!IsEmpty()) {
		printf("%d, ", Pop());
	}

	char expression[] = "587-9*+";

	printf("expression: %s, value: %d", expression, CalcReversePolish(expression));
}