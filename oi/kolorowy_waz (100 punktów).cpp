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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(diameter);
    in_i(snacks);
    in_i(queries);

    vector<vector<int>> board(diameter,vector<int>(diameter,-1));
    board[0][0] = 0;
    for (int i = 0; i < snacks; i++) {
        in_i(y);
        in_i(x);
        in_i(color);

        board[x - 1][y - 1] = -(color + 2);
    }

    int global = 0;
    vector<int> snake;
    deque<pii> coords;
    coords.pb(mp(0,0));
    snake.pb(0);
    for (int i = 0; i < queries; i++) {
        in_str(q);

        if (q != "Z") {
            int move_x;
            int move_y;

            if (q == "G") {
                move_x = 0;
                move_y = -1;
            } else if (q == "D") {
                move_x = 0;
                move_y = 1;
            } else if (q == "L") {
                move_x = -1;
                move_y = 0;
            } else if (q == "P") {
                move_x = 1;
                move_y = 0;
            }

            pii tail = coords.front();
            pii head = coords.back();
            pii new_head = mp(head.first + move_x, head.second + move_y);
            int head_ind = board[head.first][head.second];
            if (board[new_head.first][new_head.second] < -1) {
                int color = board[new_head.first][new_head.second] * (-1) - 2;
                board[new_head.first][new_head.second] = head_ind + 1;
                snake.pb(color);
                coords.pb(new_head);
            } else {
                coords.pop_front();
                coords.pb(new_head);
                board[tail.first][tail.second] = -1;
                board[new_head.first][new_head.second] = head_ind + 1;
                global++;
            }
        } else {
            in_str(y);
            in_str(x);
            int y_int = stoi(y);
            int x_int = stoi(x);
            x_int--;
            y_int--;

            int ind = board[x_int][y_int];
            if (ind < 0) {
                cout << -1 << endl;
            } else {
                int color = snake[ind - global];
                cout << color << endl;
            }
        }
    }
}