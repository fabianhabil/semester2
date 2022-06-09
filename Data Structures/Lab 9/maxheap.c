#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minHeap(int* heap) {
    return heap[1];
}

void swap(int* heap, int current, int parent) {
    printf("%d %d\n", current, parent);
    int temp = heap[current];
    heap[current] = heap[parent];
    heap[parent] = temp;
}

int parent(int current) {
    return current / 2;
}

void view(int* heap, int size) {
    for (int i = 1; i <= size / 2; i++) {
        printf("parent: %d, left child: %d, right child: %d\n", heap[i], heap[i * 2], heap[i * 2 + 1]);
    }
}

int insert(int* heap, int size, int value) {
    size++;
    heap[size] = value;

    // penukaran
    int current = size;
    while (heap[current] > heap[parent(current)]) {
        swap(heap, current, parent(current));
        current = parent(current);
    }
    return size;
}

int main() {
    int heap[100];
    int size = 0;
    size = insert(heap, size, 20);
    size = insert(heap, size, 15);
    size = insert(heap, size, 13);
    size = insert(heap, size, 16);
    size = insert(heap, size, 19);
    view(heap, size);
}