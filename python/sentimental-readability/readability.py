def main():
    text = input("Text: ")
    sentences, words, letters = count_text(text)

    # Calculate L and S
    L = (letters / words) * 100.0000
    S = (sentences / words) * 100.0000

    # Calculate the index
    index = round(0.0588 * L - 0.2960 * S - 15.8000)

    # Output the result based on the calculated index
    if index < 1:
        print('Before Grade 1')
    elif index > 16:
        print('Grade 16+')
    else:
        print(f'Grade {index}')
def count_text(text):
    # Count sentences
    sentences = text.count('.') + text.count('!') + text.count('?')

    # Count words
    words = len(text.split())

    # Count letters
    letters = sum(c.isalpha() for c in text)

    return sentences, words, letters

main()
