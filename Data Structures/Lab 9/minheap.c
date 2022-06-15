#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Lab 8 Min Heap Data Structures

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Fungsi untuk mendapatkan key paling kecil, yaitu ada di root.
int getMin(int* heap) {
    return heap[1];
}

// Procedur untuk swap dua element di array.
void swap(int* heap, int current, int parent) {
    // Jika di root, jangan diswap dengan index 0, karena
    // root ada di index ke 1.
    if (parent == 0) return;
    int temp = heap[current];
    heap[current] = heap[parent];
    heap[parent] = temp;
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

// Procedur untuk print heap tersebut.
void view(int* heap, int size) {
    // Jika size sama dengan 0, maka heap kosong.
    if (size == 0) {
        printf("Heap masih kosong!\n");
        return;
    }

    // Jika hanya ada satu node di heap tersebut
    if (size == 1) {
        printf("Hanya ada satu node di heap!\n");
        printf("Value: %d (root)\n", heap[size]);
        return;
    }

    for (int i = 1; i <= size / 2; i++) {
        printf("parent: %d, left child: %d, right child: ", heap[i], heap[i * 2]);

        // Jika size dari heap adalah genap, maka binary heap tersebut
        // leaf dari parentnya hanya memiliki satu children saja, sehingga children sebelah 
        // kanannya kosong.

        // Kita cek di iterasi saat parent terakhir.
        if (i == size / 2) {
            if (size % 2 == 0) {
                printf("kosong\n");
            }
            else {
                printf("%d\n", heap[i * 2 + 1]);
            }
        }
        // Jika bukan iterasi terakhir, maka print value dari node tersebut.
        else {
            printf("%d\n", heap[i * 2 + 1]);
        }
    }
}

// Fungsi untuk insert kepada Min Heap.
int insert(int* heap, int size, int value) {
    size = size + 1;
    // Masukkan value terbaru ke index paling ujung.
    heap[size] = value;
    // Membuat variabel baru current untuk iterasi
    // ke atas apakah ada key yang lebih besar, jika ada
    // maka kita swap
    int current = size;
    while (heap[current] < heap[parent(current)]) {
        swap(heap, current, parent(current));
        current = parent(current);
    }
    return size;
}

// Procedur untuk heapify binary heap kita.
void minHeapify(int* heap, int size, int current) {
    // Case untuk exit dari rekursif jika node yang dicek sekarang adalah leaf.
    if (isLeaf(current, size)) return;
    // Right dan Left children dari setiap node yang sekarang dicek.
    int rightchildvalue = heap[rightChildren(current)];
    int leftchildvalue = heap[leftChildren(current)];

    // Cek apakah key sekarang lebih besar antara kedua childrennya
    // jika iya, maka kita swap. Setelah kita swap, maka kita heapify kembali
    // node tersebut dan nantinya akan terus melakukan rekursif untuk heapify.
    if (heap[current] > rightchildvalue || heap[current] > leftchildvalue) {
        if (leftchildvalue < rightchildvalue) {
            // Swap dan heapify kepada node yang tadinya diswap.
            swap(heap, current, leftChildren(current));
            minHeapify(heap, size, leftChildren(current));
        }
        else {
            // Swap dan heapify kepada node yang tadinya diswap.
            swap(heap, current, rightChildren(current));
            minHeapify(heap, size, rightChildren(current));
        }
    }
}

// Procedur untuk menghapus element paling kecil atau extract min.
int extractMin(int* heap, int* size) {
    // Kita akan menghapus root atau element paling kecil dari heap
    // dengan cara kita tukar dengan element paling terakhir, lalu kita heapify
    // root tersebut.

    // Buat variabel min value untuk menyimpan dan nantinya direturn.
    int minvalue = heap[1];
    // Isi root sekarang menjadi element paling terakhir dari heap.
    // dan kurangi size nya dengan 1.
    heap[1] = heap[*size];
    *size = *size - 1;
    // Panggil fungsi rekursif min heapify dari root.
    minHeapify(heap, *size, 1);
    return minvalue;
}

// Procedur untuk delete element sesuai index input user.
int deleteByIndex(int* heap, int* size, int index) {
    // Kita akan menghapus element sesuai dengan index input dari heap
    // dengan cara kita tukar dengan element paling terakhir, lalu kita heapify
    // root tersebut.

    // Buat variabel key yang didelete untuk menyimpan dan nantinya direturn.
    int deleted = heap[index];

    // Isi root sekarang menjadi element sesuai index dari heap.
    // dan kurangi size nya dengan 1.
    heap[index] = heap[*size];
    *size = *size - 1;

    // Panggil fungsi rekursif min heapify dari index tersebut.
    minHeapify(heap, *size, index);
    return deleted;
}

// Procedur untuk print array dari heap kita.
void printArray(int* heap, int size) {
    for (int i = 1; i <= size; i++) {
        printf("%d(%d) ", heap[i], i);
    }
    printf("\n");
}

int main() {
    // Inisiasi heap dengan maksimal 100 key dan size dari heap tersebut.
    int heap[100];
    int size = 0;

    // Deklarasi choice untuk menu, valid untuk menu, dan num untuk input user.
    int valid = 0;
    int choice;
    int input;
    while (1) {
        system("cls");
        // Print heap yang ada setiap di menu
        printf("Ada %d element di heap\n", size);
        printf("Maksimal 100 element!\n\n");
        printf("Heap sekarang : \n");
        view(heap, size);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("\n1. Insert Heap");
        puts("2. Extract Min Heap");
        puts("3. Delete Heap");
        puts("4. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 4 */
        if (valid == 1 && (choice >= 1 && choice <= 4)) {
            if (choice == 1) {
                printf("Silahkan masukkan value: ");
                scanf("%d", &input);
                getchar();
                size = insert(heap, size, input);
            }
            else if (choice == 2) {
                // Jika size == 0 maka heap masih kosong.
                if (size == 0) {
                    printf("Heap masih kosong!\n");
                    enterToContinue();
                }
                else {
                    input = extractMin(heap, &size);
                    printf("%d dihapus!\n", input);
                    enterToContinue();
                }
            }
            else if (choice == 3) {
                // Jika size == 0 maka heap masih kosong.
                if (size == 0) {
                    printf("Heap masih kosong!\n");
                    enterToContinue();
                }
                else {
                    system("cls");
                    printf("Index dimulai dari 1\n");
                    printArray(heap, size);
                    printf("Silahkan masukkan index: ");
                    scanf("%d", &input);
                    getchar();
                    // Jika input user di bawah 1 dan di atas size.
                    if (input < 1 || input > size) {
                        printf("Invalid index! harus diantara 1 dan %d\n", size);
                    }
                    else {
                        int deleted = deleteByIndex(heap, &size, input);
                        printf("%d dihapus!\n", deleted);
                    }
                    enterToContinue();
                }
            }
            else if (choice == 4) {
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