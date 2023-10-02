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

int x = 1000000000000;

int brute(string &s, int cost) {
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] != '1') {
            break;
        }

        s.erase(s.begin() + i);
    }

    int ones = 0;
    for (char c : s) {
        if (c == '1') ones++;
    }

    if (ones == 0) {
        return cost;
    }

    int res = 1000000000000000000;
    for (int i = 0; i < s.length(); i++) {
        string cp = s;
        cp.erase(cp.begin() + i);
        if (i == s.length() - 2 && s[i] == '1' && s[s.length() - 1] == '0') {
            res = min(res, brute(cp, cost + x));
        } else {
            res = min(res, brute(cp, cost + x + 1));
        }
    }

    return res;
}

void readCaseData() {
    instr(s);
    /*string s = "";
    for (int i = 0; i < 9; i++) {
        s += ('0' + rand() % 2);
    }*/

    vector<pii> segments;
    int len = 0;
    int prev = -1;
    for (char c : s) {
        int n = c-'0';
        if (prev != n) {
            if (prev != -1) {
                segments.pb({prev,len});
            }
            prev = n;
            len = 0;
        }

        len++;
    }
    segments.pb({prev,len});

    if (segments[segments.size() - 1].first == 1) segments.erase(--segments.end());
    if (segments[0].first == 0) segments.erase(segments.begin());

    int zero_segments = 0;
    int ones = 0;
    deque<int> zero_lens;
    for (auto i : segments) {
        if (i.first == 0) {
            zero_segments++;
            zero_lens.pf(i.second);
        } else {
            ones += i.second;
        }
    }

    vector<int> dp(zero_segments+1);
    dp[0] = ones * (x + 1);

    for (int i = 1; i < dp.size(); i++) {
        int segment_ind = segments.size() - (i - 1) * 2 - 1;
        dp[i] = dp[i-1]-segments[segment_ind-1].second*(x+1)+segments[segment_ind].second*(x+1);
    }

    if (segments.size() >= 2 && segments[segments.size() - 1].second == 1 && segments[segments.size() - 2].second == 1) {
        dp[0]--;
    }
    for (int i = 1; i < dp.size(); i++) {
        int segment_ind = segments.size() - (i - 1) * 2 - 1;
        if (segment_ind-3 >= 0 && segments[segment_ind-2].second == 1 && segments[segment_ind-3].second == 1) {
            dp[i]--;
        }
    }

    int m = 1000000000000000000;
    for (int i : dp) {
        m = min(i,m);
    }
    
    /*if (brute(s,0) != m) {
        cout << "Found a problem:" << endl;
        cout << brute(s,0) << endl;
        cout << m << endl;
        cout << s << endl;
        exit(0);
    }*/

    cout << m << endl;
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