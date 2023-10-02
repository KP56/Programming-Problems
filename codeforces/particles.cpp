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

int brute(vector<int> &arr) {
    if (arr.size() == 1) {
        return arr[0];
    }

    int max_val = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        vector<int> cp = arr;
        if (i == 0) {
            cp.erase(cp.begin());
        } else if (i == cp.size() - 1) {
            cp.erase(--cp.end());
        } else {
            int val = cp[i - 1] + cp[i + 1];
            cp.erase(cp.begin() + i - 1);
            cp.erase(cp.begin() + i - 1);
            cp[i - 1] = val;
        }

        max_val = max(max_val, brute(cp));
    }

    return max_val;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 9 + 1;

    vector<int> arr;
    vector<int> arr1;
    vector<int> arr2;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 11 - 5;
        if (i % 2 == 0) {
            arr1.pb(el);
        } else {
            arr2.pb(el);
        }

        arr.pb(el);
    }

    int sum1 = 0;
    for (int i : arr1) {
        if (i > 0) {
            sum1 += i;
        }
    }

    if (sum1 == 0) {
        sum1 = INT_MIN;
        for (int i : arr1) {
            sum1 = max(sum1, i);
        }
    }

    int sum2 = 0;
    for (int i : arr2) {
        if (i > 0) {
            sum2 += i;
        }
    }

    if (sum2 == 0) {
        sum2 = INT_MIN;
        for (int i : arr2) {
            sum2 = max(sum2, i);
        }
    }

    int res = max(sum1,sum2);
    /*int res_brute = brute(arr);

    if (res != res_brute) {
        int test = 0;
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