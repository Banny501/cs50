import re


def get_grade(inp):
    text = re.sub(r'[\'.)(\]\[\{\},:;!?\\\"]', '', inp).split(' ')
    letters = 0
    for words in text:
        letters += len(words)
    letters = letters * 100 / len(text)
    sentences = len(re.findall(r'[.!?]+', inp)) * 100 / len(text)
    grade = round(0.0588 * letters - 0.296 * sentences - 15.8)
    if grade < 1:
        return 'Before Grade 1'
    elif grade > 16:
        return 'Grade 16+'
    else:
        return 'Grade ' + str(grade)


if __name__ == '__main__':
    while (1):
        text = input('Text: ')
        if len(text.split()) > 0:
            break
    print(get_grade(text))
