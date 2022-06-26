#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - GSLC Sesi 11 Lab - Exercise 1

// Variabel global untuk delete, 0 tidak ditemukkan 1 jika ditemukan.
int notFound = 0;

// Variabel global untuk jumlah data yang di AVL Tree.
int count = 0;

// Deklarasi struct untuk Avl Tree
struct node {
    char name[100];
    char class[100];
    double score;
    int height;
    struct node* left;
    struct node* right;
};

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter To Continue!");
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

// Function untuk pembuatan node baru
struct node* createNewNode(double score, char* name, char* class) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->score = score;
    strcpy(newNode->class, class);
    strcpy(newNode->name, name);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert new node ke AVL Tree.
struct node* insert(struct node* current, double score, char* name, char* class) {
    // Jika yang ditunjuk kosong maka buat node baru.
    if (current == NULL) {
        count = count + 1;
        return createNewNode(score, name, class);
    }

    // Jika yang akan diinsert lebih besar dari node yang divisit sekarang.
    else if (score >= current->score) {
        current->right = insert(current->right, score, name, class);
    }

    // Jika yang akan diinsert lebih kecil dari node yang divisit sekarang.
    else if (score < current->score) {
        current->left = insert(current->left, score, name, class);
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
        if (score < current->left->score) {
            return rotateRight(current);
        }
        // kasus 2 : rotasi ke kiri, baru ke kanan (2x rotasi) (Left Right Case)
        else if (score > current->left->score) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x (Right Right Case)
        if (score > current->right->score) {
            return rotateLeft(current);
        }

        // kasus 2 : rotasi ke kanan, baru ke kiri (Right Left Case)
        else if (score < current->right->score) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
    }
    return current;
}

// Search tree by name akan O(n) karena tree ini adalah BST dan value berdasarkan score
// bukan name.
int searchByName(struct node* current, char* search) {
    // Jika tidak ditemukkan.
    if (current == NULL) {
        return -1;
    }
    // Jika node sekarang sama dengan yang akan dicari.
    else if (!strcmp(current->name, search)) {
        printf("%s found in class %s with score %.2lf!\n", current->name, current->class, current->score);
        return 1;
    }
    else {
        // Rekursif ke kiri dan ke kanan children setiap node.
        searchByName(current->left, search);
        searchByName(current->right, search);
    }
}

// Untuk print nilai yang lebih besar dari input, kita mempunyai time complexity O(N).
// Karena ada kemungkinan nilai yang diinput membuat nilai yang sama dan berdekatan
// ada di subtree yang berbeda, sebelah kiri atau sebelah kanan dari root tree kita.
void searchBiggerThanScore(struct node* current, double score) {
    // Jika count
    if (count == 0) {
        printf("Data still empty!");
        return;
    }
    if (current == NULL) {
        return;
    }
    else {
        if (current->score >= score) {
            printf("Student's Name: %s\n", current->name);
            printf("Student's Class: %s\n", current->class);
            printf("Student's Score: %.2lf\n\n", current->score);
        }
        searchBiggerThanScore(current->left, score);
        searchBiggerThanScore(current->right, score);
    }
}

// Untuk mendapatkan node dengan value terbesar.
struct node* maxValueNode(struct node* current) {
    struct node* traverse = current;
    while (traverse->right != NULL) {
        traverse = traverse->right;
    }
    return traverse;
}

// Untuk mendapatkan node dengan value terkecil.
struct node* minValueNode(struct node* current) {
    struct node* traverse = current;
    while (traverse->left != NULL) {
        traverse = traverse->left;
    }
    return traverse;
}

// Untuk delete sama seperti BST, yang membedakan adalah kita melakukan balancing di tree tersebut.
struct node* delete(struct node* current, char* search) {
    // Jika kosong maka tidak ditemukkan.
    if (current == NULL) {
        notFound = 1;
        return current;
    }
    // Jika tidak ditemukkan, karena kita search by name dan tree berdasarkan score.
    // maka delete time complexity nya O(N)
    if (strcmp(current->name, search) != 0) {
        current->left = delete(current->left, search);
        current->right = delete(current->right, search);
    }
    // Jika ditemukkan
    else {
        notFound = 0;
        count = count - 1;
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
            // Copy semua data dari max node ke node sekarang yang akan dihapus.
            strcpy(current->name, temp->name);
            strcpy(current->class, temp->class);
            current->score = temp->score;
            // Delete node yang tadi ditukar ke posisi node yang dihapus.
            current->left = delete(current->left, temp->name);
        }
    }

    // Kita cek lagi, apakah tree menjadi kosong ketika sudah menghapus
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
        if (current->score < current->left->score) {
            return rotateRight(current);
        }
        // kasus 2 : rotasi ke kiri, baru ke kanan (2x rotasi) (Left Right Case)
        else if (current->score > current->left->score) {
            current->left = rotateLeft(current->left);
            return rotateRight(current);
        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x (Right Right Case)
        if (current->score > current->right->score) {
            return rotateLeft(current);
        }

        // kasus 2 : rotasi ke kanan, baru ke kiri (Right Left Case)
        else if (current->score < current->right->score) {
            current->right = rotateRight(current->right);
            return rotateLeft(current);
        }
    }

    return current;
}

// Prosedur student report.
void studentReport(struct node* current) {
    struct node* lowest = NULL;
    struct node* highest = NULL;
    if (count == 0) {
        printf("Student Data still empty!\n");
        return;
    }
    else if (count == 1) {
        lowest = minValueNode(current);
        printf("Only 1 Student in database!\n");
        printf("Student's Name: %s\n", lowest->name);
        printf("Student's Class: %s\n", lowest->class);
        printf("Student's Score: %.2lf\n\n", lowest->score);
    }
    else {
        lowest = minValueNode(current);
        highest = maxValueNode(current);
        printf("There is %d Student!\n", count);
        printf("The Lowest score in database!\n");
        printf("Student's Name: %s\n", lowest->name);
        printf("Student's Class: %s\n", lowest->class);
        printf("Student's Score: %.2lf\n\n", lowest->score);
        printf("The Highest score in database!\n");
        printf("Student's Name: %s\n", highest->name);
        printf("Student's Class: %s\n", highest->class);
        printf("Student's Score: %.2lf\n\n", highest->score);
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
        puts("Student Score Management System");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input Data Student");
        puts("2. Find a student based on their name");
        puts("3. Find a student that has a bigger score than the input");
        puts("4. Delete a certain student's data");
        puts("5. Report");
        puts("6. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 6, karena menu sampai 5 dan jika ingin keluar
           user input 6 */
        if (valid == 1 && (choice >= 1 && choice <= 6)) {
            system("cls");
            if (choice == 1) {
                char name[50];
                char class[50];
                double score;
                printf("Input student's name: ");
                scanf(" %[^\n]", name);
                getchar();
                printf("LA75 / LB75 / LC75 / LD75\n");
                printf("Input student's class: ");
                scanf(" %[^\n]", class);
                getchar();
                printf("Input student's score: ");
                scanf("%lf", &score);
                getchar();
                root = insert(root, score, name, class);
                enterToContinue();
            }
            else if (choice == 2) {
                char search[50];
                printf("Input student's name: ");
                scanf(" %[^\n]", search);
                getchar();
                int found = searchByName(root, search);
                if (found == -1) {
                    printf("Student with name %s not found!\n", search);
                }
                enterToContinue();
            }
            else if (choice == 3) {
                double search;
                printf("Input score you want to find: ");
                scanf("%lf", &search);
                getchar();
                printf("Showing all student's that have score bigger equal to %.2lf\n", search);
                searchBiggerThanScore(root, search);
                enterToContinue();
            }
            else if (choice == 4) {
                // Jadikan 0 lagi karena kita akan menghapus lagi.
                notFound = 0;
                char search[50];
                printf("Input student's name: ");
                scanf(" %[^\n]", search);
                getchar();
                root = delete(root, search);
                if (notFound == 1) {
                    printf("Student with name %s not found!", search);
                }
                else {
                    printf("Student with name %s deleted!", search);
                }
                printf("\n");
                enterToContinue();
            }
            else if (choice == 5) {
                studentReport(root);
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