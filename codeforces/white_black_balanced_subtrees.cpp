#include <bits/stdc++.h>

using namespace std;

vector<bool> outer_nodes_vis;
vector<int> outer;
vector<int> below;
void outer_nodes_dfs(int at, vector<vector<int>> &adj_list) {
    outer_nodes_vis[at] = true;

    bool is_last = true;
    for (int i : adj_list[at]) {
        if (!outer_nodes_vis[i]) {
            is_last = false;
            below[at]++;
            outer_nodes_dfs(i, adj_list);
        }
    }

    if (is_last) {
        outer.push_back(at);
    }
}

void outer_nodes(vector<vector<int>> &adj_list) {
    outer_nodes_vis = vector<bool>(adj_list.size());
    below = vector<int>(adj_list.size());
    outer = {};

    outer_nodes_dfs(0, adj_list);
}

vector<pair<int, int>> current_colors;
int subtrees = 0;
void find_to_root(int at, string &colors, vector<vector<int>> &adj_list, vector<bool> &visited) {
    if (colors[at] == 'W') {
        current_colors[at].first++;
    } else {
        current_colors[at].second++;
    }

    if (current_colors[at].first == current_colors[at].second) {
        subtrees++;
    }

    visited[at] = true;

    for (int i : adj_list[at]) {
        if (!visited[i]) {
            current_colors[i].first += current_colors[at].first;
            current_colors[i].second += current_colors[at].second;

            below[i]--;
            if (below[i] == 0) {
                find_to_root(i, colors, adj_list, visited);
            }
        }
    }
}

int balanced_subtrees(vector<vector<int>> &adj_list, string &colors) {
    outer_nodes(adj_list);

    vector<bool> visited(adj_list.size());
    current_colors = vector<pair<int, int>>(adj_list.size());
    subtrees = 0;
    for (int i : outer) {
        find_to_root(i, colors, adj_list, visited);
    }

    return subtrees;
}

void read_arr() {
    int size;
    cin >> size;

    vector<vector<int>> adj_list(size);

    for (int i = 1; i < size; i++) {
        int parent;
        cin >> parent;

        adj_list[i].push_back(parent - 1);
        adj_list[parent - 1].push_back(i);
    }

    string colors;
    cin >> colors;

    cout << balanced_subtrees(adj_list, colors) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        read_arr();
    }
}