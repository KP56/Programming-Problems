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

int dfs(int at, int l, vector<int> &radius, vector<bool> &vis, vector<vector<pii>> &graph) {
    vis[at] = true;

    int ret = 1;
    for (pii p : graph[at]) {
        if (!vis[p.first] && p.second <= l) {
            if (radius[p.first] - p.second > l) {
                return dfs(p.first, max(l - p.second, radius[p.first]), radius, vis, graph) + dfs(at, radius[p.first] - p.second, radius, vis, graph);
            }
        }
    }

    for (pii p : graph[at]) {
        if (!vis[p.first] && p.second <= l) {
            ret += dfs(p.first, max(l - p.second, radius[p.first]), radius, vis, graph);
        }
    }

    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<int> radius;
    for (int i = 0; i < size; i++) {
        in_i(r);
        radius.pb(r);
    }

    vector<vector<pii>> graph(size);
    for (int i = 0; i < size - 1; i++) {
        in_i(a);
        in_i(b);
        in_i(c);
        graph[a - 1].pb(mp(b - 1,c));
        graph[b - 1].pb(mp(a - 1,c));
    }

    for (int i = 0; i < size; i++) {
        vector<bool> vis(size);
        cout << dfs(i, radius[i], radius, vis, graph) << " ";
    }
    cout << endl;
}