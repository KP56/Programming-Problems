#include <bits/stdc++.h>
#include <any>

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
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

class Graph {
private:
    vector<vector<int>> adjacency_list;

    void dfsUtils(int at, function<bool(int,vector<any>&,Graph&)> &func, vector<any> values, vector<bool> &vis) {
        vis[at] = true;

        for (int i : adjacency_list[at]) {
            vector<any> value_copy = values;
            if (!vis[i] && func(i,value_copy,*this)) {
                dfsUtils(i, func, value_copy, vis);
            }
        }
    }
public:
    Graph(int nodes) {
        adjacency_list = vector<vector<int>>(nodes);
    }

    Graph(vector<vector<int>> adjacency_list) {
        this->adjacency_list = adjacency_list;
    }

    void connect(int n1, int n2) {
        adjacency_list[n1].push_back(n2);
    }

    void createNode() {
        adjacency_list.emplace_back();
    }

    void dfs(int starting_point, function<bool(int,vector<any>&,Graph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        if (func(starting_point, val,*this)) {
            dfsUtils(starting_point, func, val, vis);
        }
    }

    void dfs(function<bool(int,vector<any>&,Graph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        for (int i = 0; i < adjacency_list.size(); i++) {
            if (!vis[i] && func(i,val,*this)) {
                dfsUtils(i, func, val, vis);
            }
        }
    }

    vector<vector<int>> &getAdjacencyList() {
        return adjacency_list;
    }
};

int m = 0;
bool f(int at, vector<any> &data, Graph &graph) {
    if (data.empty()) {
        data.pb(0);
        data.pb(0);
    }

    int a = any_cast<int>(data[0]) + 1;
    int b = any_cast<int>(data[1]) + graph.getAdjacencyList()[at].size();

    data[0] = a;
    data[1] = b;

    m = max(b / a + (b % a != 0 ? 1 : 0), m);

    return true;
}

Graph constructing(0);
bool constructor(int at, vector<any> &data, Graph &graph) {
    if (data.empty()) {
        data.pb(at);
    } else {
        constructing.connect(any_cast<int>(data[0]), at);
        data[0] = at;
    }

    return true;
}

Graph& construct(Graph &graph) {
    constructing = Graph(graph.getAdjacencyList().size());
    graph.dfs(0,&constructor);

    return constructing;
}

//Ten kod jest dobry tylko w celach heurystycznych. Dostaje 30
//punktów na olimpiadzie. Zakłada, że budowniczy znają cele króla.
//Złożoność czasowa O(n).
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    Graph graph(size);

    for (int i = 0; i < size - 1; i++) {
        in_i(a);
        in_i(b);
        a--;
        b--;
        graph.connect(a,b);
        graph.connect(b,a);
    }
    graph = construct(graph);

    graph.dfs(0,&f);

    cout << m << endl;
}