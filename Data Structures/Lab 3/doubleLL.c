#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan Lab Double Linked List.

// Deklarasi struct dnode.
struct dnode {
    int age;
    char nama[50];
    struct dnode* next;
    struct dnode* previous;
};

// Deklarasi Head dan Tail NULL karena masih kosong.
struct dnode* Head = NULL;
struct dnode* Tail = NULL;

// Prosedur tambahan agar user menekan enter untuk melanjutkan.
void enterToContinue() {
    printf("Enter untuk melanjutkan!");
    getchar();
}

// Function pembantu untuk membuat stack yang nantinya akan disambungkan dengan yang lain.
struct dnode* createNewNode(int age, char* nama) {
    // Mengalokasikan memory untuk 1 struct yang nantinya akan disambungkan ke node yang ada.
    struct dnode* temporary = (struct dnode*)malloc(sizeof(struct dnode));
    // Set age dari age node ini menjadi input user.
    temporary->age = age;
    // Set age dari nama node ini menjadi input user.
    strcpy(temporary->nama, nama);
    /* Kita set next dari node yang baru adalah NULL dahulu, nantinya selanjutnya ada atau tidak
       akan di handle setiap skenario yang ada (insert Head maka next nya Head, dan lain lain.) */
    temporary->next = NULL;
    temporary->previous = NULL;
    // Return dari node yang sudah kita buat.
    return temporary;
}

// Procedure untuk insert di Head.
void insertHead(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct dnode* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    // Jika Ada elemen lain.
    else {
        // Kita buat sambungkan newNode ini dengan Head sebelumnya. 
        newNode->next = Head;
        // Karena Head, previousnya jadikan NULL
        newNode->previous = NULL;
        // Jadikan newNode menjadi Head yang baru.
        Head = newNode;
    }
}

// Procedure untuk insert di Tail.
void insertTail(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct dnode* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        // Sambungkan tail sebelumnya dengan node yang baru.
        Tail->next = newNode;
        // Jadikan previous dari node yang baru sekarang dengan tail sebelumnya.
        newNode->previous = Tail;
        // Jadikan node yang baru menjadi tail yang baru.
        Tail = newNode;
    }
}

// Procedure untuk insert sesuai value yang ada di linked list
void insertMid(int age, char* nama) {
    // Membuat struct newNode membuat fungsi createNewNode yang sudah dibuat di atas.
    struct dnode* newNode = createNewNode(age, nama);
    /* Ketika Head masih NULL atau Node masih kosong, maka kita akan set Head dan Tail nya
       adalah newNode yang baru dibuat karena node masih satu maka Head dan Tail sama. */
    if (Head == NULL) {
        Head = newNode;
        Tail = newNode;
    }
    else {
        // Membuat struct current mulai dari Head
        struct dnode* current = Head;
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
            insertTail(age, nama);
        }
        /* Jika diantara atau tengah - tengah node lain kita akan memasukkan ke antaranya.
           dengan cara membuat node sebelumnya menyambungkan ke node yang baru dan menyambungkan
           node yang baru ke node selanjutnya sebelumnya */
        else {
            // Sambungkan next dari node yang baru dengan current next karena ditengah2
            newNode->next = current->next;
            // Sambungkan next dari newNode yang baru previousnya dengan newNode karena ada di kanan sebelah newNode
            current->next->previous = newNode;
            // Sambungkan node yang sekarang dengan newNode karena ada di kiri sebelah newNode
            current->next = newNode;
        }
    }
}

// Procedure untuk delete di Head.
void deleteHead() {
    // Jika node masih kosong.
    struct dnode* delete = Head;
    if (Head == NULL) {
        printf("Node masih kosong!\n");
        enterToContinue();
    }
    else {
        /* Kita buat Head yang baru adalah next dari Head sekarang, lalu kita free
           memory dari struct delete yang menunjuk Head yang ingin dihapus */
        Head = Head->next;
        /* Jadikan elemen yang sebelumnya next dari head,
           previousnya kosong karena menjadi Head. */
        free(delete);
    }
}

// Procedure untuk delete Tail.
void deleteTail() {
    // Jika node masih kosong.
    if (Head == NULL) {
        printf("Node masih kosong!\n");
        enterToContinue();
    }
    else {
        // Jika hanya ada satu element di linked list.
        if (Head == Tail) {
            free(Head);
            Head = NULL;
            Tail = NULL;
        }
        // Jika tidak hanya satu elemen.
        else {
            // Karena bisa previous, tidak harus traverse.
            // Tunjuk delete menjadi Tail yang akan dihapus.
            struct dnode* delete = Tail;
            // Jadikan sebelum tail menjadi tail yang baru.
            Tail = Tail->previous;
            // Jadikan next dari tail menjadi NULL, karena kosong.
            Tail->next = NULL;
            // Free memory dari tail sebelumnya yang akan dihapus.
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
        struct dnode* current = Head;
        // Di Head ketemu.
        if (strcmp(Head->nama, nama) == 0) {
            // Kalo cuman ada satu node dan ketemu di Head.
            if (Head == Tail) {
                /* Kita akan free memory dari current yang menunjuk Head dan membuat
                   Head dan Tail kita menjadi NULL karena sudah kosong */
                free(current);
                Head = Tail = NULL;
            }
            // Ketemu di Head tetapi tidak hanya satu node.
            else {
                // Memanggil delete Head karena ditemukan di delete.
                deleteHead();
            }
        }
        else {
            /* Kita akan iterasi terus sampai ujung dan jika element yang ada di node selanjutnya sekarang
               sama dengan input user yang akan dihapus.*/
            while (current->next != NULL && strcmp(current->next->nama, nama)) {
                // Traverse Node.
                current = current->next;
            }
            // Kalo yang diinput user tidak ada di linked list.
            // If di sini jika sudah di ujung dan ternyata value dari elemen ini tidak sama dengan input user.
            if (current->next == NULL && strcmp(current->nama, nama)) {
                // Memberi tahu user bahwa tidak tertemu.
                printf("Node tidak ditemukkan!\n");
                enterToContinue();
                return;
            }
            // Jika nama yang ada di node selanjutnya sama dengan input user.
            if (!strcmp(current->next->nama, nama)) {
                // Ketemu di tail karena nextnya adalah NULL alias ini adalah TAIL.
                if (current->next->next == NULL) {
                    // Membuat struct delete yang menunjuk ke Tail yang sekarang.
                    struct dnode* delete = Tail;
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
                    struct dnode* delete = current->next;
                    // Set current dari next menjadi next dari yang ingin didelete.
                    current->next = delete->next;
                    delete->next->previous = current;
                    // Free memory dari node yang ingin dihapus.
                    free(delete);
                }
            }
        }
    }
}

// Prosedur Print node di Linked List
void printList(struct dnode* n) {
    // Akan traverse terus sampai Tail.
    while (n != NULL) {
        // Print
        printf("[%d %s]->", n->age, n->nama);
        // Traverse
        n = n->next;
    }
    printf("NULL\n");
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
        printList(Head);
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
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 5 dan jika ingin keluar
           user input 6 */
        if (valid == 1 && (choice >= 1 && choice <= 7)) {
            /* Jika user input 1, maka user akan input age dan nama dan nantinya dimasukkan ke head menggunakan
               prosedur insertHead */
            if (choice == 1) {
                printf("Insert Head\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Umur : ");
                scanf("%d", &age);
                getchar();
                printf("Nama : ");
                scanf("%[^\n]", nama);
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
                scanf("%[^\n]", nama);
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
                scanf("%s", nama);
                getchar();
                insertMid(age, nama);
            }
            /* Jika user input 4, maka user akan memilih deleteHead lalu memanggil prosedur deleteHead */
            else if (choice == 4) {
                printf("[%d %s] dihapus!\n", Head->age, Head->nama);
                deleteHead();
                enterToContinue();
            }
            /* Jika user input 5, maka user akan memilih deleteHead lalu memanggil prosedur deleteTail */
            else if (choice == 5) {
                printf("[%d %s] dihapus!\n", Tail->age, Tail->nama);
                deleteTail();
                enterToContinue();
            }
            /* Jika user input 6, maka user akan memilih deleteMid lalu input nama dari node yang ingin dihapus
               lalu memanggil prosedur deleteMid */
            else if (choice == 6) {
                printf("Menghapus Node sesuai Nama!\n");
                printf("Silahkan masukkan valuenya!\n");
                printf("Nama : ");
                scanf("%[^\n]", nama);
                getchar();
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
