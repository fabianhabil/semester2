#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Nomber 5 UTS Data Structures.

// Struct untuk menyimpan data pasien.
struct dataPasien {
    char nama[50];
    char dob[15];
    int umur;
    char alamat[50];
    // 0 = bpjs, 1 = inhealth, 2 = mandiri
    int status;
    // Setiap pasien mempunyai treatment.
    struct treatment;
};

// Struct untuk menyimpan treatment data.
struct treatment {
    char date[15];
    char clinicname[30];
    char doctorname[50];
    char diagnoses[50];
    char medications[50];
    int costs;
};

// Struct untuk menyimpan 


int main() {

}