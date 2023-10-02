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

//https://www.geeksforgeeks.org/largest-sum-subarray-least-k-numbers/
int maxSubarr(int k, vector<int> &arr) {
    int max_sum = LLONG_MIN;
    int sum = 0;
    for (int i = 0; i < k; i++) {
        sum += arr[i];
    }
 
    int last = 0;
    int j = 0;
    
    max_sum = max(max_sum, sum);
    for (int i = k; i < arr.size(); i++) {
        sum = sum + arr[i];
        last = last + arr[j++];
        max_sum = max(max_sum, sum);
        if (last < 0) {
            sum = sum - last;
            max_sum = max(max_sum, sum);
            last = 0;
        }
    }

    return max_sum;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> test = {-1, 1, 3, -2, 4};
    cout << maxSubarr(2, test) << endl;
}