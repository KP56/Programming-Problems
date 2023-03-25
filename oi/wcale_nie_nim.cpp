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

pii move(pii &current) {
    if (current.second == current.first) {
        return {current.first + 1, current.second - 1};
    } else {
        return {(current.first + current.second) / 2 + (current.first + current.second) % 2, (current.first + current.second) / 2};
    }
}

pii remove(pii &current) {
    if (current.second < current.first) {
        return {0, current.second};
    } else {
        return {current.first, 0};
    }
}

bool cmp(pii a, pii b) {
    if (max(a.first,a.second) == max(b.first,b.second)) {
        return min(a.first, a.second) < min(b.first, b.second);
    }

    return max(a.first,a.second) < max(b.first,b.second);
}

void performRemove(multiset<pii,decltype(cmp)*> &s, multiset<pii,decltype(cmp)*> &s2) {
    auto it = --s.end();
    pii p = *it;
    s.erase(it);
    auto it2 = s2.find(p);
    if (it2 != s2.end()) s2.erase(it2);
    p = remove(p);
    if (p != mp(0,0)) {
        s.insert(p);
        if (abs(p.first - p.second) > 1) s2.insert(p);
    }
}

void performMove(multiset<pii,decltype(cmp)*> &s, multiset<pii,decltype(cmp)*> &s2) {
    if (s2.empty()) {
        auto it = --s.end();
        pii p = *it;
        s.erase(it);
        auto it2 = s2.find(p);
        if (it2 != s2.end()) s2.erase(it2);
        p = move(p);
        if (p != mp(0,0)) {
            s.insert(p);
            if (abs(p.first - p.second) > 1) s2.insert(p);
        }
    } else {
        auto it = --s2.end();
        pii p = *it;
        s2.erase(it);
        auto it2 = s.find(p);
        if (it2 != s.end()) s.erase(it2);
        p = move(p);
        if (p != mp(0,0)) {
            s.insert(p);
            if (abs(p.first - p.second) > 1) s2.insert(p);
        }
    }
}

//do dokończenia, jakieś problemy
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //ini(n);
    int n = 3000;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        //ini(x);
        vec.pb(i + 1);
    }

    int sum = 0;
    multiset<pii,decltype(cmp)*> s(cmp);
    multiset<pii,decltype(cmp)*> s2(cmp);
    for (int i : vec) {
        s.insert({i,i});
    }

    while (!s.empty()) {
        performRemove(s, s2);
        sum++;
        if (!s.empty()) {
            performMove(s, s2);
            sum++;
        }
    }

    cout << sum << endl;
}