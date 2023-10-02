#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

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

int brute(vector<vector<int>> &ordering, vector<vector<int>> &vec) {
    if (vec.empty()) {
        int greatest = -1;
        int counter = 0;
        for (auto i : ordering) {
            for (int j : i) {
                if (j > greatest) {
                    counter++;
                    greatest = j;
                }
            }
        }

        return counter;
    }

    int res = 0;
    for (int i = 0; i < ordering.size(); i++) {
        if (ordering[i].empty()) {
            vector<vector<int>> cp = ordering;
            cp[i] = vec[vec.size() - 1];
            vector<vector<int>> vec_cp = vec;
            vec_cp.erase(--vec_cp.end());
            res = max(res, brute(cp, vec_cp));
        }
    }

    return res;
}

struct segment_tree {
    vector<int> vec;
    int n;

    segment_tree(int n) {
        this->n = n;
        vec = vector<int>(n*2);
    }

    void update(int x, int val) {
        for (vec[x += n] = val; x > 1; x >>= 1) vec[x>>1] = max(vec[x], vec[x^1]);
    }

    int query(int l, int r) {
        r++;
        int res = 0;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = max(res, vec[l++]);
            if (r&1) res = max(res, vec[--r]);
        }

        return res;
    }
};

struct custom_comparator {
    inline bool operator() (const vector<int>& vec1, const vector<int>& vec2) {
        return vec1[vec1.size() - 1] < vec2[vec2.size() - 1];
    }
};

void readCaseData() {
    ini(n);
    //int n = 200000;
    vector<vector<int>> vecs(n);
    int maximal = -1;
    for (int i = 0; i < n; i++) {
        ini(n2);
        //int n2 = 1;
        int greatest = -1;
        for (int j = 0; j < n2; j++) {
            ini(a);
            //int a = 200000;
            a--;
            if (a > greatest) {
                vecs[i].pb(a);
                greatest = a;
            }
            maximal = max(maximal, a);
        }
    }
    sort(all(vecs),custom_comparator());

    segment_tree dp(maximal+1);
    vector<int> dp_clone(maximal+1);
    auto it = vecs.begin();
    for (int i = 0; i < maximal + 1; i++) {
        while (*(--it->end()) < i) it++;
        if (it == vecs.end() || *(--it->end()) != i) {
            if (i != 0) {
                dp.update(i, dp_clone[i-1]);
                dp_clone[i] = dp_clone[i-1];
            }
            continue;
        }
        auto it_cp = it;
        for (; it != vecs.end() && *(--it->end()) == *(--it_cp->end()); it++) {
            vector<int> &vec = *it;
            int q = dp.query(0,vec[0]-1);
            int upd1 = max(dp_clone[i], (int) vec.size() + (vec[0] == 0 ? 0 : q));
            dp.update(i, upd1);
            dp_clone[i] = max(dp_clone[i], upd1);
            for (int j = 1; j < vec.size(); j++) {
                int dp_res = dp.query(vec[j-1],vec[j]-1);
                int upd2 = max(dp_clone[i], (int) vec.size() - j + dp_res);
                dp.update(i, upd2);
                dp_clone[i] = upd2;
            }
        }
    }

    int res = dp_clone[maximal];
    /*vector<vector<int>> brute_ord = vector<vector<int>>(n);
    int brute_res = brute(brute_ord,vecs);

    if (res != brute_res) {
        cout << "A problem has been found." << endl;
        cout << res << endl;
        cout << brute_res << endl;
        for (auto i : vecs) {
            for (auto j : i) {
                cout << j + 1 << " ";
            }
            cout << endl;
        }
        exit(0);
    }*/

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(cases);
    //int cases = 10000;

    while (cases--) {
        readCaseData();
    }
}