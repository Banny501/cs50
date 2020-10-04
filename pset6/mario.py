

if __name__ == '__main__':
    while (1):
        dollars = input("dollars : ")
        if dollars.isdigit() and int(dollars) > 0:
            cents = int(dollars) * 100
            break

    print(cents)
