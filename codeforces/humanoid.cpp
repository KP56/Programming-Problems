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
    inll(size);
    inll(power);

    vector<ll> arr;
    for (int i = 0; i < size; i++) {
        inll(el);
        arr.pb(el);
    }

    sort(all(arr), greater<ll>());
    
    vector<vector<vector<ll>>> dp(size + 1, vector<vector<ll>>(2, vector<ll>(3, -1)));
    dp[0][0][0] = power;
    for (ll i = 0; i < size + 1; i++) {
        for (ll j = 0; j < 2; j++) {
            for (ll k = 0; k < 3; k++) {
                if (j == 0) {
                    dp[i][j + 1][k] = max(dp[i][j + 1][k], dp[i][j][k] * 3);
                }

                if (k < 2) {
                    dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i][j][k] * 2);
                }

                if (i < size && dp[i][j][k] > arr[arr.size() - i - 1]) {
                    dp[i + 1][j][k] = max(dp[i + 1][j][k], dp[i][j][k] + arr[arr.size() - i - 1] / 2);
                }
            }
        }
    }

    ll max_i = 0;
    for (ll i = 0; i < size + 1; i++) {
        for (ll j = 0; j < 2; j++) {
            for (ll k = 0; k < 3; k++) {
                if (dp[i][j][k] != -1) {
                    max_i = max(max_i, i);
                }
            }
        }
    }

    cout << max_i << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}