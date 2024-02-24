#include <bits/stdc++.h>

using namespace std;

#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

struct range_tree {
    vector<int> tree;
    int n;

    range_tree(int size) {
        tree = vector<int>(size*2);
        n = size;
    }

    int query(int l, int r) {
        r++;

        int sum = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) sum += tree[l++];
            if (r&1) sum += tree[--r];
        }

        return sum;
    }

    void update(int x, int el) {
        tree[x + n] += el;
        x += n;

        for (int i = x; i > 1; i >>= 1) {
            tree[i >> 1] = tree[i]+tree[i ^ 1];
        }
    }
};

vector<int> lobotomized_euler;
int* min_positions;
int* max_positions;
int* holder_positions;
int* distance_from_root;
void euler_dfs(int at, int dist, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[at] = true;

    distance_from_root[at] = dist;

    lobotomized_euler.pb(at);
    min_positions[at] = lobotomized_euler.size() - 1;

    for (int i : graph[at]) {
        if (!vis[i]) {
            euler_dfs(i,dist+1,vis,graph);
        }
    }

    lobotomized_euler.pb(at);
    max_positions[at] = lobotomized_euler.size() - 1;
    lobotomized_euler.pb(-1);
    holder_positions[at] = lobotomized_euler.size() - 1;
}

// Sprawdza czy u jest pod v lub u=v
bool is_under(int u, int v) {
    if (min_positions[v] <= min_positions[u] && max_positions[u] <= max_positions[v]) {
        return true;
    }

    return false;
}
struct sqrt_node {
    int original_idx;
    int parent;
    int past_parent;
    set<pii,greater<pii>> forced_value_set;
    pii max_ever = {-1,-1};
    //vector<int> children;

    sqrt_node(int original_idx, int parent/*, vector<int> children*/) {
        this->original_idx = original_idx;
        this->parent = parent;
        //this->children = children;
    }

    sqrt_node() {}
};

bool can_recover = false;

struct sqrt_decomp {
    vector<sqrt_node> decomp;

    vector<int> heavy_nodes;
    int* heavy_idx;
    bool* is_heavy;
    
    int* parents;
    int* nodes_in_subtree;
    vector<vector<int>> graph;

    bool* deleted;

    int heavy_dist;
    int trees = 0;

    int find_nodes_in_subtree_and_parents(int at, vector<bool> &vis) {
        vis[at] = true;

        int sum = 0;
        for (int i : graph[at]) {
            if (!vis[i]) {
                parents[i] = at;
                sum += find_nodes_in_subtree_and_parents(i,vis);
            }
        }

        return nodes_in_subtree[at] = sum+1;
    }

    void find_heavy_nodes(int at, int dist_from_prev, int prev_heavy_node, vector<bool> &vis) {
        vis[at] = true;

        int heavy_node_idx = -1;
        if (dist_from_prev == heavy_dist-1 && (nodes_in_subtree[at] > heavy_dist || at == 0)) {
            heavy_nodes.pb(at);
            heavy_idx[at] = heavy_nodes.size() - 1;
            is_heavy[at] = true;
            /*if (prev_heavy_node != -1) {
                decomp[prev_heavy_node].children.pb(decomp.size());
            }*/
            decomp.pb(sqrt_node(at,prev_heavy_node/*,{}*/));
            heavy_node_idx = decomp.size()-1;
        }

        for (int i : graph[at]) {
            if (!vis[i]) {
                find_heavy_nodes(i,(dist_from_prev+1)%heavy_dist,dist_from_prev == heavy_dist-1 ? heavy_node_idx : prev_heavy_node,vis);
            }
        }
    }

    sqrt_decomp(vector<vector<int>> &graph) {
        this->graph = graph;
        this->heavy_dist = sqrt(graph.size());

        deleted = new bool[graph.size()]();

        parents = new int[graph.size()];
        heavy_idx = new int[graph.size()];

        for (int i = 0; i < graph.size(); i++) {
            parents[i] = -1;
            heavy_idx[i] = -1;
        }

        is_heavy = new bool[graph.size()]();
        nodes_in_subtree = new int[graph.size()]();

        vector<bool> vis(graph.size());
        find_nodes_in_subtree_and_parents(0,vis);
        
        vis = vector<bool>(graph.size());
        find_heavy_nodes(0,heavy_dist-1,-1,vis);
    }

    int find_heavy_vertex_up(int node) {
        if (parents[node] == -1 || deleted[parents[node]]) return node;

        if (is_heavy[node]) return node;
        else return find_heavy_vertex_up(parents[node]);
    }

    // Złożoność czasowa O(sqrt(n))
    // UWAGA! JEŚLI NODE JEST CIĘŻKI TO POTRAKTUJE GO JAKBY NIE BYŁ ALE ZWRÓCI GO RAZEM Z RESZTĄ
    vector<int> find_heavy_vertices_down(int node) {
        vector<int> nodes;
        for (int i : heavy_nodes) {
            // Jeżeli dystans jest większy to oznacza, że nad nim musi istnieć inny wierzchołek ciężki, więc istnieje inny
            // wierzchołek ciężki między "i", a node i nie rozważamy "i" w związku z tym
            if (is_under(i,node) && distance_from_root[i] - distance_from_root[node] <= heavy_dist) {
                nodes.pb(i);
            }
        }

        return nodes;
    }

    // Złożoność czasowa O(sqrt(n))
    int find_root_of_tree(int node) {
        // Mogę znaleźć korzeń poprzez pójście do korzenia jakiegoś drzewa na dekompozycji
        // a następnie pójście w górę, aż dojdę do korzenia.

        // W przypadku gdy nie ma wyżej ciężkiego wierzchołka, find_heavy_vertex_up zwraca indeks korzenia
        int traverse_node = find_heavy_vertex_up(node);
        int node_idx_on_tree = traverse_node;
        if (is_heavy[traverse_node]) {
            int heavy_node = heavy_idx[traverse_node];
            while (decomp[heavy_node].parent != -1) {
                heavy_node = decomp[heavy_node].parent;
            }

            node_idx_on_tree = heavy_nodes[heavy_node];
        }

        // Znaleźliśmy korzeń. Idziemy w górę na właściwym drzewie.
        while (parents[node_idx_on_tree] != -1 && !deleted[parents[node_idx_on_tree]]) {
            node_idx_on_tree = parents[node_idx_on_tree];
        }

        return node_idx_on_tree;
    }

    void delete_node(int node) {
        deleted[node] = true;

        vector<int> nodes_to_disconnect = find_heavy_vertices_down(node);
        for (int i : nodes_to_disconnect) {
            decomp[heavy_idx[i]].past_parent = decomp[heavy_idx[i]].parent;
            decomp[heavy_idx[i]].parent = -1;
        }
    }

    void undo_deletion(int node) {
        deleted[node] = false;

        vector<int> nodes_to_connect = find_heavy_vertices_down(node);
        for (int i : nodes_to_connect) {
            decomp[heavy_idx[i]].parent = decomp[heavy_idx[i]].past_parent;
        }
    }

    void update_forced_value(int node) {
        for (int i : heavy_nodes) {
            if (is_under(i,node)) {
                if (can_recover) {
                    decomp[heavy_idx[i]].forced_value_set.insert({distance_from_root[node],node});
                }
                decomp[heavy_idx[i]].max_ever = max(decomp[heavy_idx[i]].max_ever,{distance_from_root[node],node});
            }
        }
    }

    void delete_forced_value(int node) {
        for (int i : heavy_nodes) {
            if (is_under(i,node)) {
                decomp[heavy_idx[i]].forced_value_set.erase({distance_from_root[node],node});
            }
        }
    }

    int obtain_forced_value(int node, bool *is_forced_value) {
        int current_node = node;
        while (current_node != -1 && !is_heavy[current_node]) {
            if (is_forced_value[current_node]) {
                return current_node;
            }
            current_node = parents[current_node];
        }

        // teraz current_node jest ciężkim wierzchołkiem
        int current_heavy = heavy_idx[current_node];
        if (can_recover) {
            if (!decomp[current_heavy].forced_value_set.empty()) {
                return (*decomp[current_heavy].forced_value_set.begin()).second;
            }
        } else {
            if (decomp[current_heavy].max_ever != mp(-1,-1)) {
                return decomp[current_heavy].max_ever.second;
            }
        }

        // jeżeli nie ma żadnego forced_value nad wierzchołkiem to zwracamy -1
        return -1;
    }
};

vector<int> status_vec_brute;
bool* color;
int find_node_count(int at, vector<bool> &vis, vector<vector<int>> &graph, bool color_b) {
    vis[at] = true;

    if (color[at] == color_b) {
        status_vec_brute[at]++;
    } else {
        status_vec_brute[at]--;
    }

    int sum = 1;
    for (int i : graph[at]) {
        if (!vis[i]) {
            sum += find_node_count(i,vis,graph,color_b);
        }
    }

    return sum;
}

void color_dfs(int at, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[at] = true;

    for (int i : graph[at]) {
        if (!vis[i]) {
            color[i] = !color[at];
            color_dfs(i,vis,graph);
        }
    }
}

vector<int> fast_bruteforce(vector<pii> requests, int n, vector<vector<int>> &graph) {
    status_vec_brute = vector<int>(n);
    vector<int> test_res;

    vector<bool> deleted(n);

    for (pii i : requests) {
        int type = i.first;
        int k = i.second;

        if (type == 1) {
        // wyjechał w delegacje (usuwamy wierzchołek)
            deleted[k] = true;
        } else if (type == 2) {
            // wrócił z delegacji (dodajemy wierzchołek)
            deleted[k] = false;
        } else {
            // organizuje imprezę (dokonujemy zapytania)
            vector<bool> vis2 = deleted;
            test_res.pb(find_node_count(k,vis2,graph,color[k]));
        }
    }

    return test_res;
}

vector<vector<int>> random_tree_naive(int size) {
    vector<vector<int>> current_tree;

    current_tree.push_back({});
    for (int i = 1; i < size; i++) {
        int parent = rand() % current_tree.size();
        current_tree.push_back({parent});
        current_tree[parent].push_back(i);
    }

    return current_tree;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = 100000;
    vector<vector<int>> graph(n);
    for (int i = 0; i < n-1; i++) {
        ini(u);
        ini(v);

        u--;
        v--;

        graph[u].pb(v);
        graph[v].pb(u);
    }

    //vector<vector<int>> graph = random_tree_naive(n);

    color = new bool[n]();
    vector<bool> vis(n);
    color_dfs(0,vis,graph);

    ini(q);
    //int q = 100000;
    vector<pii> requests;
    //vector<bool> already_removed(n);
    bool is_subproblem_three = true;
    for (int i = 0; i < q; i++) {
        ini(type);
        //int type = rand() % 3 + 1;

        ini(k);
        k--;

        if (type == 2) {
            can_recover = true;
        }

        if (type != 3) {
            is_subproblem_three = false;
        }

        //int k = rand() % n;

        /*if (!already_removed[k] && type == 2) continue;

        if (already_removed[k] && (type == 1 || type == 3)) continue;

        if (type == 1) {
            already_removed[k] = true;
        }

        if (type == 2) {
            already_removed[k] = false;
        }*/

        requests.pb({type,k});
    }
    sqrt_decomp decomposition(graph);

    //vector<int> test_res = test(requests,n,graph);

    bool is_path = true;
    for (auto i : graph) {
        if (i.size() > 2) {
            is_path = false;
        }
    }

    if (is_subproblem_three) {
        int global_counter = 0;
        for (pii i : requests) {
            int type = i.first;
            int k = i.second;

            // organizuje imprezę (dokonujemy zapytania)
            cout << n << " ";

            if (color[k]) {
                global_counter++;
            } else {
                global_counter--;
            }
        }
        cout << endl;

        for (int i = 0; i < n; i++) {
            if (color[i]) {
                cout << global_counter << " ";
            } else {
                cout << -global_counter << " ";
            }
        }
        cout << endl;

        return 0;
    } else if (is_path) {
        vector<int> brute_res = fast_bruteforce(requests,n,graph);

        for (int i : brute_res) {
            cout << i << " ";
        }
        cout << endl;

        for (int i : status_vec_brute) {
            cout << i << " ";
        }
        cout << endl;

        return 0;
    }

    min_positions = new int[n];
    max_positions = new int[n];
    holder_positions = new int[n];
    distance_from_root = new int[n];
    lobotomized_euler = vector<int>();
    vis = vector<bool>(n);
    euler_dfs(0,0,vis,graph);

    range_tree tree(lobotomized_euler.size());
    range_tree status(lobotomized_euler.size());
    int* forced_value = new int[graph.size()]();
    bool* is_forced_value = new bool[graph.size()]();
    
    //int counter = 0;
    for (pii i : requests) {
        int type = i.first;
        int k = i.second;

        /*ini(type);
        ini(k);
        k--;*/

        if (type == 1) {
            // wyjechał w delegacje (usuwamy wierzchołek)

            int current_root = decomposition.find_root_of_tree(k);

            decomposition.delete_node(k);

            // aktualizacja na drzewie przedziałowym
            int cache = decomposition.nodes_in_subtree[k]-tree.query(min_positions[k],max_positions[k]);

            if (decomposition.parents[current_root] != -1) {
                // chcemy przechowywać informacje w usuniętym wierzchołku
                tree.update(holder_positions[decomposition.parents[current_root]],-cache);
            } else {
                tree.update(holder_positions[current_root],-cache);
            }
            tree.update(min_positions[k],cache);

            // sprawdzamy czy istnieje jakieś forced_value nad nami
            int forced_value_node = decomposition.obtain_forced_value(k,is_forced_value);

            if (forced_value_node != -1) {
                // jeżeli odnaleźliśmy jakieś forced value to musimy zrobić inny rodzaj query
                forced_value[k] = forced_value[forced_value_node] + status.query(min_positions[forced_value_node]+1,min_positions[k]);
            } else {
                // tutaj aktualizujemy forced_value
                forced_value[k] = status.query(0,min_positions[k]);
            }
            is_forced_value[k] = true;

            // teraz musimy przesłać odpowiednią informację w dół drzewa
            decomposition.update_forced_value(k);
        } else if (type == 2) {
            // przywracamy wierzchołek

            // odnajdźmy miejsce gdzie holdowana jest wartość dla wierzchołka k
            int past_root = decomposition.find_root_of_tree(k);

            int cache = tree.query(min_positions[k],min_positions[k]);

            // i ją wyzerujmy
            if (decomposition.parents[past_root] != -1) {
                // chcemy przechowywać informacje w usuniętym wierzchołku
                tree.update(holder_positions[decomposition.parents[past_root]],cache);
            } else {
                tree.update(holder_positions[past_root],cache);
            }

            // aby przywrócić wierzchołek na początek cofnijmy to co się wydarzyło na dekompozycji pierwiastkowej
            decomposition.undo_deletion(k);

            // następnie musimy wyzerować to co usuwa
            tree.update(min_positions[k],-cache);

            // teraz trzeba przenieść holdera tego wierzchołka do wierzchołka nad nowym korzeniem
            int holder = tree.query(holder_positions[k],holder_positions[k]);
            tree.update(holder_positions[k],-holder);

            // skoro usunęliśmy holdera to przenosimy
            int current_root = decomposition.find_root_of_tree(k);
            if (decomposition.parents[current_root] != -1) {
                // chcemy przechowywać informacje w usuniętym wierzchołku
                tree.update(holder_positions[decomposition.parents[current_root]],holder);
            } else {
                tree.update(holder_positions[current_root],holder);
            }

            // teraz chcemy usunąć informacje nt. forced value
            is_forced_value[k] = false;

            // usuwamy z dekompozycji pierwiastkowej
            decomposition.delete_forced_value(k);

            // sprawdzamy czy istnieje jakieś forced_value nad nami
            int forced_value_node = decomposition.obtain_forced_value(k,is_forced_value);

            int query_result;
            if (forced_value_node != -1) {
                // jeżeli odnaleźliśmy jakieś forced value to musimy zrobić inny rodzaj query
                query_result = forced_value[forced_value_node] + status.query(min_positions[forced_value_node]+1,min_positions[k]);
            } else {
                query_result = status.query(0,min_positions[k]);
            }

            // dokonujemy aktualizacji statusu
            int x = forced_value[k]-query_result;
            status.update(min_positions[k],x);
            status.update(max_positions[k],-x);
        } else {
            // organizuje imprezę (dokonujemy zapytania)

            int current_root = decomposition.find_root_of_tree(k);

            // aktualizacja statusu
            if (color[k]) {
                status.update(min_positions[current_root],1);
                status.update(max_positions[current_root],-1);
            } else {
                status.update(min_positions[current_root],-1);
                status.update(max_positions[current_root],1);
            }

            int res = decomposition.nodes_in_subtree[current_root]-tree.query(min_positions[current_root],max_positions[current_root]);

            /*if (test_res[counter] != res) {
                int test = 0;
            }*/

            cout << res << " ";
            //counter++;
        }
    }
    cout << endl;

    // dokonujemy rekonstrukcji statusu
    int current = 0;
    int* status_vec = new int[n]();
    int* mem = new int[n]();
    for (int i = 0; i < lobotomized_euler.size(); i++) {
        if (lobotomized_euler[i] != -1 && is_forced_value[lobotomized_euler[i]]) {
            if (i == min_positions[lobotomized_euler[i]]) {
                mem[lobotomized_euler[i]] = current;
                current = forced_value[lobotomized_euler[i]];
            } else {
                current = mem[lobotomized_euler[i]];
            }
        } else {
            current += status.query(i,i);
        }

        if (lobotomized_euler[i] != -1 && min_positions[lobotomized_euler[i]] == i) {
            status_vec[lobotomized_euler[i]] = current;
        }
    }

    for (int i = 0; i < n; i++) {
        if (color[i]) {
            /*if (status_vec_brute[i] != status_vec[i]) {
                int test = 0;
            }*/

            cout << status_vec[i] << " ";
        } else {
            /*if (status_vec_brute[i] != -status_vec[i]) {
                int test = 0;
            }*/

            cout << -status_vec[i] << " ";
        }
    }
    cout << endl;
}