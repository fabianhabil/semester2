#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Quiz no 1 Data Structures 15 Juni 2022

// Variabel global untuk delete, 0 tidak ditemukkan 1 jika ditemukan.
int notFound = 0;
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
        printf("Nama File: %s\n", curr->fileName);
        printf("Tipe File: %s\n", curr->fileType);
        printf("Ukuran File: %.2lfKB(%.2lfMB)\n\n", curr->fileSize, curr->fileSize / 1000);
        printInOrder(curr->rightChildren);
    }
}

// Search tree by name akan O(n) karena tree ini adalah BST dan value berdasarkan fileSize
// bukan fileName.
int searchByName(struct node* curr, char* search) {
    // Jika tidak ditemukkan.
    if (curr == NULL) {
        return -1;
    }
    // Jika node sekarang sama dengan yang akan dicari.
    else if (!strcmp(curr->fileName, search)) {
        printf("%s ditemukkan dengan ukuran file %.2lfKB(%.2lfMB) dan tipe file nya adalah %s\n", curr->fileName, curr->fileSize, curr->fileSize / 1000, curr->fileType);
        return 1;
    }
    else {
        // Rekursif ke kiri dan ke kanan children setiap node.
        searchByName(curr->leftChildren, search);
        searchByName(curr->rightChildren, search);
    }
}

// Search tree berdasarkan size
int searchBySize(struct node* curr, double fileSize) {
    // Jika tidak ditemukkan.
    if (curr == NULL) {
        return -1;
    }
    // Jika node sekarang sama ukuran file nya dengan yang dicari.
    else if (curr->fileSize == fileSize) {
        printf("%s ditemukkan dengan ukuran file %.2lfKB(%.2lfMB) dan tipe file nya adalah %s\n", curr->fileName, curr->fileSize, curr->fileSize / 1000, curr->fileType);
        return 1;
    }
    else {
        // Jika yang dicari lebih besar dari node sekarang, maka kita cari ke children sebelah kanannya.
        if (fileSize > curr->fileSize) {
            searchBySize(curr->rightChildren, fileSize);
        }
        // Jika yang dicari lebih kecil dari node sekarang, maka kita cari ke children sebelah kirinya.
        else if (fileSize < curr->fileSize) {
            searchBySize(curr->leftChildren, fileSize);
        }
    }
}

// Untuk mendapatkan node terbesar sebelah kiri.
struct node* maxValueNode(struct node* curr) {
    struct node* traverse = curr;
    while (traverse->rightChildren != NULL) {
        traverse = traverse->rightChildren;
    }
    return traverse;
}

struct node* delete(struct node* curr, double fileSize) {
    // Jika kosong maka tidak ditemukkan.
    if (curr == NULL) {
        notFound = 1;
        return curr;
    }

    // Jika yang akan dihapus lebih kecil, maka cari di children sebelah kiri.
    if (fileSize < curr->fileSize) {
        curr->leftChildren = delete(curr->leftChildren, fileSize);
    }
    // Jika yang akan dihapus lebih besar, maka cari di children sebelah kanan.
    else if (fileSize > curr->fileSize) {
        curr->rightChildren = delete(curr->rightChildren, fileSize);
    }
    // Jika ditemukkan
    else {
        // Case pertama jika tidak ada atau hanya mempunyai satu child.
        if (curr->leftChildren == NULL) {
            struct node* temp = curr->rightChildren;
            free(curr);
            return temp;
        }
        else if (curr->rightChildren == NULL) {
            struct node* temp = curr->leftChildren;
            free(curr);
            return temp;
        }
        // Jika ada dua children, maka ambil paling minimum dari children sebelah kanan
        // atau paling maksimal dari children sebelah kiri. Untuk sekarang kita akan
        // menggunakan maksimal dari children sebelah kiri.

        struct node* temp = maxValueNode(curr->leftChildren);
        // Copy all the data from the max node to the current node.
        strcpy(curr->fileName, temp->fileName);
        strcpy(curr->fileType, temp->fileType);
        curr->fileSize = temp->fileSize;
        curr->leftChildren = delete(curr->leftChildren, temp->fileSize);
    }
    return curr;
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
        puts("2. Print all file (inorder)");
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
            system("cls");
            if (choice == 1) {
                char fileName[50];
                char fileType[50];
                double fileSize;
                printf("Silahkan masukkan nama file: ");
                scanf(" %[^\n]", fileName);
                getchar();
                printf("IMG / EXE / PDF / SONG\n");
                printf("Silahan masukkan tipe file: ");
                scanf(" %[^\n]", fileType);
                getchar();
                printf("Silahkan masukkan ukuran file (dalam ukuran KB): ");
                scanf("%lf", &fileSize);
                getchar();
                root = insert(root, fileSize, fileName, fileType);
                enterToContinue();
            }
            else if (choice == 2) {
                // Print list antrian
                printInOrder(root);
                enterToContinue();
            }
            else if (choice == 3) {
                char search[50];
                printf("Silahkan masukkan nama file yang akan dicari: ");
                scanf(" %[^\n]", search);
                getchar();
                int found = searchByName(root, search);
                if (found == -1) {
                    printf("File name dengan %s tidak ditemukkan!\n", search);
                }
                enterToContinue();
            }
            else if (choice == 4) {
                double search;
                printf("Silahkan masukkan ukuran file yang akan dicari (dalam ukuran KB): ");
                scanf("%lf", &search);
                getchar();
                int found = searchBySize(root, search);
                if (found == -1) {
                    printf("File name dengan size %.2lfKB tidak ditemukkan\n", search);
                }
                enterToContinue();
            }
            else if (choice == 5) {
                // Jadikan 0 lagi karena kita akan menghapus lagi.
                notFound = 0;
                double deleteKey;
                printf("Silahkan masukkan ukuran file yang akan dihapus (dalam ukuran KB): ");
                scanf("%lf", &deleteKey);
                getchar();
                root = delete(root, deleteKey);
                if (notFound == 1) {
                    printf("File dengan ukuran %.2lfKB tidak ditemukkan!", deleteKey);
                }
                else {
                    printf("File dengan ukuran %.2lfKB berhasil dihapus!", deleteKey);
                }
                printf("\n");
                enterToContinue();
            }
            else if (choice == 6) {
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