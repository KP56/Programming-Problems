#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> apply(int x, int y, vector<vector<int>> board) {
    for (int i = 0; i < 2; i++) {
        board[x][i] = 0;
        board[i][y] = 0;
    }

    return board;
}

int test_move(int x, int y, vector<vector<int>> board) {
    int ret = 0;
    for (int i = 0; i < 2; i++) {
        ret += board[x][i] + board[i][y];
    }

    ret -= board[x][y];

    return ret;
}

bool is_full_zero(vector<vector<int>> vec) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (vec[i][j]) {
                return false;
            }
        }
    }

    return true;
}

void read_data() {
    vector<vector<int>> board(2, vector<int>(2));

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 0; i < 2; i++) {
        if (is_full_zero(board)) {
            cout << i << "\n";
            return;
        }

        int max_moves = INT_MIN;
        int best_x;
        int best_y;
        for (int x = 0; x < 2; x++) {
            for (int y = 0; y < 2; y++) {
                int moves = test_move(x, y, board);
                if (moves > max_moves) {
                    max_moves = moves;
                    best_x = x;
                    best_y = y;
                }
            }
        }

        board = apply(best_x, best_y, board);
    }

    if (is_full_zero(board)) {
        cout << 2 << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        read_data();
    }
}