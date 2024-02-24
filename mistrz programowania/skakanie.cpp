#include <bits/stdc++.h>

using namespace std;

#define int __int128
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) long long x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

int power(int a, int b, int mod) {
    int res = 1;
    a = a % mod;

    while (b > 0) {
        if (b % 2 == 1) {
            res *= a;
            res %= mod;
        }

        b >>= 1;
        a *= a;
        a %= mod;
    }

    return res;
}

struct pair_hash {
    size_t operator() (const pii& p) const {
        return (size_t) (p.first << 32) | p.second;
    }
};

int p = 1019043214942321;

int p1 = 100999;
int p2 = 100853;
int p3 = 100043;

int solve(int n, int mod) {
    vector<int> dp(2);
    unordered_map<pii,int,pair_hash> cycle_map;

    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp.pb((power(dp[i-1],3,mod)+(i-2 != 0 ? power(dp[i-2],3,mod) : 0)) % mod + (dp[i-1]+dp[i-2]) % mod);
        dp[i] %= mod;

        if (cycle_map.find({dp[i],dp[i-1]}) != cycle_map.end()) {
            int idx = cycle_map[{dp[i],dp[i-1]}];
            //i-idx=ilość liczb w cyklu
            //idx=ilość liczb, aż do początku cyklu
            //(n-idx-1)%(i-idx)=indeks cykliczny
            //(n-idx-1)%(i-idx)+idx+1=indeks bezwzględny
            int final_idx = (n-idx-1)%(i-idx)+idx+1;
            int res = dp[final_idx];

            return res;
        }
        cycle_map[{dp[i],dp[i-1]}] = i;
    }

    return dp[n];
}

int modular_inverse(int n, int mod) {
    return power(n,mod-2,mod);
}

long long chinese_remainder(vector<int> numbers, vector<int> divisors) {
    int product = 1;
    for (int i : divisors) {
        product *= i;
    }

    int res = 0;
    for (int i = 0; i < numbers.size(); i++) {
        int num = numbers[i];
        int m = product / divisors[i];
        int n = modular_inverse(m,divisors[i]);
        int k = (num*m % product) * n;
        k %= product;
        res += k;
        res %= product;
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);

    int res1 = solve(n,100999);
    int res2 = solve(n,100853);
    int res3 = solve(n,100043);

    long long res = chinese_remainder({res1,res2,res3},{100999,100853,100043});

    cout << res << endl;
}