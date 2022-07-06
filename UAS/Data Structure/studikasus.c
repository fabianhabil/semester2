#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Library untuk mendapatkan tanggal dan jam sekarang.
#include <time.h>

// 2501976503 - Fabian Habil Ramdhan - Studi Kasus UAS - Data Structures

struct node {
    char name[100];
    char nim[15];
    char time[15];
    struct node* leftChildren;
    struct node* rightChildren;
};

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter To Continue!");
    getchar();
}

// Function untuk node baru.
struct node* createNewNode(char* name, char* nim) {
    // Alokasi memory untuk node baru yang berisikan input user.
    struct node* newNode
        = (struct node*)malloc(sizeof(struct node));
    // Variabel timenow dengan data time_t, lalu kita assign menggunakan time()
    time_t timenow;
    // Dari struct sini kita bisa mendapatkan jam dan menit waktu sekarang.
    struct tm* timeinfo;
    time(&timenow);
    timeinfo = localtime(&timenow);

    char time[15];
    // Kita set value dari time menjadi waktu sekarang (hh:mm)
    sprintf(time, "%d:%d\0", timeinfo->tm_hour, timeinfo->tm_min);
    // Masukkan value nama, nim dan tanggal sekarang di node yang baru.
    strcpy(newNode->time, time);
    strcpy(newNode->name, name);
    strcpy(newNode->nim, nim);
    // Jadikan left children dan right children dari node yang baru menjadi NULL.
    newNode->leftChildren = NULL;
    newNode->rightChildren = NULL;
    // Return node yang baru.
    return newNode;
}

// Insert
struct node* insert(struct node* current, char* name, char* nim) {
    // Ketika berada di node yang kosong, assign node yang baru ke tempat yang kosong.
    if (current == NULL) {
        return createNewNode(name, nim);
    }
    // Ketika NIM dari node sekarang .
    else if (strcmp(current->nim, nim) != 0) {
        // Ketika function strcmp mereturn value lebih besar dari 0, maka current->nim
        // lebih besar atau urutannya dari input user (NIM), maka kita traverse lagi NIM
        // nya ke kiri.
        if (strcmp(current->nim, nim) > 0) {
            current->leftChildren = insert(current->leftChildren, name, nim);
        }
        // Ketika function strcmp mereturn value lebih kecil dari 0, maka current->nim
        // lebih kecil atau urutannya dari input user (NIM), maka kita traverse lagi NIM
        // nya ke kanan.
        else if (strcmp(current->nim, nim) < 0) {
            current->rightChildren = insert(current->rightChildren, name, nim);
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
        // Rekursif ke kiri, print lalu ke kanan.
        printInOrder(curr->leftChildren);
        // Print data mahasiswa.
        printf("Name: %s\n", curr->name);
        printf("ID: %s\n", curr->nim);
        printf("Time of Attendance: %s\n\n", curr->time);
        printInOrder(curr->rightChildren);
    }
}

// Search tree berdasarkan size
int searchByNIM(struct node* curr, char* search) {
    // Jika tidak ditemukkan.
    if (curr == NULL) {
        return -1;
    }
    // Jika node sekarang nim nya sama dengan search (input user)
    // Maka kita print data dari mahasiswa.
    else if (strcmp(curr->nim, search) == 0) {
        printf("%s found with ID %s\n", curr->name, curr->nim);
        printf("Time of Attendance %s\n", curr->time);
        return 1;
    }
    else {
        // Ketika function strcmp mereturn value lebih kecil dari 0, maka current->nim
        // lebih kecil atau urutannya dari input user (NIM), maka kita traverse lagi untuk
        // mencari NIM nya ke kanan.
        if (strcmp(curr->nim, search) < 0) {
            searchByNIM(curr->rightChildren, search);
        }
        // Ketika function strcmp mereturn value lebih besar dari 0, maka current->nim
        // lebih besar atau urutannya dari input user (NIM), maka kita traverse lagi untuk
        // mencari NIM nya ke kiri.
        else if (strcmp(curr->nim, search) > 0) {
            searchByNIM(curr->leftChildren, search);
        }
    }
}

int main() {
    // Deklarasi Root
    struct node* root = NULL;
    // Deklarasi choice untuk menu, valid untuk menu.
    int valid = 0;
    int choice;
    while (1) {
        system("cls");
        puts("2501976503 - Fabian Habil");
        puts("Attendance Student System");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input Student Attendance");
        puts("2. Show Student Attendance");
        puts("3. Search Student");
        puts("4. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 2, karena menu sampai 2 dan jika ingin keluar
           user input 3 */
        if (valid == 1 && (choice >= 1 && choice <= 4)) {
            system("cls");
            // Jika user input 1 maka ke menu Input Student Attendance.
            if (choice == 1) {
                // Deklarasi Variabel nama dan nim untuk input user.
                char name[100];
                char nim[15];
                // Input nama dari user.
                printf("Input Name: ");
                scanf(" %[^\n]", name);
                getchar();
                // Input Nim dari user.
                printf("Input ID: ");
                scanf(" %[^\n]", nim);
                getchar();
                // Insert ke BST Tree.
                root = insert(root, name, nim);
                enterToContinue();
            }
            // Jika user input 2 maka ke menu Show Student Attendance.
            else if (choice == 2) {
                // Print in order (Left - Print - Right)
                printInOrder(root);
                enterToContinue();
            }
            // Jika user input 3 maka ke menu Search Student.
            else if (choice == 3) {
                // Deklarasi variabel nim untuk input user.
                char nim[15];
                // Input NIM dari user.
                printf("Please Input NIM: ");
                scanf(" %[^\n]", nim);
                getchar();
                // Mencari dari tree sesuai dengan NIM
                int found = searchByNIM(root, nim);
                // Jika function searchByNIM mereturn -1, maka data tidak ditemukan.
                if (found == -1) {
                    printf("Student with ID %s still absent\n", nim);
                }
                enterToContinue();
            }
            // Jika user input 4 maka keluar dari program.
            else if (choice == 4) {
                printf("2501976503 - Fabian Habil Ramdhan");
                break;
            }
        }
        else {
            printf("Invalid Input! Please Try Again!\n");
            enterToContinue();
        }
    }
}