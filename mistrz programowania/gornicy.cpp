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

void append_level(int n, vector<vector<int>> &tree) {
    int current_size = tree.size();
    for (int i = 0; i < current_size; i++) {
        if (tree[i].size() != 1 && (i != 0 || !tree[i].empty())) continue;

        for (int j = 0; j < n; j++) {
            tree[i].pb(tree.size());
            tree.pb({});
            tree[tree.size()-1].pb(i);
        }
    }
}

vector<vector<int>> generate_tree(int n, int nodes) {
    vector<vector<int>> tree;
    tree.pb({});
    while (tree.size() < nodes) {
        append_level(n,tree);
    }

    return tree;
}

int find_level(int at, int counter, int a, vector<vector<int>> &tree, vector<bool> &vis) {
    vis[at] = true;

    if (at == a) {
        return counter;
    }

    for (int i : tree[at]) {
        if (!vis[i]) {
            int res = find_level(i,counter+1,a,tree,vis);
            if (res != -1) {
                return res;
            }
        }
    }

    return -1;
}

int bruteforce(int n, int a, int b) {
    vector<vector<int>> tree = generate_tree(n, max(a,b));

    a--;
    b--;

    int c = min(a,b);
    int d = max(a,b);

    vector<bool> vis = vector<bool>(tree.size());

    int level_c = find_level(0,0,c,tree,vis);
    vis = vector<bool>(tree.size());
    int level_d = find_level(0,0,d,tree,vis);

    if (level_c < 0) {
        int test = 0;
    }

    while (level_c < level_d) {
        for (int i : tree[d]) {
            if (i < d) {
                d = i;
                break;
            }
        }
        level_d--;
    }

    while (c != d) {
        for (int i : tree[c]) {
            if (i < c) {
                c = i;
                break;
            }
        }

        for (int i : tree[d]) {
            if (i < d) {
                d = i;
                break;
            }
        }
    }

    return c;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(t);

    while (t--) {
        ini(n);
        ini(c);
        ini(d);

        /*int n = rand() % 3 + 1;
        int c = rand() % 10 + 1;
        int d = rand() % 10 + 1;*/

        int a = min(c,d);
        int b = max(c,d);

        /*int a_cp = a;
        int b_cp = b;*/

        //int brute_res = bruteforce(n,a,b);

        if (n == 1) {
            cout << a << endl;

            continue;
        }

        vector<int> nodes_levels;
        int current = 0;
        int level = 1;
        int level_a = 0;
        int level_b = 0;
        while (current < max(a,b)) {
            if (current < a) level_a = nodes_levels.size();
            if (current < b) level_b = nodes_levels.size();
            current += level;
            nodes_levels.pb(current);
            level *= n;
        }

        a -= level_a == 0 ? 0 : nodes_levels[level_a-1];
        b -= level_b == 0 ? 0 : nodes_levels[level_b-1];

        a--;
        b--;

        while (level_a < level_b) {
            b /= n;
            level_b--;
        }

        int level_ans = level_a;
        while (a != b) {
            a /= n;
            b /= n;
            level_ans--;
        }

        int ans = (level_ans == 0 ? 0 : nodes_levels[level_ans-1]) + a + 1;

        /*if (brute_res + 1 != ans) {
            int test = 0;
        }*/

        //cout << brute_res + 1 << endl;
        cout << ans << endl;
    }
}