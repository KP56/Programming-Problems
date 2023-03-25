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

int char_to_int(char c) {
    return c - 'a';
}

void rotate(string &s) {
    char c = s[0];
    s.erase(s.begin());
    s += c;
}

ll verify(string &s) {
    ll score = 0;
    for (int i = 0; i < s.size(); i++) {
        char c = s[i];
        if (c != s[s.size() - i - 1]) {
            score++;
        }
    }

    return score;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(a);
    ini(b);
    instr(s);

    ll res = 9223372036854775807;
    for (ll i = 0; i < n; i++) {
        ll c = verify(s) / 2;
        if (c != -1) {
            res = min(c * b + i * a, res);
        }
        rotate(s);
    }

    cout << res << endl;
}