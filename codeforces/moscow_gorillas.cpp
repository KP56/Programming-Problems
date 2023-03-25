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

pii merge(pii a, pii b) {
    return mp(min(a.first,min(a.second,min(b.first,b.second))),max(a.first,max(a.second,max(b.first,b.second))));
}

int getTotalPairs(pii a, pii avoid, int n) {
    if ((avoid.first >= a.first && avoid.first <= a.second) || (avoid.second >= a.first && avoid.second <= a.second)) {
        return 0;
    }

    int res = 1;
    if (avoid.first < a.first) {
        if (avoid.second < a.first) {
            res = a.first - avoid.second;
        } else {
            res = a.first - avoid.first;
        }
    } else {
        res = a.first + 1;
    }

    int res2 = 1;
    if (avoid.second > a.second) {
        if (avoid.first > a.second) {
            res2 = avoid.first - a.second;
        } else {
            res2 = avoid.second - a.second;
        }
    } else {
        res2 = n - a.second;
    }

    return res * res2;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);

    vector<int> p_vec;
    vector<int> p_pos(n);
    for (int i = 0; i < n; i++) {
        ini(p);
        p_vec.pb(p-1);
        p_pos[p-1] = i;
    }

    vector<int> q_vec;
    vector<int> q_pos(n);
    for (int i = 0; i < n; i++) {
        ini(q);
        q_vec.pb(q-1);
        q_pos[q-1] = i;
    }

    pii current = {min(p_pos[0],q_pos[0]),max(p_pos[0],q_pos[0])};
    pii avoid;
    int solution = 0;
    for (int i = 1; i < n; i++) {
        avoid = {min(p_pos[i],q_pos[i]),max(p_pos[i],q_pos[i])};
        solution += getTotalPairs(current,avoid,n);
        current = merge(current,avoid);
    }

    int inner = max(p_pos[0],q_pos[0]) - min(p_pos[0],q_pos[0]) - 1;
    int outer1 = n - 1 - max(p_pos[0],q_pos[0]);
    int outer2 = min(p_pos[0],q_pos[0]);

    cout << solution + inner * (inner + 1) / 2 + outer1 * (outer1 + 1) / 2 + outer2 * (outer2 + 1) / 2 + 1 << endl;
}