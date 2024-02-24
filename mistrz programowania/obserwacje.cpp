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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<unordered_set<int>> graph(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        graph[b-1].insert(a-1);
    }

    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        for (int e : graph[i]) {
            if (graph[e].find(i) == graph[e].end()) {
                ans[i]++;
            }
        }
    }

    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
}