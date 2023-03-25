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

int solve(int x, int y, vector<string> &strings, bool prev) {
    vector<pii> rel = {
        {0, 1},
        {1, 0}
    };

    for (pii i : rel) {
        pii coords = {x + i.first, y + i.second};
        if (i.second == 1) coords.second = !y;

        if (i.second != 1 || !prev) {
            if (coords.first >= 0 && coords.first < strings[0].size()) {
                if (strings[coords.second][coords.first] == 'B') {
                    return 1 + solve(coords.first, coords.second, strings, i.second == 1);
                }
            }
        }
    }

    return 1;
}

void readCaseData() {
    ini(size);
    instr(s1);
    instr(s2);

    int total_count = 0;
    int x = -1;
    int y = -1;
    int x2 = -1;
    int y2 = -1;
    for (int i = 0; i < size; i++) {
        char c1 = s1[i];
        char c2 = s2[i];

        total_count += (c1 == 'B');
        total_count += (c2 == 'B');

        if (x == -1) {
            if (c1 == 'B') {
                y = 0;
                x = i;

                if (c2 == 'B') {
                    x2 = i;
                    y2 = 1;
                }
            } else if (c2 == 'B') {
                y = 1;
                x = i;
            }
        }
    }

    vector<string> strings;
    strings.pb(s1);
    strings.pb(s2);

    int a = solve(x, y, strings, false);

    if (x2 != -1) {
        int b = solve(x2, y2, strings, false);
        if (b == total_count) a = b;
    }

    if (a == total_count) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}