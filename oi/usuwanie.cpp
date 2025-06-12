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

    ini(a);
    ini(b);

    int p;
    if (a % 2 == 0) {
        p = (b - a) / 2 + 1;
    } else if (a % 2 != 0) {
        // 3 do 5
        // p = 1

        // 3 do 6
        // p = 2
        p = (b - a) / 2 + (b % 2 == 0);
    }

    int n = b - a + 1 - p;

    cout << p / 2 * 2 + n / 2 * 2 << endl;
}