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

    ini(n1);
    ini(n2);

    vector<int> vec1;
    vector<int> vec2;
    for (int i = 0; i < n1; i++) {
        ini(a);
        vec1.pb(a);
    }

    for (int i = 0; i < n2; i++) {
        ini(a);
        vec2.pb(a);
    }

    int init_val = max(vec1[0] * vec2[0], max(vec1[1] * vec2[0], vec1[0] * vec2[1]));
    vector<vector<int>> dp(n1,vector<int>(n2, init_val));
    for (int i = 1; i < n1; i++) {
        for (int j = 1; j < n2; j++) {
            dp[i][j] = max(dp[i][j], dp[i-1][j-1] + vec1[i] * vec2[j]);
        }
    }

    int maximal_val = init_val;
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            maximal_val = max(maximal_val, dp[i][j]);
        }
    }

    cout << maximal_val << endl;
}