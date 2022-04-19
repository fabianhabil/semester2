#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 2501976503 - Fabian Habil Ramdhan - Nomber 2 UTS Data Structures.

// Declare Array 30 data incase memory leak, 1 - 26 is alphabets.
int huruf[30];

// Procedure "random word"
void reverseWord(char sentence[]) {
    int length = strlen(sentence);
    printf("%crandom word%c : ", '"', '"');
    // Loop from last index of the sentence string.
    for (int i = length - 1; i >= 0; i--) {
        // If space = skip loop this iteration.
        if (sentence[i] == 32) {
            continue;
        }
        else {
            // If alphabets is lowercase.
            if (sentence[i] >= 97 && sentence[i] <= 122) {
                // Example a is 97 in ascii.
                // To make a in index 1, substract by 97 and addition by 1.
                // So sentence[1] is 1 now, and its already confirmed that a is already printed.
                if (huruf[sentence[i] - 97 + 1] == 0) {
                    huruf[sentence[i] - 97 + 1]++;
                    printf("%c", sentence[i]);
                }
                else {
                    continue;
                }
            }
            // Jika huruf besar atau uppercase.
            if (sentence[i] >= 65 && sentence[i] <= 90) {
                // Example a is 65 in ascii.
                // To make a in index 1, substract by 65 and addition by 1.
                // So sentence[1] is 1 now, and its already confirmed that a is already printed.
                if (huruf[sentence[i] - 65 + 1] == 0) {
                    huruf[sentence[i] - 65 + 1]++;
                    printf("%c", sentence[i]);
                }
                else {
                    continue;
                }
            }
            else {
                // If not letter = skip loop this iteration.
                continue;
            }
        }
    }
}

int main() {
    system("cls");
    // Declare string for input.
    char sentence[101];
    puts("Soal No 2 - Data Structures UTS - Fabian Habil");
    // Input sentence from user.
    printf("Masukkan Sentence (maksimal 100 karakter): ");
    scanf(" %[^\n]", sentence);
    // Call procedure to find "random word".
    reverseWord(sentence);
}