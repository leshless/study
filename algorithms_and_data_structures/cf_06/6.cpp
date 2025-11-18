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

    std::vector<ll> fill(n, LLONG_MAX);
    std::vector<std::vector<ll>> dist(n, fill);
    for (int u = 0; u < n; u++) {
        dist[u][u] = 0;
        for (auto [v, w] : g[u]) {
            dist[u][v] = w;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (dist[u][i] == LLONG_MAX) {
                    continue;
                }

                if (dist[i][v] == LLONG_MAX) {
                    continue;
                }

                if (dist[u][i] + dist[i][v] < dist[u][v]) {
                    dist[u][v] = dist[u][i] + dist[i][v];
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (u == v) {
                continue;
            }
            
            if (dist[u][v] == LLONG_MAX) {
                std::cout << u << " " << v << " -1" << std::endl;
                continue;
            }

            std::cout << u << " " << v << " " << dist[u][v] << std::endl;
        }
    }


    return 0;
}