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

void dfs(int at, vector<bool> &vis, stack<int> &top_sort, vector<vector<int>> &adj_list) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (!vis[i]) {
            dfs(i, vis, top_sort, adj_list);
        }
    }

    top_sort.push(at);
}

vector<int> topologicalSort(vector<vector<int>> &adj_list) {
    vector<bool> vis(adj_list.size());
    stack<int> top_sort;
    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            dfs(i, vis, top_sort, adj_list);
        }
    }

    vector<int> res;
    while (!top_sort.empty()) {
        res.pb(top_sort.top());
        top_sort.pop();
    }

    return res;
}

bool correctDFS(int at, vector<bool> &vis, vector<vector<int>> &adj_list, vector<int> &depths) {
    vis[at] = true;

    for (int i : adj_list[at]) {
        if (depths[i] > depths[at]) {
            if (!vis[i]) {
                if (!correctDFS(i, vis, adj_list, depths)) {
                    return false;
                }
            }
        } else {
            return false;
        }
    }

    return true;
}

bool isCorrect(vector<vector<int>> &adj_list, vector<int> &depths) {
    for (int i : depths) {
        if (i > 1000000000 || i < 1) {
            return false;
        }
    }

    vector<bool> vis(adj_list.size());
    for (int i = 0; i < adj_list.size(); i++) {
        if (!vis[i]) {
            if (!correctDFS(i, vis, adj_list, depths)) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(wells);
    ini(data);

    vector<int> depths(n,-1);
    for (int i = 0; i < wells; i++) {
        ini(pos);
        ini(depth);
        depths[pos - 1] = depth;
    }

    vector<vector<int>> adj_list(n);
    vector<vector<int>> rev_graph(n);
    for (int i = 0; i < data; i++) {
        ini(l);
        ini(r);
        l--;
        r--;
        ini(k);
        
        unordered_set<int> s;
        for (int j = 0; j < k; j++) {
            ini(x);
            s.insert(x - 1);
        }

        for (int i = l; i <= r; i++) {
            if (s.find(i) == s.end()) {
                for (int j : s) {
                    adj_list[i].pb(j);
                    rev_graph[j].pb(i);
                }
            }
        }
    }

    vector<int> top_sort = topologicalSort(adj_list);
    for (int i : top_sort) {
        if (depths[i] == -1) {
            int m = 0;
            for (int j : rev_graph[i]) {
                m = max(depths[j], m);
            }
            m++;
            depths[i] = m;
        }
    }

    if (isCorrect(adj_list, depths)) {
        cout << "TAK" << endl;
        for (int i : depths) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        cout << "NIE" << endl;
    }
}