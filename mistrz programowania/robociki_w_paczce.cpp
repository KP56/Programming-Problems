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

void components_dfs(int at, vector<bool> &vis, vector<vector<int>> &graph, vector<int> &component) {
    vis[at] = true;
    component.pb(at);

    for (int i : graph[at]) {
        if (!vis[i]) {
            components_dfs(i,vis,graph,component);
        }
    }
}

vector<vector<int>> find_components(vector<vector<int>> &graph) {
    vector<bool> vis(graph.size());

    vector<vector<int>> components;
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            vector<int> component;
            components_dfs(i,vis,graph,component);
            components.pb(component);
        }
    }

    return components;
}

vector<pii> find_knapsack(vector<int> &el_values, vector<vector<int>> &graph, vector<vector<int>> &components) {
    vector<pii> items(components.size());
    for (int i = 0; i < components.size(); i++) {
        int sum = 0;
        for (int j : components[i]) {
            sum += el_values[j];
        }

        items[i] = {sum,components[i].size()};
    }

    return items;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    ini(k);

    vector<int> el_values;
    for (int i = 0; i < n; i++) {
        ini(a);
        el_values.pb(a);
    }

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);

        a--;
        b--;

        graph[a].pb(b);
        graph[b].pb(a);
    }

    vector<vector<int>> components = find_components(graph);

    // {wartość,waga}
    vector<pii> knapsack_items = find_knapsack(el_values,graph,components);

    vector<vector<int>> dp(knapsack_items.size()+1,vector<int>(k+1));
    int res = 0;
    for (int i = 0; i < knapsack_items.size(); i++) {
        for (int j = 0; j <= k; j++) {
            if (j+knapsack_items[i].second <= k) {
                dp[i+1][j+knapsack_items[i].second] = max(dp[i+1][j+knapsack_items[i].second],dp[i][j]+knapsack_items[i].first);
                res = max(res,dp[i][j]+knapsack_items[i].first);
            }
            dp[i+1][j] = max(dp[i+1][j],dp[i][j]);
        }
    }

    cout << res << endl;
}