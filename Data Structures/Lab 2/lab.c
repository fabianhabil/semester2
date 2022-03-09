#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan LAB 2 - Data Structures

// Deklarasi struct node yang berisikan age, name, dan next untuk menyambungkan dengan selanjutnya.
struct node {
    int age;
    char name[50];
    struct node* next;
};

// Deklarasikan Head dan Tail yang masih berisikan NULL karena node belum ada isinya.
struct node* Head = NULL;
struct node* Tail = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Prosedur untuk Print Node yang ada sekarang.
void printNode(struct node* n) {
    /* Jika Node masih kosong, atau NULL maka kita akan beri tahu bahwa
       Node kosong*/
    if (n == NULL) {
        printf("Node masih kosong!\n");
    }
    /* Kita akan iterasi terus sampai node tidak NULL alias sudah di akhir.
       Jika masih belum NULL, kita akan print value dari node tersebut, lalu
       Kita set pointer struct nya menjadi selanjutnya terus sampai terakhir. */
    while (n != NULL) {
        printf("[%d %s] -> ", n->age, n->name);
        n = n->next;
    }
    printf("NULL\n");
}

// Function bantuan untuk membuat Node Baru dengan parameter age dan nama.
struct node* createNewNode(int age, char* nama) {
    // Mengalokasikan memory untuk 1 struct yang nantinya akan disambungkan ke node yang ada.
    struct node* temporary = (struct node*)malloc(sizeof(struct node));
    // Set value dari age node ini menjadi input user.
    temporary->age = age;
    // Set value dari nama node ini menjadi input user.
    strcpy(temporary->name, nama);
    /* Kita set next dari node yang baru adalah NULL dahulu, nantinya selanjutnya ada atau tidak
       akan di handle setiap skenario yang ada (insert Head maka next nya Head, dan lain lain.) */
    temporary->next = NULL;
    // Return dari node yang sudah kita buat.
    return temporary;
}

// Procedure untuk insert di Head
void insertHead(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct node* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        /* Namun jika sudah ada node, kita akan buat newNode menjadi Head yang baru
           sedangkan next dari head yang baru adalah Head sebelumnya*/
        newNode->next = Head;
        Head = newNode;
    }
}

// Procedure untuk insert di Tail
void insertTail(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct node* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        /* Namun jika sudah ada next node, kita akan membuat next dari tail yang sekarang menjadi
           newNode ini, dan membuat newNode menjadi tail yang baru*/
        Tail->next = newNode;
        Tail = newNode;
    }
}

// Procedure untuk insert sesuai value yang ada di linked list
void insertMid(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct node* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        // Membuat struct current mulai dari Head
        struct node* current = Head;
        /* Kita akan iterasi terus sampai ujung dan jika element yang ada di node selanjutnya sekarang
           lebih besar dari element yang mau dimasukkan.*/
        while (current->next != NULL && current->next->age <= age) {
            // Traverse node
            current = current->next;
        }
        // Jika element yang ingin dimasukkan adalah lebih kecil dari head.
        if (Head->age >= age) {
            // Kita akan memasukkan ke Head yang diinput oleh user.
            insertHead(age, nama);
        }
        /* Jika memasukkan di ujung, maka selanjutnya adalah NULL. Maka kita akan membuat
           node yang baru menjadil Tail dan Tail yang dahulu disambungkan dengan newNode*/
        else if (current->next == NULL) {
            Tail = newNode;
            current->next = newNode;
        }
        /* Jika diantara atau tengah - tengah node lain kita akan memasukkan ke antaranya.
           dengan cara membuat node sebelumnya menyambungkan ke node yang baru dan menyambungkan
           node yang baru ke node selanjutnya sebelumnya */
        else {
            newNode->next = current->next;
            current->next = newNode;
        }
    }
}

// Prosedur untuk delete Head.
void deleteHead() {
    // Membuat struct delete mulai dari Head
    struct node* delete = Head;
    // Jika linked list masih kosong, maka kita beri tahu bahwa masih kosong.
    if (Head == NULL) {
        printf("Node masih kosong!\n");
    }
    else {
        /* Kita buat Head yang baru adalah next dari Head sekarang, lalu kita free
           memory dari struct delete yang menunjuk Head yang ingin dihapus */
        Head = Head->next;
        free(delete);
    }
}

// Prosedur untuk delete Tail.
void deleteTail() {
    // Membuat struct current untuk traverse nantinya mulai dari Head
    struct node* current = Head;
    // Jika linked list masih kosong, maka kita beri tahu bahwa masih kosong.
    if (Head == NULL) {
        printf("Node masih kosong!\n");
    }
    else {
        /* Jika node hanya ada satu, kita akan free linked list tersebut dan
           membuat Head dan Tail kembali menjadi NULL karena menjadi kosong */
        if (Head == Tail) {
            free(Head);
            Head = NULL;
            Tail = NULL;
        }
        else {
            // Ketika next dan next selanjutnya tidak null, karena kita akan berhenti di sebelum tail.
            while (current->next->next != NULL) {
                // Traverse node.
                current = current->next;
            }
            // Membuat struct delete untuk nantinya didelete dan menunjuk Tail sekarang.
            struct node* delete = Tail;
            // Membuat tail menjadi current karena yang dihapus adalah next dari current.
            Tail = current;
            // Membuat next dari Tail menjadi NULL karena sudah menjadi Tail. 
            Tail->next = NULL;
            // Free memory dari struct delete yang menunjuk tail sebelumnya yang ingin dihapus
            free(delete);
        }
    }
}

// Prosedur untuk delete mid atau user input nama dan akan dicarikan nantinya.
void deleteMid(char nama[]) {
    // Jika linked list masih kosong, maka kita beri tahu bahwa masih kosong.
    if (Head == NULL) {
        printf("Node masih kosong!");
        getchar();
        return;
    }
    else {
        // Membuat struct current untuk traverse nantinya mulai dari Head
        struct node* current = Head;
        // Di Head ketemu.
        if (strcmp(Head->name, nama) == 0) {
            // Kalo cuman ada satu node dan ketemu di Head.
            if (Head == Tail) {
                /* Kita akan free memory dari current yang menunjuk Head dan membuat
                   Head dan Tail kita menjadi NULL karena sudah kosong */
                free(current);
                Head = Tail = NULL;
            }
            // Ketemu di Head tetapi tidak hanyta satu node.
            else {
                // Membuat Head yang baru adalah Next dari head yang sekarang.
                Head = Head->next;
                // Free memory dari current yang menunjuk Head sebelumnya yang ingin dihapus.
                free(current);
            }
        }
        else {
            /* Kita akan iterasi terus sampai ujung dan jika element yang ada di node selanjutnya sekarang
               sama dengan input user yang akan dihapus.*/
            while (current->next != NULL && strcmp(current->next->name, nama)) {
                // Traverse Node.
                current = current->next;
            }
            // Kalo yang diinput user tidak ada di linked list.
            // If di sini jika sudah di ujung dan ternyata value dari elemen ini tidak sama dengan input user.
            if (current->next == NULL && strcmp(current->name, nama)) {
                // Memberi tahu user bahwa tidak tertemu.
                printf("404 Node Not Found\n");
                enterToContinue();
                return;
            }
            // Jika nama yang ada di node selanjutnya sama dengan input user.
            if (!strcmp(current->next->name, nama)) {
                // Ketemu di tail karena nextnya adalah NULL alias ini adalah TAIL.
                if (current->next->next == NULL) {
                    // Membuat struct delete yang menunjuk ke Tail yang sekarang.
                    struct node* delete = Tail;
                    // Membuat tail sekarang menjadi current yaitu node sebelum tail.
                    Tail = current;
                    // Membuat next dari tail yang baru menjadi NULL karena depan Tail adalah kosong.
                    current->next = NULL;
                    // Free memory dari Tail sebelumnya yang ingin dihapus.
                    free(delete);
                }
                // Ketemu bukan di tail (di tengah antara node yang lain).
                else {
                    // Membuat struct delete yang menunjuk ke elemen yang ingin dihapus (next dari current)
                    struct node* delete = current->next;
                    // Set current dari next menjadi next dari yang ingin didelete.
                    current->next = delete->next;
                    // Free memory dari node yang ingin dihapus.
                    free(delete);
                }
            }
        }
    }
}

int main() {
    // Deklarasi choice untuk menu, age dan nama untuk input nanti ke node
    int valid = 0;
    int choice;
    int age;
    char nama[50];
    while (1) {
        system("cls");
        // Print node yang ada setiap di menu
        printf("Node sekarang : ");
        printNode(Head);
        // Memperlihatkan kepada user ada menu apa saja di program.
        puts("1. Insert Head");
        puts("2. Insert Tail");
        puts("3. Insert Mid");
        puts("4. Delete Head");
        puts("5. Delete Tail");
        puts("6. Delete Mid / Nama yang ada di Linked List");
        puts("7. Exit");
        printf("Menu: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer),
           maka akan mereturn value 0. */
        valid = scanf("%d", &choice);
        // Getchar untuk clear buffer.
        getchar();
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 7 */

           /* Jika user input 1, maka user akan input age dan nama dan nantinya dimasukkan ke head menggunakan
              prosedur insertHead */
        if (valid == 1 && (choice >= 1 && choice <= 7)) {
            if (choice == 1) {
                printf("Insert Head\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Umur : ");
                scanf("%d", &age);
                getchar();
                printf("Nama : ");
                scanf("%s", &nama);
                getchar();
                insertHead(age, nama);
            }
            /* Jika user input 2, maka user akan input age dan nama dan nantinya dimasukkan ke tail menggunakan
               prosedur insertTail */
            else if (choice == 2) {
                printf("Insert Tail\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Umur : ");
                scanf("%d", &age);
                getchar();
                printf("Nama : ");
                scanf("%s", &nama);
                getchar();
                insertTail(age, nama);
            }
            /* Jika user input 3, maka user akan input age dan nama dan nantinya dimasukkan ke mid menggunakan
               prosedur insertMid */
            else if (choice == 3) {
                printf("Insert Mid\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Umur : ");
                scanf("%d", &age);
                getchar();
                printf("Nama : ");
                scanf("%s", &nama);
                getchar();
                insertMid(age, nama);
            }
            /* Jika user input 4, maka user akan memilih deleteHead lalu memanggil prosedur deleteHead */
            else if (choice == 4) {
                printf("[%d %s] dihapus!\n", Head->age, Head->name);
                deleteHead();
                enterToContinue();
            }
            /* Jika user input 5, maka user akan memilih deleteHead lalu memanggil prosedur deleteTail */
            else if (choice == 5) {
                printf("[%d %s] dihapus!\n", Tail->age, Tail->name);
                deleteTail();
                enterToContinue();
            }
            /* Jika user input 6, maka user akan memilih deleteMid lalu input nama dari node yang ingin dihapus
               lalu memanggil prosedur deleteMid */
            else if (choice == 6) {
                printf("Menghapus Node sesuai Nama!\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Nama : ");
                scanf("%s", &nama);
                getchar();
                printf("%s", nama);
                deleteMid(nama);
            }
            // Jika user input 7, maka keluar dari program.
            else if (choice == 7) {
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