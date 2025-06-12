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

void replace_elements(int idx1, int idx2, map<pii,int> &vec, vector<pii> &vec2) {
    pii p1 = vec2[idx1];
    pii p2 = vec2[idx2];

    vec[p1] = idx2;
    vec[p2] = idx1;
    
    vec2[idx1] = p2;
    vec2[idx2] = p1;
}

bool is_correct(vector<int> a, vector<int> b, vector<pii> &moves) {
    for (pii p : moves) {
        int cp = a[p.first - 1];
        a[p.first - 1] = a[p.second - 1];
        a[p.second - 1] = cp;

        int cp2 = b[p.first - 1];
        b[p.first - 1] = b[p.second - 1];
        b[p.second - 1] = cp2;
    }

    for (int i = 0; i < a.size(); i++) {
        if (a[i] != b[a.size() - i - 1]) {
            return false;
        }
    }

    return true;
}

vector<int> random_permutation(int n) {
    vector<int> perm;
    for (int i = 0; i < n; i++) {
        perm.pb(i + 1);
    }

    random_shuffle(all(perm));

    return perm;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 10 + 2;

    vector<int> a;// = random_permutation(n);
    for (int i = 0; i < n; i++) {
        ini(el);
        a.pb(el);
    }

    vector<int> b;// = random_permutation(n);
    for (int i = 0; i < n; i++) {
        ini(el);
        b.pb(el);
    }

    map<pii,int> vec;
    vector<pii> vec2;
    for (int i = 0; i < n; i++) {
        vec[{a[i],b[i]}] = i;
        vec2.pb({a[i],b[i]});
    }

    int same = 0;
    for (pair<pii,int> p : vec) {
        if (p.first.first == p.first.second) {
            same++;
        }
    }

    if (same != n % 2) {
        cout << -1 << endl;
        return;
    }

    for (pair<pii,int> p : vec) {
        if (p.first.first == p.first.second) continue;

        if (vec.find(mp(p.first.second,p.first.first)) == vec.end()) {
            cout << -1 << endl;
            return;
        }
    }

    set<pii> iterated_over;
    int idx = 0;
    int same_el = -1;

    vector<pii> moves;
    for (pair<pii,int> p : vec) {
        int idx1 = p.second;

        if (iterated_over.find(p.first) != iterated_over.end()) continue;
        if (p.first.first == p.first.second) {
            same_el = p.first.first;
            continue;
        }

        iterated_over.insert(p.first);
        pii p2 = {p.first.second,p.first.first};
        iterated_over.insert(p2);

        // i!=j
        if (idx1 != idx) {
            replace_elements(idx1,idx,vec,vec2);
            moves.pb({idx1 + 1, idx + 1});
        }

        int idx_end = n - idx - 1;
        int idx2 = vec[p2];
        if (idx_end != idx2) {
            replace_elements(idx2,idx_end,vec,vec2);
            moves.pb({idx2 + 1, idx_end + 1});
        }

        idx++;
    }

    if (same_el != -1) {
        int same_idx = vec[{same_el,same_el}];
        if (same_idx != n / 2) {
            moves.pb({same_idx + 1, n / 2 + 1});
        }
    }

    /*if (!is_correct(a,b,moves)) {
        cout << "ERROR" << endl;
    }*/

    cout << moves.size() << endl;
    for (pii i : moves) {
        cout << i.first << " " << i.second << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}