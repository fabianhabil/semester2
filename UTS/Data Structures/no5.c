#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 2501976503 - Fabian Habil Ramdhan - Nomber 5 UTS Data Structures.

// Define something to make task easier.
#define cls system("cls");

// Struct for saving patient personal data.
struct dataPasien {
    char nama[50];
    char dob[15];
    unsigned short umur;
    char alamat[100];
    // 0 = bpjs, 1 = inhealth, 2 = mandiri, 3 = none
    unsigned short status;
};

// Struct for saving treatment data.
struct treatment {
    char date[30];
    char clinicname[15];
    char doctorname[50];
    char diagnoses[50];
    char medications[50];
    unsigned costs;
};

// Struct for saving both personal data and the treatment.
typedef struct Patient {
    struct dataPasien InfoPatient;
    struct treatment InfoTreatment;
}Patient;

// Node for the queue.
typedef struct Node {
    struct Node* next;
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
Queue* initQueue();

// push queue
void pushQueue(Queue* currentQ, Patient data);

// Procedure first initialize for the program.
// Assigning struct for hospital and doctor.
void initializeProgram();

// Procedure for print all clinic and the doctor.
void doctorList();

// Procedure to print all clinic and doctor list.
unsigned short* selectDoctor();

// Procedure to register new patient.
void registerPatient();

// Procedure to print queue
void printQueue(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor);

// Procedure to print all the doctor queue
void printAllQueue();

// Procedure to print top of the queue or peek the queue.
void peekQueue(Node* stack);

// Function to get current date and time, using time.h library.
char* getCurrentTime();

int main() {
    initializeProgram();
    menu();
}

// Procedure Menu.
void menu() {
    unsigned short exit = 0, option, valid;
    do {
        cls;
        puts("-------------------------------------");
        puts("|         Absurdly Hospital         |");
        puts("-------------------------------------");
        puts("|  1. List of Doctors               |");
        puts("|  2. Register New Patient          |");
        puts("|  3. View Doctor Queue             |");
        puts("|  4. Send Patient to pharmacy      |");
        puts("|  5. View Pharmacy Queue           |");
        puts("|  6. Reserve Medicine to Patient.  |");
        puts("|  7. Payment                       |");
        puts("|  8. Exit                          |");
        puts("|  2501976503 - Fabian Habil        |");
        puts("-------------------------------------");
        printf("Input: ");
        valid = scanf("%hu", &option);
        getchar();
        if (valid && (option >= 1 && option <= 8)) {
            cls;
            if (option == 1) {
                doctorList();
            }
            else if (option == 2) {
                registerPatient();
            }
            else if (option == 3) {
                // unsigned short* test = selectDoctor();
                // unsigned short optionClinic = test[0], optionDoctor = test[1];
                // // if optionClinic = 4, means print all the clinic and the doctor.
                // printf("%d\n", optionClinic);
                // if (optionClinic != 4) {
                //     printQueue(clinicQueue[optionClinic][optionDoctor], optionClinic, optionDoctor);
                // }
                printAllQueue();

            }
            else if (option == 8) {
                break;
            }
        }
        else {
            puts("Input salah! silahkan coba lagi!");
            enterToContinue();
        }
    } while (!exit);
}

// Procedure for prompt enterToContinue
void enterToContinue() {
    printf("Enter To Continue!");
    getchar();
}

// Procedure for print all clinic and the doctor.
void doctorList() {
    cls;
    printf("\n------------------------------\n");
    for (int i = 0; i < 4; i++) {
        printf("%s clinic\n", clinicName[i]);
        for (int j = 0; j < 2; j++) {
            printf("%d - %s", j + 1, doctorClinic[i][j]);
            if (j != 1) {
                printf("\n");
            }
        }
        printf("\n------------------------------\n");
    }
    enterToContinue();
}

// Procedure to choose clinic and the doctor.
unsigned short* selectDoctor() {
    // Contain optionClinic and optionDoctor to be used to access the array of linked list.
    unsigned short* optionReturn = malloc(sizeof(unsigned short) * 2);
    unsigned short optionClinic, optionDoctor, valid, exit = 0;
    // While true.
    do {
        cls;
        printf("       Clinic List         ");
        printf("\n-------------------------\n");
        for (int i = 0; i < 4; i++) {
            printf("%d - %s Clinic\n", i + 1, clinicName[i]);
        }
        printf("-------------------------\n");
        printf("Choose your clinic!\n");
        printf("Input: ");
        valid = scanf("%hu", &optionClinic);
        getchar();
        if (valid && (optionClinic >= 0 && optionClinic <= 5)) {
            cls;
            printf("%s Clinic Selected!\n", clinicName[optionClinic - 1]);
            do {
                cls;
                printf("       Doctor List         ");
                printf("\n-------------------------\n");
                for (int i = 0; i < 2; i++) {
                    printf("%d - %s\n", i + 1, doctorClinic[optionClinic - 1][i]);
                }
                printf("-------------------------\n");
                printf("Choose your Doctor!\n");
                printf("Input: ");
                valid = scanf("%hu", &optionDoctor);
                getchar();
                if (valid && (optionDoctor <= 2 && optionDoctor >= 1)) {
                    printf("%s selected!\n", doctorClinic[optionClinic - 1][optionDoctor - 1]);
                    exit = 1;
                }
                else {
                    printf("Wrong Input! Try again!\n");
                    enterToContinue();
                    getchar();
                }
            } while (!exit);

        }
        else {
            printf("Wrong Input! Try again!\n");
            enterToContinue();
            getchar();
        }
    } while (!exit);
    // Returning array, index 1 = optionClinic, index 2 = optionDoctor
    // Minus 1, because when choose 1, the real index is in 0.
    *(optionReturn + 0) = optionClinic - 1;
    *(optionReturn + 1) = optionDoctor - 1;
    return optionReturn;
}

// Procedure first initialize for the program.
// Initilaize the queue of the program.
// 4 Queue for doctor, queue for pharmacist and queue for payment
void initializeProgram() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            clinicQueue[i][j] = initQueue();
        }
    }
    pharmacist = initQueue();
    payment = initQueue();
}

// make queue, prev and next NULL
Queue* initQueue() {
    Queue* tempQueue = (struct Queue*)malloc(sizeof(struct Queue));
    // Empty Queue, with NULL head and NULL tail.
    tempQueue->Head = NULL;
    tempQueue->Tail = NULL;
    return tempQueue;
}

// push queue
void pushQueue(Queue* currentQ, Patient data) {
    Node* tempQueue = (struct Node*)malloc(sizeof(struct Node));
    tempQueue->patientData = data;
    tempQueue->next = NULL;
    // Queue masih kosong
    if (currentQ->Head == NULL) {
        currentQ->Head = tempQueue;
        currentQ->Tail = tempQueue;
    }
    // Queue gak kosong
    else {
        currentQ->Tail->next = tempQueue;
        currentQ->Tail = tempQueue;
    }
}

// Procedure to register new patient.
void registerPatient() {
    // ` temporary struct for the patient.
    Patient temporary;
    // Input Name Patient
    printf("Absurdly Hospital Patient Form");
    printf("\n------------------------------\n");
    printf("Enter Patient Name (50 Characters): ");
    scanf(" %[^\n]", &temporary.InfoPatient.nama);
    getchar();
    // Input Date of Birth Patient
    printf("\n------------------------------\n");
    printf("Enter Patient Date of Birth (DD-MM-YYYY): ");
    scanf(" %[^\n]", &temporary.InfoPatient.dob);
    getchar();
    // Input Age Patient
    printf("\n------------------------------\n");
    printf("Enter Patient Age: ");
    scanf("%hu", &temporary.InfoPatient.umur);
    getchar();
    // Input Address Patient
    printf("\n------------------------------\n");
    printf("Enter Patient Address (100 Characters): ");
    scanf(" %[^\n]", &temporary.InfoPatient.alamat);
    getchar();
    // Input Health Status Patient
    printf("\n------------------------------\n");
    printf("0 = BPJS, 1 = Inhealth, 2 = Mandiri, 3 = None\n");
    printf("Enter Patient Health Insurance: ");
    scanf("%hu", &temporary.InfoPatient.status);
    getchar();
    unsigned short* test = selectDoctor();
    unsigned short optionClinic = test[0], optionDoctor = test[1];
    // Assign doctor name and clinic name.
    strcpy(temporary.InfoTreatment.clinicname, clinicName[optionClinic]);
    strcpy(temporary.InfoTreatment.doctorname, doctorClinic[optionClinic][optionDoctor]);
    strcpy(temporary.InfoTreatment.date, getCurrentTime());
    pushQueue(clinicQueue[optionClinic][optionDoctor], temporary);
    enterToContinue();
}

// Procedure to print queue
void printQueue(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor) {
    if (currentQ->Head != NULL) {
        printf("Currently Checked by %s in %s Clinic:\n", doctorClinic[optionClinic][optionDoctor], clinicName[optionClinic]);
        peekQueue(currentQ->Head);
        Node* traverse = currentQ->Head->next;
        printf("Currently in the Queue: \n");
        if (traverse == NULL) {
            printf("Queue after this patient is empty!\n");
        }
        while (traverse != NULL) {
            printf("[%s] -> ", traverse->patientData.InfoPatient.nama);
            traverse = traverse->next;
        }
        printf("\n");
    }
    else {
        printf("Queue for %s in %s Clinic still empty!\n\n", doctorClinic[optionClinic][optionDoctor], clinicName[optionClinic]);
    }
    enterToContinue();
    printf("\n");
}

// Procedure to print all the doctor queue
void printAllQueue() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            printQueue(clinicQueue[i][j], i, j);
        }
    }
}

// Procedure to print top of the queue or peek the queue.
void peekQueue(Node* stack) {
    printf("nama %s\n", stack->patientData.InfoPatient.nama);
    printf("dob %s\n", stack->patientData.InfoPatient.dob);
    printf("alamat %s\n", stack->patientData.InfoPatient.alamat);
    printf("umur %hu\n", stack->patientData.InfoPatient.umur);
    printf("status %hu\n\n", stack->patientData.InfoPatient.status);
}

// Function to get current date and time, using time.h library.
char* getCurrentTime() {
    time_t t;
    time(&t);
    return(ctime(&t));
}