#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Nomber 5 UTS Data Structures.

// Define something to make task easier.
#define cls system("cls");

// Struct for saving patient personal data.
struct dataPasien {
    char nama[50];
    char dob[15];
    int umur;
    char alamat[50];
    // 0 = bpjs, 1 = inhealth, 2 = mandiri
    int status;
};

// Struct for saving treatment data.
struct treatment {
    char date[15];
    char clinicname[30];
    char doctorname[50];
    char diagnoses[50];
    char medications[50];
    int costs;
};

// Struct for saving both personal data and the treatment.
typedef struct Patient {
    struct dataPasien InfoPatient;
    struct treatment InfoTreatment;
}Patient;

// Node for the queue.
typedef struct Node {
    struct Node* next;
    struct Node* previous;
    struct Patient patientData;
}Node;

// Struct untuk queue nantinya setiap dokter, 
typedef struct Queue {
    struct Node* Head;
    struct Node* Tail;
}Queue;

// Constant Variable
const char* clinicName[4] = { "Dental", "Orthopedic", "Surgeon", "Neurologist" };
const char* doctorClinic[4][2] = {
    "drg. Fabian Habil, Sp.Ort", "drg. Raffi Utama, Sp.Ort",
    "dr. Hafizh Satryo, Sp.OT", "dr. Keysha Aufa, Sp.OT",
    "dr. Ridoka Satya, Sp.B", "dr. Deali Nur, Sp.B",
    "dr. Alldika Brama, Sp.S", "dr. Adam Adrian, Sp.S"
};

// Queue for each doctor.
Queue* clinicQueue[4][2];
// Queue for pharmacist.
Queue* pharmacist;
// Queue for payment.
Queue* payment;

// Procedure Menu.
void menu();

// Procedure for prompt enterToContinue
void enterToContinue();

// make queue, prev and next NULL
Queue* makeQueue();

// Procedure first initialize for the program.
// Assigning struct for hospital and doctor.
void initializeProgram();

// Procedure to print all clinic and doctor list.
void doctorList();

int main() {
    initializeProgram();
    menu();
}

// Procedure Menu.
void menu() {
    unsigned short exit = 0, option, valid;
    do {
        cls;
        puts("1. List of Doctors");
        puts("2. Register New Patient");
        puts("3. View Doctor Queue");
        puts("4. Send Patient to pharmacy");
        puts("5. View Pharmacy Queue");
        puts("6. Reserve Medicine to Patient.");
        puts("7. Payment");
        puts("8. Exit");
        valid = scanf("%hu", &option);
        getchar();
        if (valid && (option >= 1 && option <= 8)) {
            if (option == 1) {
                doctorList();
            }
            else if (option == 8) {
                break;
            }
        }
        else {
            printf("%d\n", clinicQueue[0][0]->Head->patientData.InfoPatient.umur);
            puts("Input salah! silahkan coba lagi!");
            getchar();
            enterToContinue();
        }
    } while (!exit);
}

// Procedure for prompt enterToContinue
void enterToContinue() {
    printf("Enter To Continue!");
    getchar();
}

// Procedure to print all clinic and doctor list.
void doctorList() {
    for (int i = 0; i < 4; i++) {
        printf("%s clinic\n", clinicName[i]);
        for (int j = 0; j < 2; j++) {
            printf("%s ", doctorClinic[i][j]);
        }
        printf("\n--------------------\n");
    }
    enterToContinue();
}

// Procedure first initialize for the program.
// Assigning struct for hospital and doctor.
void initializeProgram() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            clinicQueue[i][j] = makeQueue();
        }
    }
    clinicQueue[0][0]->Head->patientData.InfoPatient.umur = 15;
}

// make queue, prev and next NULL
Queue* makeQueue() {
    Queue* tempQueue = (struct Queue*)malloc(sizeof(struct Queue));
    // Empty Queue, with NULL head and NULL tail.
    // tempQueue->Head = NULL;
    // tempQueue->Tail = NULL;
    return tempQueue;
}