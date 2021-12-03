#include <stdio.h>
#include <cs50.h>


int main(int argc, char const *argv[])
{
    int height = 0;
    do
    {
        height = get_int("Height: ");
    }
    while ((height <= 0) || (8 < height));

    for (int line = 0; line < height; line++)
    {
        for (int space = 1; space < height - line; space++)
        {
            printf(" ");
        }

        for (int hash = 0; hash < line + 1; hash++)
        {
            printf("#");
        }
        printf("  ");

        for (int hash = 0; hash < line + 1; hash++)
        {
            printf("#");
        }
        printf("\n");
    }

    return 0;
}
