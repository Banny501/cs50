/**
 * recover.c
 *
 *
 * Computer Science 50
 * Problem Set 4
 * Recovers JPEGs from a forensic image.
 */

#include "stdio.h"


int check (char *buffer)
{
  if ((buffer[0]=='\xff')&&(buffer[1]=='\xd8')&&(buffer[2]=='\xff')&&((buffer[3]>>4)=='\xfe'))
  return 1;

  return 0;
}

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover <infile>\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[1];

    // open input file
    FILE* inptr = fopen(infile, "r");

    #ifdef DEBUG
    printf("DEBUG: Open file %s\n", infile);
    #endif

    // if error printing and exit
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    char buffer [512], name [8];
    int num = 0, flag = 0, file_write = 0;

    for (size_t i = 0; i < sizeof(name); i++)
    name[i] = '0';

    for (size_t i = 0; i < sizeof(buffer); i++)
    name[i] = '0';

    FILE* outptr = NULL;

    while (fread(&buffer, sizeof(buffer), 1 , inptr)>0) {
      if (check(buffer))
      {
        if (flag)
        fclose(outptr);

        num++;
        flag = 1;
        file_write = 1;
        sprintf(name,"%03d.jpg", num);

        #ifdef DEBUG
        printf("DEBUG: Create %s\n", name);
        #endif

        outptr = fopen(name, "w");
        if (outptr == NULL)
        {
            fclose(outptr);
            fprintf(stderr, "Could not create %s.\n", name);
            return 3;
        }
      }

      if (file_write)
        fwrite(&buffer,sizeof(buffer), 1, outptr);
    }


    // close infile
    #ifdef DEBUG
    printf("DEBUG: close file %s\n", infile);
    #endif

    fclose(inptr);
    // all good
    return 0;
}
