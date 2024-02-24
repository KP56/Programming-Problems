#include <bits/stdc++.h>

using namespace std;

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
    bool match_one = true;
    bool match_two = true;

    for (int i = 0; i < n; i++) {
        ini(a);

        if (a != 1) {
            match_one = false;
        }

        if (a != 1 && a != 2) {
            match_two = false;
        }
    }

    int res = 7;
    if (match_one) res = 1;
    else if (match_two) res = 2;

    if (n <= 100) res = min(res,3);
    if (n <= 1000) res = min(res,4);
    if (n % 2 == 0) res = min(res,5);
    if (n % 2 == 1) res = min(res,6);

    cout << res << endl;
}