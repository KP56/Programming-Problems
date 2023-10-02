#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

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

struct comp {
    bool operator()(const pair<int,bool>& p1,
                    const pair<int,bool>& p2) {
        return p1.first < p2.first;
    }
};

int dp(int x, int y, vector<vector<pair<int,bool>>> &platforms);

vector<vector<int>> dp_arr;
int callDP(int x, int y, vector<vector<pair<int,bool>>> &platforms) {
    if (x >= platforms[y].size()) {
        return 0;
    }

    if (dp_arr[y][x] == -1) {
        return dp_arr[y][x] = dp(x,y,platforms);
    }

    return dp_arr[y][x];
}

int map_pos(int x1, int y1, int y2, vector<vector<pair<int,bool>>> &platforms) {
    int original_pos = platforms[y1][x1].first;
    return lower_bound(all(platforms[y2]), mp(original_pos+1,true), comp()) - platforms[y2].begin();
}

int dp(int x, int y, vector<vector<pair<int,bool>>> &platforms) {
    pair<int,bool> p = platforms[y][x];
    if (p.second && y == platforms.size() - 1) {
        return callDP(x+1,y,platforms) + 1;
    }

    if (p.second) {
        return min(callDP(x+1,y,platforms)+1,callDP(map_pos(x,y,y+1,platforms),y+1,platforms));
    } else {
        return min(callDP(x+1,y,platforms),callDP(map_pos(x,y,y-1,platforms),y-1,platforms)+1);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(x);
    ini(z);

    vector<vector<pair<int,bool>>> platforms(n);
    for (int i = 0; i < n; i++) {
        int pointer = 0;

        ini(k);
        for (int j = 0; j < k; j++) {
            ini(ki);
            if (i != 0) {
                while (pointer < platforms[i-1].size() && platforms[i-1][pointer].first < ki) {
                    if (platforms[i-1][pointer].second) {
                        platforms[i].pb({platforms[i-1][pointer].first,false});
                    }
                    pointer++;
                }
            }
            platforms[i].pb({ki,true});
        }
    }

    for (int i = 0; i < n; i++) {
        dp_arr.pb(vector<int>(platforms[i].size(),-1));
    }

    for (int i = 0; i < z; i++) {
        ini(zi);
        zi--;

        cout << callDP(0,zi,platforms) << endl;
    }
}