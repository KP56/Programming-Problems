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

int charToInt(char c) {
    return c - 'a';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_str(str1);
    in_str(str2);

    vector<vector<int>> v(2, vector<int>(26));
    vector<vector<int>> v2(2, vector<int>(26));

    for (int i = 0; i < size; i++) {
        char c = str1[i];
        v[i % 2][charToInt(c)]++;
    }

    for (int i = 0; i < size; i++) {
        char c = str2[i];
        v2[i % 2][charToInt(c)]++;
    }

    for (int i = 0; i < 2; i++) {
        if (v[i] != v2[i]) {
            cout << "NIE" << endl;
            return 0;
        }
    }

    cout << "TAK" << endl;
}