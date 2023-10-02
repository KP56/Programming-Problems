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

vector<int> fib_arr;
void fib(int n) {
    fib_arr = vector<int>(n+1);
    fib_arr[0] = fib_arr[1] = 1;
    for (int i = 2; i <= n; i++) {
        fib_arr[i] = fib_arr[i-1] + fib_arr[i-2];
    }
}

void readCaseData() {
    ini(n);
    ini(y);
    ini(x);
    x--;
    y--;

    int width = fib_arr[n+1];
    int height = fib_arr[n];

    while (true) {
        if (x >= height) {
            x -= height;
        }

        width -= height;

        if (width <= 1 && height <= 1) {
            break;
        }

        if (y >= width) {
            y -= width;
        }

        height -= width;

        if (width <= 1 && height <= 1) {
            break;
        }
    }

    if (x == 0 && y == 0) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    fib(45);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}