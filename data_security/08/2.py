def factorize(n: int) -> list[int]:
    factors = []

    for i in range(2, n-1):
        while n % i == 0:
            factors.append(i)
            n //= i
        
        if n == 1:
            break

    return factors

def reverse_mod(a: int, m: int) -> int | None:
    for i in range(2, m):
        if (a * i) % m == 1:
            return i
    
    return None

ALPHABET = "".join([chr(i) for i in range(ord('A'), ord('Z') + 1)]) + \
" .?$" + \
"".join([chr(i) for i in range(ord('0'), ord('9') + 1)])
LENGTH = len(ALPHABET)

N = 9797
D = 2243

def pow_mod(a: int, b: int, m: int) -> int:
    if b == 1:
        return a % m

    if b % 2 == 0:
        r = pow_mod(a, b // 2, m)
        return (r * r) % m
    
    return (pow_mod(a, b - 1, m) * a) % m

def decrypt(encrypted_message: str) -> str:
    message = ""

    for i in range(0, len(encrypted_message), 3):
        trigram = list(encrypted_message)[i: i+3]

        c = ALPHABET.index(trigram[0]) * LENGTH**2 + ALPHABET.index(trigram[1]) * LENGTH + ALPHABET.index(trigram[2])
        m = pow_mod(c, D, N)

        bigram = ""
        while m > 0:
            bigram += ALPHABET[m % LENGTH]
            m //= LENGTH

        bigram = "".join(reversed(bigram))
        
        while len(bigram) < 2:
            bigram = ALPHABET[0] + bigram

        message += bigram

    return message

print(decrypt("CUAF0OCHHF92"))