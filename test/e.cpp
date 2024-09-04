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
    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;

    bool f1 = (s1 == "yes");
    bool f2 = (s2 == "yes");

    map <string, bool> bad;
    For(i, 0, n){
        string p;
        cin >> p;
        if (!f1){
            For(j, 0, Len(p)){
                if (p[j] <= 'Z' && p[j] >= 'A'){
                    p[j] -= ('Z' - 'z');
                }
            }
        }

        bad[p] = 1;
    }

    string s;
    string p;
    while (getline(cin, p)){
        s += "|";
        s += p;
    }


    map <string, int> cnt;

    int mx = 0;
    string res = "";

    p = "";
    For(i, 0, Len(s)){
        char x = s[i];

        if (((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')) || ((x >= '0') && (x <= '9')) || (x == '_')){
            if (Len(p) == 0){
                if (f2){
                    p += x;
                }else{
                    if (((x >= 'a') && (x <= 'z')) || ((x >= 'A') && (x <= 'Z')) || (x == '_')){
                        p += x;
                    }
                }
            }else{
                p += x;
            }

        }else if (Len(p)){
            if (!f1){
                For(j, 0, Len(p)){
                    if (p[j] <= 'Z' && p[j] >= 'A'){
                        p[j] -= ('Z' - 'z');
                    }
                }
            }
            if (bad.count(p) == 0){
                cnt[p]++;

                if (cnt[p] > mx){
                    mx = cnt[p];
                    res = p;
                }

            }
            p = "";
        }
    }
    if (Len(p)){
        if (!f1){
            For(j, 0, Len(p)){
                if (p[j] <= 'Z' && p[j] >= 'A'){
                    p[j] -= ('Z' - 'z');
                }
            }
        }
        if (bad.count(p) == 0){
            cnt[p]++;

            if (cnt[p] > mx){
                mx = cnt[p];
                res = p;
            }

            p = "";
        }

    }

    cout << res << endl;

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