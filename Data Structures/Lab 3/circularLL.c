#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan LAB Circular Single Linked List.

// Deklarasi Struct node.
struct node {
    int value;
    struct node* next;
};

// Deklarasi Head dan Tail NULL karena masih kosong.
struct node* Head = NULL;
struct node* Tail = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function pembantu untuk membuat stack yang nantinya akan disambungkan dengan yang lain.
struct node* createNewNode(int value) {
    // Alokasi memory.
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    // Set value dari node yang baru menjadi input dari user.
    newNode->value = value;
    // next dari node baru masih kosong, karena nanti akan menyambungkan sesuai dengan kondisi yang ada.
    // Misalnya insert Head, insert Tail itu next nya beda - beda.
    newNode->next = NULL;
    return newNode;
}

// Procedur untuk insertTail dari linked list.
void insertTail(int num) {
    // Membuat node baru dengan variabel nodeBaru dengan isi valuenya adalah input user.
    struct node* nodeBaru = createNewNode(num);
    // Jika node masih kosong, node tersebut menjadi head dan tail
    if (Head == NULL) {
        Head = nodeBaru;
        Tail = nodeBaru;
        // Lalu sambungkan next dari tail menjadi Head karena ini circular linked list (connected).
        Tail->next = Head;
    }
    else {
        // Jika sudah ada elemen yang lain.
        // Jadikan next dari node baru menjadi Head
        /* Mengapa menjadi head? karena node baru menjadi tail yang baru dan tail
           selalu bersambungan dengan head */
        nodeBaru->next = Head;
        /* Lalu jadikan next dari tail yang lama menjadi nodeBaru yang ingin dimasukkan
           ke tail. */
        Tail->next = nodeBaru;
        // Jadikan nodeBaru menjadi tail yang baru.
        Tail = nodeBaru;
    }
}

// Prosedur untuk insertHead, untuk implementasi saya masih merubah node Head nya.
void insertHead(int num) {
    // Membuat node baru dengan variabel nodeBaru dengan isi valuenya adalah input user.
    struct node* nodeBaru = createNewNode(num);
    // Jika node masih kosong, node tersebut menjadi head dan tail
    if (Head == NULL) {
        Head = nodeBaru;
        Tail = nodeBaru;
        // Lalu sambungkan next dari tail menjadi Head karena ini circular linked list (connected).
        Tail->next = Head;
    }
    else {
        // Karena insert head dan circular linkedlist, Tail yang sekarang sambungkan ke node baru.
        Tail->next = nodeBaru;
        // Lalu sambungkan node baru dengan head sebelumnya
        nodeBaru->next = Head;
        // Jadikan node baru menjadi Head yang baru.
        Head = nodeBaru;
    }
}

// Prosedur untuk delete element dari node.
void deleteNode(int num) {
    // Ketika node masih kosong.
    if (Head == NULL) {
        printf("Node masih kosong!\n");
        enterToContinue();
    }
    else {
        struct node* current = Head;
        // Ketika ketemu di Head.
        if (Head->value == num) {
            // Ketika hanya ada satu elemen di linked list.
            if (Head == Tail) {
                Head = Tail = NULL;
                // Free memory node.
                free(current);
            }
            // Ketika tidak hanya satu elemen di linked list.
            else {
                // Sambungkan Tail dengan elemen selanjutnya dari Head.
                Tail->next = Head->next;
                // Jadikan Head yang baru menjadi next dari Head sebelumnya
                Head = current->next;
                // Free memory Head yang dihapus
                free(current);
            }
        }
        else {
            // Ketika tidak ketemu di Head, kita akan traverse terus sampai ketemu.
            while (current->next != Head && current->next->value != num) {
                current = current->next;
            }
            // Yang diinput user tidak ada di linked list.
            if (current->next == Head && current->value != num) {
                printf("Node tidak ditemukkan!\n");
                enterToContinue();
                return;
            }
            // Yang diinput user ditemukkan.
            if (current->next->value == num) {
                // Yang diinput user ada di ujung.
                if (current->next->next == Head) {
                    // Buat node baru delete yang menunjuk node yang akan dihapus
                    struct node* delete = Tail;
                    // Jadikan current menjadi tail yang baru.
                    Tail = current;
                    // Tunjuk next dari tail yang baru adalah head sekarang.
                    Tail->next = Head;
                    // Free memory node yang akan dihapus.
                    free(delete);
                }
                else {
                    // Buat node baru delete yang menunjuk node yang akan dihapus.
                    struct node* delete = current->next;
                    // Set next dari node sebelum yang dihapus menjadi setelah yang dihapus.
                    current->next = delete->next;
                    // Free memory node yang akan dihapus.
                    free(delete);
                }
            }
        }
    }
}

// Prosedur Print all Node in Linked List
void printAll(struct node* n) {
    // Ketika linked list masih kosong.
    if (n == NULL) {
        printf("Node masih kosong!\n");
    }
    else {
        /* Kita akan traverse menggunakan node n yang sebagai parameter. Lalu kita akan
           terus print sampai next dari node sekarang yang traverse itu tidak sama dengan Head.
           Kenapa tidak sama dengan head? karena circular ini tidak akan ada ujungnya, kita akan
           print semuanya, berarti kita akant traverse terus sampai Tail di mana next dari tail
           adalah Head */
        while (n->next != Head) {
            // Print dari value node sekarang.
            printf("[%d]->", n->value);
            // Traverse
            n = n->next;
        }
        /* Lalu kita print node terakhir yaitu tail, kenapa tidak terbawa dari loop? karena ketika
           kita sudah berada di tail, while di atas sudah tidak terpenuhi dan akan diskip. */
        printf("[%d]->Head\n", n->value);
    }
}

int main() {
    // Deklarasi choice untuk menu, value dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    int value;
    while (1) {
        system("cls");
        // Print node yang ada setiap di menu
        printf("Node sekarang : ");
        printAll(Head);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Insert Head");
        puts("2. Insert Tail");
        puts("3. Delete Mid / Value yang ada di Linked List");
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
        if (valid == 1 && (choice >= 1 && choice <= 4)) {
            /* Jika user input 1, maka user akan input value dan nama dan nantinya dimasukkan ke head menggunakan
               prosedur insertHead */
            if (choice == 1) {
                printf("Insert Head\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Value : ");
                scanf("%d", &value);
                getchar();
                insertHead(value);
            }
            /* Jika user input 2, maka user akan input value dan nama dan nantinya dimasukkan ke tail menggunakan
               prosedur insertTail */
            else if (choice == 2) {
                printf("Insert Tail\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Value : ");
                scanf("%d", &value);
                getchar();
                insertTail(value);
            }
            /* Jika user input 3, maka user akan memilih deleteNode lalu input value dari node yang ingin dihapus
               lalu memanggil prosedur deleteNode */
            else if (choice == 3) {
                printf("Menghapus Node sesuai value!\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Value : ");
                scanf("%d", &value);
                getchar();
                deleteNode(value);
            }
            // Jika user input 7, maka keluar dari program.
            else if (choice == 4) {
                system("cls");
                printf("Terima kasih!");
                break;
            }

        }
        // Memberi tahu bahwa input dari user salah.
        else {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
    }
    free(Head);
}