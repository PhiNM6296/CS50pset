#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    // Check if the user provided a file path as an argument
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    // Open the dictionary file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("File not found or unable to open.\n");
        return 1;
    }

    char word[50];
    char letter;
    int count[26] = {0}; // Array to store counts for each letter

    // Read each word from the file
    while (fscanf(file, "%s", word) != EOF) {
        // Convert the first letter to lowercase
        letter = tolower(word[0]);

        // Check if the character is a lowercase letter
        if (isalpha(letter)) {
            // Increment the count for the corresponding letter
            count[letter - 'a']++;
        }
    }

    // Close the file
    fclose(file);

    // Output the counts for each letter
    for (int i = 0; i < 26; i++) {
        printf("Words begin with %c: %d\n", 'a' + i, count[i]);
    }

    return 0;
}
