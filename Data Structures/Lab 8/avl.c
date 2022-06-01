#include <stdio.h>
#include <stdlib.h>

// 2501976503 - Fabian Habil Ramdhan - LC75

// Declaration struct dari node.
struct node {
    int value;
    struct node* left;
    struct node* right;
    int height;
};

// Function untuk membuat node baru.
struct node* createNewNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 0;
    return newNode;
}

// Function untuk mencari max.
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function untuk mencari height dari sebuah node.
int height(struct node* curr) {
    if (curr == NULL) return 0;
    else return curr->height;
}

// Function untuk mencari balance factor dari sebuah node.
int getBalance(struct node* curr) {
    if (curr == NULL) return 0;
    else return height(curr->left) - height(curr->right);
}

// Function untuk rotate right
struct node* rotateRight(struct node* curr) {
    struct node* targetRotate = curr->left;
    // Mau ada children atau tidak, kita ambil saja,
    // Karena kalau misalnya null juga tidak masalah kita menunjuk ke null address
    // Atau tidak ada tujuan.
    struct node* targetRotateChildrenRight = targetRotate->right;

    // Node sebelah kiri dari node yang dirotate menjadi parent dari node yang dirotate.
    // dan node tersebut menjadi children sebelah kanan dari parent yang baru.
    targetRotate->right = curr;

    // Children sebelah kanan dari node yang sekarang menjadi parent,
    // maupun ada atau tidak, kita assign menjadi children sebelah
    // kiri dari node yang sudah dirotate.
    curr->left = targetRotateChildrenRight;

    // Update heights dari node tersebut.
    curr->height = 1 + max(height(curr->left), height(curr->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));

    // Return node yang baru
    return targetRotate;
}

// Function untuk rotate left
struct node* rotateLeft(struct node* curr) {
    struct node* targetRotate = curr->right;
    // Mau ada children atau tidak, kita ambil saja,
    // Karena kalau misalnya null juga tidak masalah kita menunjuk ke null address
    // Atau tidak ada tujuan.
    struct node* targetRotateChildrenLeft = targetRotate->left;

    // Node sebelah kanan dari node yang dirotate menjadi parent dari node yang dirotate.
    // dan node tersebut menjadi children sebelah kiri dari parent yang baru.
    targetRotate->left = curr;

    // Children sebelah kiri dari node yang sekarang menjadi parent,
    // maupun ada atau tidak, kita assign menjadi children sebelah
    // kanan dari node yang sudah dirotate.
    curr->right = targetRotateChildrenLeft;

    // Update heights dari node tersebut.
    curr->height = 1 + max(height(curr->left), height(curr->right));
    targetRotate->height = 1 + max(height(targetRotate->left), height(targetRotate->right));

    // Return node yang baru.
    return targetRotate;
}


// Function untuk insert terhadap AVL Tree yang ada.
struct node* insert(struct node* curr, int value) {
    // Jika yang ditunjuk kosong maka buat node baru.
    if (curr == NULL) {
        return createNewNode(value);
    }

    // Jika yang akan diinsert lebih besar dari node yang divisit sekarang.
    else if (value > curr->value) {
        curr->right = insert(curr->right, value);
    }

    // Jika yang akan diinsert lebih kecil dari node yang divisit sekarang.
    else if (value < curr->value) {
        curr->left = insert(curr->left, value);
    }

    // Jika tidak lebih besar dan tidak lebih kecil, maka sama dan tidak boleh di AVL Tree.
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

        // kasus 1 : rotasi ke kanan 1x (Left Left Case)
        if (value < curr->left->value) {
            return rotateRight(curr);
        }
        // kasus 2 : rotasi ke kiri, baru ke kanan (2x rotasi) (Left Right Case)
        else if (value > curr->left->value) {
            curr->left = rotateLeft(curr->left);
            return rotateRight(curr);
        }
    }

    // berat ke kanan
    else if (balance < -1) {
        // rotasi ke kiri (balancing ke kiri)

        // kasus 1 : rotasi ke kiri 1x (Right Right Case)
        if (value > curr->right->value) {
            return rotateLeft(curr);
        }

        // kasus 2 : rotasi ke kanan, baru ke kiri (Right Left Case)
        else if (value < curr->right->value) {
            curr->right = rotateRight(curr->right);
            return rotateLeft(curr);
        }
    }
    return curr;
}

// Left - Print Node - Right
void printInOrder(struct node* curr) {
    if (curr == NULL) {
        return;
    }
    else {
        printInOrder(curr->left);
        printf("%d ", curr->value);
        printInOrder(curr->right);
    }
}

int main() {
    struct node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 60);
    root = insert(root, 55);
    printf("Inorder: ");
    printInOrder(root);
}