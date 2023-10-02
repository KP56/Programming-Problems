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
    ini(k);

    if (n == 0) {
        cout << 1 << endl;
        return;
    }

    vector<int> fib = {1,1};
    for (int i = 2; i < k - 1; i++) {
        fib.pb(fib[fib.size() - 2] + fib[fib.size() - 1]);
        if (fib[fib.size() - 1] > n) {
            cout << 0 << endl;
            return;
        }
    }

    int fib_k1 = fib[fib.size() - 1];
    int fib_k2 = fib[fib.size() - 2];

    int combinations = 0;
    for (int i = 1; i <= n; i++) {
        int b = fib_k1 * i;
        int a = n-b;

        int f1 = a / fib_k2;

        if (a >= 0 && a % fib_k2 == 0 && a / fib_k2 <= i) {
            combinations++;
        }
    }

    cout << combinations << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}