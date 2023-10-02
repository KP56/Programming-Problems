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

int brute(int k, vector<int> &vec) {
    vector<int> numbers;
    int current = 1;
    for (int i = 0; i < k; i++) {
        int counter = 0;
        for (int j : vec) {
            while (numbers.size() < j) numbers.pb(current++);
            numbers.erase(numbers.begin() + (j - 1 - counter));

            counter++;
        }
    }

    if (numbers.empty()) return current;
    
    return numbers[0];
}

void readCaseData() {
    ini(n);
    //int n = rand() % 5 + 1;
    ini(k);
    //int k = rand() % 5 + 1;

    int sum = 0;
    bool should_return = false;
    vector<int> vec;
    int prev = 0;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = prev + (rand() % 5) + 1;
        vec.pb(el);
        if (i == 0 && el != 1) {
            cout << 1 << endl;
            should_return = true;
        }

        if (i != 0) {
            if (i*k-sum-el+1 < 0) {
                sum += k-((i*k-sum)>=el-1);
            } else {
                sum += k-(i*k-sum-el+1)/i-((i*k-sum)>=el-1);
            }
        }

        prev = el;
    }

    if (should_return)
        return;

    //int ans_brute = brute(k, vec);
    int ans = k*n+1-sum;

    /*if (ans != ans_brute) {
        int test = 0;
    }*/

    cout << ans << endl;
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