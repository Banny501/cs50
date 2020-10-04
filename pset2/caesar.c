#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (size_t i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    printf("plaintext:  ");
    int c;
    size_t counter = 0;
    char buff [124];
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        buff[counter] = c;
        counter++;
    }

    printf("ciphertext: ");
    for (size_t a = 0; a < counter; a++)
    {
        if ((buff[a] <= 122) && (buff[a] >= 97))
        {
            printf("%c", (buff[a] - 97 + atoi(argv[1])) % 26 + 97);
        }
        else if ((buff[a] <= 90) && (buff[a] >= 65))
        {
            printf("%c", (buff[a] - 65 + atoi(argv[1])) % 26 + 65);
        }
        else
        {
            printf("%c", buff[a]);
        }
    }
    printf("\n");

    return 0;
}
