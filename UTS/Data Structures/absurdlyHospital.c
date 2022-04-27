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
    int costs;
    unsigned queueNumber;
};

// Struct for saving both personal data and the treatment.
typedef struct Patient {
    struct dataPasien InfoPatient;
    struct treatment InfoTreatment;
}Patient;

// Node for the queue.
typedef struct Node {
    struct Node* next;
    struct Patient dataPatient;
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
// Queue cashier for the payment.
Queue* cashier;

// ------------------------ CONSTANT VARIABLE ------------------------ //
// All the clinic Name.
const char* clinicName[4] = { "Dental", "Orthopedic", "Surgeon", "Neurologist" };

// Price Clinic based on the index, index 0 is Dental and the price is 150000.
const unsigned priceClinic[4] = { 150000, 200000, 250000, 300000 };

// Doctor Clinic based on the index, index 0 is Dental and there is 2 more Doctor.
const char* doctorClinic[4][2] = {
    "drg. Fabian Habil, Sp.Ort", "drg. Raffi Utama, Sp.Ort",
    "dr. Hafizh Satryo, Sp.OT", "dr. Keysha Aufa, Sp.OT",
    "dr. Ridoka Satya, Sp.B", "dr. Deali Nur, Sp.B",
    "dr. Alldika Brama, Sp.S", "dr. Adam Adrian, Sp.S"
};

// All the Insurance available on this hospital.
const char* insurance[4] = { "BPJS", "Inhealth", "Mandiri", "None" };

// For queueNumber in this hospital, starting in 0 and we will preincrement before assign to struct.
unsigned short queueNumber = 0;

// ------------------------ PROCEDURE & FUNCTION FOR QUEUE------------------------ //
// Function for initalizing the first queue
// Make the Head and the Tail every node NULL because its empty.
Queue* initQueue();

// Procedure to push queue to the next of the current Tail.
void pushQueue(Queue* currentQ, Patient data);

// Procedure first initialize for the program.
// Assigning struct for hospital and doctor.
void initializeProgram();

// Procedure to print all the doctor queue
void printAllDoctorQueue();

// Procedure to print doctor queue
void printQueueDoctor(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor);

// Procedure to print all pharmacist Queue.
void printAllPharmacistQueue();

// Procedure to print Patient Data (Full Data after diagnoses and medications)
void printdataPatient(Node* patient);

// Function to print top of the queue or peek the queue doctor.
// return 1 if there is element in the queue, return 0 if empty.
int peekQueueDoctor(Node* queue);

// Procedure to delete top of the Queue.
void deleteTopQueue(Queue* currentQ);

// ------------------------ PROCEDURE & FUNCTION EXCEPT FOR QUEUE------------------------ //
// Procedure Menu.
void menu();

// Procedure for prompt enterToContinue
void enterToContinue();

// Procedure for print all clinic and the doctor.
void doctorList();

// Procedure to register new patient.
void registerPatient();

// Procedure for outPatient if the patient already completed and add the diagnosis.
void outPatient(unsigned short optionClinic, unsigned short optionDoctor);

// Procedure for pharmacist to delete the queue, calculate cost and push to queue cashier.
void reserveMedicine();

// Procedure to check the cashier, payment for the top queue of the cashier queue, and
// Display another patient that in this cashier queue. 
void checkCashier();

// Procedure to print final data for the patient, including all the price.
void printFinalPatient();

// Procedure to write history of patient data into the historyFile.database
void writeHistoryPatient(Patient dataPatient);

// Procedure to print all clinic and doctor list.
unsigned short* selectDoctor();

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
        puts("|  7. Cashier                       |");
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
                printAllDoctorQueue();
            }
            // Outpatient if the patient is completed in the doctor.
            else if (option == 4) {
                unsigned short* option = selectDoctor();
                // If option Clinic is not 5, then user choose clinic and the doctor.
                if (option[0] != 5) {
                    // First index is for the clinic, and second index is for the doctor.
                    unsigned short optionClinic = option[0], optionDoctor = option[1];
                    outPatient(optionClinic, optionDoctor);
                }
            }
            // View all pharmacist Queue
            else if (option == 5) {
                printAllPharmacistQueue();
            }
            // Medicine is finished in the pharmacist.
            else if (option == 6) {
                reserveMedicine();
            }
            // Check Cashier.
            else if (option == 7) {
                checkCashier();
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
        printf("%d - Cancel\n", 5);
        printf("-------------------------\n");
        printf("Choose your clinic!\n");

        // Input Validator.
        printf("Input: ");
        valid = scanf("%hu", &optionClinic);
        getchar();

        // If user choose Cancel.
        if (optionClinic == 5) {
            // Make the optionClinic and optionDoctor to 5 and return it, so we can handle it later.
            *(optionReturn + 0) = 5;
            *(optionReturn + 1) = 5;
            return optionReturn;
        }

        // If input is valid.
        if (valid && (optionClinic >= 0 && optionClinic <= 5)) {
            do {
                cls;
                // Tell user clinic is selected.
                printf("%s Clinic Selected!\n", clinicName[optionClinic - 1]);
                // Print the doctor list, so user can choose.
                printf("     Doctor List         ");
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
                    printf("\n%s selected!\n", doctorClinic[optionClinic - 1][optionDoctor - 1]);
                    exit = 1;
                }

                // Handler and Notice for user if the input is wrong.
                else {
                    printf("Wrong Input! Try again!\n");
                    enterToContinue();
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
// 8 Queue for doctor, queue for pharmacist and queue for payment
void initializeProgram() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            clinicQueue[i][j] = initQueue();
        }
    }
    pharmacist = initQueue();
    cashier = initQueue();
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

    // Make the value of dataPatient based on user input.
    // And then make the next is NULL, because we append or push to the tail.
    tempQueue->dataPatient = data;
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
    // Make Node Delete because we will free the memory.
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
    printf("Enter Patient Name (50 Characters MAX): ");
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
    printf("Enter Patient Address (100 Characters MAX): ");
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
    // This will make user select the clinic and the doctor.
    // And return what index they choose.
    unsigned short* value = selectDoctor();

    // If the value 5, user cancel to choose the doctor and the clinic.
    if (value[0] == 5) {
        return;
    }

    // The first index of the array is option of clinic that user choose.
    // The second index of the array is option of doctor that user choose.
    unsigned short optionClinic = value[0], optionDoctor = value[1];

    // Assign doctor name, clinic name, insurance, queue number and current time to the struct.
    strcpy(temporary.InfoTreatment.clinicname, clinicName[optionClinic]);
    strcpy(temporary.InfoTreatment.doctorname, doctorClinic[optionClinic][optionDoctor]);
    strcpy(temporary.InfoPatient.insurance, insurance[option - 1]);
    strcpy(temporary.InfoTreatment.date, getCurrentTime());
    temporary.InfoTreatment.queueNumber = ++queueNumber;

    // Push struct to the queue based on the doctor that user choose based on the index of array the linked list.
    pushQueue(clinicQueue[optionClinic][optionDoctor], temporary);
    enterToContinue();
}

// Procedure to print queue in the doctor
void printQueueDoctor(Queue* currentQ, unsigned short optionClinic, unsigned short optionDoctor) {
    // If the queue is not empty.
    if (currentQ->Head != NULL) {
        cls;
        // Tell who the patient currently checked by the doctor (top of the queue).
        printf("------------------------------------------------------------------\n");
        printf("Currently Checked by %s in %s Clinic:\n", doctorClinic[optionClinic][optionDoctor], clinicName[optionClinic]);

        // Print patient from top of the queue.
        peekQueueDoctor(currentQ->Head);

        // Make traverse node for we will traverse if there is an queue after this patient.
        Node* traverse = currentQ->Head->next;
        printf("\nCurrently in the Queue: \n");

        // If there is only one patient and its currently checked.
        if (traverse == NULL) {
            printf("Queue after this patient is empty!");
        }

        // If there is another patient except the patient that currently checked.
        else {
            // Print the Queue
            while (traverse != NULL) {
                printf("[%s] -> ", traverse->dataPatient.InfoPatient.nama);
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
void printAllDoctorQueue() {
    for (int i = 0; i < 4; i++) {
        printf("------------------------------------------------------------------\n");
        printf("%s Clinic\n", clinicName[i]);
        for (int j = 0; j < 2; j++) {
            printf("------------------------------------------------------------------\n");
            // Calling procedure to print the doctor queue based on the iteration (clinic).
            printQueueDoctor(clinicQueue[i][j], i, j);
        }
    }
}

// Function to print top of the queue or peek the queue doctor.
// return 1 if there is element in the queue, return 0 if empty.
int peekQueueDoctor(Node* queue) {
    // Queue is not empty.
    if (queue) {
        printf("Queue Hospital - Number #%03hu\n", queue->dataPatient.InfoTreatment.queueNumber);
        printf("Date Registered - at %s\n", queue->dataPatient.InfoTreatment.date);
        printf("Name        : %s\n", queue->dataPatient.InfoPatient.nama);
        printf("DOB         : %s\n", queue->dataPatient.InfoPatient.dob);
        printf("Address     : %s\n", queue->dataPatient.InfoPatient.alamat);
        printf("Age         : %hu\n", queue->dataPatient.InfoPatient.umur);
        printf("Insurance   : %s\n", queue->dataPatient.InfoPatient.insurance);
        return 1;
    }
    // Queue is empty.
    else {
        printf("Queue still empty!\n");
        return 0;
    }
}

// Function to get current date and time, using time.h library.
char* getCurrentTime() {
    // Generate time from the library <ctime.h>
    // Based on the C Programming Language Documentation
    time_t t;
    time(&t);
    return(ctime(&t));
}

// Procedure for outPatient if the patient already completed and add the diagnosis.
void outPatient(unsigned short optionClinic, unsigned short optionDoctor) {
    // Get value, if 0 = empty, if 1 = there is element in queue.
    int value = peekQueueDoctor(clinicQueue[optionClinic][optionDoctor]->Head);

    // Variable input for input YES or NO
    char input[20];
    // If queue is not empty.
    if (value) {
        cls;
        printf("-------------------------------------------------------------");
        // Print so user know who the doctor taking care of this patient.
        printf("\nCurrently being examined by %s\n", clinicQueue[optionClinic][optionDoctor]->Head->dataPatient.InfoTreatment.doctorname);

        // Print patient data that currently getting examined by the doctor.
        peekQueueDoctor(clinicQueue[optionClinic][optionDoctor]->Head);

        // Make temporary struct, because we will assign some data, and we push it to the pharmacy queue.
        Patient tempData = clinicQueue[optionClinic][optionDoctor]->Head->dataPatient;
        while (1) {
            printf("-------------------------------------------------------------");
            printf("\nIs this patient already finished being examined by the doctor?\n");
            // Input and validator.
            printf("YES or NO\n");
            printf("Input: ");
            scanf(" %[^\n]", &input);
            getchar();
            // If input is neither YES or NO
            if (!strcmp(input, "YES") || !strcmp(input, "NO")) {
                if (!strcmp(input, "YES")) {
                    // Input diagnoses.
                    printf("\nEnter the diagnoses of this patient (50 Characters MAX)\n");
                    printf("Input: ");
                    scanf(" %[^\n]", tempData.InfoTreatment.diagnoses);
                    getchar();

                    // Input medications or medicines.
                    printf("\nEnter medications for the patient\n");
                    printf("Example (Paracetamol, Allerin Expectorant and Bandage)\n");
                    printf("(50 Characters Max)\n");
                    printf("Input: ");
                    scanf(" %[^\n]", tempData.InfoTreatment.medications);
                    getchar();

                    // Push the temporaryData that just updated based on input to the pharmacy queue.
                    pushQueue(pharmacist, tempData);

                    // Because we already push to teh pharmacy, delete the top of the queue from that doctor.
                    deleteTopQueue(clinicQueue[optionClinic][optionDoctor]);

                    // Tell the user its completed.
                    printf("\nSuccess!\n");
                }
                // Its guaranteed for exit the loop, even if we input YES or NO.
                // If YES, do some tasks first. If NO, just exit the procedure.
                break;
                enterToContinue();
            }
            // Error Handler for Wrong Input
            else {
                printf("Wrong Input! Try Again!\n");
                enterToContinue();
            }
        }
    }
    enterToContinue();
}

// Procedure to print all pharmacist Queue.
void printAllPharmacistQueue() {
    // Traverse node, for us print and traverse all the queue.
    Node* traverse = pharmacist->Head;

    // Print the Queue
    // Queue pharmacist still empty.
    if (traverse == NULL) {
        printf("Pharmacist still Empty!\n");
        enterToContinue();
        return;
    }
    // Queue pharmacist is not empty.
    printf("----------------  QUEUE CLINIC  -----------------\n");
    while (traverse != NULL) {
        // Print dataPatient.
        printdataPatient(traverse);
        // Traverse Queue
        traverse = traverse->next;
        enterToContinue();
    }
}

// Procedure to print Patient Data (Full Data after diagnoses and medications)
void printdataPatient(Node* patient) {
    printf("-------------------------------------------------\n");
    printf("Queue Hospital - Number #%03hu\n", patient->dataPatient.InfoTreatment.queueNumber);
    printf("Date Registered - at %s\n", patient->dataPatient.InfoTreatment.date);
    printf("Clinic %s\n", patient->dataPatient.InfoTreatment.clinicname);
    printf("%s\n", patient->dataPatient.InfoTreatment.doctorname);
    printf("Diagnose: %s\n", patient->dataPatient.InfoTreatment.diagnoses);
    printf("Medicine: %s\n\n", patient->dataPatient.InfoTreatment.medications);
    printf("Name        : %s\n", patient->dataPatient.InfoPatient.nama);
    printf("DOB         : %s\n", patient->dataPatient.InfoPatient.dob);
    printf("Address     : %s\n", patient->dataPatient.InfoPatient.alamat);
    printf("Age         : %hu\n", patient->dataPatient.InfoPatient.umur);
    printf("Insurance   : %s\n", patient->dataPatient.InfoPatient.insurance);
    printf("-------------------------------------------------\n");
}

// Procedure for pharmacist to delete the queue, calculate cost and push to queue cashier.
void reserveMedicine() {
    // If pharmacist still empty
    if (pharmacist->Head == NULL) {
        printf("Pharmacist still Empty!\n");
        enterToContinue();
        return;
    }

    // Make temporary struct, because we will assign some data, and we push it to the cashier queue.
    Patient topPharmacist = pharmacist->Head->dataPatient;

    // Pharmacist not empty.
    // Variable input for input YES or NO
    char input[20];
    printdataPatient(pharmacist->Head);

    // Will be loop until user input neither YES or NO.
    while (1) {
        // Input and validator.
        printf("Medicine for this patient is finished?\n");
        printf("YES or NO\n");
        printf("Input: ");
        scanf(" %[^\n]", &input);
        getchar();

        // If user input neither YES or NO.
        if (!strcmp(input, "YES") || !strcmp(input, "NO")) {
            // If user input YES
            if (!strcmp(input, "YES")) {
                // Input cost for the medicine.
                printf("Enter the cost for all the medicine: Rp");
                scanf("%d", &topPharmacist.InfoTreatment.costs);
                getchar();
                printf("Medicine cost for this patients is Rp%d, proceed to the cashier.\n", topPharmacist.InfoTreatment.costs);

                // Add Administration and Clinic Fee.
                unsigned clinicPrice = 0;
                unsigned medicinePrice = topPharmacist.InfoTreatment.costs;
                unsigned short administrationPrice = 5000;

                // Check clinic, for the price per clinic and the admin.
                if (!strcmp(topPharmacist.InfoTreatment.clinicname, "Dental")) {
                    clinicPrice = priceClinic[0];
                }
                else if (!strcmp(topPharmacist.InfoTreatment.clinicname, "Orthopedic")) {
                    clinicPrice = priceClinic[1];
                }
                else if (!strcmp(topPharmacist.InfoTreatment.clinicname, "Surgeon")) {
                    clinicPrice = priceClinic[2];
                }
                else if (!strcmp(topPharmacist.InfoTreatment.clinicname, "Neurologist")) {
                    clinicPrice = priceClinic[3];
                }

                // Delete the top of the queue of pharmacist, because we will push this node to cashier queue.
                deleteTopQueue(pharmacist);
                // Update the new cost after the clinicPrice and the administrationPrice
                topPharmacist.InfoTreatment.costs = medicinePrice + clinicPrice + administrationPrice;
                // Push the newData to the cashier queue.
                pushQueue(cashier, topPharmacist);
            }
            // Its guaranteed for exit the loop, even if we input YES or NO.
            // If YES, do some tasks first. If NO, just exit the procedure.
            enterToContinue();
            break;
        }
        // Error handler for invalid Input.
        else {
            printf("Wrong Input! Try Again!");
            enterToContinue();
        }
    }
}

// Procedure to check the cashier, payment for the top queue of the cashier queue, and
// Display another patient that in this cashier queue. 
void checkCashier() {
    // Current queue the Head or top of the queue Cashier, because we will delete it if the bill is paid.
    Node* currentCashier = cashier->Head;

    // Cashier still empty.
    if (currentCashier == NULL) {
        printf("Cashier still empty!\n");
        enterToContinue();
        return;
    }
    // Cashier not empty.
    else {
        // Print the patientData that on top of the cashier queue.
        printFinalPatient(currentCashier);

        // Variable declaration for the bill and input user.
        int bayar = 0;
        int bill = currentCashier->dataPatient.InfoTreatment.costs;

        // If insurance is neither BPJS or Inhealth, is paid by insurance.
        if (!strcmp(currentCashier->dataPatient.InfoPatient.insurance, "BPJS") ||
            !strcmp(currentCashier->dataPatient.InfoPatient.insurance, "Inhealth")) {
            printf("Bill is paid by %s Insurance!\n\n", currentCashier->dataPatient.InfoPatient.insurance);
            enterToContinue();
            // Make the bill 0, so we dont get to the loop below.
            bill = 0;
        }
        else if (!strcmp(currentCashier->dataPatient.InfoPatient.insurance, "Mandiri")) {
            // Change the bill to 20% discount because Mandiri insurance.
            bill = bill * 0.8;
            printf("You get 20%% Discount by %s\n", currentCashier->dataPatient.InfoPatient.insurance);
            printf("Your bill is now %d\n", bill);
        }
        while (bill > 0) {
            // Input and validator.
            printf("\nInput -1 to Cancel!\n");
            printf("Input your money: Rp");
            scanf("%d", &bayar);
            getchar();

            // If user input -1, back to menu.
            if (bayar == -1) {
                return;
            }

            // If user pay any bills.
            else {
                // Substract current bill by input user.
                bill = bill - bayar;
                if (bill <= 0) {
                    // If the bayar variable equal to bill, bill is paid and there is no exhange.
                    if (bayar == bill) {
                        printf("Bill paid!\n");
                    }
                    else {
                        // If input exceeded the current bill, patients have some exchange.
                        printf("Bill Paid!\n");
                        printf("You get Rp%d in exchange\n", abs(bill));
                    }
                }
                // Bill is not paid.
                else {
                    printf("You still have Rp%d in the bill\n\n", bill);
                }
                enterToContinue();
            }
        };

        // If bill less or equal to zero means bill is already paid, and we will delete the top of the cashier 
        // queue and we write in on the historyFile.database
        if (bill <= 0) {
            // Make Patient for struct patientData to write it on database.data
            Patient temp = currentCashier->dataPatient;
            writeHistoryPatient(temp);

            // Delete the top of the queue cashier.
            deleteTopQueue(cashier);
        }
    }
}

// Procedure to print final data for the patient, including all the price.
void printFinalPatient(Node* patient) {
    // Variable Declaration for clinicPrice and administrationPrice
    unsigned clinicPrice = 0;
    unsigned short administrationPrice = 5000;

    // Check clinic, for the price per clinic and the admin.
    if (!strcmp(patient->dataPatient.InfoTreatment.clinicname, "Dental")) {
        clinicPrice = priceClinic[0];
    }
    else if (!strcmp(patient->dataPatient.InfoTreatment.clinicname, "Orthopedic")) {
        clinicPrice = priceClinic[1];
    }
    else if (!strcmp(patient->dataPatient.InfoTreatment.clinicname, "Surgeon")) {
        clinicPrice = priceClinic[2];
    }
    else if (!strcmp(patient->dataPatient.InfoTreatment.clinicname, "Neurologist")) {
        clinicPrice = priceClinic[3];
    }

    // Because the total cost is already sum by clinic and administrationPrice
    // To get medicine price, we substract by clinic and administrationPrice
    unsigned medicinePrice = patient->dataPatient.InfoTreatment.costs - clinicPrice - administrationPrice;

    // Print All dataPatient that is final.
    printf("Current Patient in the cashier:\n");
    printf("-----------------------------------------------\n");
    printf("Queue Hospital - Number #%03hu\n", patient->dataPatient.InfoTreatment.queueNumber);
    printf("Date Registered - at %s\n", patient->dataPatient.InfoTreatment.date);
    printf("Name           : %s\n", patient->dataPatient.InfoPatient.nama);
    printf("DOB            : %s\n", patient->dataPatient.InfoPatient.dob);
    printf("Address        : %s\n", patient->dataPatient.InfoPatient.alamat);
    printf("Age            : %hu\n", patient->dataPatient.InfoPatient.umur);
    printf("Insurance      : %s\n\n", patient->dataPatient.InfoPatient.insurance);
    printf("Clinic %s\n", patient->dataPatient.InfoTreatment.clinicname);
    printf("%s\n", patient->dataPatient.InfoTreatment.doctorname);
    printf("Diagnose       : %s\n", patient->dataPatient.InfoTreatment.diagnoses);
    printf("Medicine       : %s\n", patient->dataPatient.InfoTreatment.medications);
    printf("Medicine Cost  : Rp%d\n", medicinePrice);
    printf("Clinic Cost    : Rp%d\n", clinicPrice);
    printf("Administration Cost: Rp%d\n\n", administrationPrice);
    printf("Total Cost     : Rp%d\n", patient->dataPatient.InfoTreatment.costs);
    printf("-----------------------------------------------\n");
}


// Procedure to write history of patient data into the historyFile.database
void writeHistoryPatient(Patient dataPatient) {
    // Open file stream with mode append.
    FILE* fp = fopen("database.data", "a");
    fprintf(fp, "Date Registered - at %s\n", dataPatient.InfoTreatment.date);
    fprintf(fp, "Name           : %s\n", dataPatient.InfoPatient.nama);
    fprintf(fp, "DOB            : %s\n", dataPatient.InfoPatient.dob);
    fprintf(fp, "Address        : %s\n", dataPatient.InfoPatient.alamat);
    fprintf(fp, "Age            : %hu\n", dataPatient.InfoPatient.umur);
    fprintf(fp, "Insurance      : %s\n\n", dataPatient.InfoPatient.insurance);
    fprintf(fp, "Clinic %s\n", dataPatient.InfoTreatment.clinicname);
    fprintf(fp, "%s\n", dataPatient.InfoTreatment.doctorname);
    fprintf(fp, "Diagnose       : %s\n", dataPatient.InfoTreatment.diagnoses);
    fprintf(fp, "Medicine       : %s\n", dataPatient.InfoTreatment.medications);
    fprintf(fp, "Total Cost     : Rp%d\n", dataPatient.InfoTreatment.costs);
    fprintf(fp, "-----------------------------------------------\n");
    fclose(fp);
}