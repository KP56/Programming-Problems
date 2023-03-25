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

void dfs(int at, vector<bool> &vis, vector<vector<int>> &adj_list) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            dfs(i, vis, adj_list);
        }
    }
}

void topSortDFS(int at, vector<bool> &vis, vector<vector<int>> &adj_list, stack<int> &s) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            topSortDFS(i, vis, adj_list, s);
        }
    }

    s.push(at);
}

vector<int> topSort(vector<vector<int>> &adj_list) {
    vector<bool> vis(adj_list.size());
    stack<int> s;
    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            topSortDFS(i, vis, adj_list, s);
        }
    }
    
    vector<int> vec;
    while (!s.empty()) {
        vec.pb(s.top());
        s.pop();
    }

    return vec;
}

void sccDFS(int at, vector<bool> &vis, vector<vector<int>> &rev_graph, vector<int> &component) {
    vis[at] = true;
    component.pb(at);

    for (int i : rev_graph[at]) {
        if (!vis[i]) {
            sccDFS(i, vis, rev_graph, component);
        }
    }
}

vector<vector<int>> scc(vector<vector<int>> &adj_list, vector<vector<int>> &rev_graph) {
    vector<int> topological = topSort(adj_list);

    vector<bool> vis(adj_list.size());
    vector<vector<int>> res;
    for (int i : topological) {
        if (!vis[i]) {
            vector<int> component;
            sccDFS(i, vis, rev_graph, component);
            res.pb(component);
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<vector<int>> adj_list1(n);
    vector<vector<int>> adj_list2(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        adj_list1[a - 1].pb(b - 1);
        adj_list2[b - 1].pb(a - 1);
    }
    
    vector<int> res;
    if (n <= 5000 && m <= 5000) {
        for (int i = 0; i < n; i++) {
            vector<bool> vis(n);
            vector<bool> vis2(n);

            dfs(i, vis, adj_list1);
            dfs(i, vis2, adj_list2);

            bool atleast_in_one = true;
            for (int j = 0; j < n; j++) {
                if (!vis[j] && !vis2[j]) {
                    atleast_in_one = false;
                    break;
                }
            }
        
            if (atleast_in_one) {
                res.pb(i);
            }
        }
    } else {
        vector<vector<int>> vec = scc(adj_list1, adj_list2);
        vector<int> reversed(adj_list1.size());
        for (int i = 0; i < vec.size(); i++) {
            for (int j : vec[i]) {
                reversed[j] = i;
            }
        }

        vector<unordered_set<int>> constructed(vec.size());
        for (int i = 0; i < reversed.size(); i++) {
            for (int j : adj_list1[i]) {
                if (reversed[i] != reversed[j]) {
                    constructed[reversed[i]].insert(reversed[j]);
                }
            }
        }

        vector<vector<int>> reversed_constructed(vec.size());
        for (int i = 0; i < vec.size(); i++) {
            for (int j : constructed[i]) {
                reversed_constructed[j].pb(i);
            }
        }

        for (int i = 0; i < vec.size(); i++) {
            if (reversed_constructed[i].empty()) {
                for (int j : vec[i]) {
                    res.pb(j);
                }
            }
        }

        sort(all(res));
    }

    cout << res.size() << endl;
    for (int i : res) {
        cout << i + 1 << " ";
    }
    cout << endl;
}