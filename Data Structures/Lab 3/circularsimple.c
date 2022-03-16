#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct node {
    int value;
    struct node* next;
};
struct node* Head = NULL;
struct node* Tail = NULL;

struct node* createNewNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertTail(int num) {
    struct node* nodeBaru = createNewNode(num);
    if (Head == NULL) {
        Head = nodeBaru;
        Tail = nodeBaru;
        Tail->next = Head;
    }
    else {
        nodeBaru->next = Head;
        Tail->next = nodeBaru;
        Tail = nodeBaru;
    }
}

void insertHead(int num) {
    struct node* nodeBaru = createNewNode(num);
    if (Head == NULL) {
        // Head = Tail = nodeBaru;
        Head = nodeBaru;
        Tail = nodeBaru;
        Tail->next = nodeBaru;
    }
    else {
        Tail->next = nodeBaru;
        nodeBaru->next = Head;
        Head = nodeBaru;
    }
}

void printList(struct node* n) {
    while (n->next != Head) {
        printf("%d ", n->value);
        n = n->next;
    }
    printf("%d \n", n->value);
}

int main() {
    insertHead(2);
    insertTail(5);
    // printf("%d %d", Head->value, Tail->value);
    insertTail(10);
    insertHead(17);
    insertTail(12);
    insertTail(13);
    // printf("%d %d", Head->next->value, Tail->next->value);
    printList(Head);
    // insertHead(10);
    // printf("%d %d", Head->value, Tail->value);
    // printList(Head);
    // insertHead(3);
    // printList(Head);
    free(Head);
}