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
vector<unordered_map<int,int,custom_hash>> distances;
vector<int> min_table;
vector<int> centroid_tree;
vector<int> nodes_under;
vector<bool> vis;

int find_node_count_and_dist(int u, int prev, int dist, int centroid) {
    if (centroid != -1) {
        distances[centroid][u] = dist;
    }

    int sum = 1;
    for (int i : graph[u]) {
        if (!vis[i] && i != prev) {
            sum += find_node_count_and_dist(i,u,dist+1,centroid);
        }
    }

    return nodes_under[u] = sum;
}

int find_centroid(int u, int prev, int n) {
    for (int i : graph[u]) {
        if (prev != i && !vis[i]) {
            if (nodes_under[i] > n / 2) return find_centroid(i,u,n);
        }
    }

    return u;
}

void build(int u, int centroid) {
    int n = find_node_count_and_dist(u,centroid,1,centroid);
    int new_centroid = find_centroid(u,centroid,n);

    vis[new_centroid] = true;

    centroid_tree[new_centroid] = centroid;

    for (int i : graph[new_centroid]) {
        if (!vis[i]) {
            build(i,new_centroid);
        }
    }
}

void update_min_table(int u) {
    int current_node = u;
    while (current_node != -1) {
        min_table[current_node] = min(min_table[current_node],distances[current_node][u]);

        current_node = centroid_tree[current_node];
    }
}

int find_shortest_distance(int u) {
    int dist = INT_MAX;
    int current_node = u;
    while (current_node != -1) {
        dist = min(dist,min_table[current_node]+distances[current_node][u]);

        current_node = centroid_tree[current_node];
    }

    return dist;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    graph = vector<vector<int>>(n);
    distances = vector<unordered_map<int,int,custom_hash>>(n);
    min_table = vector<int>(n,INT_MAX);
    nodes_under = vector<int>(n);
    centroid_tree = vector<int>(n);
    vis = vector<bool>(n);
    for (int i = 0; i < n-1; i++) {
        ini(a);
        ini(b);

        graph[a-1].pb(b-1);
        graph[b-1].pb(a-1);
    }

    // building centroid decomposition
    build(0,-1);

    // first node is initially red
    update_min_table(0);

    for (int i = 0; i < m; i++) {
        ini(type);
        ini(u);

        u--;

        if (type == 1) {
            // update min table
            update_min_table(u);
        } else {
            // find shortest distance
            cout << find_shortest_distance(u) << endl;
        }
    }
}