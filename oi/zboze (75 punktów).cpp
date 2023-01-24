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

//https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
template<typename T> struct RangeTree {
    ll n;
    vector<T> tree;
    function<T(T,T)> f;
    T operation;

    RangeTree() {}

    RangeTree(vector<T> arr, function<T(T,T)> f, T operation) {
        tree = vector<T>(arr.size() * 2);
        n = arr.size();
        this->f = f;

        for (ll i = 0; i < n; i++)
            tree[n + i] = arr[i];

        for (ll i = n - 1; i > 0; --i)
            tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
        
        this->operation = operation;
    }

    void updateTreeNode(ll p, T value) {
        tree[p + n] = value;
        p = p + n;

        for (ll i = p; i > 1; i >>= 1)
            tree[i >> 1] = f(tree[i], tree[i ^ 1]);
    }

    T query(ll l, ll r) {
        r++;
        T res = operation;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) 
                res = f(res, tree[l++]);
      
            if (r&1) 
                res = f(res, tree[--r]);
        }
      
        return res;
    }
};

ll sum2(ll a, ll b) {
    return a + b;
}

//każdy wierzchołek nowego drzewa reprezentuje poddrzewo
struct node {
    pll parent;
    ll id;
    vector<pll> children;
    ll sum = 0;
    ll length = 0;
    ll castle_sum = 0;
    ll castle_count = 0;
    ll node_sum = 0;
    bool castle_in_root = false;
    vector<ll> distances;
    vector<ll> bottom_distances;
    RangeTree<ll> castles_until;
    ll castles_in_rt = 0;
    RangeTree<ll> castle_sum_until;
    RangeTree<ll> castle_sum_top;
};

void transformTreeDFS(ll at, vector<vector<pll>> &graph, vector<node> &tree, vector<pll> &mapping, vector<bool> &vis, bool connect_prev, pll prev) {
    vis[at] = true;

    if (!connect_prev) {
        node n;
        n.parent = prev;
        n.id = at;
        tree.pb(n);
        mapping[at] = mp(tree.size() - 1,-1);
    }
    ll current_node = tree.size() - 1;

    ll children = 0;
    for (pll i : graph[at]) {
        if (!vis[i.first]) {
            children++;
        }
    }

    for (pll i : graph[at]) {
        if (!vis[i.first]) {
            if (children == 1) {
                ll top = tree[current_node].distances.empty() ? 0 : tree[current_node].distances[tree[current_node].distances.size() - 1];
                tree[current_node].distances.pb(i.second + top);
                tree[current_node].length += i.second;
                mapping[i.first] = mp(current_node,tree[current_node].distances.size() - 1);
                transformTreeDFS(i.first, graph, tree, mapping, vis, true, mp(current_node,i.second));
            } else {
                tree[current_node].children.pb(mp(tree.size(),i.second));
                transformTreeDFS(i.first, graph, tree, mapping, vis, false, mp(current_node,i.second));
            }
        }
    }
}

//zamieniamy drzewo w jego uproszczoną wersję pozwalającą
//zredukować długości ścieżek pomiędzy dwoma wierzchołkami
//do maksymalnie około 2*log2(n)
pair<vector<node>,vector<pll>> transformTree(vector<vector<pll>> &graph) {
    vector<node> tree;
    vector<bool> vis(graph.size());
    vector<pll> mapping(graph.size());
    //korzystamy z algorytmu DFS od korzenia
    transformTreeDFS(0,graph,tree,mapping,vis,false,mp(-1,-1));
    for (node &n : tree) {
        n.castles_until = RangeTree<ll>(vector<ll>(n.distances.size()),&sum2,0);
        n.castle_sum_until = RangeTree<ll>(vector<ll>(n.distances.size()),&sum2,0);
        n.castle_sum_top = RangeTree<ll>(vector<ll>(n.distances.size()),&sum2,0);
        for (ll i : n.distances) {
            ll last = n.distances[n.distances.size() - 1];
            n.bottom_distances.pb(last - i);
        }
    }
    return mp(tree,mapping);
}

void updateCurrentSum(ll at, ll &current_sum, vector<pll> &mapping, vector<node> &tree) {
    pll mapping_pair = mapping[at - 1];
    //droga, którą przebyliśmy od wierzchołka
    ll sum = 0;
    ll counter = 0;
    ll castle_counter = 0;
    ll prev = -1;
    ll prev_sum = 0;
    ll prev_castle = 0;
    for (ll current_node = mapping_pair.first; current_node != -1; current_node = tree[current_node].parent.first) {
        counter = tree[current_node].sum - prev_sum;
        prev_sum = tree[current_node].sum;

        ll e = 0;
        if (prev != -1) {
            //ilość zamków w poprzednim poddrzewie
            ll castles_in_prev = tree[prev].castles_in_rt + tree[prev].castle_in_root - (prev == mapping_pair.first);
            //dla wszystkich zamków pod poprzednim poddrzewem, odejmuję
            //sumę odległości pomiędzy tym poddrzewem a tamtym oraz
            //długości tamtego poddrzewa

            //jeżeli w poprzednim właśnie dodaliśmy zamek oraz jest w korzeniu, wtedy bez tree[prev].length ???????
            //szczerze nie wiem dlaczego, doszedłem do tego eksperymentalnie porównując testy
            //pewnie jest to związane z innym błędem w kodzie, który tutaj koryguję

            e += (tree[prev].castle_count - 1 - castles_in_prev) * (tree[prev].parent.second + ((prev == mapping_pair.first && mapping_pair.second == -1) ? 0 : tree[prev].length));
            //dla każdego zamku w poprzednim poddrzewie odejmuję
            //odległość pomiędzy tym a tamtym poddrzewem
            e += castles_in_prev * tree[prev].parent.second;
            //odejmuję sumę odległości od każdego zamku w poprzednim
            //poddrzewie do korzenia tamtego poddrzewa
            e += tree[prev].node_sum - ((prev == mapping_pair.first && mapping_pair.second != -1) ? tree[mapping_pair.first].distances[mapping_pair.second] : 0);
        }

        castle_counter = tree[current_node].castle_count - prev_castle;
        prev_castle = tree[current_node].castle_count;

        current_sum += counter - e + sum * castle_counter;
        tree[current_node].castle_count++;

        if (current_node == mapping_pair.first) {
            if (mapping_pair.second != -1) {
                tree[mapping_pair.first].castle_sum += tree[mapping_pair.first].bottom_distances[mapping_pair.second];
            } else {
                tree[mapping_pair.first].castle_in_root = true;
                tree[mapping_pair.first].castle_sum += tree[mapping_pair.first].length;
                current_sum += tree[mapping_pair.first].node_sum;
            }
            if (mapping_pair.second != -1) {
                //usuwam wszelkie ślady po zamkach z tego poddrzewa
                //z current_sum
                //current_sum -= tree[current_node].node_sum;

                //przekierowuję zamki z tego poddrzewa nad tym wierzchołkiem
                //na mój zamek
                ll a = tree[current_node].castle_sum_until.query(0,mapping_pair.second);
                ll b = tree[current_node].castles_until.query(0,mapping_pair.second);
                current_sum += a - tree[current_node].bottom_distances[mapping_pair.second] * b;

                //przekierowuję zamki, które są pod tym wierzchołkiem ale w tym
                //poddrzewie na mój zamek
                ll c = tree[current_node].castle_sum_top.query(mapping_pair.second,tree[current_node].distances.size() - 1);
                ll d = tree[current_node].castles_until.query(mapping_pair.second,tree[current_node].distances.size() - 1);
                current_sum += c - tree[current_node].distances[mapping_pair.second] * d;

                tree[current_node].castle_sum_top.updateTreeNode(mapping_pair.second,tree[current_node].distances[mapping_pair.second]);
                tree[current_node].castles_until.updateTreeNode(mapping_pair.second,1);
                tree[current_node].castle_sum_until.updateTreeNode(mapping_pair.second,tree[current_node].bottom_distances[mapping_pair.second]);
                tree[current_node].castles_in_rt++;

                ll to_section_root = tree[mapping_pair.first].distances[mapping_pair.second];
                sum += to_section_root;

                tree[current_node].node_sum += to_section_root;

                //przekierowuję zamki pod tym poddrzewem na mój zamek
                current_sum += tree[current_node].bottom_distances[mapping_pair.second] * (tree[current_node].castle_count - b - d - 1 - tree[current_node].castle_in_root);

                //jeżeli zamek jest w korzeniu poddrzewa
                if (tree[current_node].castle_in_root) {
                    current_sum += sum;
                }
            }
            //tree[current_node].sum += sum;
            sum += tree[current_node].parent.second;
        } else {
            //dodajemy sumę odległości od najniższego wierzchołka
            //poddrzewa do zamków do ogólnej sumy
            current_sum += tree[current_node].castle_sum;
            //tree[x].sum oznacza sumę odległości pomiędzy tym wierzchołkiem
            //i wszystkimi zamkami, które są pod nim
            tree[current_node].sum += sum/* + tree[current_node].length*/;
            sum += tree[current_node].parent.second + tree[current_node].length;
        }
        prev = current_node;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_i(queries);

    vector<vector<pll>> graph(size);
    for (ll i = 0; i < size - 1; i++) {
        in_i(a);
        in_i(b);
        in_i(length);

        graph[a - 1].pb(mp(b - 1,length));
        graph[b - 1].pb(mp(a - 1,length));
    }

    pair<vector<node>,vector<pll>> transformed = transformTree(graph);
    vector<node> tree = transformed.first;
    vector<pll> mapping = transformed.second;

    ll current_sum = 0;
    updateCurrentSum(1,current_sum,mapping,tree);
    for (ll i = 0; i < queries; i++) {
        in_i(a);
        updateCurrentSum(a,current_sum,mapping,tree);
        cout << current_sum * 2 << endl;
    }
}