#include <ctype.h>
#include <stdbool.h>

#define FNV_OFFSET_BASIS_32 2166136261
#define FNV_PRIME_32 16777619

#include "dictionary.h"

typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 26;

unsigned int total_words = 0;

node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
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

    return hash;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    return false;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
