#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <functional>
#include <climits>

#define ll long long


bool bfs(
	std::vector<std::unordered_map<int, ll>> &g,
	std::vector<int> &path,
	int n
) {
	int t = n - 1;

	std::vector <int> parent(n, -1);
	std::queue <int> q;
	q.push(0);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (auto [v, w] : g[u]) {
			if (parent[v] != -1 || w == 0) {
				continue;
			}
			
			parent[v] = u;

			if (v == t) {
				break;
			}

			q.push(v);
		}
	}

	if (parent[t] == -1) {
		return false;
	}

	int cur = t;
	while (cur != 0) {
		path.push_back(cur);
		cur = parent[cur];
	}
	path.push_back(0);

	std::reverse(path.begin(), path.end());

	return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::unordered_map<int, ll>> g(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
	ll w;
        std::cin >> u >> v >> w;
        u--; v--;
        g[u][v] += w;
    }
	
    ll res = 0;
    std::vector<int> path;
    while (bfs(g, path, n)) {
	ll mn = LLONG_MAX;
	for (int i = 0; i < path.size() - 1; i++) {
		int u = path[i];
		int v = path[i+1];

		mn = std::min(mn, g[u][v]);	
		u = v;	
	}

        for (int i = 0; i < path.size() - 1; i++) {
                int u = path[i];
		int v = path[i+1]; 
		
		g[u][v] -= mn;
		g[v][u] += mn;
        	u = v;
	}

	res += mn;

	path.clear();
    }

    std::cout << res << std::endl;

    return 0;
}
