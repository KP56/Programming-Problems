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

struct diagonals {
    vector<vector<set<int>>> diagonals;

    //dirs:
    //- 1 - left_up
    //- 2 - left_down
    //- 3 - right_up
    //- 4 - right_down

    pii flip(int x, int y, int ball_dir, int w, int h) {
        if (ball_dir == 3) {
            return {x, y};
        } else if (ball_dir == 1) {
            return {w - x - 1, y};
        } else if (ball_dir == 4) {
            return {x, h - y - 1};
        } else {
            return {w - x - 1, h - y - 1};
        }
    }

    pii findBlock(int ball_dir, int x, int y, int w, int h) {
        int diag_x = -1;
        int diag_y = -1;
        
        pii f = flip(x, y, ball_dir, w, h);
        x = f.first;
        y = f.second;

        if (x < y) {
            x = 0;
            y = y - x;
        } else {
            y = 0;
            x = x - y;
        }

        
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(m);
    ini(n);
    ini(k);



    for (int i = 0; i < k; i++) {
        ini(x);
        ini(y);
        x--;
        y--;

    }
}