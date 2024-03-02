#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a linked list
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

const unsigned int N = 2000; // Number of buckets in hash table

// Hash table
node *table[N];

unsigned int dictionarysize = 0;



// Hashes word to a number (my solution)
// unsigned int hash(const char *word)
// {
//     if (word == NULL) {
//         // Handle null pointer case
//         return 0; // or any other appropriate value
//     }
//     int index;
//     // TODO: Improve this hash function
//     //there are 676 slot in the table.
//     //for each starting letter, like a, b, c
//     // There are 26 slot for the second letter for that starting letter
//     // The second letter can be ' , so maybe i will have to consider some cases
//     if (word[1] == 27) {
//         index = word[0] - 'a';
//     }
//     else {
//         index = (word[0] - 'a')*26 + (word[1] - 'a');
//     }
//     return index;
// }


// // Hashes word to a number
unsigned int hash(const char *word) {
     unsigned int hashValue = 0;

     for (int i = 0; word[i] != '\0'; i++)
     {
         hashValue = (hashValue << 2) ^ word[i];
     }

     return hashValue % N;
 }

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert the input word to lowercase
    char lowercaseWord[LENGTH + 1];
    int i = 0;
    while (word[i] != '\0')
    {
        lowercaseWord[i] = tolower(word[i]);
        i++;
    }
    lowercaseWord[i] = '\0'; // Null-terminate the string

    int index = hash(lowercaseWord); // Use the lowercase word for hashing

    for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        // Compare lowercase word with lowercase dictionary words
        if (strcmp(lowercaseWord, ptr->word) == 0)
        {
            return true;
        }
    }

    return false;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        strcpy(n->word, word);
        dictionarysize++;
        n->next = NULL;

        int index = hash(n->word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarysize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
