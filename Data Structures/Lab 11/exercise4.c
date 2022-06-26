#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - GSLC Sesi 11 Lab - Exercise 4

// Deklarasi struct untuk stack
struct node {
    char sentence[100];
    struct node* next;
};

// Deklarasi Top
struct node* top = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function bantuan untuk membuat Node Baru dengan parameter sentence.
struct node* createNewNode(char* sentence) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->sentence, sentence);
    newNode->next = NULL;
    return newNode;
}

// Procedur untuk push.
void push(char* sentence) {
    struct node* newNode = createNewNode(sentence);
    if (top == NULL) {
        top = newNode;
    }
    else {
        newNode->next = top;
        top = newNode;
    }
}

// Function untuk check palindrome
int checkPalindrome(char* sentence) {
    int length = strlen(sentence);
    for (int i = 0; i < length; i++) {
        if (sentence[i] != sentence[length - i - 1]) {
            return 0;
        }
    }
    return 1;
}

// Function untuk print stack
void printStack() {
    struct node* traverse = top;
    // Karena kita hanya ingin print history 5 saja.
    for (int i = 0; i < 5; i++) {
        if (traverse != NULL) {
            printf("%d. %s\n", i + 1, traverse->sentence);
            traverse = traverse->next;
        }
    }
}

int main() {
    // Deklarasi choice untuk menu, valid untuk menu, dan num untuk input user.
    int valid = 0;
    int choice;
    while (1) {
        system("cls");
        puts("2501976503 - Fabian Habil");
        puts("Check Palindrome");
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Check palindrome!");
        puts("2. Check previously input from user");
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
            system("cls");
            if (choice == 1) {
                char sentence[100];
                puts("No space and max 100 characters!");
                printf("Input a sentence: ");
                scanf("%s", sentence);
                getchar();
                push(sentence);
                if (checkPalindrome(sentence)) {
                    printf("%s is palindrome!\n", sentence);
                }
                else {
                    printf("%s is not palindrome!\n", sentence);
                }
                enterToContinue();
            }
            else if (choice == 2) {
                printStack();
                enterToContinue();
            }
        }
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
}