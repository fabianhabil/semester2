#include <stdio.h>
#include <stdlib.h>

// 2501976503 - Fabian Habil Ramdhan LAB 1 - Data Structures Nomor 4

// Deklarasi Structure menggunakan typedef.
typedef struct tanggal {
    double suhuC;
    double suhuK;
}tanggal;
// Deklarasi structure sebanyak 32 data, menghindari memory leak.
tanggal Hari[32];

// Deklarasi pointer structure yang tidak menuju address siapapun (NULL)
tanggal *Hariptr = NULL;

// Procedure untuk menu pertama yaitu Input Data.
void inputData() {
    /* Set value dari pointer structures yaitu address structure Hari yang sudah
       dideklarasikan sebanyak 32 data. */
    Hariptr = Hari;

    // Deklarasi exit, valid, input.
    int exit = 0, valid = 0, input;
    printf("Anda akan memasukkan data.\n");
    do {
        printf("Masukkan 0 jika ingin keluar.\n");
        printf("Masukkan tanggal (hanya angka saja)\n");
        printf("Input : ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
        maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer), 
        maka akan mereturn value 0. */
        valid = scanf("%d", &input);
        // Getchar untuk clear buffer.
        getchar();
        system("cls");
        /* Option valid jika angka dan angka ada di interval 0 dan 31, karena bulan sampai 31 dan jika ingin keluar
            user input 0 */
        if (valid && (input >= 0 && input <= 31)) {
            // Jika user input 0 maka exit dari menu 1.
            if (input == 0) {
                exit = 1;
            }
            // Namun jika user input tanggal, akan kita proses di sini.
            else {
                printf("Masukkan suhu dalam Celcius\n");
                printf("Input: ");
                /* Kita tunjuk pointer struct tadi dengan index user input, karena dimulai dari 0, misalnya kita input
                   tanggal 5, maka kita kurang 1 sehingga menjadi index ke 4 */
                /* Lalu kita ambil input dari user dan assign ke value suhuC dari pointer structure yang menunjuk
                kepada adress sesuai dengan input user */
                scanf("%lf", &(*(Hariptr + (input - 1))).suhuC);
                /* Karena kita menyimpan suhu Kelvin, tinggal kita tambahkan suhuC tadi dengan 275.15 sehingga didapatkan
                   suhu dalam Kelvin */
                (*(Hariptr + (input - 1))).suhuK = (*(Hariptr + (input - 1))).suhuC + 275.15;
                system("cls");
            }
        }
        // Memberi tahu bahwa input dari user salah.
        else {
            printf("Input salah silahkan coba lagi!\n");
        }
    } while (!exit);
    system("cls");
}

void showData() {
    int input;
    /* Set value dari pointer structures yaitu address structure Hari yang sudah
       dideklarasikan sebanyak 32 data. */
    Hariptr = Hari;
    printf("Ingin melihat data di tanggal berapa?\n");
    printf("Input: ");
    // Scan tanggal yang diinput user nantinya akan diperlihatkan ke user.
    scanf("%d", &input);
    getchar();
    // Memberi tahu user bahwa ini adalah data dari tanggal yang diinput dari user.
    printf("Data Tanggal %d\n", input);
    /* Kita tunjuk pointer struct tadi dengan index user input, karena dimulai dari 0, misalnya kita input
       tanggal 5, maka kita kurang 1 sehingga menjadi index ke 4 */
    /* Lalu kita ambil input dari user dan mengambbil value dari pointer structure yang menunjuk
       kepada adress sesuai dengan input user */
    printf("Suhu dalam Celcius : %.2lf\n", (*(Hariptr + (input - 1))).suhuC);
    printf("Suhu dalam Kelvin : %.2lf\n", (*(Hariptr + (input - 1))).suhuK);
    // Prompt enter untuk melanjutkan agar user bisa melihat terlebih dahulu data yang diminta user.
    printf("Tekan enter untuk melanjutkan!\n");
    getchar();
}

void average() {
    /* Set value dari pointer structures yaitu address structure Hari yang sudah
       dideklarasikan sebanyak 32 data. */
    Hariptr = Hari;
    // Deklarasikan 2 variabel float yang jumlah untuk suhu celcius dan jumlah2 untuk suhu kelvin.
    float jumlah = 0;
    float jumlah2 = 0;
    /* Melakukan iterasi sebanyak 31 kali untuk menghitung rata rata, dengan menambahkan setiap tanggalnya
       ke masing masing variabel */
    for (int i = 0; i <= 30; i++) {
        jumlah += (*(Hariptr + i)).suhuC;
        jumlah2 += (*(Hariptr + i)).suhuK;
    }
    // Setelah dijumlahkan,keduanya dibagi 31 karena kita anggap bahwa satu bulan di sini adalah 31 hari.
    jumlah = jumlah / 31;
    jumlah2 = jumlah2 / 31;
    // Lalu output ke user rata - rata dari suhu satu bulan dalam bentuk celcius dan kelvin.
    printf("Rata Rata suhu satu bulan dalam Celcius adalah : %.2lf\n", jumlah);
    printf("Rata Rata suhu satu bulan dalam Kelvin adalah : %.2lf\n", jumlah2);
    // Prompt enter untuk melanjutkan agar user bisa melihat terlebih dahulu data yang diminta user.
    printf("Tekan enter untuk melanjutkan!\n");
    getchar();
}

int menu() {
    // Deklarasi exit, valid, option.
    int option = 0, exit = 0, valid = 0;
    do {
        // Memperlihatkan kepada user ada menu apa saja di program.
        system("cls");
        puts("1. Input data");
        puts("2. Show data");
        puts("3. Average in 1 month");
        puts("4. Exit");
        printf("Input: ");
        /* Input ke variabel input, variabel valid di sini jika user input sesuai dengan format data specifier yang ada (integer),
        maka akan mereturn value 1. Sebaliknya jika user input tidak sesuai dengan format data specifier yang ada (integer), 
        maka akan mereturn value 0. */
        valid = scanf("%d", &option);
        // Getchar untuk clear buffer.
        getchar();
        system("cls");
        /* Option valid jika angka dan angka ada di interval 1 dan 4, karena menu sampai 3 dan jika ingin keluar
           user input 4 */
        if (valid == 1 && (option >= 1 && option <= 4)) {
            // Jika user input 1, maka ke menu inputData.
            if (option == 1) {
                inputData();
            }
            // Jika user input 2, maka ke menu showData.
            else if (option == 2) {
                showData();
            }
            // Jika user input 3, maka ke menu average.
            else if (option == 3) {
                average();
            }
            // Jika user input 4, maka keluar dari program.
            else if (option == 4) {
                exit = 1;
                printf("Anda telah keluar dari program!\n");
            }
        }
        // Memberi tahu bahwa input dari user salah.
        else {
            puts("Menu tidak ditemukkan! Silahkan coba lagi!");
        }
    } while (!exit);
}

int main() {
    // Fungsi main langsung ke fungsi menu.
    menu();
    return 0;
}