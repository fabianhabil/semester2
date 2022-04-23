#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 2501976503 - Fabian Habil Ramdhan - Nomber 5 UTS Data Structures.

// ------------------------ DEFINE ------------------------ //
#define cls system("cls");


// ------------------------ STRUCT DECLARATION ------------------------ //
// Struct for saving patient personal data.
struct dataPasien {
    char nama[50];
    char dob[15];
    unsigned short umur;
    char alamat[100];
    char insurance[15];
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

// Struct for the queue every doctor.
typedef struct Queue {
    struct Node* Head;
    struct Node* Tail;
}Queue;

// Queue for each doctor.
Queue* clinicQueue[4][2];
// Queue for pharmacist.
Queue* pharmacist;
// Queue for payment.
Queue* payment;


// ------------------------ CONSTANT VARIABLE ------------------------ //
const char* clinicName[4] = { "Dental", "Orthopedic", "Surgeon", "Neurologist" };
const char* doctorClinic[4][2] = {
    "drg. Fabian Habil, Sp.Ort", "drg. Raffi Utama, Sp.Ort",
    "dr. Hafizh Satryo, Sp.OT", "dr. Keysha Aufa, Sp.OT",
    "dr. Ridoka Satya, Sp.B", "dr. Deali Nur, Sp.B",
    "dr. Alldika Brama, Sp.S", "dr. Adam Adrian, Sp.S"
};
const char* insurance[4] = { "BPJS", "Inhealth", "Mandiri", "None" };

// ------------------------ PROCEDURE & FUNCTION FOR QUEUE------------------------ //
// Function for initalizing the first queue
// Make the Head and the Tail every node NULL because its empty.
Queue* initQueue();

// Procedure to push queue to the next of the current Tail.
void pushQueue(Queue* currentQ, Patient data);

// Procedure first initialize for the program.
// Assigning struct for hospital and doctor.
void initializeProgram();

// Procedure to print queue
void printQueue(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor);

// Procedure to print all the doctor queue
void printAllQueue();


// Function to print top of the queue or peek the queue.
// return 1 if there is element in the queue, return 0 if empty.
int peekQueue(Node* stack);

// Procedure to delete top of the Queue.
void deleteTopQueue(Queue* currentQ);

// ------------------------ PROCEDURE & FUNCTION EXCEPT FOR QUEUE------------------------ //
// Procedure Menu.
void menu();

// Procedure for prompt enterToContinue
void enterToContinue();

// Procedure for print all clinic and the doctor.
void doctorList();

// Procedure for outPatient if the patient already completed and add the diagnosis.
void outPatient(unsigned short optionClinic, unsigned short optionDoctor);

// Procedure to print all clinic and doctor list.
unsigned short* selectDoctor();

// Procedure to register new patient.
void registerPatient();

// Function to get current date and time, using time.h library.
char* getCurrentTime();

// ------------------------ MAIN FUNCTION ------------------------ //
int main() {
    // Initialize program, make all of the Queue.
    initializeProgram();
    // Menu procedure.
    menu();
}

// ------------------------ ALL THE FUNCTION & PROCEDURE ------------------------ //
// Procedure Menu.
void menu() {
    unsigned short exit = 0, option, valid;
    do {
        // Print Menu
        cls;
        puts("-------------------------------------");
        puts("|         Absurdly Hospital         |");
        puts("-------------------------------------");
        puts("|  1. List of Doctors               |");
        puts("|  2. Register New Patient          |");
        puts("|  3. View Doctor Queue             |");
        puts("|  4. Outpatient                    |");
        puts("|  5. View Pharmacy Queue           |");
        puts("|  6. Reserve Medicine to Patient.  |");
        puts("|  7. Payment                       |");
        puts("|  8. Exit                          |");
        puts("|  2501976503 - Fabian Habil        |");
        puts("-------------------------------------");
        printf("Input: ");
        // Input, if the input is a number, not a string
        // The valid gonna be have a value of 1, so we can handle it/
        valid = scanf("%hu", &option);
        getchar();
        // If The input is valid, and available in the menu.
        if (valid && (option >= 1 && option <= 8)) {
            cls;
            // List of Doctors
            if (option == 1) {
                doctorList();
            }
            // Register New Patient
            else if (option == 2) {
                registerPatient();
            }
            // View all Doctor Queue
            else if (option == 3) {
                printAllQueue();

            }
            // Outpatient if the patient is completed in the doctor.
            else if (option == 4) {
                unsigned short* test = selectDoctor();
                unsigned short optionClinic = test[0], optionDoctor = test[1];
                // if optionClinic = 4, means print all the clinic and the doctor.
                // if (optionClinic != 4) {
                //     printQueue(clinicQueue[optionClinic][optionDoctor], optionClinic, optionDoctor);
                // }
                outPatient(optionClinic, optionDoctor);
            }
            // Exit Program.
            else if (option == 8) {
                break;
            }
        }
        // Handler and Notice for user if the input is wrong.
        else {
            puts("Wrong Input! Try Again!");
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

    // Print All the clinic and the doctor.
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

    // While not exit.
    do {
        cls;

        // Print the clinic list, so user can choose.
        printf("       Clinic List         ");
        printf("\n-------------------------\n");
        for (int i = 0; i < 4; i++) {
            printf("%d - %s Clinic\n", i + 1, clinicName[i]);
        }
        printf("-------------------------\n");
        printf("Choose your clinic!\n");

        // Input Validator.
        printf("Input: ");
        valid = scanf("%hu", &optionClinic);
        getchar();

        // If input is valid.
        if (valid && (optionClinic >= 0 && optionClinic <= 5)) {
            do {
                cls;
                // Tell user clinic is selected.
                printf("%s Clinic Selected!\n", clinicName[optionClinic - 1]);
                // Print the doctor list, so user can choose.
                printf("       Doctor List         ");
                printf("\n-------------------------\n");
                for (int i = 0; i < 2; i++) {
                    printf("%d - %s\n", i + 1, doctorClinic[optionClinic - 1][i]);
                }
                printf("-------------------------\n");
                printf("Choose your Doctor!\n");
                printf("Input: ");

                // Input validator.
                valid = scanf("%hu", &optionDoctor);
                getchar();

                // If input is valid.
                if (valid && (optionDoctor <= 2 && optionDoctor >= 1)) {
                    printf("%s selected!\n", doctorClinic[optionClinic - 1][optionDoctor - 1]);
                    exit = 1;
                }

                // Handler and Notice for user if the input is wrong.
                else {
                    printf("Wrong Input! Try again!\n");
                    enterToContinue();
                    getchar();
                }
            } while (!exit);

        }

        // Handler and Notice for user if the input is wrong.
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

// Function for initalizing the first queue
// Make the Head and the Tail every node NULL because its empty.
Queue* initQueue() {
    Queue* tempQueue = (struct Queue*)malloc(sizeof(struct Queue));

    // Empty Queue, with NULL head and NULL tail.
    // Why NULL? because we will set it later in another function (pushQueue)
    tempQueue->Head = NULL;
    tempQueue->Tail = NULL;

    // return the Queue struct
    return tempQueue;
}

// Procedure to push queue to the next of the current Tail.
void pushQueue(Queue* currentQ, Patient data) {
    // Allocating memory for the tempQueue that we will append.
    Node* tempQueue = (struct Node*)malloc(sizeof(struct Node));

    // Make the value of patientData based on user input.
    // And then make the next is NULL, because we append or push to the tail.
    tempQueue->patientData = data;
    tempQueue->next = NULL;

    // Queue still empty.
    if (currentQ->Head == NULL) {
        // Make the tempQueue the Head and the Tail of the Queue.
        currentQ->Head = tempQueue;
        currentQ->Tail = tempQueue;
    }

    // Queue is not empty.
    else {
        // Make the next from the current Tail is the new Node (tempQueue).
        currentQ->Tail->next = tempQueue;
        // And make the new Node (tempQueue) is the new Tail.
        currentQ->Tail = tempQueue;
    }
}

// Procedure to delete top of the Queue.
void deleteTopQueue(Queue* currentQ) {
    Node* delete = currentQ->Head;

    // Queue still empty
    if (currentQ->Head == NULL) {
        // Initialize the queue again.
        currentQ = initQueue();
    }
    // Queue not empty
    else {
        // Make the new Head is the next from the old Head.
        currentQ->Head = currentQ->Head->next;
        // Free the memory of the old Head that we will delete.
        free(delete);
    }
}

// Procedure to register new patient.
void registerPatient() {
    // Temporary struct for the new patient.
    Patient temporary;
    // For options insurance
    unsigned short option;

    // Input Name Patient
    printf("Absurdly Hospital Patient Form");
    printf("\n------------------------------\n");
    printf("Enter Patient Name (50 Characters): ");
    scanf(" %[^\n]", &temporary.InfoPatient.nama);
    getchar();

    // Input Date of Birth Patient
    printf("------------------------------\n");
    printf("Enter Patient Date of Birth (DD-MM-YYYY): ");
    scanf(" %[^\n]", &temporary.InfoPatient.dob);
    getchar();

    // Input Age Patient
    printf("------------------------------\n");
    printf("Enter Patient Age: ");
    scanf("%hu", &temporary.InfoPatient.umur);
    getchar();

    // Input Address Patient
    printf("------------------------------\n");
    printf("Enter Patient Address (100 Characters): ");
    scanf(" %[^\n]", &temporary.InfoPatient.alamat);
    getchar();

    // Input Health Status Patient
    printf("------------------------------\n");
    while (1) {
        printf("1 = BPJS\n2 = Inhealth\n3 = Mandiri\n4 = None\n");
        printf("Enter Patient Health Insurance: ");
        scanf("%hu", &option);
        getchar();
        if (!(option >= 1 && option <= 4)) {
            printf("Input Salah! Silahkan coba lagi!\n");
            enterToContinue();
        }
        else {
            break;
        }
    }

    // Make variable value and calling function selectDoctor.
    unsigned short* value = selectDoctor();

    // The first index of the array is option of clinic that user choose.
    // The second index of the array is option of doctor that user choose.
    unsigned short optionClinic = value[0], optionDoctor = value[1];

    // Assign doctor name, clinic name, insurance and current time to the struct.
    strcpy(temporary.InfoTreatment.clinicname, clinicName[optionClinic]);
    strcpy(temporary.InfoTreatment.doctorname, doctorClinic[optionClinic][optionDoctor]);
    strcpy(temporary.InfoPatient.insurance, insurance[option - 1]);
    strcpy(temporary.InfoTreatment.date, getCurrentTime());

    // Push struct to the queue based on the doctor that user choose based on the index of array the linked list.
    pushQueue(clinicQueue[optionClinic][optionDoctor], temporary);
    enterToContinue();
}

// Procedure to print queue
void printQueue(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor) {
    // If the queue is not empty.
    if (currentQ->Head != NULL) {

        // Tell who the patient currently checked by the doctor (top of the queue).
        printf("Currently Checked by %s in %s Clinic:\n", doctorClinic[optionClinic][optionDoctor], clinicName[optionClinic]);

        // Print top of the queue.
        peekQueue(currentQ->Head);

        // Make traverse node for we will traverse if there is an queue after this patient.
        Node* traverse = currentQ->Head->next;
        printf("Currently in the Queue: \n");

        // If there is only one patient and its currently checked.
        if (traverse == NULL) {
            printf("Queue after this patient is empty!");
        }

        // If there is another patient except the patient that currently checked.
        else {
            // Print the Queue
            while (traverse != NULL) {
                printf("[%s] -> ", traverse->patientData.InfoPatient.nama);
                // Traverse Queue
                traverse = traverse->next;
            }
            printf("End of Queue");
        }
        printf("\n");
    }

    // If the queue is empty.
    else {
        printf("Queue for %s in %s Clinic still empty!\n", doctorClinic[optionClinic][optionDoctor], clinicName[optionClinic]);
    }
    printf("------------------------------------------------------------------\n");
    enterToContinue();
    printf("\n");
}

// Procedure to print all the doctor queue.
void printAllQueue() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            // Calling procedure to print the queue based on the queue.
            printf("------------------------------------------------------------------\n");
            printQueue(clinicQueue[i][j], i, j);
        }
    }
}

// Function to print top of the queue or peek the queue.
// return 1 if there is element in the queue, return 0 if empty.
int peekQueue(Node* stack) {
    if (stack) {
        printf("nama %s\n", stack->patientData.InfoPatient.nama);
        printf("dob %s\n", stack->patientData.InfoPatient.dob);
        printf("alamat %s\n", stack->patientData.InfoPatient.alamat);
        printf("umur %hu\n", stack->patientData.InfoPatient.umur);
        printf("insurance %s\n\n", stack->patientData.InfoPatient.insurance);
        return 1;
    }
    else {
        printf("Queue still empty!\n");
        return 0;
    }
}

// Function to get current date and time, using time.h library.
char* getCurrentTime() {
    time_t t;
    time(&t);
    return(ctime(&t));
}

// Procedure for outPatient if the patient already completed and add the diagnosis.
void outPatient(unsigned short optionClinic, unsigned short optionDoctor) {
    // Get value, if 0 = empty, if 1 = there is element in queue.
    int value = peekQueue(clinicQueue[optionClinic][optionDoctor]->Head);
    if (value) {
        deleteTopQueue(clinicQueue[optionClinic][optionDoctor]);
    }
    enterToContinue();
}