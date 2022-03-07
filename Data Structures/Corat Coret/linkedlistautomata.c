#include <stdio.h>
#include <stdlib.h>

// Properti Fabian Habil Ramdhan, dilarang nyontek seenaknya ya!
// github.com/fabianhabil

void enterToContinue() {
    printf("Enter untuk gaskeun lagi!");
    getchar();
}

struct node {
    int value;
    struct node* next;
};

struct node* Head = NULL;
struct node* Tail = NULL;

struct node* createNewNode(int value) {
    struct node* tempNode = malloc(sizeof(struct node));
    tempNode->value = value;
    tempNode->next = NULL;

    return tempNode;
}

void printNode(struct node* n) {
    if (n == NULL) {
        printf("Node masih kosong!\n");
    }
    while (n != NULL) {
        printf("%d ", n->value);
        n = n->next;
    }
    printf("\n");
}

void pushHead(int value) {
    if (Head == NULL) {
        Head = Tail = createNewNode(value);
    }
    else {
        struct node* temp = createNewNode(value);
        temp->next = Head;
        Head = temp;
    }
}

void pushTail(int value) {
    if (Head == NULL) {
        Head = Tail = createNewNode(value);
    }
    else {
        Tail->next = createNewNode(value);
        Tail = Tail->next;
    }
}

void deleteValue(int value) {
    if (Head == NULL) {
        printf("Node masih kosong!");
        getchar();
        return;
    }
    else {
        struct node* current = Head;
        // Di Head ketemu.
        if (Head->value == value) {
            // Kalo di cuman ada satu node.
            if (Head == Tail) {
                free(current);
                Head = Tail = NULL;
                printf("Hai");
            }
            // Gak cuman satu node.
            else {
                Head = Head->next;
                free(current);
                printf("Hai2");
            }
        }
        else {
            // Cari element sampe ketemu.
            while (current->next != NULL && current->next->value != value) {
                current = current->next;
            }
            // Kalo gak ada di elemen.
            if (current->next == NULL && current->value != value) {
                printf("404 not found\n");
                enterToContinue();
                return;
            }
            if (current->next->value == value) {
                // Diujung alias di tail.
                if (current->next->next == NULL) {
                    Tail = current;
                    struct node* delete = current->next;
                    current->next = delete->next;
                    free(delete);
                }
                // Gak di ujung.
                else {
                    struct node* delete = current->next;
                    current->next = delete->next;
                    free(delete);
                }
            }
        }
    }
}

int main() {
    int choice;
    int value;
    while (1) {
        system("cls");
        printf("Node sekarang : ");
        printNode(Head);
        puts("1. Push Head");
        puts("2. Push Tail");
        puts("3. Delete Value");
        puts("4. Print Head");
        puts("5. Print Tail");
        puts("6. Exit");
        printf("Mau pilih apa: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1) {
            printf("Pushing Head\n");
            printf("Silahkan masukkan valuenya!\n");
            printf("Input : ");
            scanf("%d", &value);
            getchar();
            pushHead(value);
        }
        else if (choice == 2) {
            printf("Pushing Tail\n");
            printf("Silahkan masukkan valuenya!\n");
            printf("Input : ");
            scanf("%d", &value);
            getchar();
            pushTail(value);
        }
        else if (choice == 3) {
            printf("Delete value\n");
            printf("Silahkan masukkan valuenya!\n");
            printf("Input : ");
            scanf("%d", &value);
            getchar();
            deleteValue(value);
        }
        else if (choice == 4) {
            printf("%d\n", Head->value);
            enterToContinue();
        }
        else if (choice == 5) {
            printf("%d\n", Tail->value);
            enterToContinue();
        }
        else if (choice == 6) {
            break;
        }
        else {
            printf("Salah ih, yang bener atuh!\n");
            enterToContinue();
        }
    }
}