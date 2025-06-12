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

// https://codeforces.com/blog/entry/62393
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

// https://jimmy-shen.medium.com/stl-map-unordered-map-with-a-vector-for-the-key-f30e5f670bae
struct VectorHasher {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for(auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

vector<int> composition(vector<int> &a, vector<int> &b) {
    vector<int> new_a = vector<int>(a.size());
    for (int i = 0; i < a.size(); i++) {
        new_a[i] = a[b[i]];
    }

    return new_a;
}

#define p 1000000007

int pow_mod(int a, int b, int mod) {
    int res = 1;
    for (; b > 0; b >>= 1) {
        if (b & 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
    }

    return res;
}

int inverse_mod(int a, int mod) {
    return pow_mod(a,mod-2,mod);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    unordered_map<vector<int>,int,VectorHasher> from_vec_to_int;
    vector<vector<int>> from_int_to_vec;
    for (int i = 0; i < k; i++) {
        vector<int> permutation;
        for (int j = 0; j < n; j++) {
            ini(a);
            a--;
            permutation.pb(a);
        }

        if (from_vec_to_int.find(permutation) == from_vec_to_int.end()) {
            from_int_to_vec.pb(permutation);
            from_vec_to_int[permutation] = from_int_to_vec.size() - 1;
        }
    }

    bool found = true;
    while (found) {
        found = false;
        vector<vector<int>> to_add;
        for (auto &i : from_int_to_vec) {
            for (auto &j : from_int_to_vec) {
                vector<int> potential_new = composition(i,j);
                if (from_vec_to_int.find(potential_new) == from_vec_to_int.end()) {
                    found = true;
                    from_vec_to_int[potential_new] = from_vec_to_int.size();
                    to_add.pb(potential_new);
                }
            }
        }

        for (auto &i : to_add) {
            from_int_to_vec.pb(i);
        }
    }

    int combinations = 0;
    for (auto &i : from_int_to_vec) {
        for (int j = 0; j < i.size(); j++) {
            for (int k = j + 1; k < i.size(); k++) {
                if (i[j] > i[k]) {
                    combinations++;
                }
            }
        }
    }

    combinations %= p;

    int divisor = from_int_to_vec.size();
    cout << (inverse_mod(divisor,p) * combinations) % p << endl;
    //cout << combinations << " " << divisor << endl;
}