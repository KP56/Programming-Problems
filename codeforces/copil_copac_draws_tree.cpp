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

vector<pii> randomTree(int n) {
    int size_of_tree = n;
    unordered_set<int> has_parent;

    vector<pii> edges;
    for (int i = 0; i < size_of_tree; i++) {
        for (int j = 0; j < rand() % 3; j++) {
            int node = rand() % size_of_tree;
            if (node != 0 && has_parent.find(node) == has_parent.end()) {
                has_parent.insert(node);
                edges.pb({i + 1,node + 1});
            }
        }
    }

    return edges;
}

void dfs(int at, vector<bool> &vis, deque<pii> &saved, int &total_vis, int prev, vector<vector<pii>> &tree) {
    vis[at] = true;
    total_vis++;

    for (pii i : tree[at]) {
        if (!vis[i.first] && i.second > prev) {
            dfs(i.first, vis, saved, total_vis, i.second, tree);
        } else if (!vis[i.first]) {
            saved.pb({i.first,i.second});
        }
    }
}

void readCaseData() {
    ini(n);
    //int n = rand() % 5 + 2;

    //vector<pii> vec = randomTree(n);
    vector<vector<pii>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        ini(u);
        //int u = vec[i].first;
        ini(v);
        //int v = vec[i].second;
        tree[u - 1].pb({v - 1,i});
        tree[v - 1].pb({u - 1,i});
    }

    int total_vis = 0;
    int ans = 0;
    deque<pii> saved;
    saved.pb({0,-1});
    vector<bool> vis(n);
    for (; total_vis < n; ans++) {
        int initial_size = saved.size();
        for (pii i : saved) {
            dfs(i.first, vis, saved, total_vis, i.second, tree);
        }
        for (int i = 0; i < initial_size; i++) {
            saved.pop_front();
        }
    }

    cout << ans << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}