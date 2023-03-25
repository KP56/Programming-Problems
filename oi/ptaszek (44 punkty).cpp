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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(trees);
    vector<int> heights;
    for (int i = 0; i < trees; i++) {
        ini(d);
        heights.pb(d);
    }

    ini(q);
    for (int i = 0; i < q; i++) {
        ini(k);
        int res = 0;
        map<int,set<int>> current;
        for (int i = 0; i <= k && i < trees; i++) {
            current[heights[i]].insert(i);
        }
        int pos = 0;
        for (int j = 0; j + k < trees; j++) {
            int l = j;
            int r = j + k;

            current[heights[l]].erase(l);
            if (current[heights[l]].empty()) {
                current.erase(heights[l]);
            }

            if (pos == j) {
                auto it = current.lower_bound(heights[l]);
                if (it != current.begin()) {
                    pos = *(--(*(--it)).second.end());
                } else {
                    pos = *(--(*(--current.end())).second.end());
                    res++;
                }
            }

            current[heights[r + 1]].insert(r + 1);
        }
        res += (heights[pos] <= heights[heights.size() - 1] && pos != heights.size() - 1);

        cout << res << endl;
    }
}