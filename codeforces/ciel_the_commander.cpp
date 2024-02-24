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
vector<bool> vis;
vector<vector<int>> centroid_tree;
vector<int> under_count;

int find_under(int u, int prev) {
    int sum = 1;
    for (int i : graph[u]) {
        if (!vis[i] && i != prev) {
            sum += find_under(i,u);
        }
    }

    return under_count[u] = sum;
}

int find_centroid(int u, int prev, int n) {
    for (int i : graph[u]) {
        if (i != prev && !vis[i]) {
            if (under_count[i] > n / 2) return find_centroid(i,u,n);
        }
    }

    return u;
}

int first_centroid = -1;
void build(int u, int centroid) {
    int n = find_under(u,centroid);
    int new_centroid = find_centroid(u,centroid,n);
    vis[new_centroid] = true;
    if (first_centroid == -1) first_centroid = new_centroid;
    if (centroid != -1) {
        centroid_tree[centroid].pb(new_centroid);
    }

    for (int i : graph[new_centroid]) {
        if (!vis[i]) {
            build(i,new_centroid);
        }
    }
}

vector<char> letters;
void assign_letters_dfs(int at, char letter) {
    letters[at] = letter;

    for (int i : centroid_tree[at]) {
        assign_letters_dfs(i,letter+1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);

    vis = vector<bool>(n);
    graph = vector<vector<int>>(n);
    under_count = vector<int>(n);
    centroid_tree = vector<vector<int>>(n);

    for (int i = 0; i < n-1; i++) {
        ini(a);
        ini(b);

        graph[a-1].pb(b-1);
        graph[b-1].pb(a-1);
    }

    build(0,-1);

    letters = vector<char>(n);
    assign_letters_dfs(first_centroid,'A');

    for (char c : letters) {
        cout << string(1,c) << " ";
    }
    cout << endl;
}