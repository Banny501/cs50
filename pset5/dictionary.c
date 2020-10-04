/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"

// I knov that global var is not good
Node *root = NULL;

// Procedure for normal work node after initiate
void init(Node *ptr)
{
  for (size_t i = 0; i < sizeof(ptr->children)/sizeof(&ptr); i++)
  {
    ptr->children[i] = NULL;

  }
  ptr->is_word = NULL;
}

int calculate_index(char simbol)
{
  // calculate index of simbol and check
  int res = tolower(simbol) - 'a';
  if (res == -58) // special okkasion for '
    res = 26;

  if (res < 0 || res > 26 )
  {
    return -1;
  }
  return res;
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
  Node* ptr = root;
  size_t i = 0;
  while (word[i]!=0)
  {
    if (ptr->children[calculate_index(word[i])] == NULL)
      return false;
    ptr = ptr->children[calculate_index(word[i])];
    i++;
  }
  if (ptr->is_word == true)
    return true;
  else
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
  // open dictionary
  FILE* inptr = fopen(dictionary, "r");
  if (inptr == NULL)
  {
      printf("ERROR: Could not open %s.\n", dictionary);
      return false;
  }

  // create first node
  if ((root = malloc(sizeof(Node))) == NULL)
  {
    printf("ERROR: Could not get memory for root\n");
    return false;
  }
  init(root);

  char buffer [LENGTH+2];
  for (size_t h = 0; h < sizeof(buffer); h++)
    buffer[h] = 0;

  unsigned long counter = 0;

  while (fgets(buffer, sizeof(buffer), inptr) != NULL)
  {
    // counter of lines
    counter++;
    // create a temp ptr on Node
    Node* tmp = root;
    // walk through the array and append nodes
    size_t num = 0;

    while (buffer[num] != 10 && buffer[num] != 0)
    {
      // calculate index of simbol and check
      int index = tolower(buffer[num]) - 'a';
      if (index == -58) // special okkasion for '
        index = 26;

      if (index < 0 || index > 26 )
      {
        printf("ERROR: Invalid symbol in dictionary:%ld\n", counter);
        return false;
      }

      if (tmp->children[index]==NULL)
      {
        tmp->children[index] = malloc(sizeof(Node));
        init(tmp->children[index]);
        tmp = tmp->children[index];
      }
        else
      {
        tmp = tmp->children[index];
      }

      if (buffer[num+1] == 10 || buffer[num+1] == 0)
      {
        tmp->is_word = true;
      }

      num++;
    }
    // clear array
    for (size_t h = 0; h <= num; h++)
      buffer[h] = 0;
  }

  fclose(inptr);

  return true;
}

unsigned int calc_size(Node* link)
{
  unsigned int result = 0;
  for (size_t i = 0; i < NUM_OF_CHILDREN; i++)
  {
    if (link->children[i] != NULL)
    {
      Node* tmp = link->children[i];
      result+=calc_size(tmp);
    }
  }
  if (link->is_word > 0)
  {
    result++;
  }
  return result;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return calc_size(root);
}

void unload_link (Node* link)
{
  for (size_t h = 0; h < NUM_OF_CHILDREN; h++)
  {
    if (link->children[h] != NULL)
    {
      Node* tmp = link->children[h];
      unload_link(tmp);
    }
  }
  free(link);
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    unload_link(root);
    return true;
}
