#include <vector>
#include <iostream>
#include <algorithm>

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

bool is_subseq(
	std::vector<std::string> &words1,
	std::vector<std::string> &words2	
) {
	int n = words1.size();
	int m = words2.size();

	int j = 0;
	int i = 0;
	while (i < n) {
		while (words1[i] == words2[j]) {
			i++;
			j++;

			if (j == m) {
				return true;
			}

			if (i == n) {
				return false;
			}
		}

		i++;
	}

	return false;
}

int main() {
    int n;
    std::cin >> n;
    
    std::vector<std::vector<std::string>> words(n);
    for (int u = 0; u < n; u++) {
   	int k;
	std::cin >> k;

	while (k--) {
		std::string w;
		std::cin >> w;

		words[u].push_back(w);
	}
    
    	std::sort(words[u].begin(), words[u].end());
    }

    std::vector<std::vector<int>> g(n);
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
		if (i == j) {
			continue;
		}

		if (is_subseq(words[i], words[j])) {
			g[j].push_back(i);
		}
	}
    }


    std::vector<int> par(n, -1);
    std::vector<bool> used(n, false);
    for (int u = 0; u < n; u++) {
    	dfs(g, par, used, u);
	std::fill(used.begin(), used.end(), false);
    }

    int res = 0;
    for (int u = 0; u < n; u++) {
    	    res += (par[u] == -1);
    }

    std::cout << res << std::endl;

    return 0;
}
