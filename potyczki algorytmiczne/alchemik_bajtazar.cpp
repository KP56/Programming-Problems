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
//#define endl "\n"
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

struct operation {
    bool addition;
    int a;
    int b;

    operation(bool addition, int a, int b) {
        this->addition = addition;
        this->a = a;
        this->b = b;
    }
};

vector<operation> operations;
void dfs(int at, vector<unordered_set<int,custom_hash>> &graph, vector<unordered_set<int,custom_hash>> &graph_cp, vector<bool> &vis) {
    vis[at] = true;

    if (at != 0 && graph_cp[at].find(0) == graph_cp[at].end()) {
        operations.pb(operation(true,at,0));
        graph[at].insert(0);
        graph[0].insert(at);
    }

    for (int i : graph_cp[at]) {
        if (!vis[i]) {
            dfs(i,graph,graph_cp,vis);
        }
    }
}

bool verify(vector<unordered_set<int,custom_hash>> original_graph, vector<unordered_set<int,custom_hash>> original_graph2) {
    if (operations.size() > 200000) {
        return false;
    }

    // wykonujemy kolejne operacje na oryginalnym grafie, a na koniec porównujemy grafy
    int counter = 0;
    for (operation &o : operations) {
        if (o.addition) {
            if (original_graph[o.a].find(o.b) != original_graph[o.a].end() || original_graph[o.b].find(o.a) != original_graph[o.b].end()) {
                // ta krawędź już istnieje
                return false;
            }

            // sprawdzamy czy istnieje taki wierzchołek c, który posiada zarówna a, jak i b
            bool exists = false;
            for (int i = 0; i < original_graph.size(); i++) {
                if (original_graph[i].find(o.a) != original_graph[i].end() && original_graph[i].find(o.b) != original_graph[i].end()) {
                    exists = true;
                }
            }

            if (!exists) {
                return false;
            }

            original_graph[o.a].insert(o.b);
            original_graph[o.b].insert(o.a);
        } else {
            if (original_graph[o.a].find(o.b) == original_graph[o.a].end() || original_graph[o.b].find(o.a) == original_graph[o.b].end()) {
                // ta krawędź nie istnieje
                return false;
            }

            // sprawdzamy czy istnieje taki wierzchołek c, który posiada zarówna a, jak i b
            bool exists = false;
            for (int i = 0; i < original_graph.size(); i++) {
                if (original_graph[i].find(o.a) != original_graph[i].end() && original_graph[i].find(o.b) != original_graph[i].end()) {
                    exists = true;
                }
            }

            if (!exists) {
                return false;
            }

            original_graph[o.a].erase(o.b);
            original_graph[o.b].erase(o.a);
        }
        counter++;
    }

    return original_graph == original_graph2;
}

void dfs_mark(int at, vector<unordered_set<int,custom_hash>> &graph, vector<bool> &vis) {
    vis[at] = true;

    for (int i : graph[at]) {
        if (!vis[i]) {
            dfs_mark(i,graph,vis);
        }
    }
}

vector<unordered_set<int,custom_hash>> random_graph(int n, int m) {
    vector<unordered_set<int,custom_hash>> graph(n);
    for (int i = 0; i < m; i++) {
        int a = rand() % n;
        int b = rand() % n;
        while (graph[a].find(b) != graph[a].end()) {
            a = rand() % n;
            b = rand() % n;
            while (b == a) b = rand() % n;
        }
        while (b == a) b = rand() % n;

        graph[a].insert(b);
        graph[b].insert(a);
    }

    // sprawiamy, aby graf był spójny
    vector<bool> vis(n);
    int prev = -1;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            if (prev != -1) {
                graph[prev].insert(i);
                graph[i].insert(prev);
            }
            prev = i;
            dfs_mark(i,graph,vis);
        }
    }

    return graph;
}

void dfs_delete(int at, vector<unordered_set<int,custom_hash>> &graph, vector<bool> &vis) {
    bool to_delete = false;
    if (!vis[at]) {
        to_delete = true;
    }

    vis[at] = true;

    for (int i : graph[at]) {
        if (!vis[i]) {
            dfs_delete(i,graph,vis);
        }
    }

    if (to_delete) {
        operations.pb(operation(false,at,0));
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    operations = vector<operation>();
    //clock_t c = clock();

    ini(n);
    //int n = rand() % 30000 + 2;
    ini(m1);
    //int m1 = rand() % 50000 + n-1;
    //m1 = min(m1,n*(n-1)/2);
    //m1 = min(m1,50000ll);
    vector<unordered_set<int,custom_hash>> graph(n);
    for (int i = 0; i < m1; i++) {
        ini(a);
        ini(b);
        
        a--;
        b--;

        graph[a].insert(b);
        graph[b].insert(a);
    }
    //vector<unordered_set<int,custom_hash>> graph = random_graph(n,m1);

    vector<unordered_set<int,custom_hash>> graph_cp = graph;

    ini(m2);
    //int m2 = rand() % 50000 + n-1;
    //m2 = min(m2,50000ll);
    //m2 = min(m2,n*(n-1)/2);
    vector<unordered_set<int,custom_hash>> graph2(n);
    for (int i = 0; i < m2; i++) {
        ini(a);
        ini(b);

        a--;
        b--;

        graph2[a].insert(b);
        graph2[b].insert(a);
    }
    //vector<unordered_set<int,custom_hash>> graph2 = random_graph(n,m2);

    vector<unordered_set<int,custom_hash>> graph2_cp = graph2;

    // teraz utworzymy wszystkie połączenia, jeśli nie istnieją, przy pomocy dfs-a
    vector<bool> vis(n);
    dfs(0,graph,graph_cp,vis);

    // teraz usuńmy wszystkie krawędzie, które nie są podłączeniem do wierzchołka 1
    for (int i = 1; i < n; i++) {
        auto &m = graph[i];
        for (auto j : m) {
            if (j != 0) {
                operations.pb(operation(false,i,j));
                graph[j].erase(i);
            }
        }

        graph[i].clear();
        graph[i].insert(0);
    }

    // teraz dodajemy wszystkie krawędzie grafu drugiego
    for (int i = 0; i < n; i++) {
        auto &j = graph2[i];
        for (int k : j) {
            if (graph[i].find(k) == graph[i].end()) {
                graph[i].insert(k);
                graph[k].insert(i);
                operations.pb(operation(true,i,k));
            }
        }
    }

    // teraz usuwamy wszystkie krawędzie, które nie znajdują się w nowym grafie
    /*for (int i = 0; i < n; i++) {
        auto &j = graph[i];
        vector<int> to_remove;
        for (int k : j) {
            if (graph2[i].find(k) == graph2[i].end()) {
                to_remove.pb(k);
            }
        }

        for (int k : to_remove) {
            operations.pb(operation(false,i,k));
            graph[i].erase(k);
            graph[k].erase(i);
        }
    }*/

    // podczas testowania zauważyłem, że trzeba te krawędzie dodawać w odpowiedniej kolejności
    // kolejność tę można wyznaczyć przy pomocy algorytmu dfs, zaczynając go od wierzchołków,
    // które mają w drugim grafie połączenie do wierzchołka 0

    // znajdźmy najpierw wierzchołki początkowe
    vector<int> start_nodes;
    for (int i = 1; i < n; i++) {
        if (graph2[i].find(0) != graph2[i].end()) {
            start_nodes.pb(i);
        }
    }

    // wykonujemy dfs, który omija te wierzchołki i wierzchołek 0, a który od nich zaczyna
    vis = vector<bool>(n);
    for (int i : start_nodes) {
        vis[i] = true;
    }
    vis[0] = true;
    for (int i : start_nodes) {
        dfs_delete(i,graph,vis);
    }

    /*if (operations.size() > 200000) {
        int test = 0;
    }*/

    cout << operations.size() << endl;
    for (operation &o : operations) {
        if (o.addition) {
            cout << "+ ";
        } else {
            cout << "- ";
        }

        cout << o.a + 1 << " " << o.b + 1 << endl;
    }

    // weryfikowanie poprawności konstrukcji
    /*if (!verify(graph_cp,graph2_cp)) {
        cout << "Niepoprawny graf" << endl;
    }*/
    //cout << (float) (clock()-c) / CLOCKS_PER_SEC << endl;
}