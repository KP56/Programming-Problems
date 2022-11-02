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

//Jeżeli nie chcemy zabrać jakiegoś przedmiotu, to suma przedmiotów które
//zabieramy po prawej musi być niższa od wagi tego przedmiotu.

//Rozwiązanie O(2^n)
//Rozwiązujemy zadanie rekurencją. Jeżeli weźmiemy jakiś przedmiot, zwiększamy sumę. W przeciwnym wypadku
//jeżeli obecna wartość max - suma > w wtedy suma = 0 oraz max = w. Powtarzamy rekurencję cały czas.

ll l_max = 9223372036854775807;

vector<ll> ans;
void recursion(vector<ll> &arr, ll i, ll sum, ll max, ll items, ll real_sum) {
    if (i < arr.size()) {
        ll w = arr[i];
        if (max - sum > w) {
            recursion(arr, i + 1, 0, w, items, real_sum);
        } else {
            recursion(arr, i + 1, sum, max, items, real_sum);
        }

        if (sum + w < max) {
            recursion(arr, i + 1, sum + w, max, items + 1, real_sum + w);
        }
    } else if (items > 0) {
        ans[items - 1] = min(ans[items - 1], real_sum);
    }
}

void solve(vector<ll> &arr) {
    ans = vector<ll>(arr.size(), l_max);
    recursion(arr, 0, 0, l_max, 0, 0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<ll> arr;
    for (ll i = 0; i < size; i++) {
        in_i(w);
        arr.pb(w);
    }

    solve(arr);
    for (ll i : ans) {
        cout << i << " ";
    }
    cout << endl;
}