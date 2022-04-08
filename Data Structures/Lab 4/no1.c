#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK 10

// 2501976503 - Fabian Habil Ramdhan 
struct Paket {
    char nama[100];
    char alamatPengirim[100];
    char alamatPenerima[100];
    int berat;
};

struct Paket Paket[MAX_STACK];
int top = -1;

void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

void push() {
    if (top == MAX_STACK - 1) {
        printf("Stack overflow\n");
        printf("Ingin clear antrian?\n");
        char check[10];
        printf("YES OR NO\n");
        scanf("%s", check);
        if (!strcmp(check, "YES")) {
            memset(Paket, 0, sizeof(Paket));
        }
        else {
            return;
        }
    }
    else {
        top++;
        printf("Nama? ");
        scanf(" %[^\n]", Paket[top].nama);
        printf("Alamat Pengirim? ");
        scanf(" %[^\n]", Paket[top].alamatPengirim);
        printf("Alamat Penerima? ");
        scanf(" %[^\n]", Paket[top].alamatPenerima);
        printf("Berat Paket? ");
        scanf("%d", &Paket[top].berat);
        getchar();
    }
}

int main() {
    int valid = 0;
    int choice;
    int value;
    while (1) {
        system("cls");
        puts("1. Masukkan Pelanggan");
        puts("2. Cek Kapasitas");
        puts("3. Mengecek Paket yang terakhir");
        puts("4. Mengecek apakah gudang sudah penuh");
        puts("5. Print semua Pelanggan");
        puts("6. Keluar");

        printf("Menu: ");
        valid = scanf("%d", &choice);
        getchar();
        if (valid && (choice > 0 && choice <= 6)) {
            system("cls");
            if (choice == 1) {
                push();
            }
            else if (choice == 2) {
                if (top == -1) {
                    printf("Masih kosong!\n");
                }
                else {
                    printf("Kapasitas yang tersedia sekarang: %d\n", 10 - top - 1);
                }
                enterToContinue();
            }
            else if (choice == 3) {
                if (top == -1) {
                    printf("Masih kosong!\n");
                }
                else {
                    printf("Nama : %s\n", Paket[top].nama);
                    printf("Alamat Pengirim : %s\n", Paket[top].alamatPengirim);
                    printf("Alamat Penerima: %s\n", Paket[top].alamatPenerima);
                    printf("Berat Paket : %d\n", Paket[top].berat);
                }
                enterToContinue();
            }
            else if (choice == 4) {
                if (top == MAX_STACK - 1) {
                    printf("Kapasitas penuh!\n");
                }
                else {
                    printf("Belum penuh!\n");
                }
                enterToContinue();
            }
            else if (choice == 5) {
                if (top == -1) {
                    printf("Masih kosong!\n");
                }
                else {
                    for (int i = 0; i <= top; i++) {
                        printf("Pelanggan ke %d\n", i + 1);
                        printf("Nama : %s\n", Paket[i].nama);
                        printf("Alamat Pengirim : %s\n", Paket[i].alamatPengirim);
                        printf("Alamat Penerima: %s\n", Paket[i].alamatPenerima);
                        printf("Berat Paket : %d\n\n", Paket[i].berat);
                    }
                }
                enterToContinue();
            }
            else if (choice == 6) {
                printf("2501976503 - Fabian Habil Ramdhan");
                break;
            }
        }
        else {
            puts("Input Salah!");
            enterToContinue();
        }
    }
}