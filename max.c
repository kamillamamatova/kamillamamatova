#include <stdio.h>
#include <string.h>

#define MAXN 11
#define MAXL 100

// Stores N sequences
// Add the NULL terminator
char sequences[MAXN][MAXL + 1];
// Initialize N and L
// N: Number of sequences
// L: Length of each incantation sequence
int N, L;          
// 2 adjacent strings maximum overlap between sequences             
int maxOverlap[MAXN][MAXN];
// Record used sequences
int used[MAXN];  
// Stores the best result                
char bestRes[MAXN * MAXL + 1];
// Current string
char curRes[MAXN * MAXL + 1]; //

// Calculates the maximum overlap between two adjacent strings
int overlap(const char *a, const char *b) {
    int maxOverlap = 0;
    for (int i = 1; i <= L; i++) {
        // Compare 'a' with 'b'
        if (strncmp(a + L - i, b, i) == 0) {
            // Update the max overlap between adjacent strings
            maxOverlap = i;
        }
    }
    return maxOverlap;
}

// Recursive function to make the shortest string (incantation)
void findShortest(int level, int curLen) {
    // All sequences being used would be the best case
    if (level == N) {
        // If this result is shorter than the cur best, update bestRes
        if (strlen(bestRes) == 0 || curLen < strlen(bestRes)) {
            // Update bestRes
            strcpy(bestRes, curRes);  
        }
        return;
    }

    // Attempt to add unused sequences
    for (int i = 0; i < N; i++) {
        if (!used[i]) {
            // Sequence has been used
            used[i] = 1;

            int overlapLen = 0;
            if (level > 0) {
                // Calculate overlap with the last added sequence
                int lastUsed = -1;
                for (int j = 0; j < N; j++) {
                    if (used[j] == level) {
                        lastUsed = j;
                        break;
                    }
                }
                overlapLen = maxOverlap[lastUsed][i];
            }

            // Append the sequence to the cur result
            strcpy(curRes + curLen, sequences[i] + overlapLen);

            // Recursion
            findShortest(level + 1, curLen + L - overlapLen);

            // Backtrack
            used[i] = 0;
            curRes[curLen] = '\0';
        }
    }
}

int main() {
    // Read input
    scanf("%d %d", &N, &L);
    for (int i = 0; i < N; i++) {
        scanf("%s", sequences[i]);
    }

    // Max overlaps between all pairs of sequences
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i != j) {
                maxOverlap[i][j] = overlap(sequences[i], sequences[j]);
            }
        }
    }

    // Initialize variables
    for (int i = 0; i < N; i++) {
        used[i] = 0;
    }

    for (int i = 0; i < MAXN * MAXL + 1; i++) {
        bestRes[i] = '\0';
    }

    for (int i = 0; i < MAXN * MAXL + 1; i++) {
        curRes[i] = '\0';
    }

    // Start recursion from the first sequence
    findShortest(0, 0);

    // Print the best result found
    printf("%s\n", bestRes);

    return 0;
}
