#include <iostream>
#include <vector>
#include <string>
#include <map>

int parent[50001];
int rank[50001];

void dsu_init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int dsu_find(int x) {
    if (parent[x] != x) {
        parent[x] = dsu_find(parent[x]);
    }
    return parent[x];
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    
    if (a == b) {
        return;
    }
    
    if (rank[a] < rank[b]) {
        std::swap(a, b);
    }
    
    parent[b] = a;
    
    if (rank[a] == rank[b]) {
        rank[a]++;
    }
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
    }
    
    std::vector<std::pair<std::string, std::pair<int, int>>> queries;
    
    for (int i = 0; i < k; i++) {
        std::string t;
        int u, v;

        std::cin >> t >> u >> v;
        
        queries.push_back({t, {u, v}});
    }
    
    dsu_init(n);
    
    std::vector <std::string> res;
    
    for (int i = k - 1; i >= 0; i--) {
        auto q = queries[i];
        std::string t = q.first;
        int u = q.second.first;
        int v = q.second.second;

        if (t == "ask") {
            if (dsu_find(u) == dsu_find(v)) {
                res.push_back("YES");
            } else {
                res.push_back("NO");
            }
        } else {
            dsu_unite(u, v);
        }
    }

    for (int i = res.size() - 1; i >= 0; i--) {
        std::cout << res[i] << "\n";
    }
    
    return 0;
}