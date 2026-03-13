#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

bool kun(
	std::vector<std::vector<int>> &g,
	std::vector<int> &par,
	std::vector<bool> &used,
	int u
) {
	if (used[u]) {
		return false;
	}
	used[u] = true;

	for (auto v : g[u]) {
		if (par[v] == -1 || kun(g, par, used, par[v])) {
			par[v] = u;
			return true;
		}
	}

	return false;
}

int main() {
	int n, m, a, b;
	std::cin >> n >> m >> a >> b;

	std::vector <std::string> mat(n);
	for (int i = 0; i < n; i++) {
		std::cin >> mat[i];
	}

	std::vector<bool> bad(n*m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int u = i * m + j;

			bad[u] = (mat[i][j] == '.');	
		}
	}
	
	if (2 * b <= a) {
		int res = 0;
		for (int u = 0; u < m*n; u++) {
			res += !bad[u];
		}

		std::cout << res * b << std::endl;
		return 0;
	}

	std::vector<std::vector<int>> g(n*m);
	for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
			int u = i * m + j;

			if (bad[u]) {
				continue;
			}
			
			if (i != 0) {
				int v = (i-1) * m + j;

				if (!bad[v]) {
					g[u].push_back(v);
				}
			}

			if (i != n-1) {
                                int v = (i+1) * m + j;

                                if (!bad[v]) {
                                        g[u].push_back(v);
                                }
                        }

			if (j != 0) {
                                int v = i * m + j - 1;
				
                                if (!bad[v]) {
                                        g[u].push_back(v);
                                }
                        }

                        if (j != m-1) {
                                int v = i * m + j + 1;

                                if (!bad[v]) {
                                        g[u].push_back(v);
                                }
                        }
		}
        }

	std::vector <int> par(m*n, -1);
	std::vector <bool> used(m*n, false);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if ((i ^ j) & 1) {
				continue;
			}

			int u = i * m + j;
			
			if (bad[u]) {
				continue;
			}

			kun(g, par, used, u); 
			std::fill(used.begin(), used.end(), false);
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if ((i ^ j) & 1) {
				int u = i * m + j;
				
				if (bad[u]) {
					continue;
				}

				if (par[u] == -1) {
					res += b;
				} else {
					res += a;
				}
                        }
                }
        }

	std::vector <int> cld (m*n, -1);
	for (int u = 0; u < m*n; u++) {
		if (par[u] != -1) {
			cld[par[u]] = u;
		}
	}

	for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                        if ((i ^ j) & 1) {
                       		continue;
		       	}

			int u = i * m + j;
			if (bad[u]) {
				continue;
			}

			if (cld[u] == -1) {
				res += b;
			}
                }
        }

	std::cout << res << std::endl;

//	for (int u = 0; u < n*m; u++) {
//		std::cout << u / m << " " << u % m << ": ";
//		for (auto v : g[u]) {
//			std::cout << v / m << " " << v % m << ", ";
//		}
		
//		int p = par[u];
//		std::cout << " | " << p / m << " " << p % m << ", ";

//		std::cout << std::endl;
//	}
    
	return 0;
}
