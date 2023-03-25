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

void dfs(int at, vector<bool> &vis, vector<vector<int>> &adj_list, vector<vector<int>> &rooted) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            rooted[at].pb(i);
            dfs(i, vis, adj_list, rooted);
        }
    }
}

vector<vector<int>> root(vector<vector<int>> &adj_list) {
    vector<vector<int>> rooted(adj_list.size());
    vector<bool> vis(adj_list.size());
    dfs(0, vis, adj_list, rooted);

    return rooted;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    vector<vector<int>> adj_list(n);
    for (int i = 0; i < n - 1; i++) {
        ini(a);
        ini(b);
        adj_list[a - 1].pb(b - 1);
        adj_list[b - 1].pb(a - 1);
    }

    vector<vector<int>> rooted = root(adj_list);
    vector<int> children(adj_list.size());
    for (int i = 0; i < n; i++) {
        children[i] = rooted[i].size();
    }
    vector<int> parent(n);
    for (int i = 0; i < n; i++) {
        for (int j : rooted[i]) {
            parent[j] = i;
        }
    }

    vector<bool> is_blocked(n);

    ini(m);
    int res = 1;
    for (int i = 0; i < m; i++) {
        ini(z);
        bool create = z > 0;
        z = abs(z);
        z--;
        if (create) {
            is_blocked[z] = true;
            if (z == 0) {
                res += children[z] - 1;
            } else {
                children[parent[z]]--;
                res += children[z] + (!is_blocked[parent[z]]) - 1;
            }
        } else {
            is_blocked[z] = false;
            if (z == 0) {
                res -= children[z] - 1;
            } else {
                children[parent[z]]++;
                res -= children[z] + (!is_blocked[parent[z]]) - 1;
            }
        }

        cout << res << endl;
    }
}