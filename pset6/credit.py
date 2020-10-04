from sys import exit

def check_sum(number):
    buf = 0
    for ch in range(len(number), 1, 2):
        buf += int(number[ch]) * 2 // 10 + int(number[ch]) * 2 % 10

    for c in range(len(number), 0, 2):
        buf += int(number[c])

    if buf % 10 == 0:
        return 1
    else:
        return -1

if __name__ == '__main__':
    while (1):
        card_number = input("Number: ")
        if card_number.isdigit() and int(card_number) > 0:
            break

    if len(card_number) < 13 or len(card_number) > 16 or len(card_number) == 14:
        print("INVALID1")
        exit(0)

    if check_sum(card_number) < 0:
        print("INVALID2")
        exit(0)

    if card_number[0] == '4':
        print("VISA")
        exit(0)
    elif int(card_number[0:2]) > 50 and int(card_number[0:2]) < 56:
        print("MASTERCARD")
        exit(0)
    elif card_number[0:2] == '34' or card_number[0:2] == '37':
        print("AMEX")
        exit(0)
    else:
        print("INVALID3")
        exit(0)
