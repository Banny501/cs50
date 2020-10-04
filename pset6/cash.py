
if __name__ == '__main__':

    while (1):
        inp = input("Change owed: ")
        for i in inp.split():
            try:
                dollars = float(i)
                break
            except Exception:
                continue
        if dollars >= 0:
            cents = int(dollars * 100)
            break

    result = cents // 25
    remain = cents % 25

    result += remain // 10
    remain = remain % 10

    result += remain // 5
    remain = remain % 5

    result += remain

    print(int(result))
