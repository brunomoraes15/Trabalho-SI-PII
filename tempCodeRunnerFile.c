#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 100
#define MAX_LEN 100
#define ASCII_RANGE 256  // ASCII characters range

// Counting sort for a single position in the word (used in radix style)
void countingSort(char arr[MAX_WORDS][MAX_LEN], int n, int pos) {
    char output[MAX_WORDS][MAX_LEN];
    int count[ASCII_RANGE] = {0};

    // Count frequency of each character at position pos
    for (int i = 0; i < n; i++) {
        char c = (pos < strlen(arr[i])) ? tolower(arr[i][pos]) : 0;
        count[(unsigned char)c]++;
    }

    // Compute cumulative count
    for (int i = 1; i < ASCII_RANGE; i++)
        count[i] += count[i - 1];

    // Build output array (stable sort)
    for (int i = n - 1; i >= 0; i--) {
        char c = (pos < strlen(arr[i])) ? tolower(arr[i][pos]) : 0;
        strcpy(output[--count[(unsigned char)c]], arr[i]);
    }

    // Copy back to original array
    for (int i = 0; i < n; i++)
        strcpy(arr[i], output[i]);
}

// Sorts words alphabetically using counting sort logic
void alphabeticalSort(char arr[MAX_WORDS][MAX_LEN], int n) {
    int maxLen = 0;
    for (int i = 0; i < n; i++)
        if (strlen(arr[i]) > maxLen)
            maxLen = strlen(arr[i]);

    // Sort from last character to first (radix-like approach)
    for (int pos = maxLen - 1; pos >= 0; pos--)
        countingSort(arr, n, pos);
}

int main() {
    FILE *file = fopen("data_fixed.csv", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[10000];
    char words[MAX_WORDS][MAX_LEN];
    int count = 0;

    // Read CSV line
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        while (token && count < MAX_WORDS) {
            // Remove whitespace and newlines
            token[strcspn(token, "\r\n")] = 0;
            strcpy(words[count++], token);
            token = strtok(NULL, ",");
        }
    }
    fclose(file);

    // Sort alphabetically
    alphabeticalSort(words, count);

    // Output sorted words
    printf("Sorted words:\n");
    for (int i = 0; i < count; i++)
        printf("%s\n", words[i]);

    // Optionally write back to file
    FILE *out = fopen("sorted.csv", "w");
    if (out) {
        for (int i = 0; i < count; i++) {
            fprintf(out, "%s", words[i]);
            if (i < count - 1) fprintf(out, ",");
        }
        fclose(out);
    }

    return 0;
}
