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

void readCaseData() {
    ini(n);
    //int n = 2;

    //vector<int> vec_test;
    vector<int> arr;
    //int test_sum = 0;
    int zeros = 0;
    for (int i = 0; i < n; i++) {
        ini(a);
        /*int a = rand() % 40 - 20 + 1;
        if (i == n - 1) {
            a = 0 - test_sum;
        }
        test_sum += a;*/
        if (a == 0) {
            //vec_test.pb(0);
            zeros++;
            continue;
        }

        arr.pb(a);
    }

    if (zeros == n) {
        cout << "No" << endl;
        return;
    } else {
        cout << "Yes" << endl;
    }

    for (int i = 0; i < zeros; i++) {
        cout << 0 << " ";
    }

    multiset<int> negative;
    multiset<int> negative2;
    multiset<int> positive;
    multiset<int> positive2;
    for (int i : arr) {
        if (i < 0) {
            negative.insert(i * (-1));
            negative2.insert(i);
        } else {
            positive.insert(i);
            positive2.insert(i * (-1));
        }
    }

    int current_sum = 0;
    while (!negative.empty() || !positive.empty()) {
        int candidate1 = INT_MAX;
        int candidate2 = INT_MAX;
        if (current_sum < 0) {
            int a = current_sum * (-1);
            auto it1 = positive.lower_bound(a);
            if (it1 != positive.end()) candidate1 = *it1;
            auto it2 = positive2.lower_bound(a * (-1));
            if (it2 != positive2.end()) candidate2 = (*it2) * (-1);
        } else {
            int a = current_sum;
            auto it1 = negative.lower_bound(a);
            if (it1 != negative.end()) candidate1 = *it1;
            auto it2 = negative2.lower_bound(a * (-1));
            if (it2 != negative2.end()) candidate2 = (*it2) * (-1);
        }

        int selecting;
        if (abs(current_sum + candidate1) < abs(current_sum + candidate2)) {
            selecting = candidate1;
        } else {
            selecting = candidate2;
        }

        if (current_sum < 0) {
            positive.erase(positive.find(selecting));
            positive2.erase(positive2.find(selecting * (-1)));
            current_sum += selecting;
            //vec_test.pb(selecting);
            cout << selecting << " ";
        } else {
            negative.erase(negative.find(selecting));
            negative2.erase(negative2.find(selecting * (-1)));
            current_sum -= selecting;
            //vec_test.pb(selecting * (-1));
            cout << selecting * (-1) << " ";
        }
    }
    cout << endl;

    /*int maximal_sum = INT_MIN;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += vec_test[j];
        }
        maximal_sum = max(maximal_sum, abs(sum));
    }

    int maximum = *max_element(all(vec_test));
    int minimum = *min_element(all(vec_test));

    if (maximal_sum >= maximum - minimum) {
        int test = 0;
    }*/
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}