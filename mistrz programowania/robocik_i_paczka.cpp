#include <bits/stdc++.h>

#include "r0clib.h"

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

/*pair<int,int> podnies() {
    return {0,-3};
}

int x = 0;
int y = 0;
void w_prawo() {
    x++;
}

void w_lewo() {
    x--;
}

void do_przodu() {
    y++;
}

void do_tylu() {
    y--;
}

void odstaw() {
    cout << x << " " << y << endl;
}*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    pair<int,int> goal = podnies();

    if (goal.first > 0) {
        for (int i = 0; i < goal.first; i++) {
            w_prawo();
        }
    } else {
        for (int i = 0; i < -goal.first; i++) {
            w_lewo();
        }
    }

    if (goal.second > 0) {
        for (int i = 0; i < goal.second; i++) {
            do_przodu();
        }
    } else {
        for (int i = 0; i < -goal.second; i++) {
            do_tylu();
        }
    }

    odstaw();
}