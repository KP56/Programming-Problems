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

void dfs(int at, vector<vector<pii>> &adj_list, vector<bool> &vis, vector<vector<pii>> &new_adj_list, vector<pii> &parents) {
    vis[at] = true;

    for (auto i : adj_list[at]) {
        if (!vis[i.first]) {
            new_adj_list[at].pb(i);
            parents[i.first] = {at,i.second};
            dfs(i.first, adj_list, vis, new_adj_list, parents);
        }
    }
}

pair<vector<pii>,vector<vector<pii>>> rootTree(vector<vector<pii>> &adj_list) {
    vector<bool> vis(adj_list.size());
    vector<vector<pii>> new_adj_list(adj_list.size());
    vector<pii> parents(adj_list.size());

    dfs(0,adj_list,vis,new_adj_list,parents);

    return {parents,new_adj_list};
}

void depthsDFS(int at, vector<bool> &vis, vector<vector<pii>> &adj_list, int depth, vector<int> &depths) {
    vis[at] = true;
    depths[at] = depth;

    for (auto i : adj_list[at]) {
        if (!vis[i.first]) {
            depthsDFS(i.first,vis,adj_list,depth + 1,depths);
        }
    }
}

vector<int> findDepths(vector<vector<pii>> &adj_list) {
    vector<bool> vis(adj_list.size());
    vector<int> depths(adj_list.size());
    depthsDFS(0,vis,adj_list,0,depths);
    return depths;
}

pair<pii,unordered_set<int>> findPath(int a, int b, vector<pii> &parents, vector<int> &depths) {
    int path_len = 0;
    vector<int> path_a;
    vector<int> path_b;
    path_a.pb(a);
    path_b.pb(b);
    while (depths[a] != depths[b]) {
        if (depths[a] > depths[b]) {
            path_len += parents[a].second;
            a = parents[a].first;
            path_a.pb(a);
        } else {
            path_len += parents[b].second;
            b = parents[b].first;
            path_b.pb(b);
        }
    }

    while (a != b) {
        path_len += parents[a].second + parents[b].second;
        a = parents[a].first;
        b = parents[b].first;
        path_a.pb(a);
        path_b.pb(b);
    }

    unordered_set<int> path;
    for (int i : path_a) {
        path.insert(i);
    }

    for (int i = path_b.size() - 2; i >= 0; i--) {
        path.insert(path_b[i]);
    }

    return {{path_len,path_a[path_a.size() - 1]},path};
}

int closestOfTypeDFS(int at, vector<vector<pii>> &adj_list, vector<bool> &vis, int dist, int type, vector<int> &types, unordered_set<int> &path) {
    vis[at] = true;

    if (types[at] == type) return dist;

    int closest = INT_MAX;
    for (auto i : adj_list[at]) {
        if (!vis[i.first] && path.find(i.first) == path.end()) {
            closest = min(closest, closestOfTypeDFS(i.first,adj_list,vis,dist + i.second, type, types, path));
        }
    }

    return closest;
}

int closestOfType(vector<vector<pii>> &adj_list, unordered_set<int> &path, int type, vector<int> &types) {
    for (int i : path) {
        if (types[i] == type) return 0;
    }

    vector<bool> vis(adj_list.size());
    int closest = INT_MAX;
    for (int i : path) {
        closest = min(closest, closestOfTypeDFS(i,adj_list,vis,0,type,types,path));
    }
    return closest;
}

int closestOfTypeFromDFS(int at, int type, vector<vector<pii>> &adj_list, vector<bool> &vis, vector<int> &types, unordered_set<int> &path, int dist) {
    vis[at] = true;

    if (types[at] == type) return dist;

    int closest = INT_MAX;
    for (auto i : adj_list[at]) {
        if (!vis[i.first] && path.find(i.first) == path.end()) {
            closest = min(closest, closestOfTypeDFS(i.first,adj_list,vis,dist + i.second, type, types, path));
        }
    }

    return closest;
}

int closestOfTypeFrom(vector<vector<pii>> &adj_list, int at, int type, vector<int> &types, unordered_set<int> &path) {
    vector<bool> vis(adj_list.size());
    return closestOfTypeFromDFS(at,type,adj_list,vis,types,path,0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(r);
    vector<vector<pii>> adj_list(n);
    vector<int> types;
    for (int i = 0; i < n; i++) {
        ini(t);
        types.pb(t);
    }

    for (int i = 0; i < n - 1; i++) {
        ini(a);
        ini(b);
        ini(c);
        adj_list[a - 1].pb({b - 1, c});
        adj_list[b - 1].pb({a - 1, c});
    }

    ini(q);
    vector<vector<int>> queries;
    for (int i = 0; i < q; i++) {
        ini(a);
        ini(b);
        ini(c);

        queries.pb({a,b,c});
    }

    if (n <= 1000) {
        unordered_map<int,int> type_mappings;
        int global_counter = 0;
        for (int i = 0; i < n; i++) {
            if (type_mappings.find(types[i]) == type_mappings.end()) {
                type_mappings[types[i]] = global_counter++;
                types[i] = global_counter - 1;
            } else {
                types[i] =  type_mappings[types[i]];
            }
        }

        auto p = rootTree(adj_list);
        vector<pii> parents = p.first;
        vector<vector<pii>> rooted = p.second;
        vector<int> depths = findDepths(rooted);

        for (auto query : queries) {
            int a = query[0] - 1;
            int b = query[1] - 1;

            if (type_mappings.find(query[2]) == type_mappings.end()) {
                cout << -1 << endl;
                continue;
            }

            int type = type_mappings[query[2]];
            
            auto p2 = findPath(a,b,parents,depths);
            int path_len = p2.first.first;
            unordered_set<int> path = p2.second;
            
            int res = min(closestOfType(rooted,path,type,types),closestOfTypeFrom(adj_list,p2.first.second,type,types,path));
            if (res == INT_MAX) {
                cout << -1 << endl;
            } else {
                cout << path_len + res * 2 << endl;
            }
        }
    }
}