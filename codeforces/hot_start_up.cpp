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

int brute(int cpu1, int cpu2, int current, vector<int> &to_exec, vector<int> &cold, vector<int> &hot) {
    if (current >= to_exec.size()) {
        return 0;
    }

    return min(brute(current, cpu2, current+1, to_exec, cold, hot)
            +(cpu1 != -1 ?
            (to_exec[cpu1] == to_exec[current] ? hot[to_exec[current]] : cold[to_exec[current]])
            : cold[to_exec[current]]),
            brute(cpu1, current, current+1, to_exec, cold, hot)
            +(cpu2 != -1 ?
            (to_exec[cpu2] == to_exec[current] ? hot[to_exec[current]] : cold[to_exec[current]])
            : cold[to_exec[current]]));
}

void readCaseData() {
    ini(n);
    //int n = 8;
    ini(k);
    //int k = 8;
    
    vector<int> to_exec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 4 + 1;
        a--;
        to_exec.pb(a);
    }

    vector<int> cold;
    for (int i = 0; i < k; i++) {
        ini(a);
        //int a = rand() % 10 + 1;
        cold.pb(a);
    }

    vector<int> hot;
    for (int i = 0; i < k; i++) {
        ini(a);
        //int a = rand() % 10 + 1;
        hot.pb(a);
    }

    vector<vector<int>> dp(n+1,vector<int>(n+1,100000000000000));
    dp[0][0] = 0;
    dp[1][0] = cold[to_exec[0]];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (to_exec[i-1] == to_exec[i]) {
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]+hot[to_exec[i]]);
            } else {
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]+cold[to_exec[i]]);
            }

            if (j != 0) {
                if (to_exec[j-1] == to_exec[i]) {
                    dp[i+1][i]=min(dp[i+1][i],dp[i][j]+hot[to_exec[i]]);
                } else {
                    dp[i+1][i]=min(dp[i+1][i],dp[i][j]+cold[to_exec[i]]);
                }
            } else {
                dp[i+1][i]=min(dp[i+1][i],dp[i][j]+cold[to_exec[i]]);
            }
        }
    }

    int res = 100000000000000;
    for (int i : dp[n]) {
        res = min(res, i);
    }

    //int a = brute(-1, -1, 0, to_exec, cold, hot);

    /*if (a != res) {
        cout << "test" << endl;
    }*/

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    //srand(time(NULL));
    ini(cases);

    while (cases--) {
        readCaseData();
    }
}