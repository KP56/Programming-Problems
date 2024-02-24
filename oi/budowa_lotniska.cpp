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

bool is_horizontal_possible(vector<string> &board, int i, int j, int line_size) {
    if (i + line_size - 1 >= board.size()) {
        return false;
    }
    for (int k = i; k < i + line_size; k++) {
        if (board[k][j] != '.') {
            return false;
        }
    }

    return true;
}

bool is_vertical_possible(vector<string> &board, int i, int j, int line_size) {
    if (j + line_size - 1 >= board.size()) {
        return false;
    }
    for (int k = j; k < j + line_size; k++) {
        if (board[i][k] != '.') {
            return false;
        }
    }

    return true;
}

void horizontal_modify(vector<string> &board, int i, int j, int line_size) {
    for (int k = i; k < i + line_size; k++) {
        board[k][j] = '*';
    }
}

void vertical_modify(vector<string> &board, int i, int j, int line_size) {
    for (int k = j; k < j + line_size; k++) {
        board[i][k] = '*';
    }
}

bool brute_second(vector<string> &board, int line_size, int found) {
    if (found == 2) {
        return true;
    }

    bool res = false;
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (is_vertical_possible(board, i, j, line_size)) {
                vector<string> board_cp = board;
                vertical_modify(board_cp, i, j, line_size);
                res |= brute_second(board_cp, line_size, found + 1);
            }

            if (is_horizontal_possible(board, i, j, line_size)) {
                vector<string> board_cp = board;
                horizontal_modify(board_cp, i, j, line_size);
                res |= brute_second(board_cp, line_size, found + 1);
            }
        }
    }

    return res;
}

int brute(vector<string> &board, int m) {
    int res = 0;
    for (int i = 1; i <= board.size(); i++) {
        if (brute_second(board, i, m == 1)) {
            res = i;
        }
    }

    return res;
}

int max_coexisting_len(int column, int begin_index_column, int end_index_column, int row, int begin_index_row, int end_index_row) {
    if (column >= begin_index_row && column <= end_index_row && row >= begin_index_column && row <= end_index_column) {
        int non_cut_column = max(end_index_column - row, row - begin_index_column);
        int cut_column = end_index_column - begin_index_column + 1;

        int non_cut_row = max(end_index_row - column, column - begin_index_row);
        int cut_row = end_index_row - begin_index_row + 1;

        return max(max(min(non_cut_column,cut_row),max(min(non_cut_row,cut_column),min(non_cut_row,non_cut_column))),0ll);
    }

    return min(end_index_row - begin_index_row + 1, end_index_column - begin_index_column + 1);
}

vector<string> random_board(int n) {
    int probability_x = rand() % 100 + 1;

    vector<string> board;
    for (int i = 0; i < n; i++) {
        string s = "";
        for (int j = 0; j < n; j++) {
            if (rand() % 100 < probability_x) {
                s += "X";
            } else {
                s += ".";
            }
        }

        board.pb(s);
    }

    return board;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    //int n = rand() % 5 + 1;
    //int m = rand() % 2 + 1;
    ini(n);
    ini(m);

    vector<string> board /*= random_board(n)*/;
    for (int i = 0; i < n; i++) {
        instr(s);
        board.pb(s);
    }

    vector<vector<pii>> rows;
    for (string s : board) {
        rows.pb({});
        int l = 0;
        int i = 0;
        for (char c : s) {
            if (c == 'X') {
                if (l != 0) {
                    rows[rows.size() - 1].pb({l,i-1});
                    l = 0;
                }
            } else {
                l++;
            }
            i++;
        }

        if (l != 0) {
            rows[rows.size() - 1].pb({l,n-1});
        }
    }

    vector<vector<pii>> columns;
    for (int i = 0; i < n; i++) {
        columns.pb({});
        int l = 0;
        for (int j = 0; j < n; j++) {
            char c = board[j][i];

            if (c == 'X') {
                if (l != 0) {
                    columns[columns.size() - 1].pb({l,j-1});
                    l = 0;
                }
            } else {
                l++;
            }
        }

        if (l != 0) {
            columns[columns.size() - 1].pb({l,n-1});
        }
    }

    if (m == 1) {
        int max_val = 0;
        for (auto i : rows) {
            for (pii j : i) {
                max_val = max(max_val,j.first);
            }
        }

        for (auto i : columns) {
            for (pii j : i) {
                max_val = max(max_val,j.first);
            }
        }

        /*if (max_val != brute(board, m)) {
            int test = 0;
        }*/

        cout << max_val << endl;
    } else {
        int max_val_rows = 0;
        pii max_val_rows_pos = {-1,-1};
        int second_max_val_rows = 0;
        pii second_max_val_rows_pos = {-1,-1};
        for (int i = 0; i < n; i++) {
            vector<pii> &row = rows[i];
            for (pii j : row) {
                if (j.first > max_val_rows) {
                    second_max_val_rows = max_val_rows;
                    second_max_val_rows_pos = max_val_rows_pos;
                    max_val_rows = j.first;
                    max_val_rows_pos = {i,j.second};
                } else if (j.first > second_max_val_rows) {
                    second_max_val_rows = j.first;
                    second_max_val_rows_pos = {i,j.second};
                }
            }
        }

        int max_val_columns = 0;
        pii max_val_columns_pos = {-1,-1};
        int second_max_val_columns = 0;
        pii second_max_val_columns_pos = {-1,-1};
        for (int i = 0; i < n; i++) {
            vector<pii> &column = columns[i];
            for (pii j : column) {
                if (j.first > max_val_columns) {
                    second_max_val_columns = max_val_columns;
                    second_max_val_columns_pos = max_val_columns_pos;
                    max_val_columns = j.first;
                    max_val_columns_pos = {i,j.second};
                } else if (j.first > second_max_val_columns) {
                    second_max_val_columns = j.first;
                    second_max_val_columns_pos = {i,j.second};
                }
            }
        }

        vector<int> possibilities = {
            min(max_val_rows,second_max_val_rows),
            min(max_val_columns,second_max_val_columns),
            max_val_rows / 2,
            max_val_columns / 2,
            max_coexisting_len(max_val_columns_pos.first, max_val_columns_pos.second - max_val_columns + 1,
                                max_val_columns_pos.second, max_val_rows_pos.first, max_val_rows_pos.second - max_val_rows + 1,
                                max_val_rows_pos.second),
            max_coexisting_len(max_val_columns_pos.first, max_val_columns_pos.second - max_val_columns + 1,
                                max_val_columns_pos.second, second_max_val_rows_pos.first, second_max_val_rows_pos.second - second_max_val_rows + 1,
                                second_max_val_rows_pos.second),
            max_coexisting_len(second_max_val_columns_pos.first, second_max_val_columns_pos.second - second_max_val_columns + 1,
                                second_max_val_columns_pos.second, max_val_rows_pos.first, max_val_rows_pos.second - max_val_rows + 1,
                                max_val_rows_pos.second),
            max_coexisting_len(second_max_val_columns_pos.first, second_max_val_columns_pos.second - second_max_val_columns + 1,
                                second_max_val_columns_pos.second, second_max_val_rows_pos.first, second_max_val_rows_pos.second - second_max_val_rows + 1,
                                second_max_val_rows_pos.second)
        };
        
        int res = 0;
        for (int i : possibilities) {
            res = max(res, i);
        }

        /*if (brute(board, m) != res) {
            int test = 0;
        }*/

        cout << res << endl;
    }

    //cout << brute(board, m) << endl;
}