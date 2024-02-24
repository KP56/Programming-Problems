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

    int current_num = n;
    double current_amount = 0;
    cout << fixed << setprecision(5);
    vector<double> ans(n);
    for (int i = 0; i < m; i++) {
        instr(type);
        ini(num);

        if (type == "W") {
            current_num--;
            ans[num-1] = current_amount;
        } else if (type == "Z") {
            current_amount += ((double) num) / ((double) current_num);
        } else {
            cout << "???" << endl;
        }
    }

    for (double d : ans) {
        cout << d << " ";
    }
    cout << endl;
}