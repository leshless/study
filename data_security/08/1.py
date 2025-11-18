ALPHABET = "".join([chr(i) for i in range(ord('A'), ord('Z') + 1)]) + \
" .?$" + \
"".join([chr(i) for i in range(ord('0'), ord('9') + 1)])
LENGTH = len(ALPHABET)

N = 9797
E = 107

def pow_mod(a: int, b: int, m: int) -> int:
    if b == 1:
        return a % m

    if b % 2 == 0:
        r = pow_mod(a, b // 2, m)
        return (r * r) % m
    
    return (pow_mod(a, b - 1, m) * a) % m

def encrypt(message: str) -> str:
    encrypted_message = ""

    for i in range(0, len(message), 2):
        bigram = list(message)[i: i+2]

        m = ALPHABET.index(bigram[0]) * LENGTH + ALPHABET.index(bigram[1])
        c = pow_mod(m, E, N)

        trigram = ""
        while c > 0:
            trigram += ALPHABET[c % LENGTH]
            c //= LENGTH

        trigram = "".join(reversed(trigram))
        
        while len(trigram) < 3:
            trigram = ALPHABET[0] + trigram

        encrypted_message += trigram

    return encrypted_message

print(encrypt("GET 123$"))