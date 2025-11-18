#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

int dfs(std::vector<std::unordered_map<int, int>> &g, int u, int p, int t) {
    for (auto [v, w] : g[u]) {
        if (v == t) {
            return w;
        }

        if (v == p) {
            continue;
        }

        int res = dfs(g, v, u, t);

        if (res != -1) {
            return std::max(res, w);
        }
    }

    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::unordered_map<int, int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u--; v--;
        g[u][v] = w;
        g[v][u] = w;
    }

    std::vector <bool> visited(n, false);
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, std::greater<std::pair<int, std::pair<int, int>>>> pq;
    std::vector<std::unordered_map<int, int>> mst(n);

    for (auto [v, w] : g[0]) {
        pq.push({w, {0, v}});
    }
    visited[0] = true;

    int res1 = 0;
    while (!pq.empty()) {
        int w = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();
        
        if (visited[v]) {
            continue;
        }
        
        visited[v] = true;
        
        mst[u][v] = w;
        mst[v][u] = w;
        res1 += w;
        
        for (auto [v1, w1] : g[v]) {
            pq.push({w1, {v, v1}});
        }
    }

    int res2 = -1;
    for (int u = 0; u < n; u++) {
        for (auto [v, w] : g[u]) {
            if (mst[u].count(v) != 0) {
                continue;
            }

            int cur = res1 - dfs(mst, u, -1, v) + w;
            if (res2 == -1 || cur < res2) {
                res2 = cur;
            }
            
        }
    }

    std::cout << res1 << " " << res2 << std::endl;

    return 0;
}