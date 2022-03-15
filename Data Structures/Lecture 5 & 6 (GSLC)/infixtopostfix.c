#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan Page 252 Number 2

// Deklarasi Global
// indexG untuk nanti akses array dari postfix yang baru dibuat.
int indexG = 0;
// errorStatus untuk nantinya jika sudah error, keluar dari function convert infix to postfix.
int errorStatus = 0;

// Deklarasi struct node yang berisikan value dan next untuk menyambungkan dengan selanjutnya.
struct stack {
    int value;
    struct stack* next;
};
// Deklarasikan Head atau stack yang masih berisikan NULL karena stack belum ada isinya.
struct stack* Head = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Prosedur untuk Print Node yang ada sekarang.
void printStack(struct stack* n) {
    while (n != NULL) {
        printf("[%d] -> ", n->value);
        n = n->next;
    }
    printf("NULL\n");
}

// Function bantuan untuk membuat Node baru untuk stack dengan parameter value.
struct stack* createNewStack(int value) {
    // Mengalokasikan memory untuk 1 struct yang nantinya akan disambungkan ke node yang ada.
    struct stack* temporary = (struct stack*)malloc(sizeof(struct stack));
    /* Kita set next dari node yang baru adalah NULL dahulu, nantinya selanjutnya ada atau tidak
       akan di handle setiap skenario yang ada. */
    temporary->next = NULL;
    // Set value node ini menjadi input user.
    temporary->value = value;
    // Return dari node yang sudah kita buat.
    return temporary;
}

// Push kepada stack yang ada
void push(int value) {
    // Membuat struct newNode membuat fungsi createNewStack yang sudah dibuat di atas.
    struct stack* newStack = createNewStack(value);
    // Ketika mengisi stack yang kosong, maka kita akan buat Head sekarang menjadi node yang baru.
    if (Head == NULL) {
        Head = newStack;
    }
    // Jika stack ada isinya, jadikan node yang baru menjadi head dan nextnya adalah head sebelumnya.
    else {
        newStack->next = Head;
        Head = newStack;
    }
}

// Pop ini berfungsi seperti delete Head
void pop() {
    // Ketika mengisi stack yang kosong, maka kita return -1 untuk memberi tahu bahwa stack kosong.
    if (Head == NULL) {
        return;
    }
    if (Head->next == NULL) {
        free(Head);
        Head = NULL;
        return;
    }
    // Membuat node baru bernama delete yang menunjuk Head sekarang.
    struct stack* delete = Head;
    // Set Head yang baru menjadi elemen setelah Head yang lama.
    Head = Head->next;
    // Free memory node Head alias hapus node Head yang lama.
    free(delete);
    // Return variabel deleted agar user tahu value apa yang dihapus.
}

// Fungsi untuk cek operand
int checkOperand(char operand) {
    if (operand == '/' || operand == '*' || operand == '%') return 1;
    if (operand == '+' || operand == '-') return 0;
    return -1;
}

// Fungsi untuk convert 
char* infixToPost(char* input) {
    char* postfix = (char*)malloc(100 * sizeof(char));
    for (int i = 0; input[i] != '\n' && input[i] != '\0'; i++) {
        // Jika spasi, continue iterasi selanjutnya.
        if (input[i] == ' ') continue;
        // Jika buka kurung.
        if (input[i] == '(') {
            // Masukkan ke stack dan lanjutkan iterasi selanjutnya.
            push(input[i]);
            continue;
        }
        // Jika tutup kurung.
        if (input[i] == ')') {
            // Loop terus sampai memenuhi sampai menemukan kurung pembuka di stack.
            while (1) {
                // Sudah tidak ada lagi atau tidak menemukan kurung pembuka dari stack.
                if (Head == NULL) {
                    // Set errorStatus menjadi 1.
                    errorStatus = 1;
                    return input;
                }
                // Jika ditemukan kurung pembuka, maka kita keluar dari loop
                if (Head->value == '(') break;
                // Set postfix yang baru kita menjadi value dari stack paling atas.
                postfix[indexG] = Head->value;
                // Index global++
                indexG++;
                // Pop alias delete Head dari stack.
                pop();
            }
            pop();
            continue;
        }
        // Jika operand.
        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')
            || (input[i] >= '0' && input[i] <= '9')) {
            postfix[indexG] = input[i];
            indexG++;
            continue;
        }
        // Jika operator dan yang ada distack lebih priority daripada yang ada di input index sekarang.
        while (Head != NULL && Head->value != '(' && checkOperand(input[i]) <= checkOperand(Head->value)) {
            postfix[indexG] = Head->value;
            indexG++;
            pop();
        }
        // Jika operator.
        push(input[i]);
    }
    // Operator sisanya.
    while (Head != NULL) {
        postfix[indexG] = Head->value;
        indexG++;
        pop();
    }
    return postfix;
}

int main() {
    // Define Variabel string input dengan max panjang 100 karakter.
    char input[100];
    int exit = 0;
    // Memberi tahu user untuk input infix.
    system("cls");
    printf("Input Infix yang ingin diganti menjadi postfix!\n");
    printf("Maksimal 100 Karakter!\n");
    printf("Infix: ");

    // Scan infix.
    scanf("%[^\n]", input);
    getchar();
    char postfix[100];

    // Memangil infixToPost function dengan parameter input dan copy ke variabel postfix.
    strcpy(postfix, infixToPost(input));
    // Jika error
    if (errorStatus) {
        printf("Error, Terlalu banyak Tutup Kurung!\n");
    }
    // Jika tidak error
    else {
        printf("Postfix -> %s\n", postfix);
    }
}