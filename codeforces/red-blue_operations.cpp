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

bool verify(vector<int> &arr, int k, int x) {
    vector<int> group2;
    vector<int> group1;
    for (int i : arr) {
        if (i < x) {
            group2.pb(i);
        } else {
            group1.pb(i);
        }
    }

    if (k < group2.size()) {
        return false;
    }

    for (int i = k; i >= 1 && k-i < group2.size(); i--) {
        group2[k-i] += i;
    }

    for (int i : group2) {
        if (i < x) {
            return false;
        }
    }

    int sum1 = 0;
    for (int i : group1) {
        sum1 += (i-x)*2+1;
    }

    if (k-sum1 <= group2.size() || k-sum1 <= 0) {
        return true;
    }

    int sum2 = 0;
    for (int i : group2) {
        sum2 += (i-x)*2;
    }

    if (((group2.size() % 2) == ((k-sum1) % 2)) && ((k-sum1-sum2 <= group2.size()) || k-sum1-sum2 <= 0)) {
        return true;
    }

    if (sum1 >= 1 && ((group2.size() % 2) == ((k-sum1+1) % 2)) && ((k-sum1-sum2+1 <= group2.size()) || k-sum1-sum2+1 <= 0)) {
        return true;
    }

    return false;
}

int bruteforce(vector<int> &arr, vector<bool> &will_subtract, int k, int current) {
    if (current == k + 1) {
        int ans = INT_MAX;
        for (int i : arr) {
            ans = min(ans, i);
        }
        return ans;
    }

    int val = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        vector<int> cp = arr;
        vector<bool> cp2 = will_subtract;

        if (cp2[i]) {
            cp[i] -= current;
        } else {
            cp[i] += current;
        }
        cp2[i] = !cp2[i];

        val = max(val, bruteforce(cp, cp2, k, current + 1));
    }

    return val;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));
    
    for (int b = 0; b < 1000; b++) {
    //ini(n);
    int n = 5;
    //ini(q);
    int q = 1;

    vector<int> arr;
    vector<bool> brute_arr(n);
    for (int i = 0; i < n; i++) {
        //ini(a);
        int a = rand() % 10 + 1;
        arr.pb(a);
    }
    sort(all(arr));

    int min_val = INT_MAX;
    for (int i : arr) {
        min_val = min(min_val, i);
    }

    int sum = 0;
    for (int i : arr) {
        sum += i - min_val;
    }

    for (int i = 0; i < q; i++) {
        //ini(k);
        int k = rand() % 5 + 1;
        int res_cout = -1;

        if (k / 2 >= sum) {
            int new_sum = sum - k / 2;
            res_cout = min_val - new_sum;
        }

        bool found_zero = false;
        for (int j = min_val+1; j <= min_val + k; j++) {
            bool res = verify(arr, k, j);
            //cout << res << endl;
            if (found_zero && res) {
                cout << "PROBLEM" << endl;
            }
            if (!res) found_zero = true;
            if (res) res_cout = j;
        }
        int brute_res = bruteforce(arr, brute_arr, k, 1);
        if (brute_res != res_cout) {
            cout << "PROBLEM" << endl;
        }
        //cout << res_cout << " ";
    }
    //cout << endl;
    }
}