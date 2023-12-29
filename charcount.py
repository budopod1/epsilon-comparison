#!/usr/bin/env python3
import sys


def main():
    if len(sys.argv) < 2:
        sys.exit("Not enough arguments")

    path = sys.argv[1]

    try:
        with open(path) as file:
            text = file.read()
    except IOError:
        sys.exit("Failed to read file")

    whitespace = " \n\t"

    print(len(text) - sum(map(text.count, whitespace)))


if __name__ == "__main__":
    main()
