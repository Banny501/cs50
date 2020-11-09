
#define LENGTH 45
#define NUM_OF_CHILDREN 27

typedef struct node
{
  // Маркер конца слова
  bool is_word;
  // Указатели на другие элементы
  struct node * children [NUM_OF_CHILDREN];
} Node;

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

// Procedure for print all children of node
void list_node(Node *ptr, char* name)
{
  printf("\nNode: %s\n", name);
  for (size_t i = 0; i < sizeof(ptr->children)/sizeof(&ptr); i++)
  printf("%s.children[%02ld] : %p\n", name, i, ptr->children[i]);
  printf("%s.is_word      : %d\n\n", name, ptr->is_word);
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
    //printf(" %3c %03d", word[i], word[i]);
    if (ptr->children[calculate_index(word[i])] == NULL)
      return false;
    ptr = ptr->children[calculate_index(word[i])];

    i++;
  }
  if (ptr->is_word == true)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/* Поиск элемента в префиксном дереве
function TrieLookup (root, key)
  node = root

  for i = 1 toLength(key) do
    child = GetChild(node, key[i])

    if child = NULL then
      return NULL
    end if
    node = child
  end for

    return node
  end function

  // GetChild(node, c) –возвращает указатель на дочерний узел, соответствующий символу c */


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
    #ifdef DEBUG
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%03i ", buffer[i]);
    }
    printf("\n");
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%3i ", calculate_index(buffer[i]));
    }
    printf("\n");
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%3c ", buffer[i]);
    }
    printf("\n");
    #endif

    // counter of lines
    counter++;
    // create a temp ptr on Node
    Node* tmp = root;
    // walk through the array and append nodes
    size_t num = 0;

    while (buffer[num] != '\n' && buffer[num] != '\0')
    {
      int ind = calculate_index(buffer[num]);
      if (ind < 0)
      {
        printf("ERROR: Invalid simbol in dictionary:%ld\n", counter);
        return false;
      }
      if (tmp->children[ind]==NULL)
      {
        tmp->children[ind] = malloc(sizeof(Node));
        init(tmp->children[ind]);
        tmp = tmp->children[ind];
      }
        else
      {
        tmp = tmp->children[ind];
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

  //#ifdef DEBUG
//  list_node(root, "root");
//  list_node(root->children[0], "a");
//  list_node(root->children[0]->children[26], "z");
  //list_node(root->children[0]->children[26]->children[0], "z");
  //#endif

  return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

void unload_link (Node* link)
{
  for (size_t h = 0; h < NUM_OF_CHILDREN; h++)
  {
    if (link->children[h] == NULL)
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
    Node* ptr = root->children[2];
    unload_link(ptr);

    return false;
}