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
    ini(k);

    vector<int> last_of_color(k,-1);
    vector<int> max_dist(k,0);
    vector<int> second_greatest_dist(k,0);
    for (int i = 0; i < n; i++) {
        ini(c);
        c--;
        int dist = i - last_of_color[c] - 1;
        if (dist >= max_dist[c]) {
            second_greatest_dist[c] = max_dist[c];
            max_dist[c] = dist;
        } else if (dist >= second_greatest_dist[c]) {
            second_greatest_dist[c] = dist;
        }
        last_of_color[c] = i;
    }

    for (int i = 0; i < k; i++) {
        int dist = n - last_of_color[i] - 1;

        if (dist >= max_dist[i]) {
            second_greatest_dist[i] = max_dist[i];
            max_dist[i] = dist;
        } else if (dist >= second_greatest_dist[i]) {
            second_greatest_dist[i] = dist;
        }
    }

    int res = INT_MAX;

    for (int i = 0; i < k; i++) {
        int res_for_i = max(second_greatest_dist[i],max_dist[i] / 2);
        res = min(res, res_for_i);
    }

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}