#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

//https://codeforces.com/blog/entry/62393
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(x);
    vector<pii> candidates;
    for (int m = 1; m <= x; m++) {
        int n1 = (x - m) / (2*m - 1);
        int x1 = 2*n1*m - n1 + m;

        if (x1 == x && n1 < m && n1 > 0) {
            candidates.pb({n1,m});
        }

        int n2 = sqrtl((x - 1) / 2);
        int x2 = 2*n2*n2 + 1;

        if (x2 == x && n2 == m && n2 > 0) {
            candidates.pb({n2,m});
        }
        
        int n3 = (x - 1 + m) / (2*m + 1);
        int x3 = 2*n3*m + n3 - m + 1;

        if (x3 == x && n3 > m && n3 > 0) {
            candidates.pb({n3,m});
        }
    }

    cout << candidates.size() << endl;
    for (pii i : candidates) {
        cout << i.first << " " << i.second << endl;
    }
}