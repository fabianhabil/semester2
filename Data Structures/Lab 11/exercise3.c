#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 2501976503 - Fabian Habil Ramdhan - GSLC Sesi 11 Lab - Exercise 3

// Variabel Global untuk nomor pesawat
int domestic = 1;
int international = 1;
int jumlahPenumpangDomestic = 0;
int jumlahPenumpangInternational = 0;
int jumlahPenumpangDomesticBerangkat = 0;
int jumlahPenumpangInternationalBerangkat = 0;

// Struct untuk deklarasi double linked list.
struct node {
    char nama[50];
    char flightNumber[10];
    char seatNumber[10];
    struct node* next;
    struct node* previous;
};

// Deklarasi Head dan Tail untuk flight domestic
struct node* HeadDomestic = NULL;
struct node* TailDomestic = NULL;

// Deklarasi Head dan Tail untuk flight International
struct node* HeadInternational = NULL;
struct node* TailInternational = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function pembantu untuk membuat stack yang nantinya akan disambungkan dengan yang lain.
struct node* createNewNode(char* nama, char* flightNumber, char* seatNumber) {
    // Memory Allocation.
    struct node* temporary = (struct node*)malloc(sizeof(struct node));
    // Assign value input dari user ke temporary node.
    strcpy(temporary->nama, nama);
    strcpy(temporary->flightNumber, flightNumber);
    strcpy(temporary->seatNumber, seatNumber);
    // Next dan previous dari node sekarang menunjuk NULL, karena ada beberapa skenario,
    // Seperti insert head dan insert tail, next dan previousnya menunjuk node yang berbeda, jadi nanti dihandle di setiap function.
    temporary->next = NULL;
    temporary->previous = NULL;
    return temporary;
}

// Procedure untuk insert di Tail.
void insertTail(char* nama, char* flightNumber, char* seatNumber, int tipePesawat) {
    // Membuat node baru yang isinya adalah input user.
    struct node* newNode = createNewNode(nama, flightNumber, seatNumber);

    // Ketika flight domestic.
    if (tipePesawat == 1) {
        jumlahPenumpangDomestic = jumlahPenumpangDomestic + 1;
        // Jika linked list masih kosong, node ini menjadi head dan tailnya.
        if (HeadDomestic == NULL) {
            HeadDomestic = newNode;
            TailDomestic = newNode;
        }
        else {
            // Sambungkan sebelum TailDomestic dengan node baru.
            TailDomestic->next = newNode;
            // Buat sebelum dari newNode menjadi sebelum TailDomestic.
            newNode->previous = TailDomestic;
            // Buat newNode menjadi TailDomestic yang baru.
            TailDomestic = newNode;
        }
    }
    // Ketika flight international.
    else if (tipePesawat == 2) {
        jumlahPenumpangInternational = jumlahPenumpangInternational + 1;
        // Jika linked list masih kosong, node ini menjadi head dan tailnya.
        if (HeadInternational == NULL) {
            HeadInternational = newNode;
            TailInternational = newNode;
        }
        else {
            // Sambungkan sebelum TailInternational dengan node baru.
            TailInternational->next = newNode;
            // Buat sebelum dari newNode menjadi sebelum TailInternational.
            newNode->previous = TailInternational;
            // Buat newNode menjadi TailInternational yang baru.
            TailInternational = newNode;
        }
    }

}

// Procedure untuk delete di Head.
void deleteHead(int tipePesawat) {
    // Jika pesawat tipe Domestik
    if (tipePesawat == 1) {
        // Jika linked list masih kosong.
        if (HeadDomestic == NULL) {
            printf("Penumpang masih kosong!\n");
        }
        else {
            // Jika hanya ada satu node di linked list.
            if (HeadDomestic == TailDomestic) {
                HeadDomestic = TailDomestic = NULL;
            }
            else {
                // Deklarasi node yang akan kita delete.
                struct node* delete = HeadDomestic;
                /* Buat next dari HeadDomestic yang lama menjadi HeadDomestic yang baru, lalu kita free memory
                dari struct delete yang kita tunjuk ke HeadDomestic yang lama lalu kita delete. */
                HeadDomestic = HeadDomestic->next;
                // Buat previous dari HeadDomestic yang baru menjadi NULL atau address kosong.
                HeadDomestic->previous = NULL;
                // Free memory dari node yang kita delete.
                free(delete);
            }
        }
    }
    // Jika pesawat tipe International
    else if (tipePesawat == 2) {
        // Jika linked list masih kosong.
        if (HeadInternational == NULL) {
            printf("Penumpang masih kosong!\n");
        }
        else {
            // Jika hanya ada satu node di linked list.
            if (HeadInternational == TailInternational) {
                HeadInternational = TailInternational = NULL;
            }
            else {
                // Deklarasi node yang akan kita delete.
                struct node* delete = HeadInternational;
                /* Buat next dari HeadInternational yang lama menjadi HeadInternational yang baru, lalu kita free memory
                dari struct delete yang kita tunjuk ke HeadInternational yang lama lalu kita delete. */
                HeadInternational = HeadInternational->next;
                // Buat previous dari HeadInternational yang baru menjadi NULL atau address kosong.
                HeadInternational->previous = NULL;
                // Free memory dari node yang kita delete.
                free(delete);
            }
        }
    }
}

// Prosedur untuk delete mid atau user input nama dan akan dicarikan nantinya.
void cancelPenumpang(char nama[], int tipePesawat) {
    // Jika tipe pesawat 1 atau domestik
    if (tipePesawat == 1) {
        // Jika linked list masih kosong, maka kita beri tahu bahwa masih kosong.
        if (HeadDomestic == NULL) {
            printf("Penumpang masih kosong!\n");
            return;
        }
        else {
            // Membuat struct current untuk traverse nantinya mulai dari HeadDomestic
            struct node* current = HeadDomestic;
            // Di HeadDomestic ketemu.
            if (strcmp(HeadDomestic->nama, nama) == 0) {
                // Kalo cuman ada satu node dan ketemu di HeadDomestic.
                if (HeadDomestic == TailDomestic) {
                    /* Kita akan free memory dari current yang menunjuk HeadDomestic dan membuat
                       HeadDomestic dan TailDomestic kita menjadi NULL karena sudah kosong */
                    free(current);
                    HeadDomestic = TailDomestic = NULL;
                }
                // Ketemu di HeadDomestic tetapi tidak hanya satu node.
                else {
                    // Memanggil delete Head karena ditemukan di delete.
                    deleteHead(tipePesawat);
                }
            }
            else {
                /* Kita akan iterasi terus sampai ujung dan jika element yang ada di node selanjutnya sekarang
                   sama dengan input user yang akan dihapus.*/
                while (current->next != NULL && strcmp(current->next->nama, nama)) {
                    // Traverse Node.
                    current = current->next;
                }
                // Kalo yang diinput user tidak ada di linked list.
                // Jika sudah di ujung dan ternyata value dari elemen ini tidak sama dengan input user.
                if (current->next == NULL && strcmp(current->nama, nama)) {
                    // Memberi tahu user bahwa tidak ditemukan.
                    printf("%s tidak ditemukkan!\n", nama);
                    return;
                }
                // Jika nama yang ada di node selanjutnya sama dengan input user.
                if (!strcmp(current->next->nama, nama)) {
                    // Ketemu di TailDomestic karena nextnya adalah NULL alias ini adalah TailDomestic.
                    if (current->next->next == NULL) {
                        // Membuat struct delete yang menunjuk ke TailDomestic yang sekarang.
                        struct node* delete = TailDomestic;
                        // Membuat TailDomestic sekarang menjadi current yaitu node sebelum TailDomestic.
                        TailDomestic = current;
                        // Membuat next dari tail yang baru menjadi NULL karena depan Tail adalah kosong.
                        current->next = NULL;
                        // Free memory dari Tail sebelumnya yang ingin dihapus.
                        free(delete);
                    }
                    // Ketemu bukan di tail (di tengah antara node yang lain).
                    else {
                        // Membuat struct delete yang menunjuk ke elemen yang ingin dihapus (next dari current)
                        struct node* delete = current->next;
                        // Set current dari next menjadi next dari yang ingin didelete.
                        current->next = delete->next;
                        delete->next->previous = current;
                        // Free memory dari node yang ingin dihapus.
                        free(delete);
                    }
                }
            }
        }
    }
    // Jika pesawat International
    else if (tipePesawat == 2) {
        // Jika linked list masih kosong, maka kita beri tahu bahwa masih kosong.
        if (HeadInternational == NULL) {
            printf("Penumpang masih kosong!\n");
            return;
        }
        else {
            // Membuat struct current untuk traverse nantinya mulai dari HeadInternational
            struct node* current = HeadInternational;
            // Di HeadInternational ketemu.
            if (strcmp(HeadInternational->nama, nama) == 0) {
                // Kalo cuman ada satu node dan ketemu di HeadInternational.
                if (HeadInternational == TailInternational) {
                    /* Kita akan free memory dari current yang menunjuk HeadInternational dan membuat
                       HeadInternational dan TailInternational kita menjadi NULL karena sudah kosong */
                    free(current);
                    HeadInternational = TailInternational = NULL;
                }
                // Ketemu di HeadInternational tetapi tidak hanya satu node.
                else {
                    // Memanggil delete Head karena ditemukan di delete.
                    deleteHead(tipePesawat);
                }
            }
            else {
                /* Kita akan iterasi terus sampai ujung dan jika element yang ada di node selanjutnya sekarang
                   sama dengan input user yang akan dihapus.*/
                while (current->next != NULL && strcmp(current->next->nama, nama)) {
                    // Traverse Node.
                    current = current->next;
                }
                // Kalo yang diinput user tidak ada di linked list.
                // Jika sudah di ujung dan ternyata value dari elemen ini tidak sama dengan input user.
                if (current->next == NULL && strcmp(current->nama, nama)) {
                    // Memberi tahu user bahwa tidak ditemukan.
                    printf("%s tidak ditemukkan!\n", nama);
                    return;
                }
                // Jika nama yang ada di node selanjutnya sama dengan input user.
                if (!strcmp(current->next->nama, nama)) {
                    // Ketemu di TailInternational karena nextnya adalah NULL alias ini adalah TailInternational.
                    if (current->next->next == NULL) {
                        // Membuat struct delete yang menunjuk ke TailInternational yang sekarang.
                        struct node* delete = TailInternational;
                        // Membuat TailInternational sekarang menjadi current yaitu node sebelum TailInternational.
                        TailInternational = current;
                        // Membuat next dari tail yang baru menjadi NULL karena depan Tail adalah kosong.
                        current->next = NULL;
                        // Free memory dari Tail sebelumnya yang ingin dihapus.
                        free(delete);
                    }
                    // Ketemu bukan di tail (di tengah antara node yang lain).
                    else {
                        // Membuat struct delete yang menunjuk ke elemen yang ingin dihapus (next dari current)
                        struct node* delete = current->next;
                        // Set current dari next menjadi next dari yang ingin didelete.
                        current->next = delete->next;
                        delete->next->previous = current;
                        // Free memory dari node yang ingin dihapus.
                        free(delete);
                    }
                }
            }
        }
    }
    printf("Tiket %s berhasil dicancel!\n", nama);
}

// Prosedur untuk mencari penumpang.
void searchPenumpang(char* nama, int tipePesawat) {
    struct node* n = NULL;
    // Jika tipe pesawat domestic.
    if (tipePesawat == 1) {
        n = HeadDomestic;
        while (n != NULL) {
            // Jika ketemu, maka kita print info penumpang dan keluar dari prosedur.
            if (strcmp(n->nama, nama) == 0) {
                printf("Nama: %s\n", n->nama);
                printf("Kode Pesawat: %s\n", n->flightNumber);
                printf("Nomor Kursi: %s\n", n->seatNumber);
                return;
            }
            n = n->next;
        }
    }
    // Jika tipe pesawat international.
    else if (tipePesawat == 2) {
        n = HeadInternational;
        while (n != NULL) {
            // Jika ketemu, maka kita print info penumpang dan keluar dari prosedur.
            if (strcmp(n->nama, nama) == 0) {
                printf("Nama: %s\n", n->nama);
                printf("Kode Pesawat: %s\n", n->flightNumber);
                printf("Nomor Kursi: %s\n", n->seatNumber);
                return;
            }
            n = n->next;
        }
    }
    // Jika tidak ditemukkan
    printf("%s tidak ditemukkan\n", nama);
}

// Prosedur Print node di Linked List
void printList(struct node* n) {
    // Akan traverse terus sampai Tail.
    while (n != NULL) {
        // Print
        printf("[%s %s %s]->", n->nama, n->flightNumber, n->seatNumber);
        // Traverse
        n = n->next;
    }
    printf("KOSONG\n");
}

// Function untuk generate seat.
char* generateSeat() {
    // Untuk random dari time sekarang.
    srand(time(0));
    // Random seat row dari 1 - 6
    int seatRow = rand() % 6 + 1;
    // Random seat col dari 1 - 60
    int seatCol = rand() % 60 + 1;
    char* seat;
    // Masukkan ke string seat lalu kita return.
    sprintf(seat, "%c%.3d\0", seatRow + 64, seatCol);
    printf("Kode kursi %s\n", seat);
    return seat;
}

// Procedur untuk memanggil penumpang
void memanggilPenumpang(int tipePesawat) {
    // Jika pesawat Domestik
    if (tipePesawat == 1) {
        if (HeadDomestic == NULL) {
            printf("Pesawat masih kosong!\n");
            return;
        }
        else {
            char* kodePesawat = HeadDomestic->flightNumber;
            while (HeadDomestic != NULL) {
                deleteHead(tipePesawat);
            }
            // Kode pesawat domestik karena sudah berangkat, pesawat selanjutnya.
            domestic = domestic + 1;
            // Jadikan yang sudah berangkat ditambah jumlah penumpang sekarang.
            jumlahPenumpangDomesticBerangkat += jumlahPenumpangDomestic;
            printf("Pesawat Domestik dengan kode %s sudah berangkat dengan jumlah penumpang %d\n", kodePesawat, jumlahPenumpangDomestic);
            // Jadikan jumlah penumpang domestic sekarang jadikan 0.
            jumlahPenumpangDomestic = 0;
            return;
        }
    }
    // Jika pesawat International
    if (tipePesawat == 2) {
        if (HeadInternational == NULL) {
            printf("Pesawat masih kosong!\n");
            return;
        }
        else {
            char* kodePesawat = HeadInternational->flightNumber;
            while (HeadInternational != NULL) {
                deleteHead(tipePesawat);
            }
            // Kode pesawat international karena sudah berangkat, pesawat selanjutnya.
            international = international + 1;
            // Jadikan yang sudah berangkat ditambah jumlah penumpang sekarang.
            jumlahPenumpangInternationalBerangkat += jumlahPenumpangInternational;
            printf("Pesawat Domestik dengan kode %s sudah berangkat dengan jumlah penumpang %d\n", kodePesawat, jumlahPenumpangInternational);
            // Jadikan jumlah penumpang domestic sekarang jadikan 0.
            jumlahPenumpangInternational = 0;
            return;
        }
    }
}

// Procedur untuk rekap flight report
void report(int tipePesawat) {
    if (tipePesawat == 1) {
        printf("Tipe Pesawat Domestic\n");
        printf("Kode pesawat yang belum berangkat adalah A%.3d\n", domestic);
        printf("Jumlah penumpang yang sudah berangkat adalah %d orang\n", jumlahPenumpangDomesticBerangkat);
        printf("Jumlah penumpang yang belum berangkat adalah %d orang\n", jumlahPenumpangDomestic);
        printf("Jumlah penumpang domestic hari ini adalah %d\n", jumlahPenumpangDomestic + jumlahPenumpangDomesticBerangkat);
    }
    else if (tipePesawat == 2) {
        printf("Tipe Pesawat International\n");
        printf("Kode pesawat yang belum berangkat adalah B%.3d\n", international);
        printf("Jumlah penumpang yang sudah berangkat adalah %d orang\n", jumlahPenumpangInternationalBerangkat);
        printf("Jumlah penumpang yang belum berangkat adalah %d orang\n", jumlahPenumpangInternational);
        printf("Jumlah penumpang international hari ini adalah %d\n", jumlahPenumpangInternational + jumlahPenumpangInternationalBerangkat);
    }
}

int main() {
    // Deklarasi choice untuk menu, value dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    while (1) {
        system("cls");
        puts("2501976503 - Fabian Habil Ramdhan");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input Penumpang");
        puts("2. Memanggil Penumpang");
        puts("3. Melihat isi Pesawat sekarang");
        puts("4. Mencari info tiket penumpang");
        puts("5. Cancel Keberangkatan");
        puts("6. Report");
        puts("7. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 7, karena menu sampai 6 dan jika ingin keluar
           user input 7 */
        if (valid == 1 && (choice >= 1 && choice <= 7)) {
            system("cls");
            /* Jika user input 1, maka user akan input value dan nama dan nantinya dimasukkan ke head menggunakan
               prosedur insertHead */
            if (choice == 1) {
                char kodeKeberangkatan[10];
                int tipePesawat;
                char nama[50];
                char seatNumber[10];
                puts("Input Penumpang");
                printf("Silahkan masukkan nama lengkap: ");
                scanf(" %[^\n]", nama);
                getchar();
                printf("1 untuk Domestik, 2 untuk International\n");
                printf("Jika tidak memasukkan keduanya, akan ditempatkan ke domestik!\n");
                printf("Silahkan masukkan tipe pesawat: ");
                scanf("%d", &tipePesawat);
                getchar();
                if (tipePesawat == 2) {
                    sprintf(kodeKeberangkatan, "B%.3d\0", international);
                }
                else {
                    sprintf(kodeKeberangkatan, "A%.3d\0", domestic);
                }
                printf("Kode Pesawat %s (%s)\n", kodeKeberangkatan, tipePesawat == 2 ? "International" : "Domestik");
                strcpy(seatNumber, generateSeat());
                insertTail(nama, kodeKeberangkatan, seatNumber, tipePesawat);
                enterToContinue();
            }
            else if (choice == 2) {
                int tipePesawat;
                puts("Memanggil keberangkatan");
                printf("1 untuk Domestik, 2 untuk International\n");
                printf("Jika tidak memasukkan keduanya, akan ditempatkan ke domestik!\n");
                printf("Silahkan masukkan tipe pesawat: ");
                scanf("%d", &tipePesawat);
                getchar();
                if (tipePesawat == 2) {
                    memanggilPenumpang(tipePesawat);
                }
                else {
                    memanggilPenumpang(1);
                }
                enterToContinue();
            }
            else if (choice == 3) {
                printf("Pesawat Domestik\n");
                printList(HeadDomestic);
                printf("\nPesawat International\n");
                printList(HeadInternational);
                enterToContinue();
            }
            else if (choice == 4) {
                char nama[50];
                int tipePesawat;
                puts("Mencari info tiket penumpang");
                printf("1 untuk Domestik, 2 untuk International\n");
                printf("Jika tidak memasukkan keduanya, akan ditempatkan ke domestik!\n");
                printf("Silahkan masukkan tipe pesawat: ");
                scanf("%d", &tipePesawat);
                getchar();
                printf("Silahkan masukkan nama lengkap: ");
                scanf(" %[^\n]", nama);
                getchar();
                system("cls");
                if (tipePesawat == 2) {
                    searchPenumpang(nama, tipePesawat);
                }
                else {
                    searchPenumpang(nama, 1);
                }
                enterToContinue();
            }
            else if (choice == 5) {
                char nama[50];
                int tipePesawat;
                puts("Cancel Keberangkatan");
                printf("1 untuk Domestik, 2 untuk International\n");
                printf("Jika tidak memasukkan keduanya, akan ditempatkan ke domestik!\n");
                printf("Silahkan masukkan tipe pesawat: ");
                scanf("%d", &tipePesawat);
                getchar();
                printf("Silahkan masukkan nama lengkap: ");
                scanf(" %[^\n]", nama);
                getchar();
                if (tipePesawat == 2) {
                    cancelPenumpang(nama, tipePesawat);
                }
                else {
                    cancelPenumpang(nama, 1);
                }
                enterToContinue();
            }
            else if (choice == 6) {
                int tipePesawat;
                puts("Rekap Info Pesawat");
                printf("1 untuk Domestik, 2 untuk International\n");
                printf("Jika tidak memasukkan keduanya, akan ditempatkan ke domestik!\n");
                printf("Silahkan masukkan tipe pesawat: ");
                scanf("%d", &tipePesawat);
                getchar();
                system("cls");
                if (tipePesawat == 2) {
                    report(tipePesawat);
                }
                else {
                    report(1);
                }
                enterToContinue();
            }
            else if (choice == 7) {
                printf("2501976503 - Fabian Habil Ramdhan");
                break;
            }
        }
        // Memberi tahu bahwa input dari user salah.
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
    free(HeadDomestic);
    free(HeadInternational);
}
