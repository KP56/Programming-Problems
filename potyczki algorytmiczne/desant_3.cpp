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

void bruteforce(vector<pii> &orders, vector<int> &ans, vector<bool> &soldiers, int n) {
    if (soldiers.size() == n) {
        int count = 0;
        for (bool b : soldiers) count += b;

        for (pii &o : orders) {
            if (soldiers[o.first] && !soldiers[o.second]) {
                soldiers[o.first] = 0;
                soldiers[o.second] = 1;
            }
        }

        bool prev = soldiers[0];
        bool found_segment = false;
        for (int i = 1; i < n; i++) {
            if (found_segment && soldiers[i]) {
                return;
            }
            if (prev && !soldiers[i]) {
                found_segment = true;
            }
            prev = soldiers[i];
        }

        ans[count] ^= 1;

        return;
    }

    vector<bool> cp = soldiers;
    cp.pb(0);
    bruteforce(orders,ans,cp,n);

    soldiers.pb(1);
    bruteforce(orders,ans,soldiers,n);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<pii> orders;
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);

        a--;
        b--;

        orders.pb({a,b});
    }

    vector<int> ans(n+1);
    vector<bool> soldiers;
    bruteforce(orders,ans,soldiers,n);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}