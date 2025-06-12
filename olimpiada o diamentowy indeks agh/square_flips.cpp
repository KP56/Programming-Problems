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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    instr(s);
    pii current_range = {-1,-1};
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'w' && i >= current_range.first && i <= current_range.second) {
            if (k + i - 1 >= n) {
                cout << -1 << endl;
                return 0;
            }

            current_range = {current_range.second + 1, k + i - 1};
            ans++;
        } else if (s[i] == 'b' && (i < current_range.first || i > current_range.second)) {
            if (k + i - 1 >= n) {
                cout << -1 << endl;
                return 0;
            }

            current_range = {i, i + k - 1};
            ans++;
        }
    }

    cout << ans << endl;
}