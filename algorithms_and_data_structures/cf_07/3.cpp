#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>

void find_cc(
	std::vector<std::vector<int>> &g,
	std::vector<bool> &used,
	std::vector<int> &cc,
	int u,
	int c
) {
	if (used[u]) {
		return;
	}
	
	cc[u] = c;
	used[u] = true;

	for (auto v : g[u]) {
		find_cc(g, used, cc, v, c);	
	}
	
	return;
}

int dinic(
	std::vector<std::vector<int>> &g,
        int s,
        int t		
) {
	int n = g.size();

	// Populate network
	std::vector<std::unordered_map<int, bool>> net(n);
	for (int u = 0; u < n; u++) {
		for (auto v : g[u]) {
			net[u][v] = true;
		}
	}

	int res = 0;
	bool pf = true;
	while (true) {
		// Determine layers
		std::vector<int> layer(n, -1);
		layer[s] = 0;

		std::queue<int> q;
		q.push(s);

		while (!q.empty()) {
			int u = q.front();
			q.pop();

			for (auto [v, w] : net[u]) {
				if (!w) {
					continue;
				}
			
				if (layer[v] != -1) {
					continue;
				}

				layer[v] = layer[u] + 1;
				q.push(v);
			}
		}

		// Keep launching bfs till path from s to t does not exist in current layer net
		bool f = false;
		while (true) {
			std::vector<int> par(n, -1);
			std::queue<int> q;
			q.push(s);

			while (!q.empty()) {
				int u = q.front();
				q.pop();

				for (auto [v, w] : net[u]) {
					if (!w) {
						continue;
					}
					
					if (par[v] != -1) {
						continue;
					}

					if (layer[v] <= layer[u]) {
						continue;
					}

					par[v] = u;
					q.push(v);
				}
			}
			
			if (par[t] == -1) {
				break;
			}
			
			// We found at least one incrementing path
			f = true;
			res++;

			int v = t;
			while (v != s) {
				int u = par[v];

				// Channel the flow u -> v
				net[u][v] = false;
				// Release (if not already) the flow v -> u
				net[v][u] = true;

				v = u;
			}
		}
		
		// If we are still not getting improvement on this traversal, break since there is no point to form new G_l 
		if (!f and !pf) {
			break;
		}
		pf = f;
	}

	return res;
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    std::vector<std::vector<int>> g(n);
    std::unordered_map<std::string, int> map;

    int cur = 0;
    for (int i = 0; i < m; i++) {
	std::string us, vs;
        std::cin >> us >> vs;
        
	int u;
	if (map.count(us) != 0) {
		u = map[us];	
	} else {
		u = cur++;
		map[us] = u;
	}

	
	int v;
        if (map.count(vs) != 0) {
                v = map[vs];
        } else {
                v = cur++;
		map[vs] = v;
        }

	g[u].push_back(v);
	g[v].push_back(u);	
    }

    int c = 0;
    std::vector<int> cc(n);
    std::vector<bool> used(n, false);
    for (int u = 0; u < n; u++) {
    	find_cc(g, used, cc, u, c++);
    //	std::cout << u << " " << cc[u] << std::endl; 
    }

	
	while (k--) {
		std::string ss, ts;
		std::cin >> ss >> ts;

		int s = map[ss];
		int t = map[ts];

		if (cc[s] != cc[t]) {
			std::cout << 0 << std::endl;
			continue;
		}

		std::cout << dinic(g, s, t) << std::endl;
	}

    return 0;
}
