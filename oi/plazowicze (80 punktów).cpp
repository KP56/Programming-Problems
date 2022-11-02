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

struct cmp {
    bool operator() (pair<double,ll> a, pair<double,ll> b) const {
        if (a.first == b.first) {
            if (a.second < b.second) {
                return true;
            }

            return false;
        } else {
            if (a.first > b.first) {
                return true;
            }

            return false;
        }
    }
};

pll simplify(pll a) {
    while (a.first % 2 == 0 && a.second % 2 == 0) {
        a.first /= 2;
        a.second /= 2;
    }
    return a;
}

ll prev_removed = -1;
pll solveFor(multimap<pair<double,ll>, vector<ll>, cmp> &d_vec, ll k) {
    ll solution_x1;
    ll solution_x2;
    ll solution_parts;
    ll part_id;

    ll removed = prev_removed;
    if (prev_removed == -1) {
        removed = 0;
    }
    k -= removed;

    while (true) {
        auto it = d_vec.begin();
        auto p = *it;
        ll parts = p.second[2];
        if (k < parts) {
            solution_x1 = p.second[0];
            solution_x2 = p.second[1];
            solution_parts = parts;
            part_id = k + 1;
            prev_removed = removed;
            break;
        }
        k -= parts;
        removed += parts;
        d_vec.erase(it);
        d_vec.insert({{p.first.first / 2, p.first.second}, {p.second[0], p.second[1], parts * 2}});
    }

    return simplify(mp(solution_x1*solution_parts*2+(solution_x2-solution_x1)+(part_id-1)*(solution_x2-solution_x1)*2,solution_parts*2));
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(initial_positions);
    in_i(size);
    in_i(queries);

    vector<ll> vec;
    for (ll i = 0; i < initial_positions; i++) {
        in_i(x);
        vec.pb(x);
    }

    multimap<pair<double,ll>, vector<ll>, cmp> d_vec;
    ll prev = -1;
    for (ll i : vec) {
        if (prev != -1) {
            d_vec.insert({{i - prev, prev}, {prev, i, 1}});
        }
        prev = i;
    }

    vector<pll> queries_vec;
    for (ll i = 0; i < queries; i++) {
        in_i(k);
        queries_vec.pb(mp(k,i));
    }
    sort(all(queries_vec));

    vector<pll> answers(queries);
    for (auto i : queries_vec) {
        answers[i.second] = solveFor(d_vec, i.first - 1);
    }

    for (auto i : answers) {
        cout << i.first << "/" << i.second << endl;
    }
}