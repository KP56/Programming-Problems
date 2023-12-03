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

// range query: O(log(n))
// point modification: O(log(n))
struct segment_tree {
    vector<pii> tree;

    segment_tree(int size) {
        tree = vector<pii>(size*2);
    }

    void update(int pos, int x) {
        for (tree[pos += tree.size()/2] = mp(x,pos); pos > 0; pos >>= 1) {
            tree[pos >> 1] = min(tree[pos], tree[pos^1]);
        }
    }

    pii query(int l, int r) {
        r++;

        pii res = {INT_MAX,-1};
        for (l += tree.size() / 2, r += tree.size() / 2; l < r; l >>= 1, r >>= 1) {
            if (l&1) {
                res = min(res,tree[l++]);
            }
            if (r&1) {
                res = min(res,tree[--r]);
            }
        }

        return res;
    }
};

struct fast_lca_finder {
    vector<int> levels;
    vector<int> euler;
    segment_tree seg_tree = segment_tree(0);
    vector<int> min_arr;

    fast_lca_finder(int root, vector<unordered_set<int>> &tree) {
        levels = vector<int>(tree.size());

        vector<bool> vis(tree.size());
        dfs(root,0,vis,tree);

        seg_tree = segment_tree(euler.size());
        for (int i = 0; i < euler.size(); i++) {
            seg_tree.update(i,levels[euler[i]]);
        }

        min_arr = vector<int>(tree.size(),INT_MAX);
        for (int i = 0; i < euler.size(); i++) {
            min_arr[euler[i]] = min(i,min_arr[euler[i]]);
        }
    }

    void dfs(int at, int level, vector<bool> &vis, vector<unordered_set<int>> &tree) {
        vis[at] = true;
        levels[at] = level;
        euler.pb(at);

        for (int i : tree[at]) {
            if (!vis[i]) {
                dfs(i,level+1,vis,tree);
                euler.pb(at);
            }
        }
    }

    int lca(int u, int v) {
        return euler[seg_tree.query(min(min_arr[u],min_arr[v]),max(min_arr[u],min_arr[v])).second];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<unordered_set<int>> tree(6);
    tree[0].insert(1);
    tree[1].insert(0);

    tree[1].insert(5);
    tree[5].insert(1);
    
    tree[0].insert(2);
    tree[2].insert(0);

    tree[1].insert(3);
    tree[3].insert(1);

    tree[3].insert(4);
    tree[4].insert(3);

    fast_lca_finder finder = fast_lca_finder(0,tree);
    cout << finder.lca(3,5) << endl;

    return 0;
}