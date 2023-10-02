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

void readCaseData() {
    ini(n);

    vector<int> pref(1, 1);
    vector<int> min_val(1, 1);
    vector<int> max_from_all(1, 1);
    vector<int> pref2(1, -1);
    vector<int> min_val2(1, -1);
    vector<int> max_from_all2(1, 0);
    for (int i = 0; i < n; i++) {
        instr(type);

        if (type == "+") {
            //Adding a node
            ini(v);
            ini(x);
            pref.pb(pref[v-1]+x);
            min_val.pb(min(min(pref[pref.size() - 1], 0ll), min_val[v-1]));
            max_from_all.pb(max(pref[pref.size() - 1] - min(0ll, min_val[min_val.size() - 1]), max_from_all[v-1]));
            pref2.pb(pref2[v-1]-x);
            min_val2.pb(min(min(pref2[pref2.size() - 1], 0ll), min_val2[v-1]));
            max_from_all2.pb(max(pref2[pref.size() - 1] - min(0ll, min_val2[min_val.size() - 1]), max_from_all2[v-1]));
        } else {
            ini(u);
            ini(v);
            ini(k);
            if (k == 0) {
                cout << "YES" << endl;
            } else if (k > 0) {
                if (max_from_all[v-1] >= k) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            } else {
                if (max_from_all2[v-1] >= k*(-1)) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}