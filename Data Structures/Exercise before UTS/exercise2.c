#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Queue Linked List - Aplikasi Wahana Antrian
// Queue (FIFO) fitur -> display, front, pop, push, sisa antrian (display queue)
// Aplikasi antrian -> simpan di file.

struct queue {
    int tinggi;
    char nama[50];
    int status;
    int age;
    struct queue* next;
};

struct queue* Head = NULL;
struct queue* Tail = NULL;

void enterToContinue() {
    printf("Tekan Enter untuk melanjutkan!");
    getchar();
}

struct queue* createNewNode(int tinggi, char nama[], int status, int age) {
    struct queue* newNode = (struct queue*)malloc(sizeof(struct queue));
    newNode->tinggi = tinggi;
    strcpy(newNode->nama, nama);
    newNode->status = status;
    newNode->age = age;
    newNode->next = NULL;
    return newNode;
}

void displayQueue() {
    struct queue* current = Head;
    if (current == NULL) {
        printf("Antrian masih kosong!");
    }
    while (current != NULL) {
        printf("%s %d %d -> ", current->nama, current->age, current->tinggi);
        current = current->next;
    }
    printf("\n");
}

void inputAntrian() {
    char nama[50];
    int tinggi, status, age;
    printf("Nama Pelanggan : ");
    scanf(" %[^\n]", nama);
    getchar();
    printf("Tinggi Pelanggan : ");
    scanf("%d", &tinggi);
    getchar();
    printf("Umur Pelanggan : ");
    scanf("%d", &age);
    getchar();
    printf("1 = VIP, 2 = Reguler\n");
    printf("Status Pelanggan : ");
    scanf("%d", &status);
    getchar();
    printf("KONTOL %d\n", age);
    struct queue* newNode = createNewNode(tinggi, nama, status, age);
    // Kosong
    if (Head == NULL) {
        Head = Tail = newNode;
    }
    else {
        Tail->next = newNode;
        Tail = newNode;
    }

}

int main() {
    displayQueue();
    int menu, valid, exit = 0;
    do {
        puts("Dufun");
        puts("1. Input Antrian");
        puts("2. Memanggil Antrian");
        puts("3. Sisa Antrian");
        puts("4. Keluar Program");
        valid = scanf("%d", &menu);
        getchar();
        if (valid && (menu > 0 && menu < 5)) {
            if (menu == 1) {
                inputAntrian();
            }
            else if(menu == 2){
                
            }
            else if (menu == 3) {
                displayQueue();
            }
            enterToContinue();

        }
        else {
            printf("Input Salah!\n");
            getchar();
            enterToContinue();
        }
    } while (!exit);
}