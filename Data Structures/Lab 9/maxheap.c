#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getMax(int* heap) {
    return heap[1];
}

void swap(int* heap, int current, int parent) {
    // Jika di root, jangan diswap dengan index 0, karena
    // root ada di index ke 1.
    if (parent == 0) return;
    int temp = heap[current];
    heap[current] = heap[parent];
    heap[parent] = temp;
}

int parent(int current) {
    return current / 2;
}

int leftPos(int current) {
    return current * 2;
}

int rightPos(int current) {
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
    // Jika hanya ada satu node di heap tersebut
    if (size == 1) {
        printf("Single node in heap!\n");
        printf("Value: %d\n", heap[size]);
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

int insert(int* heap, int size, int value) {
    size++;
    heap[size] = value;
    int current = size;
    // penukaran
    while (heap[current] > heap[parent(current)]) {
        swap(heap, current, parent(current));
        current = parent(current);
    }
    return size;
}

void maxheapify(int* heap, int size, int current) {
    if (isLeaf(current, size)) return;
    int rightchildvalue = heap[rightPos(current)];
    int leftchildvalue = heap[leftPos(current)];
    if (heap[current] < rightchildvalue || heap[current] < leftchildvalue) {
        if (leftchildvalue > rightchildvalue) {
            swap(heap, current, leftPos(current));
            maxheapify(heap, size, leftPos(current));
        }
        else {
            swap(heap, current, rightPos(current));
            maxheapify(heap, size, rightPos(current));
        }
    }
}

int extractmax(int* heap, int* size) {
    int maxvalue = heap[1];
    heap[1] = heap[*size];
    *size = *size - 1;
    maxheapify(heap, *size, 1);
    return maxvalue;
}

void deleteByIndex(int* heap, int* size, int index) {
    heap[index] = heap[*size];
    *size = *size - 1;
    maxheapify(heap, *size, index);
}

int main() {
    int heap[100];
    int size = 0;
    size = insert(heap, size, 20);
    // size = insert(heap, size, 15);
    // size = insert(heap, size, 13);
    // size = insert(heap, size, 16);
    // size = insert(heap, size, 19);
    // size = insert(heap, size, 12);
    view(heap, size);
    printf("root: %d\n", getMax(heap));
    extractmax(heap, &size);
    printf("root: %d\n", getMax(heap));
    view(heap, size);
    // deleteByIndex(heap, &size, 2);
    // printf("\n");
    // view(heap, size);
}