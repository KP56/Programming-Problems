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

void readCaseData() {
    ini(n);
    ini(m);

    vector<vector<int>> board;
    for (int i = 0; i < n; i++) {
        instr(s);
        vector<int> vec;
        for (char c : s) {
            vec.pb((int) (c == '1'));
        }
        board.pb(vec);
    }

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] == 0) continue;

            // there must exist either a column such that there are balls up to this cell
            // or a row such that there exist balls up to this cell
            
            bool is_row_filled = true;
            for (int k = 0; k < i; k++) {
                if (board[k][j] == 0) {
                    is_row_filled = false;
                    break;
                }
            }

            bool is_column_filled = true;
            for (int k = 0; k < j; k++) {
                if (board[i][k] == 0) {
                    is_column_filled = false;
                    break;
                }
            }

            if (!is_row_filled && !is_column_filled) {
                cout << "NO" << endl;
                return;
            }
        }
    }

    cout << "YES" << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}