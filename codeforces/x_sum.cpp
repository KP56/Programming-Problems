#include <bits/stdc++.h>

using namespace std;

pair<int, vector<pair<int, int>>> calculate_downward_line(int x, int y, vector<vector<int>> &board) {
    int sum = 0;
    vector<pair<int, int>> points;

    for (int i = 0; y + i < board[0].size() && x + i < board.size(); i++) {
        sum += board[x + i][y + i];
        points.emplace_back(x + i, y + i);
    }

    return {sum, points};
}

pair<int, vector<pair<int, int>>> calculate_upward_line(int x, int y, vector<vector<int>> &board) {
    int sum = 0;
    vector<pair<int, int>> points;

    for (int i = 0; y - i >= 0 && x + i < board.size(); i++) {
        sum += board[x + i][y - i];
        points.emplace_back(x + i, y - i);
    }

    return {sum, points};
}

void read_data() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> board;
    for (int i = 0; i < n; i++) {
        vector<int> line;
        for (int j = 0; j < m; j++) {
            int cell;
            cin >> cell;

            line.push_back(cell);
        }
        board.push_back(line);
    }

    vector<vector<int>> downward_lines(n, vector<int>(m));
    for (int x = 0; x < n; x++) {
        auto i = calculate_downward_line(x, 0, board);

        for (auto point : i.second) {
            downward_lines[point.first][point.second] = i.first;
        }
    }

    for (int y = 1; y < m; y++) {
        auto i = calculate_downward_line(0, y, board);

        for (auto point : i.second) {
            downward_lines[point.first][point.second] = i.first;
        }
    }

    vector<vector<int>> upward_lines(n, vector<int>(m));
    for (int x = 0; x < n; x++) {
        auto i = calculate_upward_line(x, m - 1, board);

        for (auto point : i.second) {
            upward_lines[point.first][point.second] = i.first;
        }
    }

    for (int y = 0; y < m - 1; y++) {
        auto i = calculate_upward_line(0, y, board);

        for (auto point : i.second) {
            upward_lines[point.first][point.second] = i.first;
        }
    }

    /*cout << "Upward lines:" << "\n";
    for (int i : upward_lines) {
        cout << i << "\n";
    }

    cout << "Downward lines:" << "\n";
    for (int i : downward_lines) {
        cout << i << "\n";
    }*/

    int max_sum = INT_MIN;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            max_sum = max(max_sum, upward_lines[x][y] + downward_lines[x][y] - board[x][y]);
        }
    }

    cout << max_sum << "\n";
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