#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs1(int v, vector<vector<int>>& g, vector<bool>& used, vector<int>& order) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to])
            dfs1(to, g, used, order);
    }
    order.push_back(v);
}

void dfs2(int v, vector<vector<int>>& gr, vector<bool>& used, vector<int>& comp, int cl) {
    used[v] = true;
    comp[v] = cl;
    for (int to : gr[v]) {
        if (!used[to])
            dfs2(to, gr, used, comp, cl);
    }
}

int main() {
    int n, m;
    while (cin >> n >> m) {
        vector<vector<int>> g(2 * n), gr(2 * n);
        
        for (int t = 0; t < m; t++) {
            int i1, e1, i2, e2;
            cin >> i1 >> e1 >> i2 >> e2;
            
            int a = 2 * i1 + (e1 ^ 1);
            int b = 2 * i2 + e2;
            g[a].push_back(b);
            gr[b].push_back(a);
            
            a = 2 * i2 + (e2 ^ 1);
            b = 2 * i1 + e1;
            g[a].push_back(b);
            gr[b].push_back(a);
        }
        
        vector<bool> used(2 * n, false);
        vector<int> order;
        
        for (int i = 0; i < 2 * n; i++) {
            if (!used[i])
                dfs1(i, g, used, order);
        }
        
        reverse(order.begin(), order.end());
        fill(used.begin(), used.end(), false);
        
        vector<int> comp(2 * n, -1);
        int cl = 0;
        for (int v : order) {
            if (!used[v]) {
                dfs2(v, gr, used, comp, cl);
                cl++;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return 1;
            }
        }
        
        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            ans[i] = (comp[2 * i] > comp[2 * i + 1]) ? 1 : 0;
        }
        
        for (int i = 0; i < n; i++) {
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}