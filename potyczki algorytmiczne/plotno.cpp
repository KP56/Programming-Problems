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
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

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

void recursion(int x, int y, vector<vector<bool>> &board, vector<vector<bool>> &vis) {
    vis[y][x] = true;

    vector<pii> v = {
        mp((x + 1) % board[0].size(), y),
        mp(x == 0 ? board[0].size() - 1 : x - 1, y),
        mp(x, !y)
    };

    for (pii p : v) {
        if (board[p.second][p.first] && !vis[p.second][p.first]) {
            recursion(p.first, p.second, board, vis);
        }
    }
}

int countCoolStuff(vector<vector<bool>> &board) {
    vector<vector<bool>> vis(board.size(), vector<bool>(board[0].size()));

    int counter = 0;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] && !vis[i][j]) {
                counter++;
                recursion(j,i,board,vis);
            }
        }
    }

    return counter;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_i(interest);

    vector<vector<int>> vec(2);
    vector<pii> loc(size * 2);
    for (int i = 0; i < size; i++) {
        in_i(a);
        loc[a - 1] = mp(i, 0);
        vec[0].pb(a - 1);
    }

    for (int i = 0; i < size; i++) {
        in_i(b);
        loc[b - 1] = mp(i, 1);
        vec[1].pb(b - 1);
    }

    vector<int> solutions(size * 2 + 1);
    for (int l = 0; l < 2*size; l++) {
        vector<vector<bool>> board(2,vector<bool>(size));
        for (int r = l; r < 2*size; r++) {
            pii p = loc[r];
            board[p.second][p.first] = true;
            solutions[countCoolStuff(board)]++;
        }
    }

    for (int i = 0; i < interest; i++) {
        cout << solutions[i + 1] << " ";
    }
    cout << endl;
}