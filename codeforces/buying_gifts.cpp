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

/*
Let's pick the lowest number "a" with index "i" from list_a.
For each such number we can prepare 2 lists:
- candidate list
- forced list
For each number lower than a from list_a we put the number
from list_b with the same index onto candidate list and the rest
into the forced list.

The solution is abs(max(max(forced_list),closest(candidate_list))-a)
*/

int brute(int current, vector<int> &chosen_a, vector<int> &chosen_b, vector<int> &a, vector<int> &b) {
    if (current == a.size()) {
        if (chosen_a.empty() || chosen_b.empty()) {
            return 10000000000000000;
        }

        int res = 0;
        for (int i : chosen_a) {
            res = max(i,res);
        }

        int res2 = 0;
        for (int i : chosen_b) {
            res2 = max(i,res2);
        }

        return abs(res-res2);
    }

    vector<int> cp = chosen_a;
    cp.pb(a[current]);
    vector<int> cp2 = chosen_b;
    cp2.pb(b[current]);

    return min(brute(current+1,cp,chosen_b,a,b),brute(current+1,chosen_a,cp2,a,b));
}

int brute(vector<int> &a, vector<int> &b) {
    vector<int> chosen_a;
    vector<int> chosen_b;

    return brute(0,chosen_a,chosen_b,a,b);
}

void readCaseData() {
    ini(size);
    //int size = 10;

    vector<int> a;
    vector<int> b;
    for (int i = 0; i < size; i++) {
        ini(el);
        ini(el2);
        //int el = rand() % 10;
        //int el2 = rand() % 10;
        a.pb(el);
        b.pb(el2);
    }

    vector<pii> sorted_a;
    for (int i = 0; i < size; i++) {
        sorted_a.pb({a[i],i});
    }
    sort(all(sorted_a));

    set<int> candidate_list;
    set<int,greater<int>> candidate_list2;
    vector<pii> forced_list;
    for (int i = sorted_a.size() - 1; i >= 1; i--) {
        forced_list.pb({b[sorted_a[i].second],sorted_a[i].second});
    }

    vector<int> maxes;
    for (int i = 0; i < forced_list.size(); i++) {
        if (maxes.empty()) {
            maxes.pb(forced_list[i].first);
        } else {
            maxes.pb(max(maxes[maxes.size() - 1], forced_list[i].first));
        }
    }

    pii prev = {-1,-1};
    int res = 100000000000000000;
    for (auto i : sorted_a) {
        if (prev != mp((int) -1, (int) -1)) {
            candidate_list.insert(b[prev.second]);
            candidate_list2.insert(b[prev.second]);
            forced_list.erase(--forced_list.end());
        }
        int closest = 100000000000000000;
        if (!candidate_list.empty()) {
            auto it = candidate_list.lower_bound(i.first);
            auto it2 = candidate_list2.lower_bound(i.first);

            int a = 100000000000000000;
            if (it != candidate_list.end()) {
                a = *it;
            }

            int b = 100000000000000000;
            if (it2 != candidate_list2.end()) {
                b = *it2;
            }

            if (a == 100000000000000000) {
                closest = b;
            } else if (b == 100000000000000000) {
                closest = a;
            } else if (abs(a-i.first) < abs(b-i.first)) {
                closest = a;
            } else {
                closest = b;
            }
        }
         
        int max_val = 100000000000000000;
        if (!forced_list.empty()) {
            max_val = maxes[forced_list.size() - 1];
        }
        if (max_val < closest) {
            res = min(res, min(abs(max_val-i.first),abs(closest-i.first)));
        } else if (max_val == 100000000000000000) {
            res = min(res, abs(closest-i.first));
        } else {
            res = min(res, abs(max_val-i.first));
        }

        prev = i;
    }

    /*if (brute(a,b) != res) {
        cout << "Found a problematic case:" << endl;
        for (int i : a) {
            cout << i << " ";
        }
        cout << endl;
        for (int i : b) {
            cout << i << " ";
        }
        cout << endl;

        cout << "Correct solution: " << brute(a,b) << endl;
        cout << "Wrong solution: " << res << endl;

        exit(0);
    }*/

    cout << res << endl;
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