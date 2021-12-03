import argparse

from cs50 import SQL

DATABASE_FILE = "sqlite:///students.db"


def main():
    parser = argparse.ArgumentParser(description='Roster', usage='python roster.py house')
    parser.add_argument('house', type=str, action='store')
    args = parser.parse_args()

    db = SQL(DATABASE_FILE)
    result = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", args.house)
    for row in result:
        if row['middle']:
            print(row['first'], row['middle'], row['last'] + ', born', row['birth'])
        else:
            print(row['first'], row['last'] + ', born', row['birth'])


if __name__ == '__main__':
    main()
