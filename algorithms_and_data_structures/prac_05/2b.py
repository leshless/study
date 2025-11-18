alph = list(range(-48, -38)) + list(range(-31, -5)) + list(range(1, 27))

for p in range(1, 32):
    neutrals = []
    for s2 in alph:
        s1 = -s2 * p
        if s1 in alph:
            neutrals.append(chr(s1 + ord("a") - 1) + chr(s2 + ord("a") - 1))
    print(f"p = {p}: {neutrals}")