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

int acc(int i, vector<int> &vec) {
    if (i < 0) {
        return 0;
    } else {
        return vec[i];
    }
}

bool all_unique(vector<int> &vals) {
    for (int i = 0; i < vals.size(); i++) {
        for (int j = i + 1; j < vals.size(); j++) {
            if (vals[i] == vals[j]) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    instr(s);

    int res = 0;
    for (int i = 0; i < n; i++) {
        int current_c = 0;
        int current_b = 0;
        int current_s = 0;
        for (int j = i; j < n; j++) {
            if (s[j] == 'C') {
                current_c++;
            } else if (s[j] == 'B') {
                current_b++;
            } else {
                current_s++;
            }

            if ((current_c != current_b || current_c == 0 || current_b == 0) && (current_c != current_s || current_c == 0 || current_s == 0)
                    && (current_b != current_s || current_b == 0 || current_s == 0)) {
                res = max(res, j - i + 1);
            }
        }
    }

    cout << res << endl;
}