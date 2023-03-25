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

struct pair_hash {
  template <typename T1, typename T2>
  auto operator()(const pair<T1, T2> &p) const -> size_t {
    return hash<T1>{}(p.first) ^ hash<T2>{}(p.second);
  }
};

int res = INT_MAX;
void bfs(pii at, pii dest, vector<vector<vector<pii>>> &adj_list2d, vector<vector<bool>> &vis) {
    queue<pair<pii,int>> q;
    q.push({at,0});
    while (!q.empty()) {
        pii current = q.front().first;
        int steps = q.front().second;
        if (current == dest) {
            res = steps;
            return;
        }
        q.pop();
        vis[current.first][current.second] = true;
        for (pii i : adj_list2d[current.first][current.second]) {
            if (!vis[i.first][i.second]) {
                vis[i.first][i.second] = true;
                q.push({i,steps+1});
            }
        }
    }
}

void readCaseData() {
    ini(n);
    ini(m);

    res = INT_MAX;

    vector<int> c_vec;
    for (int i = 0; i < n; i++) {
        ini(c);
        c_vec.pb(c);
    }

    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        a--;
        b--;

        adj_list[a].pb(b);
        adj_list[b].pb(a);
    }

    vector<vector<vector<pii>>> adj_list2d(n,vector<vector<pii>>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (c_vec[i] != c_vec[j] || (i == 0 && j == n-1)) {
                for (int i2 : adj_list[i]) {
                    for (int j2 : adj_list[j]) {
                        if (c_vec[i2] != c_vec[j2]) {
                            adj_list2d[i][j].pb({i2,j2});
                        }
                    }
                }
            }
        }
    }

    vector<vector<bool>> vis(n,vector<bool>(n));
    bfs({0,n-1},{n-1,0},adj_list2d,vis);

    if (res == INT_MAX) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}