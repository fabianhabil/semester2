#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int* heap, int curr, int parent) {
    int temp = heap[curr];
    if (parent == 0) return;
    heap[curr] = heap[parent];
    heap[parent] = temp;
}

int parent(int curr) {
    return curr / 2;
}

int insert(int* heap, int size, int value) {
    size++;
    heap[size] = value;

    //penukaran
    int curr = size;
    while (heap[size] > heap[parent(curr)]) {
        swap(heap, curr, parent(curr));
        curr = parent(curr);
    }

    return size;
}

void view(int* heap, int size) {
    for (int i = 1; i <= size / 2; i++) {
        printf("parent: %d, left child: %d, right child: %d\n", heap[i], heap[i * 2], heap[i * 2 + 1]);
    }
}

int getmax(int* heap) {
    return heap[1];
}

bool isleaf(int curr, int size) {
    if (curr >= (size / 2) && curr <= size) {
        return true;
    }
    else {
        return false;
    }
}

int rightchildpos(int curr) {
    return curr * 2 + 1;
}

int leftchildpos(int curr) {
    return curr * 2;
}


void maxheapify(int* heap, int size, int curr) {
    if (isleaf(curr, size) == true) return;

    int rightchildvalue = heap[rightchildpos(curr)];
    int leftchildvalue = heap[leftchildpos(curr)];

    if (heap[curr] < rightchildvalue || heap[curr] < leftchildvalue) {
        if (leftchildvalue > rightchildvalue) {
            swap(heap, curr, leftchildpos(curr));
            maxheapify(heap, size, leftchildpos(curr));
        }
        else {
            swap(heap, curr, rightchildpos(curr));
            maxheapify(heap, size, rightchildpos(curr));
        }
    }
}

int extractmax(int* heap, int* size) {
    int maxvalue = heap[1];
    heap[1] = heap[*size];
    *size--;

    maxheapify(heap, *size, 1);
    return maxvalue;
}

int main() {

    int heap[100];
    int size = 0;

    size = insert(heap, size, 20);
    printf("%d\n", heap[0]);
    size = insert(heap, size, 15);
    size = insert(heap, size, 13);
    size = insert(heap, size, 16);
    size = insert(heap, size, 19);
    view(heap, size);

    // printf("root: %d\n", getmax(heap));

    // int maxvalue = extractmax(heap, &size);

    // printf("root: %d\n", getmax(heap));


    return 0;
}