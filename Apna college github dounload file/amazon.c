#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_LENGTH 100

// Function to check if a word is in complaint list
int isComplaintWord(char *word, char complaints[][MAX_LENGTH], int m) {
    for (int i = 0; i < m; i++) {
        if (strcmp(word, complaints[i]) == 0)
            return 1;
    }
    return 0;
}

int getComplaintCount(char complaints[][MAX_LENGTH], int m, char transcripts[][1000], int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        char temp[1000];
        strcpy(temp, transcripts[i]); // Copy transcript to temp so we can tokenize it
        char *word = strtok(temp, " ");

        char foundWords[MAX_WORDS][MAX_LENGTH];
        int foundCount = 0;

        while (word != NULL) {
            if (isComplaintWord(word, complaints, m)) {
                // Check if this complaint word is already found
                int alreadyFound = 0;
                for (int k = 0; k < foundCount; k++) {
                    if (strcmp(foundWords[k], word) == 0) {
                        alreadyFound = 1;
                        break;
                    }
                }
                if (!alreadyFound) {
                    strcpy(foundWords[foundCount], word);
                    foundCount++;
                }
            }
            word = strtok(NULL, " ");
        }

        if (foundCount >= 2) {
            count++;
        }
    }

    return count;
}

int main() {
    int m, n;
    scanf("%d", &m);

    char complaints[m][MAX_LENGTH];
    for (int i = 0; i < m; i++) {
        scanf("%s", complaints[i]);
    }

    scanf("%d", &n);
    char transcripts[n][1000];
    getchar(); // consume newline

    for (int i = 0; i < n; i++) {
        fgets(transcripts[i], 1000, stdin);
        transcripts[i][strcspn(transcripts[i], "\n")] = 0; // Remove newline
    }

    int result = getComplaintCount(complaints, m, transcripts, n);
    printf("%d\n", result);

    return 0;
}
