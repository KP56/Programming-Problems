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
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

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

vector<vector<pair<int,bool>>> labelEach(vector<vector<int>> &graph) {
    //Moim zadaniem tutaj jest zamienienie grafu obustronnie skierowanego
    //w jednostronnie skierowany, którego wszystkie ścieżki prowadzą
    //do wierzchołka 1

    //Jak to zaimplementuję to zadanie będzie rozwiązane
}

vector<int> out;
stack<int> s;
void topSort(int at, vector<vector<pair<int,bool>>> &graph, vector<bool> &vis) {
    vis[at] = true;

    for (auto i : graph[at]) {
        if (i.second && !vis[i.first]) {
            topSort(i.first,graph,vis);
        }
    }

    s.push(at);
}

void solve(vector<vector<int>> &graph) {
    auto labeled = labelEach(graph);
    out = vector<int>(graph.size());
    vector<bool> vis(graph.size());
    topSort(0,labeled,vis);
    int current_node = 1;
    while (!s.empty()) {
        cout << s.top() << " ";
        out[s.top()] = current_node;
        s.pop();
        current_node++;
    }
    cout << endl;
    for (int i : out) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(dwarfs);
    in_i(friend_pairs);

    vector<vector<int>> graph(dwarfs);
    for (int i = 0; i < friend_pairs; i++) {
        in_i(a);
        in_i(b);
        graph[a - 1].pb(b - 1);
        graph[b - 1].pb(a - 1);
    }

    solve(graph);   
}