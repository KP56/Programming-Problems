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

int lcsUtils(vector<int> &arr, vector<int> &arr2, int i, int j);

int iterations = 0;
vector<vector<int>> dp;
int call(vector<int> &arr, vector<int> &arr2, int i, int j) {
    if (i >= 0 && j >= 0) {
        return dp[i][j] == -1 ? (dp[i][j] = lcsUtils(arr, arr2, i, j)) : dp[i][j];
    } else {
        return lcsUtils(arr, arr2, i, j);
    }
}

int lcsUtils(vector<int> &arr, vector<int> &arr2, int i, int j) {
    iterations++;

    if (i <= -1 || j <= -1) {
        return 0;
    }

    if (i == 0 || j == 0) {
        if (arr[i] == arr2[j]) {
            return 1;
        }

        if (i == 0 && j == 0) {
            return 0;
        }
        
        if (i == 0) {
            return call(arr, arr2, i, j - 1);
        }

        return call(arr, arr2, i - 1, j);
    }

    int counter = 0;
    for (; arr[i] == arr2[j] && i >= 0 && j >= 0; counter++) {
        iterations++;

        i--;
        j--;
    }

    if (counter > 0) {
        return max(counter, max(call(arr, arr2, i, j + 1), call(arr, arr2, i + 1, j)));
    }

    return max(call(arr, arr2, i - 1, j), call(arr, arr2, i, j - 1));
}

int lcs(vector<int> arr, vector<int> arr2) {
    dp = vector<vector<int>>(arr.size(), vector<int>(arr2.size(), -1));

    return lcsUtils(arr, arr2, arr.size() - 1, arr2.size() - 1);
}

//O(n*m)
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    /*cout << lcs({1, 1, 2, 3}, {1, 0, 1, 2, 3, 4}) << endl; //3
    cout << lcs({1, 2, 3}, {1, 2, 3}) << endl; //3
    cout << lcs({1, 1, 2, 3}, {1, 2, 3}) << endl; //3
    cout << lcs({1, 1, 2, 3}, {1, 1, 3}) << endl; //2
    cout << lcs({1, 1, 5}, {1, 1, 3}) << endl; //2
    cout << lcs({1}, {1}) << endl; //1
    cout << lcs({}, {}) << endl; //0
    cout << lcs({1}, {2}) << endl; //0
    cout << lcs({1, 3, 2}, {2, 1, 3}) << endl; //2
    cout << lcs({1, 1, 2, 3, 4, 8, 12}, {8, 1, 0, 1, 2, 3, 4, 8, 12}) << endl; //6*/

    vector<int> v1;
    vector<int> v2;
    for (int i = 0; i < 1000; i++) {
        v1.pb(i * 200 + 3);
        v2.pb(i * 100 + 3);
    }

    lcs(v1, v2);

    cout << iterations << endl;
}