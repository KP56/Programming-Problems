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

bool isThereACycle(int at, vector<int> &adj_list, vector<bool> &vis, int beginning) {
    vis[at] = true;

    if (adj_list[at] == -1) {
        return false;
    } else {
        if (adj_list[at] == beginning) {
            return true;
        }

        if (vis[adj_list[at]]) {
            return false;
        }

        return isThereACycle(adj_list[at], adj_list, vis, beginning);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    vector<pair<string,string>> strings;
    for (int i = 0; i < n; i++) {
        instr(a);
        instr(b);
        strings.pb(mp(a,b));
    }

    vector<int> adj_list(strings.size(), -1);
    unordered_map<string,int> m;
    for (int i = 0; i < n; i++) {
        m[strings[i].first] = i;
    }

    for (int i = 0; i < n; i++) {
        if (m.find(strings[i].second) != m.end()) {
            adj_list[i] = m[strings[i].second];
        }
    }

    vector<bool> vis(strings.size());
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (isThereACycle(i, adj_list, vis, i)) {
                cout << "No" << endl;
                return 0;
            }
        }
    }

    cout << "Yes" << endl;
}