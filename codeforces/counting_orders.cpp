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

int MOD = 1000000007;

void readCaseData() {
    ini(n);

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        arr.pb(el);
    }

    vector<int> arr2;
    for (int i = 0; i < n; i++) {
        ini(el);
        arr2.pb(el);
    }

    sort(all(arr));
    sort(all(arr2));
    int pointer = 0;
    int res = 1;
    for (int i = 0; i < arr.size(); i++) {
        int el = arr[i];
        while (arr2[pointer] < el && pointer < arr2.size()) pointer++;

        int multiply = (pointer - i) % MOD;

        if (multiply <= 0) {
            cout << 0 << endl;
            return;
        }

        res = (res * multiply) % MOD;
    }

    cout << res % MOD << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}