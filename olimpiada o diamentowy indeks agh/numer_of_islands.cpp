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

void dfs(int x, int y, vector<string> &v, vector<vector<bool>> &vis) {
    vis[x][y] = true;

    vector<pii> coords = {
        {1,0},
        {0,1},
        {-1,0},
        {0,-1}
    };

    for (pii c : coords) {
        int x_prim = x + c.first;
        int y_prim = y + c.second;

        if (x_prim < vis.size() && x_prim >= 0 && y_prim < vis[0].size() && y_prim >= 0 && !vis[x_prim][y_prim] && v[x_prim][y_prim] == 'l') {
            dfs(x_prim, y_prim, v, vis);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(m);
    ini(n);

    vector<string> v;
    for (int i = 0; i < m; i++) {
        instr(s);
        v.pb(s);
    }

    vector<vector<bool>> vis(m,vector<bool>(n));

    for (int x = 0; x < m; x++) {
        if (!vis[x][0] && v[x][0] == 'l') {
            dfs(x,0,v,vis);
        }

        if (!vis[x][n-1] && v[x][n-1] == 'l') {
            dfs(x,n-1,v,vis);
        }
    }

    for (int x = 0; x < n; x++) {
        if (!vis[0][x] && v[0][x] == 'l') {
            dfs(0,x,v,vis);
        }

        if (!vis[m-1][x] && v[m-1][x] == 'l') {
            dfs(m-1,x,v,vis);
        }
    }

    int ans = 0;
    for (int x = 0; x < m; x++) {
        for (int y = 0; y < n; y++) {
            if (!vis[x][y] && v[x][y] == 'l') {
                ans++;
            }
        }
    }

    cout << ans << endl;
}