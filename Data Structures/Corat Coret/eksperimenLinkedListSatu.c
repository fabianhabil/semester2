#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int value;
    struct tnode* next;
};
struct tnode* head = NULL;
struct tnode* tail = NULL;

struct tnode* createNewNode(int value) {
    struct tnode* temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->value = value;
    temp->next = NULL;

    return temp;
}

void pushHead(int value) {
    if (head == NULL) {
        head = tail = createNewNode(value);
    }
    else {
        struct tnode* insertNode = createNewNode(value);
        insertNode->next = head;
        head = insertNode;
    }
}

void pushTail(int value) {
    if (head == NULL) {
        head = tail = createNewNode(value);
    }
    else {
        tail->next = createNewNode(value);
        tail = tail->next;
    }
}

void printList(struct tnode* n) {
    while (n != NULL) {
        printf("%d ", n->value);
        n = n->next;
    }
    printf("\n");
}

int main() {
    pushHead(10);
    pushTail(35);
    pushTail(27);
    pushTail(31);
    printList(head);
    free(head);
}