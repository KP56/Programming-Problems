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

pii max(pii &a, pii &b) {
    if (a.first > b.first) {
        return a;
    }

    return b;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);
    vector<int> a;
    for (int i = 0; i < n; i++) {
        ini(x);
        a.pb(x - 1);
    }
    vector<int> b;
    for (int i = 0; i < m; i++) {
        ini(x);
        b.pb(x - 1);
    }

    vector<vector<int>> dp(n, vector<int>(m));
    unordered_map<int,int> prev;
    for (int i = 0; i < n; i++) {
        unordered_map<int,int> prev2;
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j] && prev.find(a[i]) != prev.end() && prev2.find(b[j]) != prev2.end()) {
                if (prev[a[i]] == 0 || prev2[b[j]] == 0) dp[i][j] = 2;
                else dp[i][j] = dp[prev[a[i]] - 1][prev2[b[j]] - 1] + 2;
            }
            if (i == 0 || j == 0) dp[i][j] = 0;
            else dp[i][j] = max(max(dp[i][j], dp[i - 1][j]), dp[i][j - 1]);
            prev2[b[j]] = j;
        }
        prev[a[i]] = i;
    }
    
    cout << dp[n - 1][m - 1] << endl;
}