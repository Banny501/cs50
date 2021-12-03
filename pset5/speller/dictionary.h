/**
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <ctype.h>
#include "stdlib.h"
#include <stdbool.h>

// maximum length for a word
#define LENGTH 45
// number of characters in the alphabet
#define NUM_OF_CHILDREN 27


// Represents a node in a trie
typedef struct node
{
  // end-of-word marker
  bool is_word;
  // pointers to other nodes
  struct node * children [NUM_OF_CHILDREN];
} Node;



/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

#endif // DICTIONARY_H
