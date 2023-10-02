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

int minBrute(int at, string &s, int doubles, int ones, int result) {
    if (at == s.size()) {
        return result;
    }

    int res = INT_MAX;

    if (doubles < s.size() / 4) {
        res = min(res, minBrute(at + 2, s, doubles + 1, ones, result + (s[at] == '1' || s[at + 1] == '1')));
    }

    if (ones < s.size() / 2) {
        res = min(res, minBrute(at + 1, s, doubles, ones + 1, result + (s[at] == '1')));
    }

    return res;
}

int maxBrute(int at, string &s, int doubles, int ones, int result) {
    if (at == s.size()) {
        return result;
    }

    int res = INT_MIN;

    if (doubles < s.size() / 4) {
        res = max(res, maxBrute(at + 2, s, doubles + 1, ones, result + (s[at] == '1' || s[at + 1] == '1')));
    }

    if (ones < s.size() / 2) {
        res = max(res, maxBrute(at + 1, s, doubles, ones + 1, result + (s[at] == '1')));
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = 100000;
    ini(m);
    //int m = 12;

    int min_ans = 0;
    int max_ans = 0;
    //vector<string> test_vec;
    for (int i = 0; i < n; i++) {
        instr(s);
        /*string s = "";
        for (int j = 0; j < m; j++) {
            if (rand() % 2) {
                s += "1";
            } else {
                s += "0";
            }
        }
        test_vec.pb(s);*/
        
        int ones = 0;
        for (char c : s) {
            if (c == '1') ones++;
        }

        int current_min_ans = 0;
        int current_len = 0;
        for (int j = 0; j < m; j++) {
            if (s[j] == '0') {
                current_min_ans += current_len / 2;
                current_len = 0;
            } else {
                current_len++;
            }
        }
        
        current_min_ans += current_len / 2;
        current_min_ans = min(current_min_ans, m/4);
        min_ans += ones - current_min_ans;
        
        int current_max_ans = 0;
        current_len = 0;
        for (int j = 0; j < m; j++) {
            if (j != 0 && s[j] == '1' && s[j-1] == '1') {
                current_max_ans += current_len / 2;
                current_len = 1;
            } else {
                current_len++;
            }
        }

        current_max_ans += current_len / 2;
        current_max_ans = min(current_max_ans, m/4);
        max_ans += ones - (m/4 - current_max_ans);
    }

    cout << min_ans << " " << max_ans << endl;

    /*int max_brute = 0;
    int min_brute = 0;
    for (int i = 0; i < n; i++) {
        string s = test_vec[i];

        max_brute += maxBrute(0, s, 0, 0, 0);
        min_brute += minBrute(0, s, 0, 0, 0);
    }

    if (min_brute != min_ans || max_brute != max_ans) {
        int test = 0;
    }*/
}