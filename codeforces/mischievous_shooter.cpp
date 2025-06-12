#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

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

void construct_diagonal(vector<string> &board, vector<vector<int>> &diagonal) {
    for (int i = 0; i < diagonal.size(); i++) {
        for (int j = 0; j < diagonal[0].size(); j++) {
            if (diagonal[i][j] == -1) {
                diagonal[i][j] = ((i != 0 && j != 0) ? diagonal[i-1][j-1] : 0)+(i < board.size()
                        && j < board[0].size() && board[i][j] == '#' ? 1 : 0);
            }
        }
    }
}

void construct_rows(vector<string> &board, vector<vector<int>> &rows) {
    for (int j = 0; j < rows[0].size(); j++) {
        for (int i = 0; i < rows.size(); i++) {
            if (rows[i][j] == -1) {
                rows[i][j] = (i != 0 ? rows[i-1][j] : 0)+(i < board.size() && j < board[0].size() && board[i][j] == '#' ? 1 : 0);
            }
        }
    }
}

void construct_columns(vector<string> &board, vector<vector<int>> &columns) {
    for (int i = 0; i < columns.size(); i++) {
        for (int j = 0; j < columns[0].size(); j++) {
            if (columns[i][j] == -1) {
                columns[i][j] = (j != 0 ? columns[i][j-1] : 0)+(i < board.size() && j < board[0].size() && board[i][j] == '#' ? 1 : 0);
            }
        }
    }
}

int solve(int k, vector<string> &board) {
    vector<vector<int>> diagonal(board.size()+1,vector<int>(board[0].size()+1,-1));
    construct_diagonal(board,diagonal);

    vector<vector<int>> rows(board.size()+1,vector<int>(board[0].size()+1,-1));
    construct_rows(board,rows);

    vector<vector<int>> columns(board.size()+1,vector<int>(board[0].size()+1,-1));
    construct_columns(board,columns);

    int current_sum = 0;
    // Initial sum
    for (int i = 0; i <= k && i < board.size(); i++) {
        current_sum += board[i][0] == '#';
    }

    int maximal_sum = current_sum;
    for (int i = 0; i < board.size(); i++) {
        int sum_cp = current_sum;
        for (int j = 0; j < board[0].size(); j++) {
            maximal_sum = max(maximal_sum,sum_cp);

            sum_cp += rows[min(i+k,(int) board.size())][j+1]-(i != 0 ? rows[i-1][j+1] : 0);
            int move_up = max(0,i+k-((int) board.size()));
            sum_cp -= (j-move_up <= board[0].size() ? diagonal[i+k-move_up][j-move_up] : 0)-((i != 0 && j-k-1 >= 0) ? diagonal[i-1][j-k-1] : 0);
        }

        current_sum += i+k+1<board.size() ? board[i+k+1][0] == '#' : 0;
        current_sum -= board[i][0] == '#';
    }

    return maximal_sum;
}

vector<string> rotate(vector<string> &board, int (*func)(int,int), int (*func2)(int,int)) {
    vector<string> rotation(board.size(),string(board[0].size(),'.'));
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            rotation[i][j] = board[(*func)(i,board.size())][(*func2)(j,board[0].size())];
        }
    }

    return rotation;
}

int invert(int val, int k) {
    return k-1-val;
}

int identity_func(int val, int k) {
    return val;
}

int solve_for_rotations(int k, vector<string> &board) {
    int best = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            vector<string> res = rotate(board, i == 0 ? &identity_func : &invert, j == 0 ? &identity_func : &invert);
            best = max(best,solve(k,res));
        }
    }

    return best;
}

int bruteforce(vector<string> &board, int k) {
    int res = 0;
    for (int x1 = 0; x1 < board.size(); x1++) {
        for (int y1 = 0; y1 < board[0].size(); y1++) {
            for (int dir1 = -1; dir1 < 2; dir1+=2) {
                for (int dir2 = -1; dir2 < 2; dir2+=2) {
                    int total = 0;
                    for (int x2 = 0; x2 < board.size(); x2++) {
                        for (int y2 = 0; y2 < board[0].size(); y2++) {
                            if (abs(x1-x2)+abs(y1-y2) <= k && board[x2][y2] == '#' && (x2-x1)*dir1>=0 && (y2-y1)*dir2>=0) {
                                total++;
                            }
                        }
                    }

                    res = max(res,total);
                }
            }
        }
    }

    return res;
}

void readCaseData() {
    ini(n);
    ini(m);
    ini(k);
    //int n = rand() % 10 + 1;
    //int m = rand() % 10 + 1;
    //int k = rand() % 10 + 1;
    vector<string> board(n);
    for (int i = 0; i < n; i++) {
        instr(str);
        /*string str = "";
        for (int j = 0; j < m; j++) {
            int ran = rand() % 2;
            if (ran == 0) {
                str += ".";
            } else if (ran == 1) {
                str += "#";
            }
        }*/
        board[i] = str;
    }

    //int res_brute = bruteforce(board,k);
    int res = solve_for_rotations(k,board);

    /*if (res_brute != res) {
        int test = 0;
    }*/

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