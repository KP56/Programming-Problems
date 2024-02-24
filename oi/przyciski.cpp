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

int button_id_to_node(int i, int n) {
    return 2*n+i;
}

int row_id_to_node(int r, int n) {
    return r;
}

int column_id_to_node(int c, int n) {
    return n + c;
}

vector<int> cycle;
void dfs(int at, int prev, vector<vector<int>> &graph, vector<bool> &vis, stack<int> &recursion_stack) {
    vis[at] = true;
    recursion_stack.push(at);

    if (!cycle.empty()) {
        return;
    }

    for (int i : graph[at]) {
        if (!cycle.empty()) {
            return;
        }

        if (!vis[i]) {
            dfs(i, at, graph, vis, recursion_stack);
        } else if (i != prev) {
            int current = recursion_stack.top();
            cycle.pb(current);
            while (current != i) {
                recursion_stack.pop();
                current = recursion_stack.top();
                cycle.pb(current);
            }
        }
    }

    if (!recursion_stack.empty()) {
        recursion_stack.pop();
    }
}

void find_cycle(vector<vector<int>> &graph) {
    stack<int> recursion_stack;
    vector<bool> vis(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            dfs(i, -1, graph, vis, recursion_stack);
        }
    }
}

void root_tree_dfs(int at, vector<vector<int>> &graph, vector<bool> &vis, vector<vector<int>> &rooted, vector<int> &parents) {
    vis[at] = true;

    for (int i : graph[at]) {
        if (!vis[i]) {
            parents[i] = at;
            rooted[at].pb(i);
            root_tree_dfs(i, graph, vis, rooted, parents);
        }
    }
}

pair<vector<vector<int>>, vector<int>> root_tree(vector<vector<int>> &graph) {
    vector<vector<int>> rooted(graph.size());
    vector<int> parents(graph.size());
    parents[0] = -1;

    vector<bool> vis(graph.size());

    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            root_tree_dfs(i, graph, vis, rooted, parents);
        }
    }

    return mp(rooted, parents);
}

int n2;
bool res = false;
void climb_up_for_fun(int at, vector<vector<int>> &tree, vector<int> &parents, vector<int> &indices, vector<int> &managed_to_get,
        vector<int> &forced_chosen, vector<bool> &is_chosen) {
    managed_to_get[at]++;

    if (managed_to_get[at] >= tree[at].size()) {
        if (at == 0) {
            // Osiągneliśmy korzeń
            if (forced_chosen[at] % 2 == 1) {
                // Jeżeli mamy nieparzystą liczbę wierzchołków wybranych to odpowiedzią jest prawda
                res = true;
            }
            return;
        }

        if (indices[at] >= 2*n2) {
            // Jeżeli wierzchołek jest przyciskiem
            // Podejmijmy decyzję czy wybieramy dany wierzchołek czy nie
            if (forced_chosen[tree[at][0]] % 2 == 0) {
                // Jeżeli mamy parzystą liczbę to jesteśmy zmuszeni wybrać ten wierzchołek
                is_chosen[at] = true;
                forced_chosen[parents[at]]++;
            }
        }

        // Możemy iść wyżej
        climb_up_for_fun(parents[at], tree, parents, indices, managed_to_get, forced_chosen, is_chosen);
    }
}

pair<bool, vector<bool>> is_odd_possible(vector<vector<int>> &tree, vector<int> &parents, vector<int> &indices) {
    vector<int> managed_to_get(tree.size());
    vector<int> forced_chosen(tree.size());
    vector<bool> is_chosen(tree.size());

    for (int i = 1; i < tree.size(); i++) {
        if (tree[i].empty()) {
            // Jeżeli jest liściem to idziemy w górę drzewa
            climb_up_for_fun(i, tree, parents, indices, managed_to_get, forced_chosen, is_chosen);
        }
    }

    return mp(res, is_chosen);
}

void split_into_components_dfs(int at, int prev_idx, vector<vector<int>> &tree, vector<bool> &vis,
            vector<vector<int>> &component, vector<int> &component_parents, vector<int> &idx) {
    vis[at] = true;
    component.pb({});
    component_parents.pb(prev_idx);
    idx.pb(at);

    int current_idx = component.size() - 1;

    for (int i : tree[at]) {
        if (!vis[i]) {
            component[current_idx].pb(component.size());
            split_into_components_dfs(i, current_idx, tree, vis, component, component_parents, idx);
        }
    }
}

tuple<vector<vector<vector<int>>>, vector<vector<int>>, vector<vector<int>>> split_into_components(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());

    vector<vector<vector<int>>> components;
    vector<vector<int>> components_parents;
    vector<vector<int>> indices;
    for (int i = 0; i < tree.size(); i++) {
        if (!vis[i]) {
            vector<vector<int>> component;
            vector<int> component_parent;
            vector<int> idx;
            split_into_components_dfs(i, -1, tree, vis, component, component_parent, idx);
            components.pb(component);
            components_parents.pb(component_parent);
            indices.pb(idx);
        }
    }

    return tuple(components, components_parents, indices);
}

bool verify(int n, vector<pii> &selected_buttons) {
    vector<int> rows(n);
    vector<int> columns(n);

    for (pii i : selected_buttons) {
        rows[i.first]++;
        columns[i.second]++;
    }

    int prev = -1;
    for (int i : rows) {
        if (prev != -1 && i % 2 != prev) {
            return false;
        }
        prev = i % 2;
    }

    for (int i : columns) {
        if (i % 2 != prev) {
            return false;
        }
        prev = i % 2;
    }

    return true;
}

bool execute(int n, vector<pii> &buttons, int current, vector<pii> &chosen_so_far) {
    if (current >= buttons.size()) {
        if (chosen_so_far.size() > 0) {
            return verify(n, chosen_so_far);
        } else {
            return false;
        }
    }

    bool any = false;
    vector<pii> chosen_so_far_cp = chosen_so_far;
    if (chosen_so_far_cp.size() != 0) {
        any |= verify(n, chosen_so_far_cp);
    }
    vector<pii> chosen_so_far_cp2 = chosen_so_far;
    any |= execute(n, buttons, current+1, chosen_so_far_cp2);
    chosen_so_far_cp2.pb(buttons[current]);
    any |= execute(n, buttons, current+1, chosen_so_far_cp2);

    return any;
}

bool brute(int n, vector<pii> &buttons) {
    vector<pii> chosen_so_far;
    return execute(n, buttons, 0, chosen_so_far);
}

pii extract_from_line(string s) {
    string num = "";
    for (char c : s) {
        if (c == ' ') {
            break;
        }

        num += string(1,c);
    }

    string num2 = "";
    bool found = false;
    for (char c : s) {
        if (c == ' ') {
            found = true;
            continue;
        }

        if (found) {
            num2 += string(1,c);
        }
    }

    return mp(stoi(num), stoi(num2));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    cycle = vector<int>();

    /*ifstream file("prz3ocen.in");
    string line;
    getline(file, line);*/

    ini(n);
    //int n = extract_from_line(line).first;
    //int n = rand() % 8 + 1;
    ini(m);
    //int m = extract_from_line(line).second;
    //int m = rand() % min(5ll,n*n) + 1;

    n2 = n;

    //vector<pii> buttons;
    vector<vector<bool>> taken(n,vector<bool>(n));

    vector<vector<int>> graph(2*n+m);
    for (int i = 0; i < m; i++) {
        //getline(file, line);
        ini(r);
        //int r = extract_from_line(line).first;
        //int r = rand() % n + 1;
        ini(c);
        //int c = extract_from_line(line).second;
        //int c = rand() % n + 1;
        
        /*while (taken[r-1][c-1]) {
            r = rand() % n + 1;
            c = rand() % n + 1;
        }
        taken[r-1][c-1] = true;*/

        r--;
        c--;

        //buttons.pb({r,c});

        graph[button_id_to_node(i,n)].pb(row_id_to_node(r,n));
        graph[row_id_to_node(r,n)].pb(button_id_to_node(i,n));
        graph[button_id_to_node(i,n)].pb(column_id_to_node(c,n));
        graph[column_id_to_node(c,n)].pb(button_id_to_node(i,n));
    }

    find_cycle(graph);

    //bool brute_res = brute(n, buttons);

    if (!cycle.empty()) {
        vector<int> buttons_vec;
        for (int i : cycle) {
            if (i >= 2*n) {
                buttons_vec.pb(i - 2*n);
            }
        }

        /*if (!brute_res) {
            int test = 0;
        }

        vector<pii> selected_buttons;
        for (int i : buttons_vec) {
            selected_buttons.pb(buttons[i]);
        }
        
        if (!verify(n, selected_buttons)) {
            int test = 0;
        }*/

        cout << "TAK" << endl;
        cout << buttons_vec.size() << endl;
        for (int i : buttons_vec) {
            cout << i + 1 << " ";
        }
        cout << endl;
    } else {
        // Tutaj zaczyna się zabawa - rozważamy drzewo
        auto component_split = split_into_components(graph);

        vector<int> result;

        // Zmienne do debugowania
        bool broke = false;

        for (int i = 0; i < get<0>(component_split).size(); i++) {
            vector<vector<int>> rooted = get<0>(component_split)[i];
            vector<int> parents = get<1>(component_split)[i];
            vector<int> indices = get<2>(component_split)[i];

            auto res_of_real_fun = is_odd_possible(rooted, parents, indices);

            if (res) {
                res = false;

                for (int i = 0; i < rooted.size(); i++) {
                    if (res_of_real_fun.second[i]) {
                        result.pb(indices[i] - 2*n);
                    }
                }
            } else {
                /*if (brute_res) {
                    int test = 0;
                }*/

                cout << "NIE" << endl;

                /*broke = true;
                break;*/

                return 0;
            }
        }

        /*if (broke) {
            continue;
        }

        if (!brute_res) {
            int test = 0;
        }

        vector<pii> selected_buttons;
        for (int i : result) {
            selected_buttons.pb(buttons[i]);
        }
        if (!verify(n, selected_buttons)) {
            int test = 0;
        }*/

        cout << "TAK" << endl;
        cout << result.size() << endl;
        for (int i = 0; i < result.size(); i++) {
            cout << result[i] + 1 << " ";
        }
        cout << endl;
    }
}