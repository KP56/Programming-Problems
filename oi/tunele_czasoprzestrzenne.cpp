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

void dfs(int at, vector<bool> &vis, vector<bool> &vis2, vector<unordered_map<int,int>> &graph, vector<int> &dist) {
    vis[at] = true;
    vis2[at] = true;

    for (auto &i : graph[at]) {
        // aktualizujemy dist
        dist[i.first] = min(dist[i.first], dist[at] + i.second);

        if (!vis2[i.first]) {
            dfs(i.first,vis,vis2,graph,dist);
        }
    }
}

bool contains_negative_cycle(vector<unordered_map<int,int>> &graph) {
    vector<bool> vis(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            vector<int> dist(graph.size(),INT_MAX);
            dist[i] = 0;
            for (int j = 0; j < graph.size() - 1; j++) {
                vector<bool> vis2(graph.size());
                dfs(i,vis,vis2,graph,dist);
            }

            vector<int> dist_cp = dist;
            vector<bool> vis2(graph.size());
            dfs(i,vis,vis2,graph,dist_cp);

            if (dist != dist_cp) {
                // odnaleźliśmy negatywny cykl
                return true;
            }
        }
    }

    // nie ma negatywnego cyklu
    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(q);

    vector<unordered_map<int,int>> graph(n);
    vector<pii> tunnels;
    for (int i = 0; i < q; i++) {
        instr(type);

        if (type == "B") {
            // budowa
            ini(a);
            ini(b);
            ini(c);

            tunnels.pb({a-1,b-1});

            graph[a-1][b-1] = c;
        } else {
            // zniszczenie
            ini(a);
            a--;

            graph[tunnels[a].first].erase(tunnels[a].second);

            tunnels.pb({-1,-1});
        }

        // teraz sprawdzamy czy istnieje negatywny cykl
        bool res = contains_negative_cycle(graph);

        if (res) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }
    }
}