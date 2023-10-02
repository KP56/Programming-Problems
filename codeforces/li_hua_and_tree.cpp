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

void rootDFS(int at, vector<bool> &vis, vector<vector<int>> &tree, vector<vector<int>> &rooted, vector<int> &parents) {
    vis[at] = true;

    for (int i : tree[at]) {
        if (!vis[i]) {
            rooted[at].pb(i);
            parents[i] = at;
            rootDFS(i, vis, tree, rooted, parents);
        }
    }
}

void root(vector<vector<int>> &tree, vector<vector<int>> &rooted, vector<int> &parents) {
    vector<bool> vis(tree.size());
    rootDFS(0, vis, tree, rooted, parents);
}

pii computeRec(int at, vector<vector<int>> &rooted, vector<int> &singular_importance, vector<int> &importance, vector<int> &size_vec) {
    pii ret = {singular_importance[at],1};
    for (int i : rooted[at]) {
        pii val = computeRec(i, rooted, singular_importance, importance, size_vec);
        ret.first += val.first;
        ret.second += val.second;
    }

    importance[at] = ret.first;
    size_vec[at] = ret.second;
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<int> singular_importance;
    for (int i = 0; i < n; i++) {
        ini(a);
        singular_importance.pb(a);
    }

    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        ini(a);
        ini(b);
        tree[a - 1].pb(b - 1);
        tree[b - 1].pb(a - 1);
    }

    vector<vector<int>> rooted(n);
    vector<int> parents(n);
    parents[0] = -1;
    root(tree,rooted,parents);
    vector<int> importance(n);
    vector<int> size_vec(n);
    computeRec(0, rooted, singular_importance, importance, size_vec);

    vector<map<int,set<int>>> rb_tree(n);
    for (int i = 0; i < n; i++) {
        for (int j : rooted[i]) {
            rb_tree[i][size_vec[j]].insert(j);
        }
    }

    for (int i = 0; i < m; i++) {
        ini(q_type);
        ini(x);
        x--;

        if (q_type == 1) {
            cout << importance[x] << endl;
        } else {
            if (rb_tree[x].empty()) {
                continue;
            }
            auto it = --rb_tree[x].end();
            int heavy_child = *(*it).second.begin();

            int cp_imp = importance[x];
            importance[x] -= importance[heavy_child];
            importance[heavy_child] = cp_imp;

            int cp_size = size_vec[x];
            size_vec[x] -= size_vec[heavy_child];
            size_vec[heavy_child] = cp_size;

            rb_tree[x][it->first].erase(heavy_child);
            if (rb_tree[x][it->first].empty()) rb_tree[x].erase(it->first);
            rb_tree[heavy_child][size_vec[x]].insert(x);
            rb_tree[parents[x]][cp_size].erase(x);
            rb_tree[parents[x]][cp_size].insert(heavy_child);

            parents[heavy_child] = parents[x];
            parents[x] = heavy_child;
        }
    }
}