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


//Finding the number of nodes for each subtree rooted at node u
int findNodes(int u, vector<vector<int>> &tree, vector<bool> &vis, vector<int> &node_count) {
    vis[u] = true;
    
    int sum = 0;
    for (int i : tree[u]) {
        if (!vis[i]) {
            sum += findNodes(i, tree, vis, node_count);
        }
    }

    return node_count[u] = sum + 1;
}

//Finding the sum of distances of each node in a subtree rooted at node u to root
int sumOfDists(int u, vector<vector<int>> &tree, vector<int> &node_count, vector<bool> &vis, vector<int> &subtree_dists) {
    vis[u] = true;

    int sum = 0;
    for (int i : tree[u]) {
        if (!vis[i]) {
            sum += sumOfDists(i, tree, node_count, vis, subtree_dists) + node_count[i];
        }
    }

    return subtree_dists[u] = sum;
}

int solveRecursively(int u, vector<vector<int>> &tree, vector<int> &node_count, vector<int> &subtree_dists, vector<bool> &vis) {
    vis[u] = true;

    int sum = 0;
    int y_sum = 0;
    vector<int> visited;
    for (int i : tree[u]) {
        if (!vis[i]) {
            visited.pb(i);
            int solution = solveRecursively(i, tree, node_count, subtree_dists, vis);
            sum += solution + node_count[i] + subtree_dists[i];
            y_sum += node_count[i];
        }
    }

    for (int i : visited) {
        sum += (subtree_dists[i] + node_count[i]) * (y_sum - node_count[i]);
    }

    return sum % 1000000007;
}

int sumOfAllPaths(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());
    vector<int> node_count(tree.size());
    vector<int> subtree_dists(tree.size());

    findNodes(0, tree, vis, node_count);
    vis = vector<bool>(tree.size());
    sumOfDists(0, tree, node_count, vis, subtree_dists);
    vis = vector<bool>(tree.size());

    return solveRecursively(0, tree, node_count, subtree_dists, vis);
}

int pow(int x, int y, int mod) {
    int res = x;
    int i = 2;
    for (; i <= y; i <<= 1) {
        res *= res;
        res %= mod;
    }

    if ((i >> 1) < y) {
        return (res*pow(x, y - (i >> 1), mod)) % mod;
    }

    return res % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        ini(u);
        ini(v);

        tree[u - 1].pb(v - 1);
        tree[v - 1].pb(u - 1);
    }

    if (k == 1 || k == 3) {
        cout << 1 << endl;
        return 0;
    }

    int sum = sumOfAllPaths(tree);
    //The answer in case of k=2 is sum/(n(n-1)/2)
    int lower_part = n*(n-1)/2 % 1000000007;
    //Taking into account the fact that also the nodes representing people are "good"
    sum += lower_part;
    int modular_inverse = pow(lower_part, 1000000007 - 2, 1000000007);
    int ans = ((sum % 1000000007) * modular_inverse) % 1000000007;

    cout << ans << endl;
}