#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - GSLC Sesi 11 Lab - Exercise 2

// Variabel global untuk jumlah data yang di Queue Dufan
int count = 0;

// Deklarasi struct node yang berisikan value dari queue dufan.
struct node {
    char name[100];
    double height;
    int age;
    // 1 = VIP, 0 = REGULAR.
    int status;
    struct node* next;
};

// Deklarasikan Front dan Back yang masih berisikan NULL karena node belum ada isinya.
struct node* Front = NULL;
struct node* Back = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Prosedur untuk Print Queue yang ada sekarang.
void displayQueue(struct node* n) {
    /* Jika Node masih kosong, atau NULL maka kita akan beri tahu bahwa
       Node kosong*/
    if (n == NULL) {
        printf("Antrian masih kosong!\n");
    }
    // Variabel nomor antrian
    int nomorAntrian = 1;
    /* Kita akan iterasi terus sampai node tidak NULL alias sudah di akhir.
       Jika masih belum NULL, kita akan print value dari node tersebut, lalu
       Kita set pointer struct nya menjadi selanjutnya terus sampai terakhir. */
    while (n != NULL) {
        printf("Antrian %d: %s (%s)\n\n", nomorAntrian, n->name, n->status == 1 ? "VIP" : "REGULER");
        // printf("[%d] -> ", n->value);
        n = n->next;
        nomorAntrian++;
    }
}

// Function bantuan untuk membuat Node Baru dengan parameter value dan nama.
struct node* createNewNode(int age, int status, double height, char* name) {
    // Mengalokasikan memory untuk 1 struct yang nantinya akan disambungkan ke node yang ada.
    struct node* temporary = (struct node*)malloc(sizeof(struct node));
    // Set value dari value node ini menjadi input user.
    temporary->age = age;
    temporary->status = status;
    temporary->height = height;
    strcpy(temporary->name, name);
    /* Kita set next dari node yang baru adalah NULL dahulu, nantinya selanjutnya ada atau tidak
       akan di handle setiap skenario yang ada (insert Front maka next nya Front, dan lain lain.) */
    temporary->next = NULL;
    // Return dari node yang sudah kita buat.
    return temporary;
}


// Procedure untuk insert
void push(int age, int status, double height, char* name) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct node* newNode = createNewNode(age, status, height, name);
    /* Ketika Front masih NULL atau Node masih kosong, maka kita akan set Front dan Back nya
       adalah newNode yang baru dibuat karena node masih satu maka Front dan Back sama. */

    if (status == 1) {
        // Jika pengunjung VIP maka status == 1
        // dan insert ke depan.
        if (Front == NULL) {
            Front = newNode;
            Back = newNode;
        }
        // Insert ke head atau ke depan.
        else {
            /* Namun jika sudah ada node, kita akan buat newNode menjadi Head yang baru
            sedangkan next dari head yang baru adalah Head sebelumnya */
            newNode->next = Front;
            Front = newNode;
        }
    }
    else if (status == 0) {
        // Jika pengunjung Reguler maka status == 0
        // dan insert ke back.
        if (Front == NULL) {
            Front = newNode;
            Back = newNode;
        }
        // Insert ke tail atau ke belakang.
        else {
            /* Namun jika sudah ada next node, kita akan membuat next dari Back yang sekarang menjadi
               newNode ini, dan membuat newNode menjadi Back yang baru*/
            Back->next = newNode;
            Back = newNode;
        }
    }
    // Tambah variabel global count karena pengunjung nambah satu.
    count = count + 1;
}

// Procedure untuk pop queue
void pop() {
    // Jika queue masih kosong.
    if (Front == NULL) {
        // Karena queue menjadi kosong alias count jadi 0.
        count = 0;
        Front = Back = NULL;
        free(Front);
    }
    else {
        // Ketika berkurang lalu kita kurangi global variabel
        // count nya dikurangi 1.
        count = count - 1;
        // Jika hanya satu node saja di linked list.
        if (Front->next == NULL) {
            Front = Back = NULL;
            free(Front);
        }
        // Jadikan next dari front yang sekarang menjadi front yang baru.
        else {
            struct node* delete = Front;
            Front = Front->next;
            free(delete);
        }
    }
}

// Procedure untuk mencari antrian sesuai nama pengunjung.
void searchByName(struct node* n, char* search) {
    /* Jika Node masih kosong, atau NULL maka kita akan beri tahu bahwa
       Node kosong*/
    if (n == NULL) {
        printf("Antrian masih kosong!\n");
        return;
    }
    // Variabel nomor antrian
    int nomorAntrian = 1;
    // Kita akan iterasi terus mencari nama yang kita cari.
    while (n != NULL) {
        if (strcmp(n->name, search) == 0) {
            printf("Antrian no %d\n", nomorAntrian);
            printf("Nama: %s\n", n->name);
            printf("Umur: %d\n", n->age);
            printf("Tinggi Badan: %.2lfcm\n", n->height);
            printf("Status Pengunjung: %s\n", n->status == 1 ? "VIP" : "REGULER");
            return;
        }
        n = n->next;
        nomorAntrian = nomorAntrian + 1;
    }
    printf("%s tidak ditemukkan\n", search);
}

// Procedure untuk report
void report(struct node* n) {
    int income = 0;
    int vip = 0;
    int reguler = 0;
    if (n == NULL) {
        printf("Antiran masih kosong!\n");
        return;
    }
    while (n != NULL) {
        // Reguler
        if (n->status == 0) {
            income = income + 20000;
            reguler = reguler + 1;
        }
        // VIP
        else if (n->status == 1) {
            income = income + 30000;
            vip = vip + 1;
        }
        n = n->next;
    }
    printf("Ada %d pengunjung dengan %d VIP dan %d REGULER\n", count, vip, reguler);
    printf("Total income sebesar Rp%d\n", income);
}

// Function main
int main() {
    // Deklarasi choice untuk menu, value dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    while (1) {
        system("cls");
        // Print node yang ada setiap di menu
        printf("Jumlah Pengunjung : %d Orang\n", count);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("2501976503 - Fabian Habil Ramdhan");
        puts("1. Tambah Pengunjung");
        puts("2. Memanggil pengunjung untuk wahana");
        puts("3. Melihat semua antrian");
        puts("4. Mencari pengunjung berdasarkan nama");
        puts("5. Report");
        puts("6. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 6, karena menu sampai 5 dan jika ingin keluar
           user input 6 */
        if (valid == 1 && (choice >= 1 && choice <= 5)) {
            system("cls");
            if (choice == 1) {
                char name[100];
                char statusPengunjung[15];
                double height;
                int age;
                int status = 0;
                puts("Memasukkan data pengunjung");
                printf("Masukkan nama: ");
                scanf(" %[^\n]", name);
                getchar();
                printf("Masukkan umur pengunjung: ");
                scanf("%d", &age);
                getchar();
                printf("Masukkan tinggi pengunjung (cm): ");
                scanf("%lf", &height);
                getchar();
                printf("REGULER atau VIP\n");
                printf("Jika salah maka pengunjung akan ditempatkan di REGULER\n");
                printf("Masukkan status pengunjung: ");
                scanf(" %[^\n]", statusPengunjung);
                getchar();
                if (strcmp(statusPengunjung, "VIP") == 0) {
                    status = 1;
                }
                else {
                    status = 0;
                }
                printf("Pengunjung masuk ke antrian!\n");
                // Push ke queue
                push(age, status, height, name);
            }
            else if (choice == 2) {
                // Kita menggunakan temp count jika pengunjung kurang dari 5
                // Kenapa menggunakan temp count, karena variabel global count ketika
                // kita pop akan mengurangi, ini akan menganggu iterasi dan notice kepada user.
                int tempCount = count;
                // Ketika jumlah sekarang masih kurang dari 5
                if (count == 0) {
                    printf("Antrian masih kosong!\n");
                }
                else if (count > 5) {
                    // Hanya panggil 5.
                    for (int i = 0; i < 5;i++) {
                        pop();
                    }
                    printf("5 Pengunjung sudah dipanggil!\n");
                }
                else {
                    for (int i = 0; i < tempCount; i++) {
                        pop();
                    }
                    printf("%d Pengunjung sudah dipanggil!\n", tempCount);
                }
            }
            else if (choice == 3) {
                displayQueue(Front);
            }
            else if (choice == 4) {
                char search[100];
                printf("Cari pengunjung: ");
                scanf(" %[^\n]", search);
                getchar();
                searchByName(Front, search);
            }
            else if (choice == 5) {
                report(Front);
            }
            enterToContinue();
        }
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
}