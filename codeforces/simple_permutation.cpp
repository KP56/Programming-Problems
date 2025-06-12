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

int counter = 1;
void readCaseData() {
    ini(n);
    //int n = counter;

    vector<bool> is_prime(n+1, true);
    vector<int> prim_vec;
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && (long long) i * i <= n) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 0; i < is_prime.size(); i++) {
        if (is_prime[i]) {
            prim_vec.pb(i);
        }
    }

    set<int> all_nums;
    for (int i = 0; i < n; i++) all_nums.insert(i+1);

    int middle_prime = prim_vec[prim_vec.size() / 2];

    vector<int> permut;
    permut.pb(middle_prime);
    all_nums.erase(middle_prime);
    for (int i = middle_prime+1; i <= n && middle_prime - (i - middle_prime) >= 1; i++) {
        permut.pb(i);
        permut.pb(middle_prime - (i - middle_prime));

        all_nums.erase(i);
        all_nums.erase(middle_prime - (i - middle_prime));
    }

    for (int i : all_nums) {
        permut.pb(i);
    }

    /*int running_sum = 0;
    int els = 0;
    int primes = 0;
    for (int i : permut) {
        running_sum += i;
        els++;
        
        int res = (running_sum + els - 1) / els;
        if (res > n) {
            cout << res << endl;
        }
        if (is_prime[res]) {
            primes++;
        }
    }

    if (primes < n / 3 - 1) {
        cout << n << " is problematic" << endl;
    }*/

    for (int i : permut) {
        cout << i << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        counter++;
        readCaseData();
    }
}