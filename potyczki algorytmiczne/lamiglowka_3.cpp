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

struct paint_operation {
    int idx;
    bool is_row;
    int color;

    paint_operation(int idx, bool is_row, int color) {
        this->idx = idx;
        this->is_row = is_row;
        this->color = color;
    }
};

bool is_possible(vector<string> &board, vector<string> &target, int current, int limit) {
    if (board == target) {
        return true;
    }

    if (current == limit) {
        return false;
    }

    bool possibility = false;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < 3; j++) {
            vector<string> new_board = board;
            for (int k = 0; k < board[0].size(); k++) {
                new_board[i][k] = 'A' + j;
            }

            possibility |= is_possible(new_board,target,current+1,limit);
        }
    }

    for (int i = 0; i < board[0].size(); i++) {
        for (int j = 0; j < 3; j++) {
            vector<string> new_board = board;
            for (int k = 0; k < board.size(); k++) {
                new_board[k][i] = 'A' + j;
            }

            possibility |= is_possible(new_board,target,current+1,limit);
        }
    }

    return possibility;
}

bool verify(vector<string> &board, vector<string> &target, stack<paint_operation> operations) {
    vector<paint_operation> vec;
    while (!operations.empty()) {
        vec.pb(operations.top());
        operations.pop();
    }

    for (paint_operation &o : vec) {
        if (o.is_row) {
            for (int i = 0; i < board[0].size(); i++) {
                board[o.idx][i] = o.color + 'A';
            }
        } else {
            for (int i = 0; i < board.size(); i++) {
                board[i][o.idx] = o.color + 'A';
            }
        }
    }

    return board == target;
}

string random_string(int size) {
    string s = "";
    for (int i = 0; i < size; i++) {
        s += string(1,'A' + (rand() % 3));
    }

    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = 3;
    ini(m);
    //int m = 2;

    vector<vector<int>> rows(n,vector<int>(26));
    vector<vector<int>> columns(m,vector<int>(26));

    //vector<string> board;
    for (int i = 0; i < n; i++) {
        instr(s);
        //string s = random_string(m);
        for (int j = 0; j < m; j++) {
            rows[i][s[j]-'A']++;
            columns[j][s[j]-'A']++;
        }
        //board.pb(s);
    }

    /*vector<string> brute_board(board.size(),string(board[0].size(),'.'));
    if (!is_possible(brute_board,board,0,n+m)) {
        continue;
    }*/

    stack<paint_operation> to_paint;

    vector<bool> rows_vis(n);
    vector<bool> columns_vis(m);

    int found = 0;
    do {
        found = 0;
        // szukamy rzędu, który posiada tylko jedną literkę
        for (int i = 0; i < n; i++) {
            int diff_from_zero = 0;
            int prev = -1;
            for (int j = 0; j < 26; j++) {
                if (rows[i][j] != 0) {
                    diff_from_zero++;
                    prev = j;
                }
            }

            if (diff_from_zero == 1) {
                // odnaleźliśmy ten rząd
                found++;
                rows[i][prev] = 0;
                to_paint.push(paint_operation(i,true,prev));
                rows_vis[i] = true;
                for (int j = 0; j < m; j++) {
                    if (!columns_vis[j]) {
                        columns[j][prev]--;
                    }
                }
            }
        }

        // szukamy kolumny, która posiada tylko jedną literkę
        for (int i = 0; i < m; i++) {
            int diff_from_zero = 0;
            int prev = -1;
            for (int j = 0; j < 26; j++) {
                if (columns[i][j] != 0) {
                    diff_from_zero++;
                    prev = j;
                }
            }

            if (diff_from_zero == 1) {
                // odnaleźliśmy tę kolumnę
                found++;
                columns[i][prev] = 0;
                columns_vis[i] = true;
                to_paint.push(paint_operation(i,false,prev));
                for (int j = 0; j < n; j++) {
                    if (!rows_vis[j]) {
                        rows[j][prev]--;
                    }
                }
            }
        }
    } while (found != 0);

    
    /*vector<string> brute_board2(board.size(),string(board[0].size(),'.'));
    if (!verify(brute_board2,board,to_paint)) {
        int test = 0;
    }*/

    cout << to_paint.size() << endl;
    while (!to_paint.empty()) {
        paint_operation &o = to_paint.top();
        if (o.is_row) {
            cout << "R ";
        } else {
            cout << "K ";
        }
        cout << o.idx + 1 << " " << string(1,'A' + o.color) << endl;

        to_paint.pop();
    }
}