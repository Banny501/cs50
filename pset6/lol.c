#include <stdio.h>
#include <math.h>

int check_sum(long number)
{
    int result = -1;
    int sum = 0;
    int buf = 0;
    for (int step = 1; step <= 8; step++)
    {
        buf = (2 * ((number % (long)pow(10, step * 2)) - (number % (long)pow(10, (step * 2) - 1))) / (long)pow(10, (step * 2) - 1));
        sum += buf / 10 + buf % 10;
        sum += ((number % (long)pow(10, step * 2 - 1)) - (number % (long)pow(10, step * 2 - 2))) / (long)pow(10, step * 2 - 2);
    }

    if ((sum % 10) == 0)
    {
        result = 1;
    }

    return result;
}

int main(void)
{
    long card_number = 0;
    do
    {
        card_number = get_long("Number: ");
    }
    while (card_number < 0);

    if ((card_number < pow(10, 12)) || (card_number > pow(10, 16) - 1) ||
        ((card_number > pow(10, 13) - 1) && (card_number < pow(10, 14))))
    {
        printf("INVALID\n");
        return 0;
    }

    if (check_sum(card_number) < 0)
    {
        printf("INVALID\n");
        return 0;
    }

    if ((card_number / (long)pow(10, 13) == 37) || (card_number / (long)pow(10, 13) == 34))
    {
        printf("AMEX\n");
    }
    else if ((card_number / (long)pow(10, 14) > 50) && (card_number / (long)pow(10, 14) <= 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((card_number / (long)pow(10, 12) == 4) || (card_number / (long)pow(10, 15) == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}
