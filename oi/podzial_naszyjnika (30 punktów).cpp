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

    ini(n);
    ini(k);

    vector<int> vec;
    vector<int> color_table(k);
    for (int i = 0; i < n; i++) {
        ini(a);
        vec.pb(a - 1);
        color_table[a - 1]++;
    }

    int res = 0;
    int min_diff = INT_MAX;
    for (int i = 0; i < n; i++) {
        unordered_map<int,int> color_map;
        
        for (int j = i + 1; j < n; j++) {
            if (color_map.find(vec[j]) != color_map.end()) {
                color_map[vec[j]]--;
                if (color_map[vec[j]] == 0) {
                    color_map.erase(vec[j]);
                }
            } else if (color_table[vec[j]] != 1) {
                color_map[vec[j]] = color_table[vec[j]] - 1;
            }

            if (color_map.empty()) {
                res++;
                min_diff = min(min_diff, abs((n - (j - i)) - (j - i))); 
            }
        }
    }

    cout << res << " " << min_diff << endl;
}