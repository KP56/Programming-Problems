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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<int> vec;
    for (int i = 0; i < size; i++) {
        in_i(a);
        vec.pb(a);
    }

    //Rozważmy dwa przypadki: dźwięk będzie malał, rosnął, malał rosnął
    //lub: rosnął, malał, rosnął, malał

    //Wyświetlamy min operacji potrzebnych

    //pierwszy przypadek
    int op1 = 0;
    int prev = INT_MAX;
    bool lowering = true;
    for (int i : vec) {
        if (lowering && prev > i) {
            //wszystko jest w porządku
            prev = i;
        } else if (!lowering && prev < i) {
            //tutaj też jest wszystko w porządku
            prev = i;
        } else {
            //musimy dokonać modyfikacji
            op1++;
            if (lowering) {
                prev = INT_MIN;
            } else {
                prev = INT_MAX;
            }
        }

        lowering = !lowering;
    }

    //drugi przypadek
    int op2 = 0;
    prev = INT_MIN;
    lowering = false;
    for (int i : vec) {
        if (lowering && prev > i) {
            //wszystko jest w porządku
            prev = i;
        } else if (!lowering && prev < i) {
            //tutaj też jest wszystko w porządku
            prev = i;
        } else {
            //musimy dokonać modyfikacji
            op2++;
            if (lowering) {
                prev = INT_MIN;
            } else {
                prev = INT_MAX;
            }
        }

        lowering = !lowering;
    }

    cout << min(op1,op2) << endl;
}