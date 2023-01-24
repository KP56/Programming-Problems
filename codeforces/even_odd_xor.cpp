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

uint get_bit_at(uint at, uint x) {
    return x >> at & 1;
}

uint set_bit_at(uint at, uint x) {
    return x |= 1 << at;
}

//after performing a NOT operation, we get rid of the very left bit
uint get_reversed_int(uint x) {
    return ~x << 1 >> 1;
}

uint solve_xor(uint x, uint result) {
    uint y = 0;
    for (int i = 0; i < 31; i++) {
        if (get_bit_at(i, x) != get_bit_at(i, result)) {
            y = set_bit_at(i, y);
        }
    }

    return y;
}

//int s = 3;
void readCaseData() {
    in_i(size);
    //int size = s;

    if (size == 3) {
        cout << "2 1 3" << endl;
        return;
    } else if (size == 4) {
        cout << "2 1 3 0" << endl;
        return;
    }

    unordered_set<int,custom_hash> us;
    vector<int> first_vec;
    for (int i = 0; i < size / 2 + size % 2; i++) {
        first_vec.pb(i);
        us.insert(i);
    }

    vector<int> second_vec;
    for (int i = 0; i < size / 2; i++) {
        second_vec.pb(INT_MAX-i*7);
        us.insert(INT_MAX-i*7);
    }

    int first_result = 0;
    for (int i = 0; i < first_vec.size() - 1; i++) {
        first_result ^= first_vec[i];
    }

    int second_result = 0;
    for (int i = 0; i < second_vec.size() - 1; i++) {
        second_result ^= second_vec[i];
    }

    int solution = ~0;
    solution >>= 1;

    if (first_result == second_result) {
        cout << "Collision detected for: " << size << endl;
        return;
    }

    for (; us.find(solve_xor(first_result,solution)) != us.end() || us.find(solve_xor(second_result,solution)) != us.end()
            || solve_xor(first_result,solution) == solve_xor(second_result,solution); solution--);
    first_vec[first_vec.size() - 1] = solve_xor(first_result,solution);
    second_vec[second_vec.size() - 1] = solve_xor(second_result,solution);

    vector<int> result;
    for (int i = 0; i < first_vec.size() + second_vec.size(); i++) {
        if (i % 2 == 0) {
            result.pb(first_vec[i / 2]);
        } else {
            result.pb(second_vec[i / 2]);
        }
    }

    for (int i : result) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
        //s++;
    }
}