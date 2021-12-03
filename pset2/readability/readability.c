#include <stdio.h>
#include <ctype.h>
#include <math.h>


int main(void)
{
    int c, flag, old_flag;
    long nc, l, s;
    l = s = nc = c = flag = old_flag = 0;
    printf("Text: ");
    while ((c = getchar()) != EOF)
    {
        old_flag = flag;
        if (isalnum(c) != 0)
        {
            nc++;
            flag = 1;
        }
        else if ((c == '\'') || (c == '-'))
        {
            flag = 1;
        }
        else
        {
            flag = 0;
        }
        if ((c == '.') || (c == '?') || (c == '!'))
        {
            s++;
        }
        if ((c == '\n') && (nc == 0))
        {
            printf("Text: ");
            continue;
            nc = 0;
        }
        else if ((c == '\n') && (nc != 0))
        {
            break;
        }
        if ((old_flag == 0) && (flag == 1))
        {
            l++;
        }
    }

    double  Lf, Sf;
    int result;
    Sf = (float)s * 100 / (float)l;
    Lf = (float)nc * 100 / (float)l;

    result = round(0.0588 * Lf - 0.296 * Sf - 15.8);

    if (result < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (result > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", result);
    }

    return 0;
}
