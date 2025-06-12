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

// Dorób tutaj bruta jeszcze do testowania
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n1);
    ini(n2);

    vector<int> line1;
    vector<int> line2;

    vector<vector<int>> lines(n1);
    for (int i = 0; i < n1; i++) {
        ini(a);
        line1.pb(a);
    }

    for (int i = 0; i < n2; i++) {
        ini(a);
        line2.pb(a);
    }

    for (int i = 0; i < line1.size(); i++) {
        for (int j = 0; j < line2.size(); j++) {
            if (line1[i] == line2[j]) {
                lines[i].pb(j);
            }
        }
    }

    vector<int> dp(n2);
    for (int i = 0; i < n1; i++) {
        for (int j : lines[i]) {
            int max_val = 0;
            for (int k = 0; k < j; k++) {
                max_val = max(max_val,dp[k]);
            }
            
            dp[j] = max(dp[j], max_val + 1);
        }
    }

    int max_val2 = 0;
    for (int i : dp) {
        max_val2 = max(max_val2,i);
    }

    cout << max_val2 << endl;
}