#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<vector<bool>>> sub_exist(3, vector<vector<bool>>(3, vector<bool>(9)));
        vector<vector<bool>> columns_exist(9, vector<bool>(9));
        vector<vector<bool>> rows_exist(9, vector<bool>(9));

        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                if (board[x][y] != '.') {
                    int num = board[x][y] - '1';
                    int sub_x = x / 3;
                    int sub_y = y / 3;
                    int column = x;
                    int row = y;

                    sub_exist[sub_x][sub_y][num] = true;
                    columns_exist[column][num] = true;
                    rows_exist[row][num] = true;
                }
            }
        }

        bool b;
        do {
            b = false;
            for (int x = 0; x < 9 && !b; x++) {
                for (int y = 0; y < 9 && !b; y++) {
                    char c = board[x][y];
                    if (c == '.') {
                        vector<bool> restricted(9);
                        for (int i = 0; i < columns_exist[x].size(); i++) {
                            restricted[i] = restricted[i] | columns_exist[x][i];
                        }

                        for (int i = 0; i < rows_exist[y].size(); i++) {
                            restricted[i] = restricted[i] | rows_exist[y][i];
                        }

                        for (int i = 0; i < sub_exist[x / 3][y / 3].size(); i++) {
                            restricted[i] = restricted[i] | sub_exist[x / 3][y / 3][i];
                        }

                        int counter = 0;
                        for (bool b : restricted) {
                            counter += !b;
                        }

                        if (counter == 1) {
                            b = true;
                            for (int i = 0; i < restricted.size(); i++) {
                                if (!restricted[i]) {
                                    columns_exist[x][i] = true;
                                    rows_exist[y][i] = true;
                                    sub_exist[x / 3][y / 3][i] = true;
                                    board[x][y] = i + '1';
                                    break;
                                }
                            }
                        }

                        //check if we are forced to put a number in this specific field
                        for (int i = 0; i < 9; i++) {
                            if (!sub_exist[x / 3][y / 3][i] && !columns_exist[x][i] && !rows_exist[y][i]) {
                                counter = 0;
                                for (int sub_x = 0; sub_x < 3; sub_x++) {
                                    for (int sub_y = 0; sub_y < 3; sub_y++) {
                                        int x2 = x / 3 * 3 + sub_x;
                                        int y2 = y / 3 * 3 + sub_y;

                                        if (x2 != x || y2 != y) {
                                            if (columns_exist[x2][i] || rows_exist[y2][i]) {
                                                counter++;
                                            }
                                        }
                                    }
                                }

                                if (counter == 8) {
                                    b = true;
                                    columns_exist[x][i] = true;
                                    rows_exist[y][i] = true;
                                    sub_exist[x / 3][y / 3][i] = true;
                                    board[x][y] = i + '1';
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        } while (b);

        int lowest_counter = INT_MAX;
        pair<int,int> best_pair;
        vector<bool> best_restrictions;
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                if (board[x][y] == '.') {
                    vector<bool> restricted(9);
                    for (int i = 0; i < columns_exist[x].size(); i++) {
                        restricted[i] = restricted[i] | columns_exist[x][i];
                    }

                    for (int i = 0; i < rows_exist[y].size(); i++) {
                        restricted[i] = restricted[i] | rows_exist[y][i];
                    }

                    for (int i = 0; i < sub_exist[x / 3][y / 3].size(); i++) {
                        restricted[i] = restricted[i] | sub_exist[x / 3][y / 3][i];
                    }

                    int counter = 0;
                    for (bool b : restricted) {
                        counter += !b;
                    }

                    if (counter < lowest_counter) {
                        lowest_counter = counter;
                        best_pair = {x,y};
                        best_restrictions = restricted;
                    }
                }
            }
        }

        if (lowest_counter == INT_MAX) {
            return;
        }

        for (int i = 0; i < 9; i++) {
            if (!best_restrictions[i]) {
                vector<vector<char>> cp = board;
                cp[best_pair.first][best_pair.second] = i + '1';
                solveSudoku(cp);
                bool solved = true;
                for (int x = 0; x < 9 && solved; x++) {
                    for (int y = 0; y < 9 && solved; y++) {
                        if (cp[x][y] == '.') {
                            solved = false;
                            break;
                        }
                    }
                }

                if (solved) {
                    board = cp;
                    return;
                }
            }
        }
    }
};

int main() {
    Solution solution;
    vector<vector<char>> vec = {
        {'.','.','.', '2','.','.', '.','6','3'},
        {'3','.','.', '.','.','5', '4','.','1'},
        {'.','.','1', '.','.','3', '9','8','.'},

        {'.','.','.', '.','.','.', '.','9','.'},
        {'.','.','.', '5','3','8', '.','.','.'},
        {'.','3','.', '.','.','.', '.','.','.'},

        {'.','2','6', '3','.','.', '5','.','.'},
        {'5','.','3', '7','.','.', '.','.','8'},
        {'4','7','.', '.','.','1', '.','.','.'}
    };
    
    solution.solveSudoku(vec);
    cout << "test" << endl;
}