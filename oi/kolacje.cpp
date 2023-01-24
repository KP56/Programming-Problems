#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

//https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int lca(int a, int b, vector<vector<pii>> &adj_list, vector<int> &root_dist) {

}

void rootDistDFS(int at, int current, vector<bool> &vis, vector<vector<pii>> &adj_list, vector<int> &vec) {
    vec[at] = current;
    vis[at] = true;

    for (pii i : adj_list[at]) {
        if (!vis[i.first]) {
            rootDistDFS(i.first, current + 1, vis, adj_list, vec);
        }
    }
}

vector<int> getRootDistances(int root, vector<vector<pii>> &adj_list) {
    vector<int> vec(adj_list.size());
    vector<bool> vis(adj_list.size());
    
    rootDistDFS(root, 0, vis, adj_list, vec);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(n);
    in_i(r);

    vector<int> types;
    for (int i = 0; i < n; i++) {
        in_i(type);
        types.pb(type);
    }

    vector<vector<pii>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        in_i(a);
        in_i(b);
        in_i(c);

        adj_list[a].pb(mp(b,c));
    }

    vector<int> root_dist = getRootDistances(0, adj_list);

    in_i(q);
    for (int i = 0; i < q; i++) {
        in_i(a);
        in_i(b);
        in_i(type);

        //O(H) szukanie wspólnego "przodka"
        int c = lca(a, b, adj_list, root_dist);
        
    }
}