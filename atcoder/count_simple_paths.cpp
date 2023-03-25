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
#define inll(x) ll x; in(x)
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

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

int counter = 0;
void dfs(int at, vector<bool> &vis, deque<int> &q, vector<vector<int>> &adj_list) {
    vis[at] = true;
    q.pf(at);
    counter++;
    if (counter >= 1000000) {
        return;
    }

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            dfs(i, vis, q, adj_list);
            while (q.front() != at) {
                vis[q.front()] = false;
                q.pop_front();
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        ini(u);
        ini(v);
        adj_list[u - 1].pb(v - 1);
        adj_list[v - 1].pb(u - 1);
    }

    vector<bool> vis(n);
    deque<int> q;
    dfs(0, vis, q, adj_list);

    cout << min(counter, 1000000) << endl;
}