#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int value;
    struct node* parent;
    struct node* left;
    struct node* right;
};

struct node* createNewNode(int value) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void inOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    else {
        inOrder(root->left);
        printf("%d - ", root->value);
        inOrder(root->right);
    }
}

void preOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    else {
        printf("%d - ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct node* root) {
    if (root == NULL) {
        return;
    }
    else {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d - ", root->value);
    }
}

struct node* insert(struct node* root, int value) {
    if (root == NULL) {
        return createNewNode(value);
    }
    else {
        if (value < root->value) {
            root->left = insert(root->left, value);
        }
        else if (value > root->value) {
            root->right = insert(root->right, value);
        }
    }
    return root;
}

int main() {
    struct node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 1);
    root = insert(root, 4);
    printf("Inorder = ");
    inOrder(root);
    printf("\n");

    printf("Preorder = ");
    preOrder(root);
    printf("\n");

    printf("Postorder = ");
    postOrder(root);
    printf("\n");
}