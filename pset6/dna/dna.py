import argparse
import re
import csv
from sys import exit


def main(file_data, file_seq):

    print(file_data + ' ' + file_seq)

    # open database
    try:
        db_handler = open(file_data, 'r')
    except IOError:
            print('ERROR: can\'t open file ' + file_data)
            exit(0)

    database = list(csv.DictReader(db_handler))
    search_dict = {}

    try:
        with open(file_seq, 'r') as dna:
            for line in dna:
                for id, item in enumerate(database[0].keys()):
                    if item == 'name':
                        continue
                    res = re.findall(item, line)
                    search_dict[item] = str(len(res))
    except IOError:
        print('ERROR: can\'t open file ' + file_seq)
        exit(0)

    print('dict :  ', end='')
    print(search_dict, end='\n\n')

    for man in database:
        print(man)
        counter = 0
        for key, value in man.items():
            if key == 'name':
                name = value
            elif search_dict[key] == value:
                counter += 1
        if counter == len(man) - 1:
            print(name)
            exit(0)

    db_handler.close()
    exit(0)

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Program that identifies a person based on their DNA',
                                     usage='python %(prog)s data.csv sequence.txt')
    parser.add_argument('database', type=str, help='name of a CSV file containing the STR counts')
    parser.add_argument('sequence', type=str, help='name of a text file containing the DNA sequence to identify')
    args = parser.parse_args()
    main(args.database, args.sequence)
