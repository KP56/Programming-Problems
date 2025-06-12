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

void dfs(int at, int prev, int color, int dist, int dist_max, vector<int> &colors, vector<unordered_map<int,int,custom_hash>> &graph) {
    colors[at] = color;

    for (auto &i : graph[at]) {
        if (dist + i.second <= dist_max) {
            if (i.first != prev) {
                dfs(i.first,at,color,dist+i.second,dist_max,colors,graph);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    ini(q);

    vector<unordered_map<int,int,custom_hash>> graph(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        ini(d);

        a--;
        b--;

        graph[a][b] = d;
        graph[b][a] = d;
    }

    vector<int> colors(n);
    for (int i = 0; i < q; i++) {
        ini(type);
        if (type == 1) {
            ini(a);
            ini(b);
            ini(d);

            a--;
            b--;

            // dodajemy krawędź a->b o długości d
            graph[a][b] = d;
            graph[b][a] = d;
        } else if (type == 2) {
            ini(a);
            ini(b);

            a--;
            b--;

            // usuwamy krawędź {a,b}
            graph[a].erase(b);
            graph[b].erase(a);
        } else if (type == 3) {
            ini(v);
            ini(z);
            ini(k);

            v--;

            // przemalowujemy wszystkie wierzchołki odległe o maksymalnie z od v na kolor k
            dfs(v,-1,k,0,z,colors,graph);
        } else {
            ini(u);
            u--;

            // aktualny kolor u
            cout << colors[u] << endl;
        }
    }
}