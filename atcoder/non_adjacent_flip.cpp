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

const int N = 2e5+10;
const int M = 5e3+10;

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
    instr(s);

    int counter = 0;
    for (char c : s) {
        if (c == '1') counter++;
    }

    if (counter % 2 == 1) {
        cout << -1 << endl;
        return;
    }

    if (s == "0110") {
        cout << 3 << endl;
        return;
    }

    bool adjacent = false;
    for (int i = 0; i < n-1; i++) {
        if (s[i] == '1' && s[i+1] == '1') adjacent = true;
    }

    if (s == "110" || s == "011") {
        cout << -1 << endl;
        return;
    }

    if (counter != 2 || !adjacent) {
        cout << counter / 2 << endl;
        return;
    }

    cout << 2 << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}