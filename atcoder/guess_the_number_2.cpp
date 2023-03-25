#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define aint(x) (x).begin(),(x).end()
#define fi first
#define se second
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

int gcd(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

int mod_inv(int a, int m) {
    int x, y;
    int g = gcd(a, m, x, y);
    if (g != 1) {
        return -1;
    } else {
        return (x % m + m) % m;
    }
}

int chinese_remainder(const vector<int>& a, const vector<int>& m) {
    int M = 1;
    for (int i = 0; i < m.size(); i++) {
        M *= m[i];
    }
    int res = 0;
    for (int i = 0; i < m.size(); i++) {
        int Mi = M / m[i];
        int xi = mod_inv(Mi, m[i]);
        res = (res + a[i] * xi * Mi) % M;
    }
    return res;
}

int move(vector<int> &nums, int i, int n) {
    for (int j = 0; j < n; j++) {
        i = nums[i - 1];
    }
    return i;
}

signed main() {
    vector<int> mods = {4, 5, 7, 9, 11, 13, 17, 19, 23};
    cout << 108 << endl;
    int counter = 0;
    vector<int> subtract;
    vector<int> nums;
    for (int i : mods) {
        for (int j = 1; j <= i; j++) {
            if (j != i) {
                cout << j + counter + 1 << " ";
                nums.pb(j + counter + 1);
                subtract.pb(j + counter);
            } else {
                cout << counter + 1 << " ";
                nums.pb(counter + 1);
                subtract.pb(counter);
            }
        }
        counter += i;
    }
    cout << endl;

    vector<int> remainders;
    bool next_numbers = true;
    int next_mod = 0;
    int current_mod = 0;
    for (int i = 0; i < 108; i++) {
        ini(b);
        if (i == next_mod) {
            if (b != i + 1) next_numbers = false;
            b -= subtract[i];
            remainders.pb(b);
            next_mod += mods[current_mod];
            current_mod++;
        }
    }
    if (next_numbers) {
        cout << 1 << endl;
        return 0;
    }
    
    int n = chinese_remainder(remainders, mods);
    cout << n << endl;
}