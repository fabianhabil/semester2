#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - GSLC Sesi 11 Lab - Exercise 5

typedef struct {
    char nama[50];
    char resourceLocation[50];
    double price;
}data;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Procedur untuk swap dua struct.
void swap(data Data[], int current, int parent) {
    // Jika di root, jangan diswap dengan index 0, karena
    // root ada di index ke 1.
    if (parent == 0) return;
    data temp = Data[current];
    Data[current] = Data[parent];
    Data[parent] = temp;
}

// Fungsi untuk mendapatkan posisi parent dari node tersebut.
int parent(int current) {
    return current / 2;
}

// Fungsi untuk insert kepada Min Heap.
int insert(data Data[], int size, double value, char* nama, char* resourceLocation) {
    size = size + 1;
    // Masukkan value nama produk, alamat produk dan harga produk ke index paling ujung.
    Data[size].price = value;
    strcpy(Data[size].nama, nama);
    strcpy(Data[size].resourceLocation, resourceLocation);

    // Membuat variabel baru current untuk iterasi
    // ke atas apakah ada key yang lebih besar, jika ada
    // maka kita swap
    int current = size;
    while (Data[current].price < Data[parent(current)].price) {
        swap(Data, current, parent(current));
        current = parent(current);
    }
    return size;
}

// Procedur untuk print heap tersebut.
void view(data Data[], int size) {
    // Jika size sama dengan 0, maka heap kosong.
    if (size == 0) {
        printf("Data still empty!\n");
        return;
    }

    // Jika hanya ada satu node di heap tersebut
    if (size == 1) {
        printf("Only one product in data!\n");
        // printf("Value: %d (root)\n", Data[size]);
        printf("Product Name: %s\n", Data[1].nama);
        printf("Resource Product: %s\n", Data[1].resourceLocation);
        printf("Product Price: Rp%.2lf\n\n", Data[1].price);
        return;
    }

    // Print sesuai level karena minheap, maka sudah dari paling kecil.
    for (int i = 1; i <= size; i++) {
        printf("Product Name: %s\n", Data[i].nama);
        printf("Resource Product: %s\n", Data[i].resourceLocation);
        printf("Product Price: Rp%.2lf\n\n", Data[i].price);
    }
}

int main() {
    // Inisiasi heap dengan maksimal 100 key dan size dari heap tersebut.
    data Data[100];
    int size = 0;
    // Deklarasi choice untuk menu, valid untuk menu, dan num untuk input user.
    int valid = 0;
    int choice;
    double input;
    while (1) {
        system("cls");
        puts("2501976503 - Fabian Habil");
        puts("Yokopedia");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input Data");
        puts("2. View Data");
        puts("3. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 2, karena menu sampai 2 dan jika ingin keluar
           user input 3 */
        if (valid == 1 && (choice >= 1 && choice <= 3)) {
            if (choice == 1) {
                char nama[50];
                char resourceLocation[50];
                printf("Input Product Name: ");
                scanf(" %[^\n]", nama);
                getchar();
                printf("Input Resource Product: ");
                scanf(" %[^\n]", resourceLocation);
                getchar();
                printf("Input Product Price: Rp");
                scanf("%lf", &input);
                getchar();
                enterToContinue();
                size = insert(Data, size, input, nama, resourceLocation);
            }
            else if (choice == 2) {
                // Print list produk
                system("cls");
                view(Data, size);
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