#include <bits/stdc++.h>

using namespace std;

#define int long long
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

vector<bool> vis;
vector<int> time_vec;
vector<int> low;
vector<bool> processed;
stack<int> nodes;
vector<vector<int>> sccs;

int timer = 0;
void scc_dfs(int at, vector<vector<int>> &graph) {
    vis[at] = true;

    time_vec[at] = timer++;
    low[at] = time_vec[at];
    nodes.push(at);

    for (int i : graph[at]) {
        if (!vis[i]) {
            scc_dfs(i,graph);
            low[at] = min(low[at],low[i]);
        } else if (!processed[i]) {
            low[at] = min(low[at],time_vec[i]);
        }
    }

    processed[at] = true;

    if (time_vec[at] == low[at]) {
        vector<int> scc_found;
        while (scc_found.empty() || scc_found[scc_found.size()-1] != at) {
            scc_found.pb(nodes.top());
            nodes.pop();
        }

        sccs.pb(scc_found);
    }
}

void find_sccs(vector<vector<int>> &graph) {
    vis = vector<bool>(graph.size());
    time_vec = vector<int>(graph.size());
    low = vector<int>(graph.size());
    processed = vector<bool>(graph.size());

    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            scc_dfs(i,graph);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<vector<int>> graph = {{1},{2,3},{0},{4},{5},{4},{4,7},{5,8},{9},{6,7}};

    find_sccs(graph);

    for (auto i : sccs) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}