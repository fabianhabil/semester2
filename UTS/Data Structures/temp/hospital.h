#ifndef HOSPITAL_H
#define HOSPITAL_H

#define RECORD_FILE "released_patient_record.txt"

/*------------------------------Data Structure--------------------------------*/

/* First patient subdata struct,
   containing patient's personal information (private) */
struct Info {
    char name[51];              // Name
    char addr[128];             // Home address
    char DOB[11];               // Date of birth
    unsigned char insr;         // Insurance
    unsigned age;               // Age
};

/* Second patient subdata struct,
   containing patient's treatment information (private) */
struct Trmt {
    char diag[256];           // Diagnosis
    char appt[11];            // Date of appointment
    unsigned char dept;       // Chosen clinic department
    unsigned char doct;       // Chosen #%c%03hu
    unsigned medsAmt[4];      // Amount of medicines (4 types)
    long long unsigned cost;  // Total treatment cost
};

/* Node (patient data) struct, based on linked list (public) */
typedef struct Node {
    struct Info patInfo;     // First subdata
    struct Trmt patTrmt;     // Second subdata
    struct Node* next;        // Pointer to the next node
} Node;

/* Queue struct container, based on linked list (public) */
typedef struct Queue {
    Node* rear;               // Latest node added into the queue
    Node* front;              // Oldest node added into the queue
} Queue;

/*--------------------------------Variables-----------------------------------*/

/* The name of the medicines, the insurance, the clinic departments, and the #%c%03hus */
const char* medName[4] = { "Solifenacin", "Fluoxetine", "Isotretinoin", "Digoxin" };
const char* insName[3] = { "BPJS", "Inhealth", "None" };
const char* depName[4] = { "Urology", "Psychiatry", "Dermatology", "Cardiology" };
const char* docName[4][2] = { "dr. Hendry Ramadhan, Sp.U", "dr. Dedi Putri, Sp.U",
                              "dr. Santi Maya, Sp.KJ", "dr. Nanda Fatimah, Sp.KJ",
                              "dr. Rama Putra, Sp.DV", "dr. Evan Ho, Sp.DV",
                              "dr. Natasha Levina, Sp.JP", "dr. Elis Agung, Sp.JP" };

/* The cost of the medicines, the administrative fees, and the #%c%03hu's service */
const unsigned medPrice[4] = { 14300, 28100, 57000, 34700 };
const unsigned depPrice[4] = { 31000, 29000, 30000, 32000 };
const unsigned docPrice[4][2] = { 2296100, 2870200,
                                 2726400, 2205900,
                                 2152800, 2511556,
                                 2942108, 2683600 };

/* Multidimensional array to store patient's queue number
   Number format: #XYYY
   X: Doctor's code (A - H)
   YYY: The 3-digit queue number
   Example: #F032 -> dr. Evan Ho's queue, number 32 */
short unsigned numQueue[2][4][2] = { 0 };

/* The queues */
Queue* docQueue[4][2]; // The doctors' queue
Queue* phrQueue;       // The pharmacy queue
Queue* payQueue;       // The payment queue

/*---------------------------------Functions----------------------------------*/

/* Queue-related functions */
Queue* Q_initiate(void);                            // Initiates queue
int   Q_enqueue(Queue*, const Node*);             // Stores a node into a queue
int   Q_dequeue(Queue*);                           // Releases a node from a queue
Node* Q_peek(const Queue*);                       // Returns data of the frontmost node in a queue

/* Miscellaneous functions */
static void flushInput(void);                       // Flushes input
static void getCurrentTime(char*);                 // Get the current date in the form of a string ("dd/mm/yyyy")
static int  appInitiate(void);                      // Initiates app functionality by preallocating every queue

/* Main app functions */
unsigned menu(void);                                // Shows menu and returns chosen option
void     viewPatientInfo(Node* data);
void     recordPatient(Node* data);                 // Archives the data of every patient that has finished treatment
void     viewDoctorList(void);                      // Prints list of #%c%03hus
void     registerPatient(void);                        // Registers new patient's data and stores it into the #%c%03hu's queue
void     viewDoctorQueue(void);                     // Prints current patient's name & queue number of every #%c%03hu
void     sendToPharmacy(void);                      // Sends a patient from their #%c%03hu's queue to the pharmacy queue
void     orderMedicines(void);                      // Prescribe medicines to a patient in the pharmacy queue
void     viewPharmacyQueue(void);                   // Prints every patient data in the pharmaccy queue
void     showFinalPayment(void);                    // Prints total payment to the patient

#endif