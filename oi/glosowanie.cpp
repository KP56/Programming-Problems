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

struct node {
    // Vector containing nodes which are yet to be chosen by player A
    vector<int> not_yet_chosen_a;

    // Lowest LCA of this node and any node that was selected by player A
    int min_node = -1;
};

struct centroid_decomposition {
    vector<unordered_set<int>> centroid_tree;
    vector<int> parents;

    centroid_decomposition(vector<unordered_set<int>> &tree) {
        centroid_tree = vector<unordered_set<int>>(tree.size());
        parents = vector<int>(tree.size());

        construct_tree(tree);
        find_parents();
    }

    void find_parents_dfs(int at, int prev, vector<bool> &vis, vector<unordered_set<int>> &tree) {
        vis[at] = true;
        parents[at] = prev;

        for (int i : tree[at]) {
            if (!vis[i]) {
                find_parents_dfs(i,at,vis,tree);
            }
        }
    }

    void find_parents() {
        vector<bool> vis(centroid_tree.size());

        find_parents_dfs(0,-1,vis,centroid_tree);
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
            centroid_tree[centroid2].insert(centroid);
            centroid_tree[centroid].insert(centroid2);
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

// Problem: powinienem zignorować ten wierzchołek, który właśnie rozważamy
void select(int selected, centroid_decomposition &decomposition, fast_lca_finder &finder, vector<node> &nodes) {
    // Zaczynamy wyszukanie od parenta na dekompozycji tego wierzchołka selected
    for (int current = decomposition.parents[selected]; current != -1; current = decomposition.parents[selected]) {
        int min_height = finder.levels[nodes[current].min_node];
        int lca_res = finder.lca(current,selected);
        int current_lca_height = finder.levels[lca_res];

        if (current_lca_height < min_height) {
            nodes[current].min_node = lca_res;
        }
    }
}

int find_closest_parent(int selected, centroid_decomposition &decomposition, fast_lca_finder &finder, vector<node> &nodes) {
    // Zaczynamy wyszukanie od parenta na dekompozycji tego wierzchołka selected
    int closest_parent = -1;
    for (int current = decomposition.parents[selected]; current != -1; current = decomposition.parents[selected]) {
        if (nodes[current].min_node != -1) {
            int lca_with_min = finder.lca(nodes[current].min_node,current);
            if (closest_parent != -1 && finder.levels[lca_with_min] < finder.levels[closest_parent]) {
                closest_parent = lca_with_min;
            }
        }
    }

    return closest_parent;
}

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

    fast_lca_finder finder = fast_lca_finder(0,tree);
    vector<node> nodes(tree.size());

    
}