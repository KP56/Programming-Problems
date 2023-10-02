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

vector<bool> to_bits(int a, int n) {
    vector<bool> bits;
    for (int i = 0; i < n; i++, a >>= 1) {
        bits.pb(a&1);
    }

    return bits;
}

pii renormalize(int forward_pos, int backward_pos, int i, int m) {
    forward_pos += m;
    backward_pos += m;

    forward_pos -= i;
    backward_pos -= i;

    forward_pos %= m;
    backward_pos %= m;

    return mp(forward_pos, backward_pos);
}

struct hash_like_array {
    int size = 0;
    vector<int> vec;

    hash_like_array(int size) {
        this->vec = vector<int>(size);
    }

    void increment(int i) {
        vec[i]++;

        if (vec[i] == 1) {
            size++;
        }
    }

    void decrement(int i) {
        vec[i]--;

        if (vec[i] == 0) {
            size--;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<vector<uint8_t>> groups(m);
    vector<int> groups_vec(n*2);
    for (int i = 0; i < m; i++) {
        ini(a);
        vector<bool> bits = to_bits(a,n);

        for (int j = 0; j < n; j++) {
            groups[i].pb(j+n*bits[j]);
            groups_vec[j+n*bits[j]]++;
        }
    }

    int existant_groups = 0;
    for (auto i : groups_vec) {
        if (i == 1) {
            cout << 0 << endl;
            return 0;
        } else if (i != 0) {
            existant_groups++;
        }
    }

    hash_like_array backward_map(2*n);
    hash_like_array forward_map(2*n);

    int forward_pos = 0;
    while (forward_map.size < existant_groups) {
        for (int i : groups[forward_pos]) {
            forward_map.increment(i);
        }

        forward_pos++;
    }

    int backward_pos = m-1;
    while (backward_map.size < existant_groups) {
        for (int i : groups[backward_pos]) {
            backward_map.increment(i);
        }

        backward_pos--;
    }

    backward_pos++;

    int res = 0;

    pii renormalized = renormalize(forward_pos, backward_pos, 0, m);

    res += max(0ll,(renormalized.second - renormalized.first) + 1);

    for (int i = 1; i < m; i++) {
        for (int i : groups[i-1]) {
            forward_map.decrement(i);
        }

        for (int i : groups[i-1]) {
            backward_map.increment(i);
        }

        while (forward_map.size < existant_groups) {
            for (int i : groups[forward_pos]) {
                forward_map.increment(i);
            }

            forward_pos = (forward_pos + 1) % m;
        }

        while (backward_map.size == existant_groups) {
            for (int i : groups[backward_pos]) {
                backward_map.decrement(i);
            }

            backward_pos = (backward_pos + 1) % m;
        }

        backward_pos--;
        backward_pos += m;
        backward_pos %= m;

        for (int i : groups[backward_pos]) {
            backward_map.increment(i);
        }

        pii renormalized = renormalize(forward_pos, backward_pos, i, m);

        res += max(0ll,(renormalized.second - renormalized.first) + 1);
    }

    cout << res / 2 << endl;
}