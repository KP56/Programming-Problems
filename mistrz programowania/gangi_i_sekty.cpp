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

int dist_on_graph(int u, int v, vector<int> &time) {
    return time[u]-time[v];
}

void find_shortest_cycle_dfs(int at, int prev, int dist, vector<bool> &vis, vector<int> &time, vector<vector<int>> &graph, pii &current_shortest) {
    vis[at] = true;
    time[at] = dist;

    for (int i : graph[at]) {
        if (!vis[i]) {
            find_shortest_cycle_dfs(i,at,dist+1,vis,time,graph,current_shortest);
        } else if (i != prev) {
            // znaleźliśmy cykl
            if (current_shortest == mp(-1,-1)) {
                current_shortest.first = at;
                current_shortest.second = i;
            } else if (dist_on_graph(at,i,time) < dist_on_graph(current_shortest.first,current_shortest.second,time)) {
                current_shortest.first = at;
                current_shortest.second = i;
            }
        }
    }

    
}

vector<int> find_non_direct_path(int u, int v, vector<vector<int>> &graph) {
    vector<bool> vis(graph.size());
    vector<int> before(graph.size(),-1);

    queue<int> q;
    q.push(u);
    vis[u] = true;
    while (!q.empty()) {
        int current_node = q.front();
        q.pop();

        if (current_node == v) {
            break;
        }
        
        for (int i : graph[current_node]) {
            if (!vis[i] && (current_node != u || i != v)) {
                vis[i] = true;
                before[i] = current_node;
                q.push(i);
            }
        }
    }

    vector<int> path;
    int current_node = v;
    while (current_node != -1) {
        path.pb(current_node);
        current_node = before[current_node];
    }
    return path;
}

vector<int> find_shortest_cycle(vector<vector<int>> &graph) {
    vector<bool> vis(graph.size());
    vector<int> time(graph.size());
    pii node_pair = {-1,-1};
    find_shortest_cycle_dfs(0,-1,0,vis,time,graph,node_pair);

    if (node_pair == mp(-1,-1)) return {};

    vector<int> non_direct_path = find_non_direct_path(node_pair.first,node_pair.second,graph);

    return non_direct_path;
}

void color_tree(int at, bool current_color, vector<bool> &colors, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[at] = true;
    colors[at] = current_color;

    for (int i : graph[at]) {
        if (!vis[i]) {
            color_tree(i,!current_color,colors,vis,graph);
        }
    }
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

vector<vector<int>> random_graph(int n) {
    vector<vector<int>> graph = random_tree_naive(n);

    // gdy mamy wygenerowane losowo drzewo, naszym celem jest dodanie kilku losowych krawędzi
    int edges = rand() % (n*(n+1)/2);
    for (int i = 0; i < edges; i++) {
        int a = rand() % n;
        int b = rand() % n;

        if (a == b) continue;

        if (find(all(graph[a]),b) == graph[a].end()) {
            // jeżeli taka krawędź nie istnieje
            graph[a].pb(b);
            graph[b].pb(a);
        }
    }

    // tym samym mamy losowy graf
    return graph;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    //int n = rand() % 20 + 3;
    ini(m);
    ini(k);
    //int k = rand() % (n-2) + 3;

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);

        graph[a-1].pb(b-1);
        graph[b-1].pb(a-1);
    }
    //vector<vector<int>> graph = random_graph(n);

    // szukamy cyklu prostego
    vector<int> cycle = find_shortest_cycle(graph);

    if (!cycle.empty()) {
        // jeżeli odnaleźliśmy cykl to sprawdzamy czy jego długość jest mniejsza bądź równa k
        if (cycle.size() <= k) {
            // jeżeli tak, to mamy odpowiedź
            cout << 2 << endl;
            cout << cycle.size() << endl;
            for (int i = 0; i < cycle.size(); i++) {
                /*if (find(all(graph[cycle[i]]),cycle[(i+1) % cycle.size()]) == graph[cycle[i]].end()) {
                    int test = 0;
                }*/

                cout << cycle[i] + 1 << " ";
            }
            cout << endl;
        } else {
            // w tym przypadku cykl jest za długi, po prostu bierzemy pierwsze ceil(k/2) co drugich elementów jako sektę
            int elements = k/2+k%2;
            cout << 1 << endl;
            for (int i = 0; i < elements; i++) {
                /*for (int j = 0; j < elements; j++) {
                    if (find(all(graph[cycle[i*2]]),cycle[j*2]) != graph[cycle[i*2]].end()) {
                        int test = 0;
                    }
                }*/

                cout << cycle[i*2] + 1 << " ";
            }
            cout << endl;
        }
    } else {
        // jeżeli żaden cykl nie istnieje to graf jest drzewem
        int elements = k/2+k%2;

        // po prostu dokonujemy kolorowania drzewa, a następnie bierzemy pierwszych ceil(k/2) wierzchołków tego samego koloru
        vector<bool> colors(n);
        vector<bool> vis(n);
        
        color_tree(0,false,colors,vis,graph);

        vector<int> first_color;
        vector<int> second_color;
        for (int i = 0; i < n; i++) {
            if (colors[i]) first_color.pb(i);
            else second_color.pb(i);
        }

        cout << 1 << endl;
        if (first_color.size() >= elements) {
            for (int i = 0; i < elements; i++) {
                /*for (int j = 0; j < elements; j++) {
                    if (find(all(graph[first_color[i]]),first_color[j]) != graph[first_color[i]].end()) {
                        int test = 0;
                    }
                }*/

                cout << first_color[i] + 1 << " ";
            }
            cout << endl;
        } else {
            for (int i = 0; i < elements; i++) {
                /*for (int j = 0; j < elements; j++) {
                    if (find(all(graph[second_color[i]]),second_color[j]) != graph[second_color[i]].end()) {
                        int test = 0;
                    }
                }*/

                cout << second_color[i] + 1 << " ";
            }
            cout << endl;
        }
    }


}