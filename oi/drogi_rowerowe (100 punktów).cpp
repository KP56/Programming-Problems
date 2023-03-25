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

void topSortDFS(int at, vector<bool> &vis, vector<vector<int>> &adj_list, stack<int> &top_ordering) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            topSortDFS(i, vis, adj_list, top_ordering);
        }
    }

    top_ordering.push(at);
}

vector<int> topSort(vector<vector<int>> &adj_list) {
    vector<bool> vis(adj_list.size());
    stack<int> topological_ordering;

    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            topSortDFS(i, vis, adj_list, topological_ordering);
        }
    }

    vector<int> res;
    while (!topological_ordering.empty()) {
        res.pb(topological_ordering.top());
        topological_ordering.pop();
    }

    return res;
}

void sccDFS(int at, vector<bool> &vis, vector<vector<int>> &adj_list, vector<int> &scc) {
    vis[at] = true;
    scc.pb(at);

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            sccDFS(i, vis, adj_list, scc);
        }
    }
}

vector<vector<int>> findSCCs(vector<vector<int>> &adj_list) {
    vector<vector<int>> rev_list(adj_list.size());
    for (int i = 0; i < adj_list.size(); i++) {
        for (int j : adj_list[i]) {
            rev_list[j].pb(i);
        }
    }

    vector<int> top_ordering = topSort(adj_list);
    vector<bool> vis(adj_list.size());
    vector<vector<int>> res;
    for (int i : top_ordering) {
        if (!vis[i]) {
            vector<int> scc;
            sccDFS(i, vis, rev_list, scc);
            res.pb(scc);
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<vector<int>> adj_list(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);

        adj_list[a - 1].pb(b - 1);
    }

    vector<vector<int>> sccs = findSCCs(adj_list);
    vector<int> reverse_scc(n);
    for (int i = 0; i < sccs.size(); i++) {
        for (int j : sccs[i]) {
            reverse_scc[j] = i;
        }
    }

    vector<vector<int>> construct_rev(sccs.size());
    vector<vector<int>> construct(sccs.size());
    for (int i = 0; i < sccs.size(); i++) {
        for (int j : sccs[i]) {
            for (int k : adj_list[j]) {
                if (reverse_scc[k] != i) {
                    construct_rev[reverse_scc[k]].pb(i);
                    construct[i].pb(reverse_scc[k]);
                }
            }
        }
    }

    vector<int> scc_res(sccs.size());
    vector<int> currents(sccs.size());
    vector<int> top_sort = topSort(construct_rev);
    for (int i : top_sort) {
        for (int j : construct[i]) {
            currents[i] += currents[j];
            scc_res[i] += currents[j];
        }
        currents[i] += sccs[i].size();
    }

    for (int i = 0; i < n; i++) {
        int s = sccs[reverse_scc[i]].size();
        cout << scc_res[reverse_scc[i]] + s - 1 << endl;
    }
}