#include <vector>
#include <iostream>

bool dfs(
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
		if (par[v] == -1 || dfs(g, par, used, par[v])) {
			par[v] = u;
			return true;
		}
	}

	return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> g(n);
    
    for (int u = 0; u < n; u++) {
    	int v;
	while (std::cin >> v) {
		if (v == 0) {
			break;
		}
		v -= 1;
		g[u].push_back(v);
	}
    }

    std::vector<bool> used(n, false);
    std::vector<int> par(m, -1);

    for (int u = 0; u < n; u++) {
    	dfs(g, par, used, u);
	std::fill(used.begin(), used.end(), false);
    }
	
    int res = 0;
    for (int u = 0; u < m; u++) {
    	res += (par[u] != -1);
    }

    std::cout << res << std::endl;


    for (int u = 0; u < m; u++) {
	if (par[u] == -1) {
		continue;
	}

	std::cout << par[u] + 1 << " " << u + 1  << std::endl;
    }

    return 0;
}
