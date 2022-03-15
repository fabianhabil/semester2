#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan Page 252 Number 1

// Feature Stack
// Push = Push value to stack.
// Pop = Remove top of the stack.
// Peek / Top = See the value in top.

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

// Function untuk melihat value dari top stack.
int top() {
    // Ketika stack kosong.
    if (Head == NULL) {
        return -1;
    }
    // Stack ada isinya.
    else {
        return Head->value;
    }
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
int pop() {
    // Ketika mengisi stack yang kosong, maka kita return -1 untuk memberi tahu bahwa stack kosong.
    if (Head == NULL) {
        return -1;
    }
    else {
        // Membuat node baru bernama delete yang menunjuk Head sekarang.
        struct stack* delete = Head;
        // Mengambil variabel value dari node yang didelete untuk diberitahu dari user.
        int deleted = Head->value;
        // Set Head yang baru menjadi elemen setelah Head yang lama.
        Head = Head->next;
        // Free memory node Head alias hapus node Head yang lama.
        free(delete);
        // Return variabel deleted agar user tahu value apa yang dihapus.
        return deleted;
    }
}

int main() {
    // Deklarasi choice untuk menu, age dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    int value;
    while (1) {
        system("cls");
        // Print node yang ada setiap di menu
        printf("Node sekarang : ");
        printStack(Head);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Push Stack");
        puts("2. Pop Stack");
        puts("3. Top Stack");
        puts("4. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();

        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 4 */
        if (valid && (choice > 0 && choice < 5)) {
            /* Jika user input 1, maka user akan input value yang akan dipush ke stack menggunakan prosedur push */
            if (choice == 1) {
                puts("Push Stack");
                printf("Value yang akan dipush ke stack: ");
                scanf("%d", &value);
                getchar();
                push(value);
            }
            else if (choice == 2) {
                /* Jika user input 2, maka akan pop dari stack atau hapus head */
                puts("Pop Stack");
                int valueDeleted = pop();
                // Jika stack kosong.
                if (valueDeleted == -1) {
                    printf("Stack kosong!\n");
                }
                else {
                    printf("[%d] berhasil dipop dari stack!\n", valueDeleted);
                }
                enterToContinue();
            }
            else if (choice == 3) {
                /* Jika user input 3, maka akan mengambil value head dari stack */
                puts("Value of Top Stack");
                int valueTop = top();
                // Jika stack kosong.
                if (valueTop == -1) {
                    printf("Stack kosong!\n");
                }
                else {
                    printf("Value dari Top stack sekarang adalah [%d]\n", valueTop);
                }
                enterToContinue();
            }
            else if (choice == 4) {
                /* Keluar dari program */
                system("cls");
                printf("Terima kasih!");
                break;
            }
        }
        /* Input Salah */
        else {
            puts("Input Salah!");
            enterToContinue();
        }
    }
}