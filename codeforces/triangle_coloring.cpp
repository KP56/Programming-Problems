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

//https://stackoverflow.com/questions/35226781/finding-binomial-coefficient-for-large-n-and-k-modulo-m
int xGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (long long)(a / b) * y1;
    return gcd;
}

int modfact(int n) {
    int result = 1;
    while (n > 1) {
        result = (long long)result * n % 998244353;
        n -= 1;
    }
    return result;
}

int modmult(int a, int b) {
    return (long long)a * b % 998244353;
}

int inverse(int a) {
    int x, y;
    xGCD(a, 998244353, x, y);
    return x;
}

int bc(int n, int k) {
    return modmult(modmult(modfact(n), inverse(modfact(k))), inverse(modfact(n - k)));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    vector<vector<int>> triples(n/3,vector<int>(3));
    for (int i = 0; i < n; i++) {
        ini(w);
        if (i % 3 == 0) {
            triples[i / 3][0] += w;
            triples[i / 3][1] += w;
        } else if (i % 3 == 1) {
            triples[i / 3][0] += w;
            triples[i / 3][2] += w;
        } else {
            triples[i / 3][1] += w;
            triples[i / 3][2] += w;
        }
    }

    vector<int> maxes(n);
    for (int i = 0; i < n/3; i++) {
        maxes[i] = max(triples[i][0],max(triples[i][1],triples[i][2]));
    }

    int solution = 1;
    for (int i = 0; i < n/3; i++) {
        int counter = 0;
        for (int j : triples[i]) {
            counter += j == maxes[i];
        }
        solution = (solution * counter) % 998244353;
    }

    cout << solution * bc(n/3,n/6) % 998244353 << endl;
}