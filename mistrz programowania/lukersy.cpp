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

int sqrt(int num) {
    int i = 0;
    for (; i*i < num; i++);

    if (i*i == num) return i;
    else return i-1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(x);

    int y = (-1+sqrt(1+8*(x-1)))/2;

    int y_prim = y+1;

    /*int lower = y*(y+1)/2+1;
    int upper = (y+1)*(y+2)/2+1;
    if (lower > x || upper < x) {
        int test = 0;
    }*/

    cout << y_prim << endl;
}