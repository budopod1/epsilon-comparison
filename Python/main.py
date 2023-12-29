from collections import Counter
from enum import Enum


LetterResponse = Enum("LetterResponse", ["GRAY", "ORANGE", "GREEN"])


def find_best_word(words):
    freq = Counter("".join(words))
    return max(words, key=lambda word: sum(map(freq.get, set(word))))


def get_wordle_response(guess, target):
    return [
        (LetterResponse.GREEN if guess_char == target_char else (
            LetterResponse.ORANGE if guess_char in target else
            LetterResponse.GRAY
        ))
        for guess_char, target_char in zip(guess, target)
    ] 


def filter_words_given_response(words, response, guess):
    return list(filter(
        lambda word: all([
            (word[i] == guess) 
                if lresponse == LetterResponse.GREEN else 
            (
                (guess not in word) 
                    if lresponse == LetterResponse.GRAY else 
                (word[i] != guess and guess in word)
            )
            for i, (lresponse, guess) in enumerate(zip(response, guess))
        ]), words
    ))


def do_wordle(words, target):
    for i in range(6):
        guess = find_best_word(words)
        if guess == target:
            return True
        response = get_wordle_response(guess, target)
        words = filter_words_given_response(words, response, guess)
    return False


def main():
    with open("words.txt") as file:
        words = list(map(str.strip, file.readlines()))

    succeeded = 0
    failed = 0
    
    for target in words:
        success = do_wordle(words, target)
        if success:
            succeeded += 1
        else:
            failed += 1

    print("Succeeded:", succeeded)
    print("Failed:", failed)


if __name__ == "__main__":
    main()
