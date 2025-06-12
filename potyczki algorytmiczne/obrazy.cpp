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

pii find_greatest_rectangle_to_fit(int w, int h, int s) {
    return {w / s, h / s};
}

int recursive_solve(int idx, int w, int h, vector<int> &types) {
    if (w == 0 || h == 0) {
        return 0;
    }

    pii greatest_rectangle = find_greatest_rectangle_to_fit(w,h,types[idx]);
    while (greatest_rectangle.first == 0 || greatest_rectangle.second == 0) {
        greatest_rectangle = find_greatest_rectangle_to_fit(w,h,types[--idx]);
    }

    return greatest_rectangle.first * greatest_rectangle.second + recursive_solve(idx, w - greatest_rectangle.first * types[idx],
            greatest_rectangle.second * types[idx], types) + recursive_solve(idx, greatest_rectangle.first * types[idx],
            h - greatest_rectangle.second * types[idx], types) + recursive_solve(idx, w - greatest_rectangle.first * types[idx],
            h - greatest_rectangle.second * types[idx], types);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(h);
    ini(w);

    ini(n);
    vector<int> types;
    for (int i = 0; i < n; i++) {
        ini(a);
        types.pb(a);
    }

    if (h % types[0] != 0 || w % types[0] != 0) {
        cout << -1 << endl;
        return 0;
    }

    cout << recursive_solve(types.size() - 1, w, h, types) << endl;
}