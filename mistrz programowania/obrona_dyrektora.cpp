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

void modify(string &a) {
    for (int i = 1; i < a.size() - 1; i++) {
        a[i] = '*';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    instr(a);
    instr(b);

    modify(a);
    modify(b);

    cout << a << " " << b << endl;
}