#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan
struct node {
    char fileName[100];
    char fileType[100];
    int height;
    double fileSize;
    struct node* left;
    struct node* right;
};

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function untuk mencari max.
int max(double a, double b) {
    return (a > b) ? a : b;
}

// Function untuk mencari height dari sebuah node.
int height(struct node* current) {
    if (current == NULL) return 0;
    else return current->height;
}

// Function untuk mencari balance factor dari sebuah node.
int getBalance(struct node* current) {
    if (current == NULL) return 0;
    else return height(current->left) - height(current->right);
}

// Function untuk rotate right
struct node* rotateRight(struct node* current) {
    struct node* targetRotate = current->left;
    // Mau ada children atau tidak, kita ambil saja,
    // Karena kalau misalnya null juga tidak masalah kita menunjuk ke null address
    // Atau tidak ada tujuan.
    struct node* targetRotateChildrenRight = targetRotate->right;

    // Node sebelah kiri dari node yang dirotate menjadi parent dari node yang dirotate.
    // dan node tersebut menjadi children sebelah kanan dari parent yang baru.
    targetRotate->right = current;

    // Children sebelah kanan dari node yang sekarang menjadi parent,
    // maupun ada atau tidak, kita assign menjadi children sebelah
    // kiri dari node yang sudah dirotate.
    current->left = targetRotateChildrenRight;

    // Update heights dari node tersebut.
    current->height = 1 + max(height(current->left), height(current->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));

    // Return node yang baru
    return targetRotate;
}

// Function untuk rotate left
struct node* rotateLeft(struct node* current) {
    struct node* targetRotate = current->right;
    // Mau ada children atau tidak, kita ambil saja,
    // Karena kalau misalnya null juga tidak masalah kita menunjuk ke null address
    // Atau tidak ada tujuan.
    struct node* targetRotateChildrenLeft = targetRotate->left;

    // Node sebelah kanan dari node yang dirotate menjadi parent dari node yang dirotate.
    // dan node tersebut menjadi children sebelah kiri dari parent yang baru.
    targetRotate->left = current;

    // Children sebelah kiri dari node yang sekarang menjadi parent,
    // maupun ada atau tidak, kita assign menjadi children sebelah
    // kanan dari node yang sudah dirotate.
    current->right = targetRotateChildrenLeft;

    // Update heights dari node tersebut.
    current->height = 1 + max(height(current->left), height(current->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));

    // Return node yang baru.
    return targetRotate;
}

// Function for new node.
struct node* createNewNode(double fileSize, char* fileName, char* fileType) {
    struct node* newNode
        = (struct node*)malloc(sizeof(struct node));
    newNode->fileSize = fileSize;
    strcpy(newNode->fileName, fileName);
    strcpy(newNode->fileType, fileType);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert
struct node* insert(struct node* current, double fileSize, char* fileName, char* fileType) {
    // Jika yang ditunjuk kosong maka buat node baru.
    if (current == NULL) {
        return createNewNode(fileSize, fileName, fileType);
    }

    // Jika yang akan diinsert lebih besar dari node yang divisit sekarang.
    else if (fileSize > current->fileSize) {
        current->right = insert(current->right, fileSize, fileName, fileType);
    }

    // Jika yang akan diinsert lebih kecil dari node yang divisit sekarang.
    else if (fileSize < current->fileSize) {
        current->left = insert(current->left, fileSize, fileName, fileType);
    }

    // Jika tidak lebih besar dan tidak lebih kecil, maka sama dan tidak boleh di AVL Tree.
    else {
        return current;
    }

    // update height
    current->height = 1 + max(height(current->left), height(current->right));

    // balance
    int balance = getBalance(current);

    // berat ke kiri
    if (balance > 1) {
        // rotasi ke kanan (balancing ke kanan)

        // kasus 1 : rotasi ke kanan 1x (Left Left Case)
        if (fileSize < current->left->fileSize) {
            return rotateRight(current);
        }
        // kasus 2 : rotasi ke kiri, baru ke kanan (2x rotasi) (Left Right Case)
        else if (fileSize > current->left->fileSize) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x (Right Right Case)
        if (fileSize > current->right->fileSize) {
            return rotateLeft(current);
        }

        // kasus 2 : rotasi ke kanan, baru ke kiri (Right Left Case)
        else if (fileSize < current->right->fileSize) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
    }
    return current;
}

// Left - Print Node - Right
void printInOrder(struct node* current) {
    if (current == NULL) {
        return;
    }
    else {
        printInOrder(current->left);
        printf("%s %s %lf\n", current->fileName, current->fileType, current->fileSize);
        printInOrder(current->right);
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