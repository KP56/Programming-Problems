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

bool brute(int j, vector<int> vec) {
    if (j == vec.size() - 1) {
        int prev = -10000000;
        for (int i : vec) {
            if (i < prev) {
                return false;
            }
            prev = i;
        }

        return true;
    }

    bool ans = false;
    for (int i = -10; i <= 10; i++) {
        vector<int> cp = vec;
        cp[j] += i;
        cp[j+1] += i;
        ans |= brute(j+1,cp);
    }

    return ans;
}

void readCaseData() {
    ini(n);
    //int n = 2;
    vector<int> original;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 5 + 1;
        vec.pb(a);
    }
    original = vec;

    for (int i = 1; i < n - 1; i++) {
        if (vec[i - 1] > vec[i]) {
            vec[i + 1] += vec[i - 1] - vec[i];
            vec[i] += vec[i - 1] - vec[i];
        }
    }

    //making everything besides the last and first element as low as possible
    if (vec.size() % 2 == 0) {
        for (int i = 1; i < n - 2; i++) {
            vec[i+1] -= vec[i] - vec[i-1];
            vec[i] -= vec[i] - vec[i-1];
        }
    }

    if (vec[n - 1] < vec[n - 2]) {
        if (vec.size() % 2 == 0) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    } else {
        cout << "YES" << endl;
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