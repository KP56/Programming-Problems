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

    ini(hx);
    ini(hy);
    ini(sx);
    ini(sy);

    if (hx == sx && hy == sy) {
        cout << 0 << endl;
    } else if (abs(hx-sx) == abs(hy-sy) || hx == sx || sy == hy) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }
}