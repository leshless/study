import re
import sys

def shift(i):
    def f(c):
        return chr(ord("a") + (ord(c) - ord("a") + i) % 26)

    return f

def main():
    alphabet = re.compile(r"[a-z]*")
    word = input()

    if alphabet.fullmatch(word) == None:
        print("String should only contain lowercase english letters")
        sys.exit(1)
    
    for i in range(26):
        shifted_word = "".join(map(shift(i), list(word)))
        print(f"+{i}: {shifted_word}")


if __name__ == "__main__":
    main()