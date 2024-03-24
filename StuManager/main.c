#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student {
    int id;
    char name[8];
    char gender;
    char age;
};

struct Node {
    struct Student value;
    struct Node* next;
};

struct Node* NewNode(struct Student* value) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->value = *value;
}

struct Student* NewStudent(int id) {
    struct Student* newNode = (struct Student*)malloc(sizeof(struct Student));
    newNode->id = id;
}

void FillStudent(struct Student* student) {
    printf("Provide the information about the student: name, gender, age\n");
    scanf_s("%s, %c, %c", &student->name, 8, &student->gender, &student->age);
}

void PrintSingle(struct Student student) {
    printf("%d %c %c %s", student.id, student.gender, student.age, student.name);
}

void AddStudent(struct Node** list, struct Student* student) {
    struct Node* newNode = NewNode(student);
    if (*list == NULL) {
        *list = newNode;
        return;
    }

    struct Node* head = *list;
    while (head->next != NULL) head = head->next;
    head->next = newNode;
}

void PrintStudents(struct Node** list) {
    struct Node* head = *list;
    while (head != NULL) {
        PrintSingle(head->value);
        head = head->next;
    }
}

int main() {
    char command[6];
    struct Node* list = NULL;
    int id = 0;
    printf("StuManager: Type in your command\n");
    printf("add: add a student to the list\n");
    printf("list: show all the students\n");
    printf("remove: remove a stduent by id\n");
    printf("edit: edit a student by id\n");
    printf("search: search a student by id\n");
    printf("load: load students from the file\n");
    printf("save: save students to the file\n");
    printf("exit: exit the program\n");
    while (1) {
        scanf_s("%s", &command, 6);
        if (strcmp(command, "add") == 0) {
            struct Student* student = NewStudent(id++);
            FillStudent(student);
            AddStudent(&list, student);
        }
        if (strcmp(command, "list") == 0) {
            PrintStudents(&list);
        }
    }
}
