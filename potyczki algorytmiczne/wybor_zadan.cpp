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
    return c - '1';
}

int charToIntAlphabet(char c) {
    return c - 'A';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(n);

    vector<string> vec;
    for (int i = 0; i < n; i++) {
        in_str(a);
        vec.pb(a);
    }
    
    vector<vector<int>> matches(5, vector<int>(3));
    for (string s : vec) {
        matches[charToInt(s[0])][charToIntAlphabet(s[1])]++;
    }

    for (int i = 0; i < 5; i++) {
        if (i == 4) {
            for (int j : matches[i]) {
                if (j < 2) {
                    cout << "NIE" << endl;
                    return 0;
                }
            }
        } else {
            for (int j : matches[i]) {
                if (j < 1) {
                    cout << "NIE" << endl;
                    return 0;
                }
            }
        }
    }

    cout << "TAK" << endl;
}