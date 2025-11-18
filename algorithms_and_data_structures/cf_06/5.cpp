#include <vector>
#include <stack>
#include <iostream>
#include <climits>
#include <queue>
#include <functional>
#include <unordered_map>

#define ll long long

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::unordered_map<int, ll>> g(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        std::cin >> u >> v >> w;
        g[u][v] = w;
    }

    std::vector<ll> dist(n, LLONG_MAX);
    dist[0] = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }                
            }
        }
    }

    std::vector<bool> cycle(n, false);

    std::queue<int> q;
    for (int u = 0; u < n; u++) {
        if (dist[u] == LLONG_MAX) {
            continue;
        }
        
        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                if (!cycle[v]) {
                    cycle[v] = true;
                    q.push(v);
                }
                if (!cycle[u]) {
                    cycle[u] = true;
                    q.push(u);
                }
            }                
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (auto [v, w] : g[u]) {
            if (!cycle[v]) {
                cycle[v] = true;
                q.push(v);
            }
        }
    }


    for (int u = 1; u < n; u++) {
        if (cycle[u]) {
            std::cout << "-inf" << std::endl;
            continue;
        }

        std::cout << dist[u] << std::endl;
    }

    return 0;
}