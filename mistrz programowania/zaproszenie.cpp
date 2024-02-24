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

    ini(s);
    ini(n);

    char border;
    char filling;
    for (int i = 0; i < s; i++) {
        instr(a);

        if (i == 0) {
            border = a[0];
        } else if (i == 1) {
            filling = a[1];
        }
    }

    string border_str = string(1,border);
    string filling_str = string(1,filling);
    for (int i = 0; i < n; i++) {
        cout << border_str;
    }
    cout << endl;
    for (int i = 1; i < n-1; i++) {
        cout << border_str;
        for (int j = 0; j < n-2; j++) {
            cout << filling_str;
        }
        cout << border_str;
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        cout << border_str;
    }
    cout << endl;
}