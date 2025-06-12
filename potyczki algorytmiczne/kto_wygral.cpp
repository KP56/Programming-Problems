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

    int sum1 = 0;
    vector<int> vec1;
    for (int i = 0; i < 18; i++) {
        ini(a);
        vec1.pb(a);

        sum1 += a;
    }

    int sum2 = 0;
    vector<int> vec2;
    for (int i = 0; i < 18; i++) {
        ini(a);
        vec2.pb(a);

        sum2 += a;
    }

    if (sum1 > sum2) {
        cout << "Algosia" << endl;
    } else if (sum1 < sum2) {
        cout << "Bajtek" << endl;
    } else {
        vector<int> by_points1(11);
        vector<int> by_points2(11);

        for (int i : vec1) {
            by_points1[i]++;
        }

        for (int i : vec2) {
            by_points2[i]++;
        }

        for (int i = 10; i >= 0; i--) {
            if (by_points1[i] > by_points2[i]) {
                cout << "Algosia" << endl;
                return 0;
            } else if (by_points1[i] < by_points2[i]) {
                cout << "Bajtek" << endl;
                return 0;
            }
        }

        cout << "remis" << endl;
    }
}