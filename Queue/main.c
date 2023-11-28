#include<stdio.h>
#include<stdlib.h>

struct Node* front; // Dequeue direction
struct Node* rear; // Enqueue direction

struct Node {
	int value;
	struct Node* next;
};

struct Node* CreateNode(int value) {
	struct Node* node = malloc(sizeof(struct Node));
	node->value = value;
	node->next = NULL;
}

void Enqueue(int value) {
	struct Node* newNode = CreateNode(value);
	if (front == NULL) { front = rear = newNode; return; }
	rear->next = newNode;
	rear = newNode;
}

int Dequeue() {
	struct Node* last = front;
	if (front == NULL) return -1;
	if (front == rear) { front = rear = NULL; }
	int value = last->value;
	front = last->next;
	free(last);
	return value;
}

int IsEmpty() {
	return front == NULL;
}

int Size() {
	int size = 0;
	struct Node* copy = front;

	while (copy != NULL) {
		copy = copy->next;
		size = size + 1;
	}

	return size;
}

/*
	// O(n): https://sm.ms/image/eRmkuxBofdHEtMa
	int DequeueLinear() {
		struct Node* cursor = front;
		struct Node* last = NULL;
		while (cursor->next != NULL) {
			last = cursor;
			cursor = cursor->next;
		}
		last->next = NULL;
		int cursorValue = cursor->value;
		free(cursor);
		return cursorValue;
	}
*/

//TODO: circular array

void main() {
	Enqueue(8);
	Enqueue(2);
	Enqueue(7);
	Enqueue(3);
	printf("\nUsing list (size: %d): ", Size());
	while (!IsEmpty()) {
		printf("%d, ", Dequeue());
	}
}