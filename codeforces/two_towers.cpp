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
    ini(n);
    ini(n2);
    instr(s);
    instr(s2);

    for (int i = 2; i < n; i++) {
        if ((s[i] == s[i - 1] && s[i - 1] == s[i - 2])) {
            cout << "NO" << endl;
            return;
        }
    }

    for (int i = 2; i < n2; i++) {
        if (s2[i] == s2[i - 1] && s2[i - 1] == s2[i - 2]) {
            cout << "NO" << endl;
            return;
        }
    }

    int i1 = 0;
    int pos1 = -1;
    int i2 = 0;
    int pos2 = -1;
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i - 1]) {
            i1++;
            pos1 = i;
        }
    }

    for (int i = 1; i < n2; i++) {
        if (s2[i] == s2[i - 1]) {
            i2++;
            pos2 = i;
        }
    }

    if (i1 + i2 >= 2) {
        cout << "NO" << endl;
        return;
    }

    if (i1 + i2 == 0) {
        cout << "YES" << endl;
        return;
    }
    
    if (pos1 != -1) {
        for (int i = n - 1; i >= 0; i--) {
            if (s2[s2.length() - 1] == s[s.length() - 1]) {
                cout << "NO" << endl;
                return;
            }

            s2 += s[i];
            s.erase(--s.end());
            if (pos1 == i) {
                cout << "YES" << endl;
                return;
            }
        }
    } else if (pos2 != -1) {
        for (int i = n2 - 1; i >= 0; i--) {
            if (s2[s2.length() - 1] == s[s.length() - 1]) {
                cout << "NO" << endl;
                return;
            }

            s += s2[i];
            s2.erase(--s2.end());
            if (pos2 == i) {
                cout << "YES" << endl;
                return;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}