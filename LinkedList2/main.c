#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int value;
    struct Node* next;
    struct Node* previous;
};

struct Node* CreateNode(int value)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->next = NULL;
    new_node->previous = NULL;
    return new_node;
}

struct Node* Insert(struct Node* head, int value)
{
    struct Node* new_node = CreateNode(value);
    head->previous = new_node;
    new_node->next = head;
    return new_node;
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
    new_node->previous = head;
    head->next = new_node;

    if (new_node->next != NULL)
    {
        new_node->next->previous = new_node;
    }

    return the_head;
}

struct Node* RemoveAt(struct Node* head, int index)
{
    if (head == NULL)
    {
        return NULL;
    }

    if (index < 1)
    {
        struct Node* new_head = head->next;
        if (new_head != NULL)
        {
            new_head->previous = NULL;
        }
        free(head);
        return new_head;
    }

    struct Node* current = head;
    int count = 0;

    while (current != NULL && count < index)
    {
        current = current->next;
        count++;
    }

    if (current == NULL)
    {
        return head;
    }

    struct Node* previous_node = current->previous;
    struct Node* next_node = current->next;

    if (previous_node != NULL)
    {
        previous_node->next = next_node;
    }

    if (next_node != NULL)
    {
        next_node->previous = previous_node;
    }

    free(current);

    return head;
}

void Print(struct Node* head)
{
    while (head != NULL)
    {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void ReversePrint(struct Node* head)
{
    if (head == NULL)
    {
        return;
    }

    // Traverse to the last node
    struct Node* last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }

    // Print the values in reverse order
    while (last != NULL)
    {
        printf("%d ", last->value);
        last = last->previous;
    }
    printf("\n");
}

int main()
{
    struct Node* head = CreateNode(1);
    head = Insert(head, 2);
    head = Insert(head, 3);
    head = Insert(head, 4);
    head = Insert(head, 5);
    head = Insert(head, 6);
    head = Insert(head, 7);
    head = Insert(head, 8);
    head = Insert(head, 9);
    head = Insert(head, 10);

    Print(head);
    ReversePrint(head);

    head = InsertAt(head, 11, 5);
    Print(head);
    ReversePrint(head);

    head = RemoveAt(head, 5);
    Print(head);
    ReversePrint(head);

    return 0;
}