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

const int N = 2e5+10;
const int M = 5e3+10;

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

int modpow(int b, int e, int m) {
    int ans = 1;
    for (; e; b = b * b % m, e /= 2)
        if (e & 1) ans = ans * b % m;
    return ans;
}

int primsMST (int source_node, vector<vector<pii>> &graph){
    priority_queue<pii, vector<pii>, greater<pii>> q;

    q.push(mp(0, source_node));

    vector<bool> added(graph.size());

    int mst_cost = 0;

    while (!q.empty()) {
        pii item;
        item = q.top();
        q.pop();

        int node = item.second;
        int cost = item.first;

        if (!added[node]) {
            mst_cost += cost;
            added[node] = true;

            for (auto & pair_cost_node : graph[node]) {
                int adj_node = pair_cost_node.second;
                if (added[adj_node] == false) {
                    q.push(pair_cost_node);
                }
            }
        }
    }

    return mst_cost;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    vector<int> a_vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        a_vec.pb(a);
    }

    vector<vector<pii>> adj_list(n);
    for (int i = 0; i < a_vec.size(); i++) {
        for (int j = 0; j < a_vec.size(); j++) {
            if (i != j) {
                int a = (modpow(a_vec[i],a_vec[j],m)+modpow(a_vec[j],a_vec[i],m))%m;
                adj_list[i].pb({-a,j});
            }
        }
    }

    cout << -primsMST(0,adj_list) << endl;
}