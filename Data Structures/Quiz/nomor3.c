#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan
typedef struct {
    char nama[50];
    char pendidikan[50];
    double penghasilan;
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

// Fungsi untuk mendapatkan posisi children sebelah kiri dari node tersebut.
int leftChildren(int current) {
    return current * 2;
}

// Fungsi untuk mendapatkan posisi children sebelah kanan dari node tersebut.
int rightChildren(int current) {
    return current * 2 + 1;
}

// Cek apakah node tersebut leaf atau bukan.
// Jika iya return 1, jika tidak return 0
int isLeaf(int current, int size) {
    if (current > (size / 2) && current <= size) {
        return 1;
    }
    else {
        return 0;
    }
}

// Procedur untuk heapify binary heap kita.
void minHeapify(data Data[], int size, int current) {
    // Case untuk exit dari rekursif jika node yang dicek sekarang adalah leaf.
    if (isLeaf(current, size)) return;
    // Right dan Left children dari setiap node yang sekarang dicek.
    data rightchildvalue = Data[rightChildren(current)];
    data leftchildvalue = Data[leftChildren(current)];

    // Cek apakah key sekarang lebih besar antara kedua childrennya
    // jika iya, maka kita swap. Setelah kita swap, maka kita heapify kembali
    // node tersebut dan nantinya akan terus melakukan rekursif untuk heapify.
    if (Data[current].penghasilan > rightchildvalue.penghasilan || Data[current].penghasilan > leftchildvalue.penghasilan) {
        if (leftchildvalue.penghasilan < rightchildvalue.penghasilan) {
            // Swap dan heapify kepada node yang tadinya diswap.
            swap(Data, current, leftChildren(current));
            minHeapify(Data, size, leftChildren(current));
        }
        else {
            // Swap dan heapify kepada node yang tadinya diswap.
            swap(Data, current, rightChildren(current));
            minHeapify(Data, size, rightChildren(current));
        }
    }
}

// Fungsi untuk insert kepada Min Heap.
int insert(data Data[], int size, double value, char* nama, char* pendidikan) {
    size = size + 1;
    // Masukkan value nama, pendidikan dan penghasilan ke index paling ujung.
    Data[size].penghasilan = value;
    strcpy(Data[size].nama, nama);
    strcpy(Data[size].pendidikan, pendidikan);

    // Membuat variabel baru current untuk iterasi
    // ke atas apakah ada key yang lebih besar, jika ada
    // maka kita swap
    int current = size;
    while (Data[current].penghasilan < Data[parent(current)].penghasilan) {
        swap(Data, current, parent(current));
        current = parent(current);
    }
    return size;
}

// Find
int findIndex(data Data[], int size, double penghasilan) {
    for (int i = 1; i <= size; i++) {
        if (Data[i].penghasilan == penghasilan) {
            return i;
        }
    }
    return -1;
}

// Extract Min atau kita hapus element paling kecil di heap.
int extractMin(data Data[], int* size) {
    // Kita akan menghapus element sesuai paling atas dari heap
    // dengan cara kita tukar dengan element paling terakhir, lalu kita heapify
    // root tersebut.

    // Buat variabel key yang didelete untuk menyimpan dan nantinya direturn.
    int deleted = Data[1].penghasilan;

    // Isi root sekarang menjadi element pertama dari heap.
    // dan kurangi size nya dengan 1.
    Data[1] = Data[*size];
    *size = *size - 1;
    // Jika menjadi 0 maka tinggal satu tersisa, tidak perlu min heapify.
    if (*size == 0) {
        return deleted;
    }
    // Panggil fungsi rekursif min heapify dari index tersebut.
    minHeapify(Data, *size, 1);
    return deleted;
}

// Procedur untuk delete element sesuai index input user.
int deleteByIndex(data Data[], int* size, int index) {
    // Kita akan menghapus element sesuai dengan index input dari heap
    // dengan cara kita tukar dengan element paling terakhir, lalu kita heapify
    // root tersebut.

    // Buat variabel key yang didelete untuk menyimpan dan nantinya direturn.
    int deleted = Data[index].penghasilan;
    // Isi root sekarang menjadi element sesuai index dari heap.
    // dan kurangi size nya dengan 1.
    Data[index] = Data[*size];
    *size = *size - 1;
    // Jika menjadi 0 maka tinggal satu tersisa, tidak perlu min heapify.
    if (*size == 0) {
        return deleted;
    }
    // Panggil fungsi rekursif min heapify dari index tersebut.
    minHeapify(Data, *size, index);
    return deleted;
}

// Procedur untuk print heap tersebut.
void view(data Data[], int size) {
    // Jika size sama dengan 0, maka heap kosong.
    if (size == 0) {
        printf("Data masih kosong!\n");
        return;
    }

    // Jika hanya ada satu node di heap tersebut
    if (size == 1) {
        printf("Hanya ada satu node di heap!\n");
        // printf("Value: %d (root)\n", Data[size]);
        printf("Nama: %s\n", Data[1].nama);
        printf("Pendidikan: %s\n", Data[1].pendidikan);
        printf("Penghasilan: %lf\n", Data[1].penghasilan);
        return;
    }

    // Print sesuai level karena minheap, maka sudah dari paling kecil.
    for (int i = 1; i <= size; i++) {
        printf("Antrian ke %d\n", i);
        printf("Nama: %s\n", Data[i].nama);
        printf("Pendidikan: %s\n", Data[i].pendidikan);
        printf("Penghasilan: %lf\n\n", Data[i].penghasilan);
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
        puts("Dana Pendidikan Pemerintah");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Input Data");
        puts("2. View Data");
        puts("3. Delete by Penghasilan");
        puts("4. Extract Min");
        puts("5. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 2, karena menu sampai 2 dan jika ingin keluar
           user input 3 */
        if (valid == 1 && (choice >= 1 && choice <= 5)) {
            if (choice == 1) {
                char nama[50];
                char pendidikan[50];
                printf("Silahkan masukkan Nama: ");
                scanf(" %[^\n]", nama);
                getchar();
                printf("SD / SMP / SMA / KULIAH\n");
                printf("Silahan masukkan Jenjang Pendidikan: ");
                scanf(" %[^\n]", pendidikan);
                getchar();
                printf("Silahkan masukkan Penghasilan: ");
                scanf("%lf", &input);
                getchar();
                enterToContinue();
                size = insert(Data, size, input, nama, pendidikan);
            }
            else if (choice == 2) {
                // Print list antrian
                system("cls");
                view(Data, size);
                enterToContinue();
            }
            else if (choice == 3) {
                printf("Silahkan masukkan Penghasilan: ");
                scanf("%lf", &input);
                int index = findIndex(Data, size, input);
                if (index == -1) {
                    printf("Data tidak ditemukan!\n");
                }
                else {
                    int deleted = deleteByIndex(Data, &size, index);
                    printf("%d dihapus!\n", deleted);
                }
                enterToContinue();
            }
            else if (choice == 4) {
                int value = extractMin(Data, &size);
                printf("%d\n", value);
                enterToContinue();
            }
            else if (choice == 5) {
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