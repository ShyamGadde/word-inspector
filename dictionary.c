#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#define FNV_OFFSET_BASIS_32 2166136261
#define FNV_PRIME_32 16777619

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 214000;

unsigned int total_words = 0;

node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_index = hash(word);

    for (node *cursor = table[hash_index]; cursor != NULL; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}


// Uses FNV-1a hashing algorithm
unsigned int hash(const char *word)
{
    unsigned int hash = FNV_OFFSET_BASIS_32;
    const unsigned char *s = (const unsigned char *)word;

    while (*s)
    {
        hash ^= *s++;
        hash *= FNV_PRIME_32;
    }

    return hash % N;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Creating a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain a hash value
        int hash_index = hash(word);

        // Insert node into hash table at that location
        if (table[hash_index] == NULL)
        {
            table[hash_index] = n;
        }
        else
        {
            n->next = table[hash_index];
            table[hash_index] = n;
        }
        total_words++;
    }
    fclose(file);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return total_words;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        for (node *head = table[i]; head != NULL;)
        {
            node *cursor = head->next;
            free(head);
            head = cursor;
        }
    }
    return true;
}
