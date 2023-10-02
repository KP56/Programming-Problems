#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

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

void construct_depth(int at, int current_depth, vector<vector<int>> &depth, vector<bool> &vis, vector<vector<pii>> &tree) {
    vis[at] = true;

    while (depth.size() <= current_depth) {
        depth.pb({});
    }

    depth[current_depth].pb(at);

    for (pii i : tree[at]) {
        if (!vis[i.first]) {
            construct_depth(i.first, current_depth + 1, depth, vis, tree);
        }
    }
}

void construct_parent(int at, int prev, int edge_ind, vector<pii> &parent, vector<bool> &vis, vector<vector<pii>> &tree) {
    vis[at] = true;

    if (prev != -1) {
        parent[at] = {prev,edge_ind};
    }

    for (pii i : tree[at]) {
        if (!vis[i.first]) {
            construct_parent(i.first, at, i.second, parent, vis, tree);
        }
    }
}

void readCaseData() {
    ini(n);

    vector<vector<pii>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        ini(v);
        ini(u);
        tree[v-1].pb({u-1,i});
        tree[u-1].pb({v-1,i});
    }

    vector<vector<int>> depth;
    vector<bool> vis(n);
    construct_depth(0, 0, depth, vis, tree);

    vector<pii> parent(n,{-1,-1});
    vis = vector<bool>(n);
    construct_parent(0, -1, -1, parent, vis, tree);

    vector<int> to_cut;
    vector<int> arr(n, 1);
    for (int i = depth.size() - 1; i >= 0; i--) {
        for (int u : depth[i]) {
            if (parent[u].first == -1 && arr[u] != 3) {
                cout << -1 << endl;
                return;
            }

            if (arr[u] == 3) {
                if (u == 0) {
                    continue;
                }

                to_cut.pb(parent[u].second + 1);
                continue;
            }

            if (arr[u] > 3) {
                cout << -1 << endl;
                return;
            }

            arr[parent[u].first] += arr[u];
            arr[u] = 0;
        }
    }

    cout << to_cut.size() << endl;
    for (int i : to_cut) {
        cout << i << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}