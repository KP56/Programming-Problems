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

// Program lokalnie testowany na losowych testach nie zgłasza żadnych problemów z zakresem wyników, natomiast podczas testowania
// online na przygotowanych testach już tak. Błąd w zrozumieniu zadania???

bool canMove(vector<vector<bool>> &vis, int i, int j) {
    if (i < 0 || j < 0 || i >= vis.size() || j >= vis[0].size()) {
        return false;
    }

    return !vis[i][j];
}

void update(int i, int j, int prev_i, int prev_j, vector<vector<bool>> &vis, vector<vector<int>> &ans, int debugFlag) {
    vis[i][j] = true;
    ans.pb({j+1,i+1,prev_j+1,prev_i+1});
}

vector<vector<int>> solve(int n, int m, int k) {
    vector<vector<int>> ans;
    vector<vector<bool>> vis(n,vector<bool>(m));
    vis[0][0] = true;

    if (m == 1) {
        if (n == k+1) {
            for (int i = 1; i < n; i++) {
                update(i,0,i-1,0,vis,ans,1);
            }

            return ans;
        } else {
            return {};
        }
    }

    int pillar_x = -1;
    int min_val_cp = -1;
    for (int i = 0; i <= n/2-(!(n%2)); i++) {
        int min_val = 2*n-2*i+m-3;
        if (k>=min_val) {
            pillar_x = i;
            min_val_cp = min_val;
            break;
        }
    }

    int dist = 2*(n-pillar_x-1)+m-1;

    if (pillar_x == -1) {
        return {};
    }

    for (int i = 1; i < n; i++) {
        update(i,0,i-1,0,vis,ans,2);
    }

    for (int i = 1; i < m; i++) {
        update(pillar_x,i,pillar_x,i-1,vis,ans,3);
    }

    for (int i = pillar_x + 1; i < n; i++) {
        update(i,m-1,i-1,m-1,vis,ans,4);
    }

    if (pillar_x != 0 && min_val_cp == k - 1) {
        if (m != 2) {
            dist++;
            update(n-1,m-2,n-1,m-1,vis,ans,6);
        }
    }

    if (min_val_cp == k - 1 && m == 2 && n % 2 == 1 && pillar_x == n / 2) {
        update(0,1,0,0,vis,ans,5);
        dist++;
    }

    if (pillar_x == 0 && dist != k && canMove(vis,n-1,m-2)) {
        int x = n-1;
        int y = m-2;
        int prev_x = n-1;
        int prev_y = m-1;

        while (y >= 0) {
            update(x,y,prev_x,prev_y,vis,ans,9);
            dist++;
            if (dist >= k)
                break;

            if (!canMove(vis,x,y-1)) {
                if (!canMove(vis,x,y+1)) {
                    if (!canMove(vis,x-1,y)) {
                        return {};
                    } else {
                        prev_x = x;
                        prev_y = y;
                        x--;
                    }
                } else {
                    prev_x = x;
                    prev_y = y;
                    y++;
                }
            } else {
                prev_x = x;
                prev_y = y;
                y--;
            }
        }
    }

    if (dist != k) {
        return {};
    }

    for (int i = 0; i < m; i++) {
        for (int j = pillar_x + 1; j < n; j++) {
            if (canMove(vis,j,i)) {
                update(j,i,j-1,i,vis,ans,7);
            }
        }

        for (int j = pillar_x - 1; j >= 0; j--) {
            if (canMove(vis,j,i)) {
                update(j,i,j+1,i,vis,ans,8);
            }
        }
    }


    return ans;
}

int longestPathGraph(int at, vector<vector<int>> &graph, vector<bool> vis) {
    vis[at] = true;

    int ans = 0;
    for (int i : graph[at]) {
        if (!vis[i]) {
            ans = max(ans, longestPathGraph(i, graph, vis)+1);
        }
    }

    return ans;
}

int coordsToID(int i, int j, int n, int m) {
    if (i >= m || j >= n) {
        int test = 0;
    }

    return i*n+j;
}

bool verify(int n, int m, int k, vector<vector<int>> &ans) {
    vector<vector<int>> graph(n*m);
    for (auto i : ans) {
        graph[coordsToID(i[0]-1,i[1]-1,n,m)].pb(coordsToID(i[2]-1,i[3]-1,n,m));
        graph[coordsToID(i[2]-1,i[3]-1,n,m)].pb(coordsToID(i[0]-1,i[1]-1,n,m));
    }

    int longest_path = 0;
    for (int i = 0; i < n*m; i++) {
        longest_path = max(longest_path, longestPathGraph(i, graph, vector<bool>(n*m)));
    }

    return longest_path == k;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    for (int i = 0; i < 100; i++) {
    //ini(n);
    int n = rand() % 6 + 1;
    //ini(m);
    int m = rand() % 6 + 1;
    //ini(k);
    int k = rand() % 36 + 1;

    if ((n == 1 || n == 2) && m != 1) {
        int cp_m = m;
        m = n;
        n = cp_m;
    }

    vector<vector<int>> ans = solve(n,m,k);

    if (m != 1 && m != 2 && ans.empty()) {
        ans = solve(m,n,k);

        for (auto &i : ans) {
            int cp1 = i[0];
            i[0] = i[1];
            i[1] = cp1;
            int cp2 = i[2];
            i[2] = i[3];
            i[3] = cp2;
        }
    }

    if (ans.empty()) {
        //cout << "NIE" << endl;
        //return 0;
        continue;
    }

    if (!verify(n,m,k,ans)) {
        int test = 0;
    }

    //cout << "TAK" << endl;
    for (auto i : ans) {
        if (i[0] > m || i[2] > m || i[1] > n || i[3] > n || i[0] <= 0 || i[1] <= 0 || i[2] <= 0 || i[3] <= 0) {
            int test = 0;
        }

        for (int j : i) {
            //cout << j << " ";
        }
        //cout << endl;
    }
    }
}