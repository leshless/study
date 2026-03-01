#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <functional>

int main() {
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> g(n);
    std::vector<std::vector<int>> rg(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        rg[v].push_back(u);
    }

    std::vector<bool> visited(n, false);
    std::stack<int> order;
    
    std::function<void(int)> dfs1 = [&](int u) {
        visited[u] = true;
        for (int v : g[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push(u);
    };
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }

    std::vector<int> scc(n, -1);
    int nc = 0;
    
    std::function<void(int, int)> dfs2 = [&](int u, int id) {
        scc[u] = id;
        for (int v : rg[u]) {
            if (scc[v] == -1) {
                dfs2(v, id);
            }
        }
    };
    
    while (!order.empty()) {
        int u = order.top();
        order.pop();
        if (scc[u] == -1) {
            dfs2(u, nc++);
        }
    }

    std::vector<std::vector<int>> cg(nc);
    for (int u = 0; u < n; u++) {
        for (int v : g[u]) {
            if (scc[u] != scc[v]) {
                cg[scc[u]].push_back(scc[v]);
            }
        }
    }

    std::vector<int> ord(nc, -1);
    std::queue<int> q;
    
    std::vector<int> deg(nc, 0);
    for (int u = 0; u < nc; u++) {
        for (int v : cg[u]) {
            deg[v]++;
        }
    }
    
    for (int i = 0; i < nc; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    
    int cur = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ord[u] = cur++;
        
        for (int v : cg[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }

    std::cout << nc << std::endl;
    for (int u = 0; u < n; u++) {
        std::cout << ord[scc[u]] << " ";
    }
    std::cout << std::endl;

    return 0;
}