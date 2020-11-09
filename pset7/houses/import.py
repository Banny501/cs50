import csv
from cs50 import SQL
from sys import exit
import argparse


def main():
    parser = argparse.ArgumentParser(description='Import', usage='python import.py file.csv')
    parser.add_argument('file', type=str, action='store')
    args = parser.parse_args()

    try:
        db = SQL("sqlite:///students.db")
        with open(args.file, 'r') as file:
            reader = csv.DictReader(file, delimiter=',')
            db.execute("DELETE FROM students")
            for row in reader:
                if len(row['name'].split()) == 3:
                    first = row['name'].split()[0]
                    middle = row['name'].split()[1]
                    last = row['name'].split()[2]
                else:
                    first = row['name'].split()[0]
                    middle = None
                    last = row['name'].split()[1]

                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           first, middle, last, row['house'], row['birth'])
    except Exception as e:
        print("ERROR :", e)
        exit(0)


if __name__ == '__main__':
    main()
