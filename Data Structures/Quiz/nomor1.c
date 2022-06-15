#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan
struct node {
    char fileName[100];
    char fileType[100];
    double fileSize;
    struct node* leftChildren;
    struct node* rightChildren;
};

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function for new node.
struct node* createNewNode(double fileSize, char* fileName, char* fileType) {
    struct node* newNode
        = (struct node*)malloc(sizeof(struct node));
    newNode->fileSize = fileSize;
    strcpy(newNode->fileName, fileName);
    strcpy(newNode->fileType, fileType);
    newNode->leftChildren = NULL;
    newNode->rightChildren = NULL;
    return newNode;
}

// Insert
struct node* insert(struct node* current, double fileSize, char* fileName, char* fileType) {
    if (current == NULL) {
        return createNewNode(fileSize, fileName, fileType);
    }
    else if (fileSize != current->fileSize) {
        if (fileSize < current->fileSize) {
            current->leftChildren = insert(current->leftChildren, fileSize, fileName, fileType);
        }
        else {
            current->rightChildren = insert(current->rightChildren, fileSize, fileName, fileType);
        }
    }
    return current;
}

// Left - Print Node - Right
void printInOrder(struct node* curr) {
    if (curr == NULL) {
        return;
    }
    else {
        printInOrder(curr->leftChildren);
        printf("%s %s %lf\n", curr->fileName, curr->fileType, curr->fileSize);
        printInOrder(curr->rightChildren);
    }
}

int main() {
    // Deklarasi Root
    struct node* root = NULL;
    // Deklarasi choice untuk menu, valid untuk menu, dan num untuk input user.
    int valid = 0;
    int choice;
    while (1) {
        system("cls");
        puts("2501976503 - Fabian Habil");
        puts("Filing System");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input File Data");
        puts("2. Print all file (level order)");
        puts("3. Search by Name");
        puts("4. Search by Size");
        puts("5. Delete File");
        puts("6. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 2, karena menu sampai 2 dan jika ingin keluar
           user input 3 */
        if (valid == 1 && (choice >= 1 && choice <= 6)) {
            if (choice == 1) {
                char fileName[50];
                char fileType[50];
                double fileSize;
                printf("Silahkan masukkan fileName: ");
                scanf(" %[^\n]", fileName);
                getchar();
                printf("IMG / EXE / PDF / SONG\n");
                printf("Silahan masukkan fileType: ");
                scanf(" %[^\n]", fileType);
                getchar();
                printf("Silahkan masukkan fileSize: ");
                scanf("%lf", &fileSize);
                getchar();
                root = insert(root, fileSize, fileName, fileType);
                enterToContinue();
            }
            else if (choice == 2) {
                // Print list antrian
                system("cls");
                printInOrder(root);
                enterToContinue();
            }
            else if (choice == 3) {
                system("cls");
                printf("2501976503 - Fabian Habil Ramdhan");
                break;
            }
        }
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
}