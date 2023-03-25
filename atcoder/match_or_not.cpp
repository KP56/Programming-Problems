#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

const int N = 3e5+10;
const int M = 5e3+10;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    instr(s);
    instr(t);

    string x0 = "";
    for (int i = s.length() - t.length(); i < s.length(); i++) {
        x0 += s[i];
    }

    vector<bool> match(N);
    int how_many = 0;
    for (int i = 0; i < x0.length(); i++) {
        if (x0[i] == t[i] || x0[i] == '?' || t[i] == '?') {
            match[i] = true;
            how_many++;
        }
    }

    if (how_many == t.length()) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    for (int x = 0; x < t.length(); x++) {
        x0[x] = s[x];
        if (match[x]) {
            if (x0[x] != t[x] && x0[x] != '?' && t[x] != '?') {
                how_many--;
                match[x] = false;
            }
        } else {
            if (x0[x] == t[x] || x0[x] == '?' || t[x] == '?') {
                how_many++;
                match[x] = true;
            }
        }

        if (how_many == t.length()) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}