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

bool brute(vector<int> &arr, vector<int> &current) {
    if (current.size() == arr.size()) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == current[i]) {
                return false;
            }
        }

        int sum = 0;
        for (int i : arr) sum += i;

        int sum2 = 0;
        for (int i : current) sum2 += i;

        if (sum != sum2) {
            return false;
        }

        return true;
    }

    bool exists = false;
    for (int i = 1; i <= 6; i++) {
        vector<int> cp = current;
        cp.pb(i);

        if (brute(arr, cp)) exists = true;
    }

    return exists;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 6 + 1;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 4 + 1;
        arr.pb(el);
    }

    vector<int> test;
    //bool brute_res = brute(arr, test);

    if (n == 1) {
        /*if (brute_res) {
            int test = 0;
        }*/

        cout << "NO" << endl;
        return;
    }

    int ones = 0;
    int sum = 0;
    for (int i : arr) {
        if (i == 1) {
            ones++;
        } else {
            sum += i - 2;
        }
    }

    int other = n - ones;

    if (ones - other > sum) {
        /*if (brute_res) {
            int test = 0;
        }*/

        cout << "NO" << endl;
        return;
    }

    /*if (!brute_res) {
        int test = 0;
    }*/

    cout << "YES" << endl;
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