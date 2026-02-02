a = 6
c = 34
p = 41

for b in range(41):
    if a ** b % p == c:
        print(b)
        break