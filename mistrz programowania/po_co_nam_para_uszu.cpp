#include <bits/stdc++.h>

#include "r3clib.h"

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

/*int actual_x = 7536653;
int actual_y = -31415;
int sluchaj(int x1, int y1, int x2, int y2) {
    if (x1 == 0 && x2 == -1) {
        if (y1 < actual_y) {
            return 1;
        } else if (y1 == actual_y) {
            return 0;
        } else {
            return -1;
        }
    } else {
        if (x1 < actual_x) {
            return 1;
        } else if (x1 == actual_x) {
            return 0;
        } else {
            return -1;
        }
    }
}*/

int call_func(int x, bool dim) {
    if (dim) return sluchaj(x,0,x,1);
    else return sluchaj(0,x,-1,x);
}

int binary_search(bool dim) {
    int upper_bound = 1e9;
    int lower_bound = -1e9;

    while (upper_bound >= lower_bound) {
        int mid = lower_bound + (upper_bound - lower_bound) / 2;
        int res = call_func(mid,dim);

        if (res == 0) {
            return mid;
        } else if (res == -1) {
            upper_bound = mid-1;
        } else {
            lower_bound = mid+1;
        }
    }

    cout << "Something went wrong?" << endl;
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int res1 = binary_search(true);
    int res2 = binary_search(false);
    odpowiedz(res1,res2);
    //cout << res1 << " " << res2 << endl;
}