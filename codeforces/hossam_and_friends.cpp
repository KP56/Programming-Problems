#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define inll(x) ll x; in(x)
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

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
    inll(n);
    inll(m);

    vector<pll> vec;
    for (ll i = 0; i < m; i++) {
        inll(a);
        inll(b);
        a--;
        b--;

        if (a < b) {
            vec.pb({b,a});
        } else {
            vec.pb({a,b});
        }
    }
    sort(all(vec));

    vector<pll> rev;
    for (pll p : vec) {
        rev.pb({p.second,p.first});
    }

    vector<ll> column_records(n);
    ll prev = -1;
    for (pll p : rev) {
        for (ll i = p.first; i > prev; i--) {
            column_records[i] = n - p.second;
        }

        prev = max(prev, p.first);
    }

    ll s = 0;
    for (ll i : column_records) {
        s += i;
    }

    cout << n * (n + 1) / 2 - s << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}