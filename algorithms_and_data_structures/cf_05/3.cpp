#include <vector>
#include <cmath>
#include <iostream>
#include <unordered_map>

#define ll long long

const int N = 1e6 + 1;
const ll M = 1e9 + 9;

int main() {
    std:srand(80082);

    int n;
    std::cin >> n;

    std::vector<ll> a(n);
    for (int i=0; i < n; i++) {
        std::cin >> a[i];
    }

    int m;
    std::cin >> m;

    std::vector<ll> b(m);
    for (int i=0; i < m; i++) {
        std::cin >> b[i];
    }

    std::vector<ll> r(N);
    for (int i = 0; i < N; i++) {
        r[i] = rand();
    }

    std::vector<std::unordered_map<ll, int>> hs(n + 1);

    for (int i = 0; i < n; i++) {
        ll h1 = 0;
        ll h2 = 0;
        ll h3 = 0;

        for (int j = i; j < n; j++) {
            int k = j - i + 1;
            
            h1 = (h1 + r[a[j]]) % M;
            if (hs[k].count(h1) == 0) {
                hs[k][h1] = i;
            }

            h2 = (h2 + r[(a[j] + 1) % N]) % M;
            if (hs[k].count(h2) == 0) {
                hs[k][h2] = i;
            }

            h3 = (h3 + r[(a[j] + 2) % N]) % M;
            if (hs[k].count(h3) == 0) {
                hs[k][h3] = i;
            }
        }
    }

    int res_k = 0;
    int res_i = -1;
    int res_j = -1;
    
    for (int i = 0; i < m; i++) {
        ll h1 = 0;
        ll h2 = 0;
        ll h3 = 0;

        for (int j = i; j < m; j++) {
            h1 = (h1 + r[b[j]]) % M;
            h2 = (h2 + r[(b[j] + 1) % N]) % M;
            h3 = (h3 + r[(b[j] + 2) % N]) % M;

            int k = j - i + 1;
            if (k <= res_k) {
                continue;
            }
            if (k > n) {
                break;
            }

            if (hs[k].count(h1) != 0 && hs[k].count(h2) != 0 && hs[k].count(h3) != 0) {
                res_k = k;
                res_i = hs[k][h1];
                res_j = i;
            }
        }
    }

    std::cout << res_k << " " << res_i+1 << " " << res_j+1 << std::endl;
}