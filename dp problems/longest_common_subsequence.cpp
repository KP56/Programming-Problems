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
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

vector<vector<int>> dp;
int lcsUtils(vector<int> &vec, vector<int> &vec2, int i, int j) {
    if (i <= -1 || j <= -1) {
        return 0;
    }

    if (i == 0 || j == 0) {
        if (vec[i] == vec2[j]) {
            return 1;
        }

        if (i == 0 && j == 0) {
            return 0;
        } else if (i == 0) {
            return dp[i][j - 1] == -1 ? (dp[i][j - 1] = lcsUtils(vec, vec2, i, j - 1)) : dp[i][j - 1];
        } else {
            return dp[i - 1][j] == -1 ? (dp[i - 1][j] = lcsUtils(vec, vec2, i - 1, j)) : dp[i - 1][j];
        }
    }

    if (vec[i] == vec2[j]) {
        return (dp[i - 1][j - 1] == -1 ? (dp[i - 1][j - 1] = lcsUtils(vec, vec2, i - 1, j - 1)) : dp[i - 1][j - 1]) + 1;
    }

    return max(dp[i - 1][j] == -1 ? (dp[i - 1][j] = lcsUtils(vec, vec2, i - 1, j)) : dp[i - 1][j],
            dp[i][j - 1] == -1 ? (dp[i][j - 1] = lcsUtils(vec, vec2, i, j - 1)) : dp[i][j - 1]);
}

int lcs(vector<int> vec, vector<int> vec2) {
    dp = vector<vector<int>>(vec.size(), vector<int>(vec2.size(), -1));

    return lcsUtils(vec, vec2, vec.size() - 1, vec2.size() - 1);
}

//O(n*m)
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << lcs({1, 1, 3}, {1, 2, 3}) << endl;
}