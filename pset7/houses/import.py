import argparse
import csv
from sys import exit

from cs50 import SQL

DATABASE_FILE = "sqlite:///students.db"


def main():
    parser = argparse.ArgumentParser(description='Import', usage='python import.py file')
    parser.add_argument('file', type=str, action='store')
    args = parser.parse_args()

    try:
        db = SQL(DATABASE_FILE)
        # delete old data
        db.execute("DELETE FROM students")
        with open(args.file, 'r') as file:
            reader = csv.DictReader(file, delimiter=',')
            for row in reader:
                if len(row['name'].split()) == 3:
                    first = row['name'].split()[0]
                    middle = row['name'].split()[1]
                    last = row['name'].split()[2]
                else:
                    first = row['name'].split()[0]
                    middle = ""
                    last = row['name'].split()[1]

                db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                           first, middle, last, row['house'], row['birth'])
    except Exception as e:
        print("ERROR :", e)
        exit(0)


if __name__ == '__main__':
    main()
