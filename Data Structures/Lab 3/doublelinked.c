#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode {
    int value;
    char nama[50];
    struct tnode* next;
    struct tnode* previous;
};

struct tnode* head = NULL;
struct tnode* tail = NULL;

struct tnode* createNewNode(int value, char* nama) {
    struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->value = value;
    strcpy(temp->nama, nama);
    temp->next = NULL;
    temp->previous = NULL;

    return temp;
}

void pushHead(int value, char* nama) {
    if (head == NULL) {
        head = tail = createNewNode(value, nama);
    }
    else {
        struct tnode* insertNode = createNewNode(value, nama);
        insertNode->next = head;
        insertNode->previous = NULL;
        head = insertNode;
    }
}

void pushTail(int value, char* nama) {
    if (head == NULL) {
        head = tail = createNewNode(value, nama);
    }
    else {
        struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
        tail->next = createNewNode(value, nama);
        temp = tail->next;
        tail = tail->next;
        temp->previous = tail;
    }
}

void printList(struct tnode* n) {
    while (n != NULL) {
        printf("[%d %s]-> ", n->value, n->nama);
        n = n->next;
    }
    printf("NULL \n");
}

int main() {
    pushHead(50, "A");
    pushHead(10, "B");
    pushTail(35, "C");
    pushTail(27, "D");
    pushTail(31, "E");
    printList(head);
    free(head);
}