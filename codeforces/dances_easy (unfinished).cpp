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

void brute() {
    
}

void readCaseData() {
    ini(n);
    ini(m);

    vector<int> a_arr;
    a_arr.pb(1);
    for (int i = 0; i < n-1; i++) {
        ini(el);
        a_arr.pb(el);
    }

    vector<int> b_arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        b_arr.pb(el);
    }

    bool found_not_working = false;
    for (int i = 0; i < n; i++) {
        if (a_arr[i] >= b_arr[i]) {
            found_not_working = true;
        }
    }

    if (!found_not_working) {
        cout << 0 << endl;
        return;
    }

    sort(all(a_arr));
    sort(all(b_arr));

    int max_val = 0;
    for (int i = 0; i < a_arr.size(); i++) {
        auto it = upper_bound(all(b_arr),a_arr[i]);
        if (it == b_arr.end()) {
            max_val = max(((int) a_arr.size())-i,max_val);
            continue;
        }
        int found = it-b_arr.begin();
        max_val = max(found-i,max_val);
    }

    if (max_val == 0) {
        cout << 1 << endl;
        return;
    }

    cout << max_val << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}