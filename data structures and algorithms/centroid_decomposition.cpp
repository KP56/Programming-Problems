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

struct centroid_decomposition {
    vector<vector<int>> centroid_tree;

    centroid_decomposition(vector<unordered_set<int>> &tree) {
        centroid_tree = vector<vector<int>>(tree.size());

        construct_tree(tree);
    }

    void construct_tree(vector<unordered_set<int>> tree) {
        int centroid = find_centroid(tree,0);
        perform_construction(tree,centroid);
    }

    void perform_construction(vector<unordered_set<int>> &tree, int centroid) {
        vector<int> nodes_to_execute_for;
        for (int i : tree[centroid]) {
            nodes_to_execute_for.pb(i);
        }

        split_tree(tree,centroid);
        for (int i : nodes_to_execute_for) {
            int centroid2 = find_centroid(tree,i);
            centroid_tree[centroid2].pb(centroid);
            centroid_tree[centroid].pb(centroid2);
            perform_construction(tree,centroid2);
        }
    }

    void split_tree(vector<unordered_set<int>> &tree, int centroid) {
        for (int i : tree[centroid]) {
            tree[i].erase(centroid);
        }
        tree[centroid].clear();
    }

    int get_nodes_in_subtrees_dfs(int at, unordered_set<int> &visited, unordered_map<int,int> &dp, vector<int> &nodes_in_component,
                vector<unordered_set<int>> &tree) {
        visited.insert(at);
        nodes_in_component.pb(at);

        int nodes = 1;
        for (int i : tree[at]) {
            if (visited.find(i) == visited.end()) {
                nodes += get_nodes_in_subtrees_dfs(i,visited,dp,nodes_in_component,tree);
            }
        }

        return dp[at] = nodes;
    }

    pair<unordered_map<int,int>,vector<int>> get_nodes_in_subtrees(vector<unordered_set<int>> &tree, int component) {
        unordered_map<int,int> dp;
        vector<int> nodes_in_component;

        unordered_set<int> visited;
        get_nodes_in_subtrees_dfs(component, visited, dp, nodes_in_component, tree);

        return {dp,nodes_in_component};
    }    

    int find_centroid(vector<unordered_set<int>> &tree, int component) {
        auto res = get_nodes_in_subtrees(tree,component);
        unordered_map<int,int> nodes_in_subtrees = res.first;
        vector<int> nodes_in_component = res.second;
        int total_nodes_in_component = nodes_in_subtrees[component];

        for (int u : nodes_in_component) {
            int max_nodes = 0;
            for (int v : tree[u]) {
                if (nodes_in_subtrees[v] > nodes_in_subtrees[u]) {
                    // Parent node
                    max_nodes = max(max_nodes, total_nodes_in_component-nodes_in_subtrees[u]);
                } else {
                    // Child node
                    max_nodes = max(max_nodes, nodes_in_subtrees[v]);
                }
            }

            if (max_nodes <= total_nodes_in_component/2) {
                return u;
            }
        }

        // Should theoretically never happen as every single tree has atleast a single centroid
        return -1;
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

    centroid_decomposition decomposition(tree);

    return 0;
}