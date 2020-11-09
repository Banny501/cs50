import argparse
import csv
from sys import exit


def find_num(str, find):
    num = 0
    old = str.find(find)
    count = 0
    result = 0
    flag = 0
    while 1:
        num = str.find(find, num + flag)
        flag = 1
        if num < 0:
            break
        else:
            if (num - old) > len(find):
                count = 1
            else:
                count += 1
            old = num
            if count > result:
                result = count
    return result


def main(database, dna_file):
    dna = ''

    try:
        with open(dna_file, 'r') as file:
            for line in file:
                dna += line.strip()
    except Exception as e:
        print('ERROR: ', e)

    try:
        with open(database, 'r') as file:
            reader = csv.reader(file)
            headers = next(reader)
            people = []
            dna_list = []

            for row in reader:
                people.append(list(row))

            for item in range(1, len(headers)):
                dna_list.append(str(find_num(dna, headers[item])))

            for man in people:
                counter = 0
                for item in range(1, len(man)):
                    if man[item] == dna_list[item-1]:
                        counter += 1

                if counter == len(dna_list):
                    return man[0]
                    exit(0)
            return 'No match'

    except Exception as e:
        print('ERROR: ', e)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='DNA', usage='python dna.py data.csv sequence.txt')
    parser.add_argument('database', type=str, action='store')
    parser.add_argument('dna_file', type=str, action='store')
    args = parser.parse_args()
    print(main(args.database, args.dna_file))
