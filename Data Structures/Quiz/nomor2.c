#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Quiz no 2 Data Structures 15 Juni 2022

// Jawaban Quiz
// Untuk searching, jika dibandingkan AVL Tree dengan BST mana lebih cepat itu kembali lagi
// dengan data yang ada, namun jika kita mengambil Worst Case, melakukan searching di BST
// adalah O(N) karena ada kemungkinan tree tersebut menjadi skewed dengan height sebanyak data.
// Namun, searching di AVL Tree Worst Case Scenario nya adalah O(log n) karena tree yang kita
// punya tidak mungkin berat ke kanan atau ke kiri karena tree tersebut kita maintain atau
// pertahankan balance nya.


// Variabel global untuk delete, 0 tidak ditemukkan 1 jika ditemukan.
int notFound = 0;

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
        printf("Nama File: %s\n", current->fileName);
        printf("Tipe File: %s\n", current->fileType);
        printf("Ukuran File: %.2lfKB(%.2lfMB)\n\n", current->fileSize, current->fileSize / 1000);
        printInOrder(current->right);
    }
}

// Search tree by name akan O(n) karena tree ini adalah BST dan value berdasarkan fileSize
// bukan fileName.
int searchByName(struct node* current, char* search) {
    // Jika tidak ditemukkan.
    if (current == NULL) {
        return -1;
    }
    // Jika node sekarang sama dengan yang akan dicari.
    else if (!strcmp(current->fileName, search)) {
        printf("%s ditemukkan dengan ukuran file %.2lfKB(%.2lfMB) dan tipe file nya adalah %s\n", current->fileName, current->fileSize, current->fileSize / 1000, current->fileType);
        return 1;
    }
    else {
        // Rekursif ke kiri dan ke kanan children setiap node.
        searchByName(current->left, search);
        searchByName(current->right, search);
    }
}

// Search tree berdasarkan size
int searchBySize(struct node* current, double fileSize) {
    // Jika tidak ditemukkan.
    if (current == NULL) {
        return -1;
    }
    // Jika node sekarang sama ukuran file nya dengan yang dicari.
    else if (current->fileSize == fileSize) {
        printf("%s ditemukkan dengan ukuran file %.2lfKB(%.2lfMB) dan tipe file nya adalah %s\n", current->fileName, current->fileSize, current->fileSize / 1000, current->fileType);
        return 1;
    }
    else {
        // Jika yang dicari lebih besar dari node sekarang, maka kita cari ke children sebelah kanannya.
        if (fileSize > current->fileSize) {
            searchBySize(current->right, fileSize);
        }
        // Jika yang dicari lebih kecil dari node sekarang, maka kita cari ke children sebelah kirinya.
        else if (fileSize < current->fileSize) {
            searchBySize(current->left, fileSize);
        }
    }
}

// Untuk mendapatkan node dengan value terbesar.
struct node* maxValueNode(struct node* curr) {
    struct node* traverse = curr;
    while (traverse->right != NULL) {
        traverse = traverse->right;
    }
    return traverse;
}

// Untuk delete sama seperti BST, yang membedakan adalah kita melakukan balancing di tree tersebut.
struct node* delete(struct node* current, double fileSize) {
    // Jika kosong maka tidak ditemukkan.
    if (current == NULL) {
        notFound = 1;
        return current;
    }
    // Jika yang akan dihapus lebih kecil, maka cari di children sebelah kiri.
    if (fileSize < current->fileSize) {
        current->left = delete(current->left, fileSize);
    }
    // Jika yang akan dihapus lebih besar, maka cari di children sebelah kanan.
    else if (fileSize > current->fileSize) {
        current->right = delete(current->right, fileSize);
    }
    // Jika ditemukkan
    else {
        // Case pertama jika tidak ada atau hanya mempunyai satu child.
        struct node* temp = NULL;
        if (current->left == NULL || current->right == NULL) {
            // Jika children kiri kosong, maka ambil children kanan
            if (current->left == NULL) {
                temp = current->right;
            }
            // Jika children kanan kosong, maka ambil children kiri
            else if (current->right == NULL) {
                temp = current->left;
            }
            // Jika tidak mempunyai child
            if (temp == NULL) {
                temp = current;
                current = NULL;
            }
            // Mempunyai satu child 
            else {
                // Tukar node sekarang dengan node sebelah kiri atau sebelah kanan yang sudah ditunjuk
                *current = *temp;
                free(temp);
            }
        }
        // Jika ada dua children, maka ambil paling minimum dari children sebelah kanan
        // atau paling maksimal dari children sebelah kiri. Untuk sekarang kita akan
        // menggunakan maksimal dari children sebelah kiri.
        else {
            temp = maxValueNode(current->left);
            // Copy all the data from the max node to the current node.
            strcpy(current->fileName, temp->fileName);
            strcpy(current->fileType, temp->fileType);
            current->fileSize = temp->fileSize;
            current->left = delete(current->left, temp->fileSize);
        }
    }

    // Kita cek lagi, apakah tree hanya menjadi satu node ketika sudah menghapus
    // Jika iya, maka langsung return
    if (current == NULL) {
        return current;
    }

    // Lakukan balancing terhadap node tersebut.
    // update height
    current->height = 1 + max(height(current->left), height(current->right));

    // balance
    int balance = getBalance(current);

    // berat ke kiri
    if (balance > 1) {
        // rotasi ke kanan (balancing ke kanan)

        // kasus 1 : rotasi ke kanan 1x (Left Left Case)
        if (current->fileSize < current->left->fileSize) {
            return rotateRight(current);
        }
        // kasus 2 : rotasi ke kiri, baru ke kanan (2x rotasi) (Left Right Case)
        else if (current->fileSize > current->left->fileSize) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x (Right Right Case)
        if (current->fileSize > current->right->fileSize) {
            return rotateLeft(current);
        }

        // kasus 2 : rotasi ke kanan, baru ke kiri (Right Left Case)
        else if (current->fileSize < current->right->fileSize) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
    }

    return current;
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
                enterToContinue();
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