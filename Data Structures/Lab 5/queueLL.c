#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan

// Deklarasi struct node yang berisikan value, dan next untuk menyambungkan dengan selanjutnya.
struct node {
    int value;
    struct node* next;
};
// Deklarasikan Front dan Back yang masih berisikan NULL karena node belum ada isinya.
struct node* Front = NULL;
struct node* Back = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Prosedur untuk Print Queue yang ada sekarang.
void displayQueue(struct node* n) {
    /* Jika Node masih kosong, atau NULL maka kita akan beri tahu bahwa
       Node kosong*/
    if (n == NULL) {
        printf("Node masih kosong!\n");
    }
    /* Kita akan iterasi terus sampai node tidak NULL alias sudah di akhir.
       Jika masih belum NULL, kita akan print value dari node tersebut, lalu
       Kita set pointer struct nya menjadi selanjutnya terus sampai terakhir. */
    while (n != NULL) {
        printf("[%d] -> ", n->value);
        n = n->next;
    }
    printf("NULL\n");
}

// 2501976503 - Fabian Habil Ramdhan
// Function bantuan untuk membuat Node Baru dengan parameter value dan nama.
struct node* createNewNode(int value) {
    // Mengalokasikan memory untuk 1 struct yang nantinya akan disambungkan ke node yang ada.
    struct node* temporary = (struct node*)malloc(sizeof(struct node));
    // Set value dari value node ini menjadi input user.
    temporary->value = value;
    /* Kita set next dari node yang baru adalah NULL dahulu, nantinya selanjutnya ada atau tidak
       akan di handle setiap skenario yang ada (insert Front maka next nya Front, dan lain lain.) */
    temporary->next = NULL;
    // Return dari node yang sudah kita buat.
    return temporary;
}

// Procedure untuk insert di Back
void push(int value) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct node* newNode = createNewNode(value);
    /* Ketika Front masih NULL atau Node masih kosong, maka kita akan set Front dan Back nya
       adalah newNode yang baru dibuat karena node masih satu maka Front dan Back sama. */
    if (Front == NULL) {
        Front = newNode;
        Back = newNode;
    }
    else {
        /* Namun jika sudah ada next node, kita akan membuat next dari Back yang sekarang menjadi
           newNode ini, dan membuat newNode menjadi Back yang baru*/
        Back->next = newNode;
        Back = newNode;
    }
}

void pop() {
    if (Front == NULL) {
        Front = Back = NULL;
        free(Front);
    }
    else {
        // Jika hanya satu node saja di linked list.
        if (Front->next == NULL) {
            free(Front);
        }
        else {
            struct node* delete = Front;
            Front = Front->next;
            free(delete);
        }
    }
    enterToContinue();
}

int front() {
    if (Front == NULL) {
        printf("Queue masih kosong!\n");
        return 0;
    }
    else {
        return Front->value;
    }
}

int main() {
    // Deklarasi choice untuk menu, value dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    int value;
    char nama[50];
    while (1) {
        system("cls");
        // Print node yang ada setiap di menu
        printf("Node sekarang : ");
        displayQueue(Front);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Push Queue");
        puts("2. Pop Queue");
        puts("3. Peek Queue");
        puts("4. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 7 */
        if (valid == 1 && (choice >= 1 && choice <= 4)) {
            if (choice == 1) {
                int num;
                printf("Silahkan masukkan value: ");
                scanf("%d", &num);
                getchar();
                push(num);
            }
            else if (choice == 2) {
                pop();
            }
            else if (choice == 3) {
                int frontVal = front();
                if (frontVal != 0) {
                    printf("Antrian paling depan adalah %d\n", frontVal);
                }
                enterToContinue();
            }
            else if (choice == 4) {
                break;
            }
        }
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
    return 0;
}