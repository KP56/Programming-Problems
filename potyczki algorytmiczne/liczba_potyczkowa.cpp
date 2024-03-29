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

//O(l-r)
//Pierwszym możliwym rozwiązaniem jest rozwiązanie brutalne. Polega ono na iteracji
//przez wszystkie liczby w zakresie od l do r, dla każdej z nich sprawdzamy czy spełnia
//odpowiedni warunek, jeżeli tak to dodajemy 1 do sumy. Na końcu wyświetlamy sumę.

char charToDigit(char c) {
    return c - '0';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_ll(l);
    in_ll(r);

    ll sum = 0;
    for (ll i = l; i <= r; i++) {
        bool b = true;
        for (char c : to_string(i)) {
            if (c == '0') {
                b = false;
                break;
            }
            if (i % charToDigit(c) != 0) {
                b = false;
                break;
            }
            
        }

        if (b)
            sum++;
    }

    cout << sum << endl;
}