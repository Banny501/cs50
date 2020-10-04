

#include "stdbool.h"
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"
#include "headers.h"



int main(int argc, char *argv[])
{

  if (argc != 2)
  {
      printf("Usage: ./test infile\n");
      return 1;
  }

  char* infile = argv[1];

  if (load(infile) == false)
  {
    printf("ERROR: Could not load dictionary\n");
    return 2;
  }

  // open dictionary
  FILE* inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
      printf("ERROR: Could not open %s.\n", infile);
      return false;
  }

  unload();
  list_node(root, "root");

  return 0;
}
