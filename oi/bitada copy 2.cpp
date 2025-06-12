#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define st first
#define nd second
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

void dfs(int at, vector<vector<int>> &tree1, vector<bool> &vis, vector<int> &depths, vector<vector<int>> &by_depth) {
    vis[at] = true;
    by_depth[depths[at]].pb(at);

    for (int i : tree1[at]) {
        if (!vis[i]) {
            depths[i] = depths[at] + 1;
            dfs(i,tree1,vis,depths,by_depth);
        }
    }
}

void gather_info(vector<vector<int>> &tree1, vector<int> &depths, vector<vector<int>> &by_depth) {
    vector<bool> vis(tree1.size());
    
    for (int i = 0; i < tree1.size(); i++) {
        if (!vis[i]) {
            dfs(i,tree1,vis,depths,by_depth);
        }
    }
}

vector<bool> to_bits(int b, int n) {
    vector<bool> b_vec;
    while (b_vec.size() < n) {
        b_vec.pb(b & 1);
        b >>= 1;
    }

    return b_vec;
}

void all_perms_rec(vector<int> &vec, vector<bool> &vis, vector<vector<int>> &permutations, int n) {
    if (vec.size() == n) {
        permutations.pb(vec);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            vector<bool> vis_cp = vis;
            vis_cp[i] = true;
            vector<int> v_cp = vec;
            v_cp.pb(i);
            all_perms_rec(v_cp,vis_cp,permutations,n);
        }
    }
}

void all_permutations(vector<vector<int>> &permutations, int n) {
    vector<int> vec;
    vector<bool> vis(n);
    all_perms_rec(vec,vis,permutations,n);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ini(n);
    ini(m);
    ini(k);

    if (n == 1 && m == 1) {
        cout << 1 << endl;
        return 0;
    }

    vector<vector<int>> tree1(n);
    for (int i = 0; i < n-1; i++) {
        ini(a);
        ini(b);

        tree1[a - 1].pb(b - 1);
        tree1[b - 1].pb(a - 1);
    }

    vector<vector<int>> tree2(m);
    for (int i = 0; i < m - 1; i++) {
        ini(a);
        ini(b);

        tree2[a - 1].pb(b - 1);
        tree2[b - 1].pb(a - 1);
    }

    vector<int> depths(n);
    vector<vector<int>> by_depth(n);
    gather_info(tree1,depths,by_depth);

    int maximum_depth = 0;
    for (int i : depths) {
        maximum_depth = max(i, maximum_depth);
    }

    //vector<vector<vector<int>>> dp(n,vector<vector<int>>(m,vector<int>(8)));
    // przechowuje sume wszystkich dla których konkretny bit jest zerem
    //vector<vector<vector<int>>> sum_dp(n,vector<vector<int>>(m,vector<int>(3)));
    static int sum_dp[3000][3000][3] = {0};

    int ans = 0;
    for (int u : by_depth[maximum_depth]) {
        for (int v = 0; v < m; v++) {
            //dp[u][v][0] = 1;
            for (int i = 0; i < 3; i++) {
                sum_dp[u][v][i] = (1 + sum_dp[u][v][i]) % k;
            }

            if (u == 0) {
                ans = (ans + 1) % k;
            }
        }
    }
    for (int i = maximum_depth - 1; i >= 0; i--) {
        vector<int> at_depth = by_depth[i];
        for (int u : at_depth) {
            vector<int> children;
            for (int j : tree1[u]) {
                if (depths[j] > depths[u]) {
                    children.pb(j);
                }
            }

            for (int v = 0; v < m; v++) {
                if (tree2[v].size() < tree1[u].size()) continue;

                for (int dir = 0; dir < (1 << tree2[v].size()); dir++) {
                    int total_taken = 0;
                    for (int b = 0; b < 3; b++) {
                        total_taken += (dir >> b) & 1;
                    }

                    if (total_taken != (u == 0 ? tree1[u].size() : tree1[u].size() - 1)) continue;

                    // Tutaj powinienem przeiterować po wszystkich możliwych wstawieniach
                    // wierzchołków z bitady do grafu z bajtogrodu w bity reprezentowane przez
                    // bits

                    vector<int> bitada_permut;
                    for (int j = 0; j < (u == 0 ? tree1[u].size() : tree1[u].size() - 1); j++) {
                        bitada_permut.pb(j);
                    }

                    int total_sum = 0;
                    do {
                        int which_node_to_insert = 0;
                        int combinations_for_a_permutation = 1;
                        for (int other_node = 0; other_node < tree2[v].size(); other_node++) {
                            if (!((dir >> other_node) & 1)) continue;

                            // Problem tu jest taki, że musimy ignorować wierzchołek w górę
                            int insertion_node_id = children[bitada_permut[which_node_to_insert]];
                            int to_place_node_id = tree2[v][other_node];
                            // Chcemy wziąć insertion_node_id z tree1 i wsadzić w to_place_node_id
                            int edge_idx = find(all(tree2[to_place_node_id]),v) - tree2[to_place_node_id].begin();

                            int combinations_for_all_dirs = sum_dp[insertion_node_id][to_place_node_id][edge_idx];

                            combinations_for_a_permutation = (combinations_for_a_permutation * combinations_for_all_dirs) % k;

                            which_node_to_insert++;
                        }

                        total_sum = (total_sum + combinations_for_a_permutation) % k;
                    } while (next_permutation(all(bitada_permut)));

                    for (int j = 0; j < 3; j++) {
                        if (!((dir >> j) & 1)) {
                            sum_dp[u][v][j] = (total_sum + sum_dp[u][v][j]) % k;
                        }
                    }

                    if (u == 0) {
                        ans = (ans + total_sum) % k;
                    }
                }
            }
        }
    }

    cout << ans << endl;
}
