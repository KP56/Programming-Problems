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
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

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
    in_i(width);
    in_i(depth);
    in_i(height);

    in_i(laptop_x);
    in_i(laptop_y);

    in_i(projector_x);
    in_i(projector_y);

    //We need to find x and y such that:
    //abs(laptop_x - x) + abs(projector_x - x) + abs(laptop_y - y) + abs(projector_y - y)
    //is minimal and x=width, x=0, y=depth or y=0
    //Since the limit is just 1000, we can just bruteforce 4 different cases.

    int a = INT_MAX;
    //x=width
    for (int y = 0; y <= depth; y++) {
        a = min(abs(laptop_x - width) + abs(projector_x - width) + abs(projector_y - y) + abs(laptop_y - y), a);
    }

    //x=0
    for (int y = 0; y <= depth; y++) {
        a = min(laptop_x + projector_x + abs(projector_y - y) + abs(laptop_y - y), a);
    }

    //y=depth
    for (int x = 0; x <= width; x++) {
        a = min(abs(laptop_x - x) + abs(projector_x - x) + abs(projector_y - depth) + abs(laptop_y - depth), a);
    }

    //y=0
    for (int x = 0; x <= width; x++) {
        a = min(abs(laptop_x - x) + abs(projector_x - x) + projector_y + laptop_y, a);
    }

    cout << a + height << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}