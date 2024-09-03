#pragma GCC optimize("O3")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double dbl;
typedef long double ld;
typedef unsigned int uint;
typedef unsigned long long ull;

typedef pair <int, int> pi;
typedef pair <ll,ll> pll;

typedef vector <int> vi;
typedef vector <string> vs;
typedef vector <ll> vll;
typedef vector <ld> vld;
typedef vector <pi> vpi;
typedef vector <pll> vpll;

template <class T> using peque = priority_queue<T>;
template <class T> using pequeg = priority_queue<T, vector<T>, greater<T>>;

#define map unordered_map
#define ft first 
#define sd second

#define For(i, l, r) for (int i=l; i<r; i++)
#define ForR(i, r, l) for (int i=r; i>l; i--)
#define ForEach(x, vec) for (auto &x : vec)

template <typename T>
void Println(T &x) {cout << x << "\n";}
template <typename T>
void Print(T &x) {cout << x << " ";}
template <typename T>
void Print(vector <T> &vec) {
    for (auto &x : vec){
        cout << x << " ";
    }
    cout << "\n";
}
template <typename K, typename V>
void Print(map <K, V> &m) {
    for (auto &[k, v] : m){
        cout << k << ":" << v << " ";
    }
    cout << "\n";
}

#define All(vec) vec.begin(), vec.end()
#define Len(vec) int(vec.size())
#define Reverse(vec) reverse(vec.begin(), vec.end())
#define Sort(vec) sort(vec.begin(), vec.end())
#define Min(vec) *min_element(vec.begin(), vec.end())
#define Max(vec) *max_element(vec.begin(), vec.end())

void solve(){
    int n, y;
    cin >> n >> y;

    vector <pair<int, string>> free(n);
    For(i, 0, n){
        cin >> free[i].ft >> free[i].sd;
    }

    string day;
    cin >> day;

    vs days{"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    vs months{"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
    vi amount{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
        amount[1] = 29; 
    }

    int cur;
    For(i, 0, 7){
        if (days[i] == day){
            cur = i;
        }
    }

    vi cnt(7, 0);

    For(i, 0, 12){
        string m = months[i];
        For(d, 1, amount[i]+1){
            bool f = 1;
            ForEach(p, free){
                if (p.ft == d && p.sd == m){
                    f = 0;
                    break;
                }
            }

            if (f){
                cnt[cur] += 1;
            }
            cur = (cur+1) % 7;
        }
    }

    int mx = 0;
    int mxi = -1;
    int mn = 400;
    int mni = -1;

    For(i, 0, 7){
        if (cnt[i] >= mx){
            mx = cnt[i];
            mxi = i;
        }

        if (cnt[i] < mn){
            mn = cnt[i];
            mni = i;
        }
    }

    cout << days[mxi] << " " << days[mni] << endl;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    srand(80085);

    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }

    return 0;
}