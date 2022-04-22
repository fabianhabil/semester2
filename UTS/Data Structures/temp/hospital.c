#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "hospital.h"

/*-------------Functions (see header file for brief explanation)--------------*/

/* Initiates the queue the function is assigned to */
Queue* Q_initiate(void) {
    Queue* q = malloc(sizeof(Queue));
    if (q) { // if malloc() fails for some reason, "q" will become NULL instead
        q->front = NULL;
        q->rear = NULL;
    }
    return q;
}

/* Returns the frontmost node in a queue (without releasing it)
   Will return NULL if queue is empty */
Node* Q_peek(const Queue* q) {
    return q->front;
}

/* Stores a node into a queue*/
int Q_enqueue(Queue* q, const Node* input) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode) {
        // Proceed if new node is successfully allocated
        *newNode = *input;
        if (Q_peek(q)) {
            // Link rearmost node to new node if queue is not empty
            q->rear->next = newNode;
        }
        else {
            // Link front pointer to new node if queue is empty
            q->front = newNode;
        }
        // Move rear pointer to the new node & NULL-ify new node's next pointer
        q->rear = newNode;
        q->rear->next = NULL;
        // Return success code
        return EXIT_SUCCESS;
    }
    // Return error code if new node cannot be allocated (see line 41)
    return EXIT_FAILURE;
}

/* Releases frontmost node from a queue */
int Q_dequeue(Queue* q) {
    Node* temp = NULL;
    if (Q_peek(q)) {
        // Proceed if queue is not empty yet
        temp = q->front;
        if (temp->next) {
            // Move front pointer if queue is not empty
            q->front = q->front->next;
        }
        else {
            // NULL-ify both front and rear pointers if queue is about to be empty
            q->front = NULL;
            q->rear = NULL;
        }
        // Deallocate newly-released node
        free(temp);
        return EXIT_SUCCESS;
    }
    // see line 64
    return EXIT_FAILURE;
}

/* Flushes input */
inline void flushInput(void) {
    scanf("%*[^\n]");
    getchar();
}

/* Get the current date (i.e. when the function is called)
   and store it to the argument char buffer */
void getCurrentTime(char* buffer) {
    time_t mcTime = time(NULL);
    struct tm* crTime = localtime(&mcTime);

    sprintf(buffer, "%02d/%02d/%d", crTime->tm_mday, crTime->tm_mon + 1, crTime->tm_year + 1900);
}

/* Prepares app functionality by allocating all queues */
int appInitiate(void) {
    for (unsigned i = 0; i < 8; i++) {
        // Abort if queue initiation fails
        if (!(docQueue[i / 2][i % 2] = Q_initiate())) {
            return EXIT_FAILURE;
        }
    }
    // Abort if queue initiation fails
    if (!(phrQueue = Q_initiate()) || !(payQueue = Q_initiate())) {
        return EXIT_FAILURE;
    }
    // Return success code if all initiations are successful
    return EXIT_SUCCESS;
}

/* Prints patient's personal data
   (not including information related to treatment) */
void viewPatientInfo(Node* data) {
    printf("--------------------------------------------------------\n");
    printf("Name          : %s\n"
        "Date of Birth : %s\n"
        "Age           : %u\n"
        "Home Address  : %s\n"
        "Insurance     : %s\n",
        data->patInfo.name,
        data->patInfo.DOB,
        data->patInfo.age,
        data->patInfo.addr,
        insName[data->patInfo.insr]);
}

/* Archives all information pertaining to a patient
   that has fully finished treatment */
void recordPatient(Node* node) {
    FILE* file = fopen(RECORD_FILE, "a");
    fprintf(file,
        "Name             : %s\n"
        "Date of Birth    : %s\n"
        "Age              : %u\n"
        "Home Address     : %s\n"
        "Insurance        : %s\n"
        "Department       : %s\n"
        "Doctor           : %s\n"
        "Appointment Date : %s\n"
        "Diagnosis        : %s\n"
        "Medicines        : %-13s * %03u"
        "                   %-13s * %03u"
        "                   %-13s * %03u"
        "                   %-13s * %03u"
        "Total Cost       : Rp%llu\n\n",
        node->patInfo.name,
        node->patInfo.DOB,
        node->patInfo.age,
        node->patInfo.addr,
        insName[node->patInfo.insr],
        depName[node->patTrmt.dept],
        docName[node->patTrmt.dept][node->patTrmt.doct],
        node->patTrmt.appt,
        node->patTrmt.diag,
        medName[0], node->patTrmt.medsAmt[0],
        medName[1], node->patTrmt.medsAmt[1],
        medName[2], node->patTrmt.medsAmt[2],
        medName[3], node->patTrmt.medsAmt[3],
        node->patTrmt.cost);
    fclose(file);
}

/* View the list of doctors in the hospital*/
void viewDoctorList(void) {
    for (unsigned dept = 0; dept < 4; dept++) {
        printf("#-----------------------------------------------#\n"
            "| Anglorum Hospital - Department of %-11s |\n"
            "| [1] %-41s |\n"
            "| [2] %-41s |\n",
            depName[dept], docName[dept][0], docName[dept][1]);
    }
    printf("#-----------------------------------------------#\n\n");
}

void registerPatient(void) {
    unsigned length, d, m, y; // To temporarily store patient's day of birth
    Node newPat; // Temporary node for patient's data

enterName: // Enter name name
    printf("Enter patient's name (max 50 characters): ");
    scanf("%50[^\n]%n", newPat.patInfo.name, &length);
    flushInput();
    if (length > 50) { // Ask to reenter if length is excessive
        printf("Error: max character amount exceeded.\n");
        goto enterName;
    }

enterDOB: // Enter day of birth
    printf("\nEnter patient's date of birth (dd*mm*yyyy): ");
    if (scanf("%2u%*c%2u%*c%4u", &d, &m, &y) != 3) {
        // Ask to reenter DOB scanf() fails to parse input
        flushInput();
        printf("Error: invalid date of birth.\n");
        goto enterDOB;
    }
    else {
        // Store DOB as a string to the temporary node
        flushInput();
        sprintf(newPat.patInfo.DOB, "%02u/%02u/%04u", d, m, y);
    }

enterAge: // Enter age
    printf("\nEnter patient's age: ");
    scanf("%u", &newPat.patInfo.age);
    flushInput();
    if (newPat.patInfo.age > 150) {
        // Ask to reenter if age is impossibly old
        printf("Error: invalid age.\n");
        goto enterAge;
    }

enterAddr: // Enter home address
    printf("\nEnter patient's home address (max 127 characters): ");
    scanf("%127[^\n]%n", newPat.patInfo.addr, &length);
    flushInput();
    if (length > 127) {
        // Ask to reenter if length is excessive
        printf("Error: max character amount exceeded.\n");
        goto enterAddr;
    }

enterInsr: // Choose insurance
    printf("\nChoose patient's insurance\n");
    for (unsigned ins = 0; ins < 3; ins++) {
        // Print list of available insurances
        printf("[%u] %s\n", ins + 1, insName[ins]);
    }
    printf("Option: ");
    scanf("%hhu", &newPat.patInfo.insr);
    flushInput();
    if (newPat.patInfo.insr > 3 || newPat.patInfo.insr < 1) {
        // Ask to reenter if input is outside the option range
        printf("Error: invalid option (choose 1 - 3).\n");
        goto enterInsr;
    }
    else {
        // Decrement the stored input (for zero-based indexing)
        newPat.patInfo.insr--;
    }

enterDept: // Choose clinic department
    printf("\nChoose patient's department\n");
    for (unsigned dep = 0; dep < 4; dep++) {
        // List all four clinic departments
        printf("[%u] %s\n", dep + 1, depName[dep]);
    }
    printf("Option: ");
    scanf("%hhu", &newPat.patTrmt.dept);
    flushInput();
    if (newPat.patTrmt.dept > 4 || newPat.patTrmt.dept < 1) {
        // Ask to reenter if input is outside the option range
        printf("Error: invalid option (choose 1 - 4).\n");
        goto enterDept;
    }
    else {
        // Decrement the stored input (for zero-based indexing)
        newPat.patTrmt.dept--;
    }

enterDoct: // Choose doctor
// Print list of available doctors in the department
    printf("\nChoose patient's doctor\n"
        "[1] %s\n"
        "[2] %s\n"
        "Option: ",
        docName[newPat.patTrmt.dept][0], docName[newPat.patTrmt.dept][1]);
    scanf("%hhu", &newPat.patTrmt.doct);
    flushInput();
    if (newPat.patTrmt.doct > 2 || newPat.patTrmt.doct < 1) {
        // Ask to reenter if input is outside the option range
        printf("Error: invalid option (choose 1 - 2).\n");
        goto enterDoct;
    }
    else {
        // Decrement the stored input (for zero-based indexing)
        newPat.patTrmt.doct--;
    }

    if (Q_enqueue(docQueue[newPat.patTrmt.dept][newPat.patTrmt.doct], &newPat) == EXIT_FAILURE) {
        // Abort if enqueue operation fails due to insufficient memory
        printf("Error: Insufficient memory to store patient's data into the doctor's queue.\n\n");
    }
    else {
        // Show all patient's data right before returning to main()
        printf("\nThe following patient:\n");
        viewPatientInfo(&newPat);
        printf("...has been queued to %s at the Department of %s (Queue no. #%c%03hu).\n\n",
            docName[newPat.patTrmt.dept][newPat.patTrmt.doct],
            depName[newPat.patTrmt.dept],
            newPat.patTrmt.dept * 2 + newPat.patTrmt.doct + 65,
            ++numQueue[0][newPat.patTrmt.dept][newPat.patTrmt.doct]);
    }
}

// Show all doctors' frontmost queue (i.e. the patient that is being treated)
void viewDoctorQueue(void) {
    Node* temp = NULL;

    for (unsigned i = 0; i < 8; i++) {
        // Show the department and the doctor's name
        printf("\n#---------------------------------------------------------------#\n"
            "| Department: %-12s | Doctor: %-26s |\n",
            depName[i / 2], docName[i / 2][i % 2]);
        if ((temp = (Node*)Q_peek(docQueue[i / 2][i % 2]))) {
            // Print patient's queue number and name if queue is not empty
            printf("| No #%c%03u | %-50s |\n",
                temp->patTrmt.dept * 2 + temp->patTrmt.doct + 65,
                numQueue[1][temp->patTrmt.dept][temp->patTrmt.doct] + 1,
                temp->patInfo.name);
        }
        else {
            // Indicate that the queue is currently empty otherwise
            printf("| No #---- | %-50s |\n", "(empty)");
        }
        printf("#---------------------------------------------------------------#\n\n");
    }
}

// Transfer patient to the pharmacy queue after examination by their doctor
void sendToPharmacy(void) {
    unsigned length;
    unsigned option;

    printf("Choose a doctor whose patient is to be sent to the pharmacy\n");
    // List all available doctors to be chosen
    for (unsigned i = 0; i < 8; i++) {
        printf("[%u] %s (%s)\n", i + 1, docName[i / 2][i % 2], depName[i / 2]);
    }

enterOption:
    printf("\nOption: ");
    scanf("%u", &option);
    flushInput();
    if (option > 8 || option < 1) {
        // Ask to reenter if choice is outside the option range
        printf("Error: invaid option.\n");
        goto enterOption;
    }
    else {
        // Decrement the choice input (for zero-based indexing later)
        option--;
    }

    Node* data = Q_peek(docQueue[option / 2][option % 2]);
    if (!data) {
        // Abort if chosen doctor's queue is empty
        printf("Error: this doctor's queue is empty.\n\n");
        return;
    }

    // Review patient's data
    printf("\nWrite diagnosis & prescription for the following patient:\n");
    viewPatientInfo(data);

enterDiag: // Enter diagnosis
    printf("\nDiagnosis (max 255 characters):\n");
    scanf("%255[^\n]%n", data->patTrmt.diag, &length);
    flushInput();
    if (length > 255) {
        // Ask to reenter if input is excessive
        printf("Error: max character amount exceeded.\n");
        goto enterDiag;
    }

    // Enter the amount of medicines
    printf("\nMedicine:\n");
    for (int med = 0; med < 4; med++) {
        printf("Amount of %-13s: ", medName[med]);
        scanf("%u", &data->patTrmt.medsAmt[med]);
        flushInput();
    }

    // Get current date of patient finishing treatment
    getCurrentTime(data->patTrmt.appt);

    if (Q_enqueue(phrQueue, data) == EXIT_FAILURE) {
        // Abort if enqueue opeartion fails due to insufficient memory
        printf("Error: Insufficient memory to store patient's data into the pharmacy queue.\n\n");
    }
    else {
        // Dequeue patient data from the doctor's queue if enqueue operation is successful
        Q_dequeue(docQueue[option / 2][option % 2]);
        printf("Patient no. #%c%03hu - %s has been moved to the pharmacy queue.\n\n",
            data->patTrmt.dept * 2 + data->patTrmt.doct + 65,
            ++numQueue[1][data->patTrmt.dept][data->patTrmt.doct],
            data->patInfo.name);
    }
}

void orderMedicines(void) {
    Node* data = Q_peek(phrQueue);
    if (!data) {
        printf("Error: the pharmacy queue is empty.\n\n");
        return;
    }
    long long unsigned total[4] = { 0 };

    printf("The following patient:\n");
    viewPatientInfo(data);
    printf("\n...has been prescribed these medicines:\n");
    for (int med = 0; med < 4; med++) {
        total[med] = data->patTrmt.medsAmt[med] * medPrice[med];
        printf("%-13s * %-3u = Rp%llu\n",
            medName[med], data->patTrmt.medsAmt[med], total[med]);
    }
    data->patTrmt.cost = total[0] + total[1] + total[2] + total[3];
    printf("--------------------------------------------------------\n\n");
    printf("%-19s = Rp%llu\n\n", "Total", data->patTrmt.cost);

    Q_dequeue(phrQueue);
    Q_enqueue(payQueue, data);
    printf("Patient %s has been moved to the payment queue.\n\n", data->patInfo.name);
}

void viewPharmacyQueue(void) {
    Node* patient = NULL;
    if ((patient = Q_peek(phrQueue))) {
        do {
            viewPatientInfo(patient);
        } while ((patient = patient->next));
        printf("--------------------------------------------------------\n\n");
    }
}

void showFinalPayment(void) {
    Node* data = Q_peek(payQueue);
    if (!data) {
        printf("Error: The payment queue is empty.\n\n");
        return;
    }

    printf("The following patient:\n");
    viewPatientInfo(data);
    printf("\n...has the following payment receipt:\n");
    printf("Medicines      = Rp%llu\n"
        "Doctor Service = Rp%u\n"
        "Administrative = Rp%u\n",
        data->patTrmt.cost,
        docPrice[data->patTrmt.dept][data->patTrmt.doct],
        depPrice[data->patTrmt.dept]);
    data->patTrmt.cost += docPrice[data->patTrmt.dept][data->patTrmt.doct] +
        depPrice[data->patTrmt.dept];
    printf("--------------------------------------------------------\n\n");
    printf("Total          = Rp%llu\n", data->patTrmt.cost);

    if (data->patInfo.insr != 2) {
        printf("Note: the costs are covered by the insurance (%s).\n\n",
            insName[data->patInfo.insr]);
    }
    else {
        printf("\n");
    }

    printf("Node %s has been removed from the payment queue.\n", data->patInfo.name);
    recordPatient(data);
}

unsigned menu(void) {
    printf("#----------------------MENU-----------------------#\n"
        "| [1] View list of doctors                        |\n"
        "| [2] Register new patient                        |\n"
        "| [3] Send patient to the pharmacy                |\n"
        "| [4] View doctor queue                           |\n"
        "| [5] Send medicines to patient in pharmacy queue |\n"
        "| [6] View pharmacy queue                         |\n"
        "| [7] Show latest patient's total costs           |\n"
        "| [8] Exit application                            |\n"
        "#-------------------------------------------------#\n\n"
        "Option: ");

    unsigned option;
    scanf("%u", &option);
    getchar();

    return option;
}

int main(void) {
    printf("-----ANGLORUM HOSPITAL MANAGEMENT APP-----\n\n");
    if (appInitiate() == EXIT_FAILURE) {
        printf("Error: unable to start app, possibly due to insufficient memory.\n\n");
        return -1;
    }

    while (1) {
        switch (menu()) {
        case 1:
            viewDoctorList();
            continue;
        case 2:
            registerPatient();
            continue;
        case 3:
            sendToPharmacy();
            continue;
        case 4:
            viewDoctorQueue();
            continue;
        case 5:
            orderMedicines();
            continue;
        case 6:
            viewPharmacyQueue();
            continue;
        case 7:
            showFinalPayment();
            continue;
        case 8:
            return 0;
        default:
            printf("Error: invalid option\n\n");
            continue;
        }
    }
}