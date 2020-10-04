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

  char buffer [LENGTH+1];
  for (size_t h = 0; h < sizeof(buffer); h++)
    buffer[h] = 0;

  unsigned long counter = 0;

  while (fgets(buffer, sizeof(buffer), inptr) != NULL)
  {
    counter++;
    #ifdef DEBUG
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%03i ", buffer[i]);
    }
    printf("\n");
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%3i ", tolower(buffer[i]) - 'a');
    }
    printf("\n");
    for (size_t i = 0; i < sizeof(buffer); i++)
    {
      printf("%3c ", buffer[i]);
    }
    printf("\n");
    #endif

    // create a temp ptr on Node
    Node* tmp = root;

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


    for (size_t h = 0; h < sizeof(buffer); h++)
      buffer[h] = 0;
  }


  fclose(inptr);

  //#ifdef DEBUG
  list_node(root, "root");
  list_node(root->children[0], "a");
//  list_node(root->children[0]->children[26], "z");
  //list_node(root->children[0]->children[26]->children[0], "z");
  //#endif

    return true;
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
