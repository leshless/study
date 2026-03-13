#include <vector>
#include <stack>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>


using namespace std;

int main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;

	vector<unordered_map<int, int>> net(n);
	vector<unordered_map<int, int>> cap(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;

		net[u][v]++;
		cap[u][v]++;
	}
		
	vector<int> par(n, -1);
	queue<int> q;
	q.push(s);

	while (!q.empty()) {
		int u = q.front();
		q.pop();
	
		for (auto [v, w] : net[u]) {
			if (par[v] != -1) {
				continue;
			}

			if (w == 0) {
				continue;
			}

			par[v] = u;
			q.push(v);
		}
	}

	if (par[t] == -1) {
		cout << "NO" << endl;
		return 0;
	}

	int v = t;
	while (v != s) {
		int u = par[v];

		net[u][v]--;
		net[v][u]++;

		v = u;
	}

	fill(par.begin(), par.end(), -1);
	q.push(s);

	while (!q.empty()) {
                int u = q.front();
                q.pop();

                for (auto [v, w] : net[u]) {
                        if (par[v] != -1) {
                                continue;
                        }

                        if (w == 0) {
                                continue;
                        }

                        par[v] = u;
                        q.push(v);
                }
        }

        if (par[t] == -1) {
                cout << "NO" << endl;
                return 0;
        }

        v = t;
        while (v != s) {
                int u = par[v];

                net[u][v]--;
                net[v][u]++;

                v = u;
        }

	cout << "YES" << endl;

	cout << s+1 << " ";
	int u = s;
	while (u != t) {
		for (auto [v, w] : net[u]) {
			if (w < cap[u][v]) {
				cout << v+1 << " ";

				net[u][v]++;
				net[v][u]--;
				u = v;

				break;
			}
		}
	}

	cout << endl;

	cout << s+1 << " ";
        u = s;
        while (u != t) {
                for (auto [v, w] : net[u]) {
                        if (w < cap[u][v]) {
                                cout << v+1 << " ";

                                net[u][v]++;
                                net[v][u]--;
                                u = v;

                                break;
                        }
                }
        }

	cout << endl;

	return 0;
}
