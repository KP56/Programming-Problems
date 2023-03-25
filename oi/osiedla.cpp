#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define inll(x) ll x; in(x)
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

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

void bridgesDFS(int at, int prev, vector<unordered_multiset<int>> &adj_list, vector<bool> &vis, vector<int> &low, vector<int> &timer,
        int &counter, vector<pii> &bridges) {
    vis[at] = true;
    timer[at] = low[at] = counter++;

    for (int i : adj_list[at]) {
        if (i == prev) continue;
        if (vis[i]) {
            low[at] = min(low[at], timer[i]);
        } else {
            bridgesDFS(i, at, adj_list, vis, low, timer, counter, bridges);
            low[at] = min(low[at], low[i]);
            if (low[i] > timer[at] && adj_list[at].count(i) == 1) {
                bridges.pb({at,i});
            }
        }
    }
}

vector<pii> findBridges(vector<unordered_multiset<int>> &adj_list) {
    vector<bool> vis(adj_list.size());
    vector<int> low(adj_list.size(),-1);
    vector<int> timer(adj_list.size(),-1);
    int counter = 0;
    vector<pii> bridges;

    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            bridgesDFS(i, -1, adj_list, vis, low, timer, counter, bridges);
        }
    }

    return bridges;
}

void solveDFS(int at, int prev, vector<bool> &vis, vector<unordered_multiset<int>> &adj_list, vector<unordered_map<int,pair<int,bool>>> &edges, vector<bool> &solution) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (i == prev) continue;
        solution[edges[at][i].first] = edges[at][i].second;
        if (!vis[i]) {
            solveDFS(i,at,vis,adj_list,edges,solution);
        }
    }
}

void solve(vector<unordered_multiset<int>> &adj_list, vector<unordered_map<int,pair<int,bool>>> &edges, vector<bool> &solution) {
    vector<bool> vis(adj_list.size());
    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            solveDFS(i,-1,vis,adj_list,edges,solution);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    
    vector<unordered_map<int,pair<int,bool>>> edges(n);
    vector<unordered_multiset<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        adj_list[a - 1].insert(b - 1);
        adj_list[b - 1].insert(a - 1);
        edges[a - 1][b - 1] = {i,true};
        edges[b - 1][a - 1] = {i,false};
    }

    vector<pii> bridges = findBridges(adj_list);
    for (pii bridge : bridges) {
        adj_list[bridge.first].erase(bridge.second);
        adj_list[bridge.second].erase(bridge.first);
    }

    vector<bool> solution(m);

}