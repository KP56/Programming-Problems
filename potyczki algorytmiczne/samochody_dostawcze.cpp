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
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

    in_i(size);
    unordered_map<int,int,custom_hash> v1;
    unordered_map<int,int,custom_hash> v2;
    for (int i = 0; i < size; i++) {
        in_i(type);
        in_i(coords);
        in_i(time);
        if (type == 1) {
            v1[coords - time]++;
        } else {
            v2[coords - time]++;
        }
    }

    int ans = 0;
    for (auto it = v1.begin(); it != v1.end();) {
        pii i = *it;
        auto it2 = v2.find(i.first);
        if (it2 != v2.end()) {
            pii i2 = *it2;
            int c1 = i2.second;
            int c2 = i.second;

            if (c1 != 0 || c2 != 0) {
                if (c1 > c2) {
                    it = v1.erase(it);
                    ans += c2;
                    continue;
                } else if (c1 != 0) {
                    v2.erase(i.first);
                    ans += c1;
                }
            }
        }

        it++;
    }
    cout << ans << endl;
}