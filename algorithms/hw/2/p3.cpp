#include <vector>
#include <cmath>
#include <iostream>

const int THRESHOLD = 64;

#define mat std::vector<std::vector <long long>>

mat add(int n, mat& a, int ai, int aj, mat&b, int bi, int bj) {
    mat res(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[ai+i][aj+j] + b[bi+i][bj+j];
        }
    }

    return res;
}

mat sub(int n, mat& a, int ai, int aj, mat&b, int bi, int bj) {
    mat res(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] = a[ai+i][aj+j] - b[bi+i][bj+j];
        }
    }

    return res;
}

mat naive_mul(int n, mat& a, int ai, int aj, mat&b, int bi, int bj) {
    mat res(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int r = 0; r < n; r++) {
                res[i][j] += a[ai+i][aj+r] * b[bi+r][bj+j];
            }
        }
    }
    
    return res;
}

mat mul(int n, mat& a, int ai, int aj, mat&b, int bi, int bj) {
    if (n <= THRESHOLD) {
        return naive_mul(n, a, ai, aj, b, bi, bj);
    }

    int half = n / 2;
    
    mat s1 = sub(half, b, bi, bj + half, b, bi + half, bj + half); // B12 - B22
    mat s2 = add(half, a, ai, aj, a, ai, aj + half);               // A11 + A12
    mat s3 = add(half, a, ai + half, aj, a, ai + half, aj + half); // A21 + A22
    mat s4 = sub(half, b, bi + half, bj, b, bi, bj);               // B21 - B11
    mat s5 = add(half, a, ai, aj, a, ai + half, aj + half);        // A11 + A22
    mat s6 = add(half, b, bi, bj, b, bi + half, bj + half);        // B11 + B22
    mat s7 = sub(half, a, ai, aj + half, a, ai + half, aj + half); // A12 - A22
    mat s8 = add(half, b, bi + half, bj, b, bi + half, bj + half); // B21 + B22
    mat s9 = sub(half, a, ai, aj, a, ai + half, aj);               // A11 - A21
    mat s10 = add(half, b, bi, bj, b, bi, bj + half);              // B11 + B12

    mat p1 = mul(half, a, ai, aj, s1, 0, 0);       // A11 × (B12 - B22)
    mat p2 = mul(half, s2, 0, 0, b, bi + half, bj + half); // (A11 + A12) × B22
    mat p3 = mul(half, s3, 0, 0, b, bi, bj);       // (A21 + A22) × B11
    mat p4 = mul(half, a, ai + half, aj + half, s4, 0, 0); // A22 × (B21 - B11)
    mat p5 = mul(half, s5, 0, 0, s6, 0, 0);        // (A11 + A22) × (B11 + B22)
    mat p6 = mul(half, s7, 0, 0, s8, 0, 0);        // (A12 - A22) × (B21 + B22)
    mat p7 = mul(half, s9, 0, 0, s10, 0, 0);       // (A11 - A21) × (B11 + B12)
    
    mat temp1 = add(half, p5, 0, 0, p4, 0, 0);
    mat temp2 = sub(half, temp1, 0, 0, p2, 0, 0);
    mat c11 = add(half, temp2, 0, 0, p6, 0, 0);
    
    mat c12 = add(half, p1, 0, 0, p2, 0, 0);
    
    mat c21 = add(half, p3, 0, 0, p4, 0, 0);
    
    mat temp3 = add(half, p5, 0, 0, p1, 0, 0);
    mat temp4 = sub(half, temp3, 0, 0, p3, 0, 0);
    mat c22 = sub(half, temp4, 0, 0, p7, 0, 0);
    
    mat c(n, std::vector<long long>(n, 0));
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            c[i][j] = c11[i][j];
            c[i][j + half] = c12[i][j];
            c[i + half][j] = c21[i][j];
            c[i + half][j + half] = c22[i][j];
        }
    }

    return c;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    mat a(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    mat b(n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> b[i][j];
        }
    }

    auto res = mul(n, a, 0, 0, b, 0, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << res[i][j] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}