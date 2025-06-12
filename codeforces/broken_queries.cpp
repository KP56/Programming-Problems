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

int p;
int k_hidden;
void init(int n) {
    p = rand() % n + 1;
    k_hidden = rand() % (n - 2) + 2;
}

int queries = 0;
int query(int l, int r) {
    /*queries++;
    if (p >= l && p <= r) {
        return (r - l + 1 < k_hidden);
    } else {
        return (r - l + 1 >= k_hidden);
    }*/

    cout << "? " << l << " " << r << endl;
    cout.flush();
    int q_ans;
    cin >> q_ans;

    return q_ans;
}

int ans_inside_range_one(int k_tested, int range_one_l, int range_one_r) {
    return query(range_one_l, range_one_l + k_tested - 1);
}

int bin_search_lowest_increasing(int n, int range_one_l, int range_one_r) {
    int l = 2;
    int r = n / 4;

    while (l <= r) {
        if (r == l) {
            return l;
        }

        int mid = (l + r) / 2;
        int res = ans_inside_range_one(mid, range_one_l, range_one_r);

        if (res == 1) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return -1;
}

int ans_containing_range_one(int k_tested, int range_one_l, int range_one_r, int n) {
    int final_range_l = range_one_l;
    int final_range_r = range_one_r;

    final_range_r = min(max(1ll,final_range_r + k_tested - (final_range_r - final_range_l + 1)), n);
    int rest = k_tested - (final_range_r - final_range_l + 1);
    if (rest > 0) {
        final_range_l -= rest;
    }

    return query(final_range_l,final_range_r);
}

int bin_search_lowest_decreasing(int n, int range_one_l, int range_one_r) {
    int l = n / 4 + 1;
    int r = n - 1;

    while (l <= r) {
        if (r == l) {
            return l;
        }

        int mid = (l + r) / 2;
        int res = ans_containing_range_one(mid, range_one_l, range_one_r, n);

        if (res == 1) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    return -1;
}

void readCaseData() {
    ini(n);
    //int n = 1 << 30;
    queries = 0;

    //init(n);

    vector<int> res;
    for (int i = 0; i < 3; i++) {
        res.pb(query(n / 4 * i + 1, n / 4 * (i + 1)));
    }

    unordered_map<int,int> m;
    for (int i : res) {
        m[i]++;
    }

    int max_count = 0;
    int maximum = -1;
    for (auto i : m) {
        if (i.second > max_count) {
            max_count = i.second;
            maximum = i.first;
        }
    }
    
    int result = -1;
    if (maximum == 0) {
        // k > n / 4
        // ustalmy gdzie jest zakres z 1
        auto it = find(all(res),1);
        int pos = -1;
        if (it == res.end()) {
            pos = 3;
        } else {
            pos = it - res.begin();
        }

        int range_one_l = n / 4 * pos + 1;
        int range_one_r = n / 4 * (pos + 1);
        result = bin_search_lowest_decreasing(n, range_one_l, range_one_r);
    } else {
        // k <= n / 4
        // ustalmy gdzie jest zakres z 1
        auto it = find(all(res),1);
        int pos = it - res.begin();

        int range_one_l = n / 4 * pos + 1;
        int range_one_r = n / 4 * (pos + 1);
        result = bin_search_lowest_increasing(n, range_one_l, range_one_r);
    }

    /*if (result != k_hidden || queries > 33) {
        int test = 0;
    }*/

    cout << "! " << result << endl;
    cout.flush();
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}