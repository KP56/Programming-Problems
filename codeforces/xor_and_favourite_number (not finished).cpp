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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(q);
    ini(k);

    vector<vector<int>> arr;
    int block_size = sqrt(n);
    for (int i = 0; i < n; i++) {
        ini(a);
        if (i % block_size == 0) {
            arr.pb({});
        }
        arr[i / block_size].pb(a);
    }

    //dp[x][y] - pairs when considering just blocks x and y
    vector<vector<int>> dp(arr.size(),vector<int>(arr.size()));
    //O(n*sqrt(n))
    for (int block_ind = 0; block_ind < arr.size(); block_ind++) {
        auto block = arr[block_ind];
        int res = 0;
        for (int i : block) {
            if (i == k) {
                res++;
            }
        }
        for (int i = 0; i < block.size(); i++) {
            int xor_of = block[i];
            for (int j = i + 1; j < block.size(); j++) {
                xor_of ^= block[j];
                if (xor_of == k) {
                    res++;
                }
            }
        }
        dp[block_ind][block_ind] = res;
    }

    vector<int> xor_prefix;
    for (auto i : arr) {
        for (auto j : i) {
            if (!xor_prefix.empty()) {
                xor_prefix.pb(xor_prefix[xor_prefix.size() - 1] ^ j);
            } else {
                xor_prefix.pb(j);
            }
        }
    }

    //xor_prefix[l-1] ^ xor_prefix[r] = xor of values from l to r
    vector<unordered_map<int,int,custom_hash>> left_directed(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            left_directed[i][(i == 0 ? 0 : xor_prefix[i*block_size-1])^xor_prefix[i*block_size+j]]++;
        }
    }

    vector<unordered_map<int,int,custom_hash>> right_directed(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            right_directed[i][(i == 0 && j == 0 ? 0 : xor_prefix[i*block_size+j-1])^xor_prefix[(i+1)*block_size-1]]++;
        }
    }

    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            int res = 0;
            //looking for pairs where the left element is in block i and the right one in block j
            for (auto left : left_directed[j]) {
                int xored = left.first ^ (i != j ? xor_prefix[(i+1)*block_size-1] ^ xor_prefix[j*block_size-1] : 0) ^ k;
                if (right_directed[i].find(xored) != right_directed[i].end()) {
                    res += left.second * right_directed[i][xored];
                }
            }

            dp[i][j] = res;
        }
    }

    //dp2[x][y] - pairs when considering blocks between x and y
    vector<vector<int>> dp2(arr.size(),vector<int>(arr.size()));
    for (int i = 0; i < arr.size(); i++) {
        dp2[i][i] = dp[i][i];
    }
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            int res = 0;
            for (int i2 = i; i2 <= j; i2++) {
                res += dp[i2][j];
            }

            dp2[i][j] = dp2[i][j-1] + res;
        }
    }

    for (int i = 0; i < q; i++) {
        ini(l);
        ini(r);
        l--;
        r--;

        int block_l = l / block_size + (l % block_size != 0);
        int block_r = r / block_size - (r % block_size != 0);

        int ans = 0;
        if (block_l <= block_r && block_l >= 0 && block_l < arr.size() && block_r >= 0 && block_r < arr.size()) {
            ans += dp2[block_l][block_r];
        }

        
    }
}