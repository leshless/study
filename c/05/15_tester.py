import subprocess
import random

valid_alph = "0123456789"
max_len = 5
c_program_path = "./15"

def gen_valid_equation():
    a = [valid_alph[random.randint(0, len(valid_alph) - 1)] for _ in range(random.randint(1, max_len))]
    b = [valid_alph[random.randint(0, len(valid_alph) - 1)] for _ in range(random.randint(1, max_len))]

    # eliminate leading zeros    
    a = list(str(int("".join(a))))
    b = list(str(int("".join(b))))
    
    # eval c
    c = list(str(int("".join(a)) + int("".join(b))))


    # sa = "".join(a)
    # sb = "".join(b)
    # sc = "".join(c)
    # print(f"{sa}+{sb}={sc}")

    # replace random digits with ?
    for i in range(len(a)):
        if random.random() < 0.5:
            a[i] = "?"
    for i in range(len(b)):
        if random.random() < 0.5:
            b[i] = "?"
    for i in range(len(c)):
        if random.random() < 0.5:
            c[i] = "?"
    
    sa = "".join(a)
    sb = "".join(b)
    sc = "".join(c)

    s = f"{sa}+{sb}={sc}"

    return s

def run_c_program(input):
    process = subprocess.run([c_program_path], input=input, capture_output=True, text=True)
    
    assert process.returncode == 0

    return process.stdout

def test_returned_equation_is_valid():
    input = gen_valid_equation()

    output = run_c_program(input + "\n").strip("\n")

    print(input)
    print(output)
    print("")

    a = output.split("+")[0]
    b = output.split("+")[1].split("=")[0]
    c = output.split("+")[1].split("=")[1]

    # Returned equtation is valid
    assert int(a) + int(b) == int(c)

for i in range(100):
    test_returned_equation_is_valid()
