#include<stdio.h>
#include<stdlib.h>

struct Node
{
	int value;
	struct Node* next;
};

struct Node* CreateNode(int value)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->value = value;
	new_node->next = NULL;
	return new_node;
}

struct Node* Insert(struct Node* head, int value)
{
	struct Node* new_node = CreateNode(value);
	new_node->next = head;
	return new_node;
}

// we get a clone of pointer head, we dare to modify it
void Print(struct Node* head)
{
	// struct Node* cursor = head; // clone the header pointer when global.
	printf("Linked List: ");
	while (head != NULL)
	{
		printf("%d, ", head->value);
		head = head->next;
	}
}

void PrintReverse(struct Node* head)
{
	if (head == NULL)
	{
		printf("Linked List (Reverse): ");
		return;
	}
	PrintReverse(head->next);
	printf("%d, ", head->value);
}

struct Node* InsertAt(struct Node* head, int value, int index)
{
	if (index < 2) return Insert(head, value);

	struct Node* the_head = head;

	for (int i = 0; i < index - 2; i++)
	{
		head = head->next;
	}

	struct Node* new_node = CreateNode(value);
	new_node->next = head->next;
	head->next = new_node;

	return the_head;
}

struct Node* RemoveAt(struct Node* head, int index)
{
	if (index < 2)
	{
		// head needs to be changed if we modified the first element
		struct Node* wait_for_return = head->next;
		free(head);
		return wait_for_return;
	}

	struct Node* the_head = head;

	for (int i = 0; i < index - 2; i++)
	{
		head = head->next;
	}

	struct Node* wait_for_free = head->next;

	head->next = head->next->next;
	free(wait_for_free);
	return the_head;
}

struct Node* Reverse(struct Node* current)
{
	struct Node* prev = NULL, * next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return prev;
}

struct Node* ReverseRecur(struct Node* head)
{
	if (head->next == NULL) return head; // We get the real head here (pass it to the top layer).
	struct Node* real_head = ReverseRecur(head->next);
	head->next->next = head;
	head->next = NULL;
	return real_head;
}

int main()
{
	struct Node* linked_list = NULL;
	linked_list = Insert(linked_list, 8);
	linked_list =  Insert(linked_list, 7);
	linked_list = Insert(linked_list, 4);
	linked_list = Insert(linked_list, 2);
	linked_list = Reverse(linked_list);
	linked_list = InsertAt(linked_list, 2, 2);
	Print(linked_list);
}