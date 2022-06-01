#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* left;
    struct node* right;
    int height;
};

struct node* root = NULL;

struct node* createNewNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 0;
    return newNode;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct node* curr) {
    if (curr == NULL) return -1;
    else return curr->height;
}

int getBalance(struct node* curr) {
    if (curr == NULL) return 0;
    else return height(curr->left) - height(curr->right);
}

struct node* insert(struct node* curr, int value) {
    if (curr == NULL) {
        return createNewNode(value);
    }
    else if (value > curr->value) {
        curr->right = insert(curr->right, value);
    }
    else if (value < curr->value) {
        curr->left = insert(curr->right, value);
    }
    else {
        return curr;
    }

    // update height
    curr->height = 1 + max(height(curr->left), height(curr->right));

    // balance
    int balance = getBalance(curr);

    // berat ke kiri
    if (balance > 1) {
        // rotasi ke kanan (balancing ke kanan)

        // kasus 1 : rotasi ke kanan 1x
        if (value < curr->left->value) {

        }
        // kasus 2 : rotasi ke kiri, baru ke kanan
        else if (value > curr->left->value) {

        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x

        // kasus 2 : rotasi ke kanan, baru ke kiri
    }

    else {

    }
}

int main() {

}