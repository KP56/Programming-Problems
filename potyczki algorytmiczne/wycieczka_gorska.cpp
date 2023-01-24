#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

pii bfs(ll n, ll m, vector<string> &board) {
    vector<vector<bool>> vis(n, vector<bool>(m));
    queue<pair<pii,vector<ll>>> q;
    q.emplace(mp(0,0),vector<ll>(3));

    vector<pii> rel = {
        {0, 1},
        {1, 0},
        {-1, 0},
        {0, -1}
    };

    while (!q.empty()) {
        pair<pii,vector<ll>> current = q.front();
        q.pop();
        pii coords = current.first;
        vis[coords.first][coords.second] = true;
        vector<ll> data = current.second;
        //data[0] = total steps
        //data[1] = right
        //data[2] = down

        for (pii i : rel) {
            pii new_coords = {coords.first + i.first, coords.second + i.second};
            if (new_coords.first < n && new_coords.second < m && new_coords.first >= 0 && new_coords.second >= 0) {
                if (!vis[new_coords.first][new_coords.second] && board[new_coords.first][new_coords.second] == '.') {
                    vector<ll> new_data = data;
                    new_data[0]++;
                    new_data[1] += (i.second == 1);
                    new_data[2] += (i.first == 1);

                    vis[new_coords.first][new_coords.second] = true;

                    if (new_coords.first == n - 1 && new_coords.second == m - 1) {
                        return mp(new_data[1],new_data[2]);
                    }

                    q.emplace(new_coords, new_data);
                }
            }
        }
    }

    return {-1,-1};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(n);
    in_i(m);
    in_i(k);
    vector<string> board;
    for (ll i = 0; i < n; i++) {
        in_str(str);
        board.pb(str);
    }

    auto p = bfs(n,m,board);
    ll right = p.first;
    ll down = p.second;

    ll minimum = 9223372036854775807;
    ll amount = 0;
    for (ll i = 0; i < k; i++) {
        in_i(a);
        in_i(b);

        ll ans = a * right + a * down + b * (right - m + 1) + b * (down - n + 1);
        if (ans < minimum) {
            minimum = ans;
            amount = 1;
        } else if (ans == minimum) {
            amount++;
        }
    }

    cout << minimum << " " << amount << endl;
}