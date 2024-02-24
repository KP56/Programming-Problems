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

vector<vector<int>> graph;
vector<int> under;
vector<unordered_map<int,vector<int>,custom_hash>> dist_vec;
vector<unordered_map<int,int,custom_hash>> dist_vec2;
vector<unordered_map<int,unordered_map<int,vector<int>,custom_hash>,custom_hash>> dist_vec_specific;
vector<unordered_map<int,int,custom_hash>> subtree;
vector<int> centroid_decomp;
vector<bool> vis;
int dfs(int at, int prev, int dist, int c, int initial) {
    under[at] = 1;
    if (c != -1) {
        dist_vec[c][dist].pb(at);
        dist_vec2[c][at] = dist;
        dist_vec_specific[c][initial][dist].pb(at);
        subtree[c][at] = initial;
    }

    for (int i : graph[at]) {
        if (prev != i && !vis[i]) {
            under[at] += dfs(i,at,dist+1,c,initial);
        }
    }

    return under[at];
}

int find_centroid(int at, int prev, int n) {
    for (int i : graph[at]) {
        if (i != prev && !vis[i]) {
            if (under[i] > n / 2) return find_centroid(i,at,n);
        }
    }

    return at;
}

void build(int at, int c) {
    int nodes_in_subtree = dfs(at,c,1,c,at);
    int new_centroid = find_centroid(at,c,nodes_in_subtree);

    centroid_decomp[new_centroid] = c;
    vis[new_centroid] = true;

    for (int i : graph[new_centroid]) {
        if (!vis[i]) {
            build(i,new_centroid);
        }
    }
}

vector<vector<int>> random_tree_naive(int size) {
    vector<vector<int>> current_tree;

    current_tree.push_back({});
    for (int i = 1; i < size; i++) {
        int parent = rand() % current_tree.size();
        current_tree.push_back({parent});
        current_tree[parent].push_back(i);
    }

    return current_tree;
}

int find_paths_dfs(int at, int dist, vector<bool> &vis, int k) {
    vis[at] = true;

    int paths = (dist == k);
    for (int i : graph[at]) {
        if (!vis[i]) {
            paths += find_paths_dfs(i,dist+1,vis,k);
        }
    }

    return paths;
}

int paths_bruteforce(int k) {
    int sum = 0;
    for (int i = 0; i < graph.size(); i++) {
        vector<bool> vis(graph.size());
        sum += find_paths_dfs(i,0,vis,k);
    }

    return sum / 2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 10 + 1;
    ini(k);
    //int k = rand() % 10 + 1;

    graph = vector<vector<int>>(n);
    under = vector<int>(n);
    dist_vec = vector<unordered_map<int,vector<int>,custom_hash>>(n);
    dist_vec2 = vector<unordered_map<int,int,custom_hash>>(n);
    dist_vec_specific = vector<unordered_map<int,unordered_map<int,vector<int>,custom_hash>,custom_hash>>(n);
    subtree = vector<unordered_map<int,int,custom_hash>>(n);
    centroid_decomp = vector<int>(n,-1);
    vis = vector<bool>(n);

    for (int i = 0; i < n-1; i++) {
        ini(a);
        ini(b);

        graph[a-1].pb(b-1);
        graph[b-1].pb(a-1);
    }
    //graph = random_tree_naive(n);

    build(0,-1);

    int res = 0;
    for (int i = 0; i < n; i++) {
        int current_node = i;
        //int prev_node = -1;
        while (current_node != -1) {
            int distance = dist_vec2[current_node][i];
            if (distance == k) {
                res++;
            }
            vector<int> &vec = dist_vec[current_node][k-distance];
            /*if (prev_node != -1) {
                vector<int> &vec2 = dist_vec[prev_node][k-distance-1];
                res -= vec2.size();
            }*/

            if (subtree[current_node].find(i) != subtree[current_node].end()) {
                vector<int> &vec2 = dist_vec_specific[current_node][subtree[current_node][i]][k-distance];
                res -= vec2.size();
            }

            res += vec.size();
            //prev_node = current_node;
            current_node = centroid_decomp[current_node];
        }
    }

    /*int brute_res = paths_bruteforce(k);
    if (res / 2 != brute_res) {
        int test = 0;
    }*/

    cout << res / 2 << endl;
}