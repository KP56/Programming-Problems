#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lli = long long int;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using vlli = vector<lli>;
using vvlli = vector<vector<lli>>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)
#define vec(x, y) vector<(x)> y

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
    in_i(size);

    vector<pair<int, int>> arr;
    int prev = -1;
    int skipped = 0;
    for (int i = 0; i < size; i++) {
        in_i(el);
        if (prev != el) {
            arr.pb({el, i - skipped});
        } else {
            skipped++;
        }

        prev = el;
    }
    sort(all(arr));

    int lower = 0;
    int upper = arr.size() - 1;
    for (auto i : arr) {
        if (i.second > lower && i.second < upper) {
            cout << "NO" << endl;
            return;
        } else if (i.second == lower) {
            lower++;
        } else {
            upper--;
        }
    }

    cout << "YES" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}