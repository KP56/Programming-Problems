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

int brute(int at, vector<int> &arr, vector<int> &add_vec, int k, int x) {
    if (at == arr.size() || add_vec.size() == k) {
        if (add_vec.size() != k) {
            return 0;
        } else {
            vector<int> new_arr = arr;
            for (int i : add_vec) {
                new_arr[i] += x;
            }
            for (int i = 0; i < arr.size(); i++) {
                if (find(all(add_vec), i) == add_vec.end()) {
                    new_arr[i] -= x;
                }
            }

            int result = 0;
            for (int i = 0; i < new_arr.size(); i++) {
                int sum = 0;
                for (int j = i; j < new_arr.size(); j++) {
                    sum += new_arr[j];
                    result = max(sum, result);
                }
            }

            return result;
        }
    }

    int res = 0;
    for (int i = at; i < arr.size(); i++) {
        vector<int> cp = add_vec;
        cp.pb(i);
        res = max(brute(i + 1, arr, cp, k, x), res);
    }

    return res;
}

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
        if (!deq.empty() && deq[0][1] < i - d)
            deq.pop_front();
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

void readCaseData() {
    ini(n);
    //int n = 2;
    ini(k);
    //int k = rand() % 2 + 1;
    ini(x);
    //int x = rand() % 30 + 1 - 30;
    //int original_k = k;
    //int original_x = x;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 200 + 1 - 200;
        arr.pb(a);
    }

    if (x < 0) {
        x *= (-1);
        k = n - k;
    }

    vector<int> arr1;
    for (int i : arr) {
        arr1.pb(i - x);
    }

    int max_sum = maxSubarray(k, n, arr1) + 2*k*x;
    if (max_sum < 0) max_sum = 0;

    vector<int> arr2;
    for (int i : arr) {
        arr2.pb(i + x);
    }

    max_sum = max(max_sum, maxSubarray(1, k, arr2));
    
    /*vector<int> brute_test;
    int brute_res = brute(0, arr, brute_test, original_k, original_x);
    if (brute_res != max_sum) {
        int test = 0;
        maxSubarray(1, k, arr2);
    }*/
    cout << max_sum << endl;
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