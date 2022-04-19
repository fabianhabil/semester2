#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan LAB Circular Single Linked List.

// Struct for node declaration.
struct node {
    int value;
    struct node* next;
};

// Declaration Head and Tail, its NULL because still empty.
struct node* Head = NULL;
struct node* Tail = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function pembantu untuk membuat stack yang nantinya akan disambungkan dengan yang lain.
struct node* createNewNode(int value) {
    // Memory Allocation.
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    // Set the value of the node from user input.
    newNode->value = value;
    // Next of the node pointing NULL, because there's a lot of scenario,
    // Like insert head and insert tail, the next of the node is different, so we'll decide later per functions.
    newNode->next = NULL;
    return newNode;
}

// Procedur untuk insertTail dari linked list.
void insertTail(int num) {
    // Make new node with nodeBaru variable name, and the value is from user input.
    struct node* nodeBaru = createNewNode(num);
    // If linked list still empty, this node will be the Head and the Tail.
    if (Head == NULL) {
        Head = nodeBaru;
        Tail = nodeBaru;
        // We connnect the next from the tail is the Head, because this is Circular Linked List (connected).
        Tail->next = Head;
    }
    else {
        // If there is another node in the linked list.
        // Connect the next from the newnode is the Head
        /* Why head? because the new node is gonna be the new Tail, and Tail always
           connected with the Head. */
        nodeBaru->next = Head;
        // And we connect the next from the old Tail with the newNode
        Tail->next = nodeBaru;
        // Make nodeBaru the new Tail.
        Tail = nodeBaru;
    }
}

// Prosedur untuk insertHead, untuk implementasi saya masih merubah node Head nya.
void insertHead(int num) {
    // Make new node with nodeBaru variable name, and the value is from user input.
    struct node* nodeBaru = createNewNode(num);
    // If linked list still empty, this node will be the Head and the Tail.
    if (Head == NULL) {
        Head = nodeBaru;
        Tail = nodeBaru;
        // We connnect the next from the tail is the Head, because this is Circular Linked List (connected).
        Tail->next = Head;
    }
    else {
        // If there is another node in the linked list.
        // We connect the next from the old Tail with the newNode
        Tail->next = nodeBaru;
        // Connect the next from the newnode is the Head
        /* Why head? because the new node is gonna be the new Tail, and Tail always
           connected with the Head. */
        nodeBaru->next = Head;
        // make nodeBaru the new Head.
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


void deleteHead() {
    // If linked list still empty
    if (Head == NULL) {
        printf("Node masih kosong!\n");
        enterToContinue();
    }
    else {
        // Declaration for the node that we will delete.
        struct node* delete = Head;
        // If there is only one node in linked list.
        if (Head == Tail) {
            Head = Tail = NULL;
        }
        else {
            // Make the next from the tail is the next from the old Head.
            Tail->next = Head->next;
            // Make the Head is next from the old Head.
            Head = Head->next;
            // Free the memory of the node that we delete.
            free(delete);
        }
    }
}

void deleteTail() {
    // If linked list still empty
    if (Head == NULL) {
        printf("Node masih kosong!\n");
        enterToContinue();
    }
    else {
        // If there is only one node in linked list.
        if (Head == Tail) {
            Head = Tail = NULL;
        }
        else {
            // Declaration for the node that we will traverse.
            struct node* current = Head;
            /* Because we need to get the node before the Tail and there's no previous,
               so we need to traverse to before the tail.   */
            while (current->next->next != Head) {
                // Traverse node.
                current = current->next;
            }
            // Declaration for the node that we will delete.
            struct node* delete = Tail;
            // Make the previous of the Tail become the new Tail.
            Tail = current;
            // Connect the next of the new Tail pointing to the Head.
            Tail->next = Head;
            // Free the memory of the node that we delete.
            free(delete);
        }
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
        puts("4. Delete Head");
        puts("5. Delete Tail");
        puts("6. Print Head");
        puts("7. Print Tail");
        puts("8. Print Tail->next");
        puts("9. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 4 */
        if (valid == 1 && (choice >= 1 && choice <= 9)) {
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
            else if (choice == 4) {
                deleteHead();
            }
            else if (choice == 5) {
                deleteTail();
            }
            else if (choice == 6) {
                if (Head != NULL) {
                    printf("%d\n", Head->value);
                }
                else {
                    printf("euweuh\n");
                }
                enterToContinue();
            }
            else if (choice == 7) {
                if (Head != NULL) {
                    printf("%d\n", Tail->value);
                }
                else {
                    printf("euweuh\n");
                }
                enterToContinue();
            }
            else if (choice == 8) {
                if (Head != NULL) {
                    printf("%d\n", Tail->next->value);
                }
                else {
                    printf("euweuh\n");
                }
                enterToContinue();
            }
            // Jika user input 7, maka keluar dari program.
            else if (choice == 9) {
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