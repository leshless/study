import random
import numpy as np
import itertools

N = 4
P = 5

def random_elem():
    return random.randint(1, P-1)

def random_row():
    return np.array([random.randint(0, P-1) for _ in range(N)])

def random_mat():
    return np.vstack([random_row() for _ in range(N)])

def in_linear_span(rows, row):
    for coefs in itertools.combinations_with_replacement(range(0, P), len(rows)):
        lc = sum([rows[i] * coefs[i] for i in range(len(rows))])

        if (lc == row).all():
            return True

    return False

def gen_first_sss():
    A: np.array

    # while True:
    #     a1 = random_row()
    #     l1 = random_elem()
    #     a2 = random_row()
    #     l2 = random_elem()

    #     a0 = (a1 * l1 + a2 * l2) % P

    #     a3 = random_row()
    #     l3 = random_elem()

    #     a4 = (a0 - a3 * l3) % P

    #     flags = np.array([
    #         in_linear_span([a1, a2], a0),
    #         in_linear_span([a3, a4], a0),
    #         not in_linear_span([a1], a0),
    #         not in_linear_span([a2], a0),
    #         not in_linear_span([a3], a0),
    #         not in_linear_span([a4], a0),
    #         not in_linear_span([a1, a4], a0),
    #         not in_linear_span([a2, a3], a0),
    #     ])
        
    #     if flags.all():
    #         A = np.vstack([a0, a1, a2, a3, a4]) 
    #         break
        

    A = np.array([
        [5, 6, 5, 4, 4],
        [3, 2, 5, 1, 0],
        [2, 4, 0, 3, 4],
        [4, 0, 1, 1, 3],
        [1, 6, 4, 3, 1],
    ])
    
    v = random_row()

    s = np.dot(A, v) % P

    print(f"P={P}")
    print(f"MATRIX:\n{A}")           
    print(f"SECRET:\n{v.reshape(-1, 1)}")
    print(f"SHARES:\n{s.reshape(-1, 1)}")         

def gen_second_sss():
    A: np.array

    while True:
        a1 = random_row()
        l1 = random_elem()
        a2 = random_row()
        l2 = random_elem()
        a3 = random_row()
        l3 = random_elem()

        a0 = (a1 * l1 + a2 * l2 + a3 * l3) % P

        a4 = a0
        
        flags = np.array([
            in_linear_span([a1, a2, a3], a0),
            in_linear_span([a4], a0),
            not in_linear_span([a1, a2], a0),
            not in_linear_span([a1, a3], a0),
            not in_linear_span([a2, a3], a0),
        ])
        
        if flags.all():
            A = np.vstack([a0, a1, a2, a3, a4]) 
            break
        
    v = random_row()

    s = np.dot(A, v) % P

    print(f"P={P}")
    print(f"MATRIX:\n{A}")           
    print(f"SECRET:\n{v.reshape(-1, 1)}")
    print(f"SHARES:\n{s.reshape(-1, 1)}")

def gen_example_sss():
    while True:
        A = random_mat()

        flags = np.array([
            in_linear_span([A[1], A[2]], A[0]),
            in_linear_span([A[1], A[3]], A[0]),
            in_linear_span([A[2], A[3]], A[0]),
            not in_linear_span([A[1]], A[0]),
            not in_linear_span([A[2]], A[0]),
            not in_linear_span([A[3]], A[0]),
        ])

        if flags.all():
            print(A)
            break
    
    v = random_row()

    s = np.dot(A, v) % P

    print(f"P={P}")
    print(f"MATRIX:\n{A}")           
    print(f"SECRET:\n{v.reshape(-1, 1)}")
    print(f"SHARES:\n{s.reshape(-1, 1)}")

def main():
    # gen_first_sss()
    # gen_second_sss()
    gen_example_sss()


if __name__ == "__main__":
    main()
