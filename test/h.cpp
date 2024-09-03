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

ld t_meet(ld x, ld u, ld y, ld v){
    if ((u < 0) && (u <= v)){
        return LDBL_MAX;
    }
    if ((v > 0) && (v >= u)){
        return LDBL_MAX;
    }
    if ((u >= 0) && (v <= 0)){
        return (y-x)/(abs(u)+abs(v));
    }else if ((u <= 0) && (v <= 0)){
        return (y-x)/(abs(v)-abs(u));
    }
    return (y-x)/(abs(u)-abs(v));
    
}

ld t_wall(ld l, ld x, ld u){
    if (u > 0){
        return abs((l-x) / u);
    }else if (u < 0){
        return abs(x / u);
    }
    return LDBL_MAX;
}

void solve(){
    ld l, x, u, y, v;
    cin >> l >> x >> u >> y >> v;

    if (x > y){
        swap(x, y);
        swap(u, v);
    }

    if (x == y){
        cout << fixed << setprecision(6) << ld(0) << endl;
        return;
    }

    if ((u == 0) && (v == 0)){
        cout << -1 << endl;
        return;
    }

    ld t = 0;
    if ((u < 0) && (v < 0)){
        // <- <-
        ld tm = t_meet(x, u, y, v);
        ld tw = t_wall(l, x, u);
        if (tm <= tw){
            t += tm;
        }else{
            t += (x + y) / (abs(u) + abs(v));
        }
    }else if ((u >= 0) && (v >= 0)){
        // -> ->
        ld tm = t_meet(x, u, y, v);
        ld tw = t_wall(l, y, v);
        if (tm <= tw){
            t += tm;
        }else{
            t += (l - x + l - y) / (abs(u) + abs(v));
        }
    }else if ((u < 0) && (v >= 0)){
        t += (l + x + l - y) / (abs(u) + abs(v));
    }else{ 
        // -> <-
        t += t_meet(x, u, y, v);
    }

    cout << fixed << setprecision(6) << t << endl;

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