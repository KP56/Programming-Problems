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

//https://cs.stackexchange.com/questions/151165/maximum-subarray-sum-of-given-length-range
int maxSubarray(int a, int b, vector<int> &arr) {
    vector<int> prefix_sums;
    prefix_sums.pb(0);
    for (int i : arr) {
        prefix_sums.pb(prefix_sums[prefix_sums.size() - 1] + i);
    }

    int d = b - a;
    deque<vector<int>> deq;
    int answer = LLONG_MIN;
    for (int i = a; i < arr.size() + d + 1; i++) {
        if (!deq.empty() && deq[0][1] < i - d) {
            deq.pop_front();
        }
        if (i <= arr.size()) {
            while (!deq.empty() && deq[deq.size() - 1][0] <= prefix_sums[i])
                deq.pop_back();
            deq.pb({prefix_sums[i], i});
        }
        if (i >= b) {
            answer = max(answer, deq[0][0] - prefix_sums[i - b]);
        }
    }

    return answer;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    vector<int> test = {1, 3, -2, 5, -67, 12};
    cout << maxSubarray(1, 3, test) << endl;
    cout << maxSubarray(2, 3, test) << endl;
    cout << maxSubarray(2, 4, test) << endl;
}