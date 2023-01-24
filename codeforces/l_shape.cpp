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

vector<pair<int, int>> relative = {{0,1},{1,0},{-1,0},{0,-1}};
vector<pair<int, int>> corners = {{1,1},{1,-1},{-1,1},{-1,-1}};
vector<vector<bool>> marker;

void mark(int x, int y, vector<string> &board) {
    int counter = 0;
    vector<pair<int,int>> all_points;
    for (auto i : relative) {
        if (board[y + i.second][x + i.first] == '*' && !marker[x + i.first][y + i.second]) {
            all_points.pb({x+i.first,y+i.second});
            counter++;
        }
    }

    if (counter == 2 && all_points[0].first != all_points[1].first && all_points[0].second != all_points[1].second) {
        marker[x][y] = true;

        for (auto i : relative) {
            if (board[y + i.second][x + i.first] == '*' && !marker[x + i.first][y + i.second]) {
                marker[x + i.first][y + i.second] = true;
            }
        }
    }
}

bool dfs(int x, int y, vector<string> &board, int &sum) {
    marker[x][y] = false;
    sum++;

    for (auto i : relative) {
        if (board[y + i.second][x + i.first] == '*' && marker[x + i.first][y + i.second]) {
            dfs(x + i.first, y + i.second, board, sum);
        }
    }

    for (auto i : corners) {
        if (board[y + i.second][x + i.first] == '*' && marker[x + i.first][y + i.second]) {
            dfs(x + i.first, y + i.second, board, sum);
        }
    }

    return sum == 3;
}

void readCaseData() {
    in_i(height);
    in_i(width);

    marker = vector<vector<bool>>(width + 2, vector<bool>(height + 2));
    vector<string> board;

    string full_dots = "";
    for (int i = 0; i < width; i++) {
        full_dots += ".";
    }

    board.pb(full_dots);
    for (int i = 0; i < height; i++) {
        in_str(line);
        board.pb("." + line + ".");
    }
    board.pb(full_dots);

    height += 2;
    width += 2;

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (board[y][x] == '*' && !marker[x][y]) {
                mark(x,y,board);
            }
        }
    }

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (board[y][x] == '*' && !marker[x][y]) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (board[y][x] == '*' && marker[x][y]) {
                int sum = 0;
                if (!dfs(x,y,board,sum)) {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
    }

    cout << "YES" << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}