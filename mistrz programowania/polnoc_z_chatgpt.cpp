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
    int current_h = INT_MAX;
    int current_m = INT_MAX;
    for (int i = 0; i < n; i++) {
        ini(h);
        ini(m);

        if (h == 12) {
            h = 0;
        }

        if (h < current_h) {
            current_h = h;
            current_m = m;
        } else if (h == current_h && m < current_m) {
            current_h = h;
            current_m = m;
        } 
    }

    if (current_h == 0) {
        current_h = 12;
    }

    cout << current_h << " " << current_m << endl;
}