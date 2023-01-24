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

int toNum(char c) {
    if (c == 'G') {
        return 1;
    } else if (c == 'D') {
        return -1;
    } else if (c == 'L') {
        return 2;
    } else if (c == 'P') {
        return -2;
    }

    return INT_MIN;
}

void process(string sequence, vector<string> &board, int width, int height) {
    for (char c : sequence) {
        if (c == 'G') {
            vector<int> tower(width);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    char c = board[y][x];
                    if (c != '.') {
                        board[y][x] = '.';
                        board[tower[x]][x] = c;
                        tower[x]++;
                    }
                }
            }
        }
    
        if (c == 'D') {
            vector<int> tower(width);
            for (int x = 0; x < width; x++) {
                for (int y = height - 1; y >= 0; y--) {
                    char c = board[y][x];
                    if (c != '.') {
                        board[y][x] = '.';
                        board[height - tower[x] - 1][x] = c;
                        tower[x]++;
                    }
                }
            }
        }

        if (c == 'L') {
            vector<int> tower(height);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    char c = board[y][x];
                    if (c != '.') {
                        board[y][x] = '.';
                        board[y][tower[y]] = c;
                        tower[y]++;
                    }
                }
            }
        }

        if (c == 'P') {
            vector<int> tower(height);
            for (int x = width - 1; x >= 0; x--) {
                for (int y = 0; y < height; y++) {
                    char c = board[y][x];
                    if (c != '.') {
                        board[y][x] = '.';
                        board[y][width - tower[y] - 1] = c;
                        tower[y]++;
                    }
                }
            }
        }
    }
}

string op1(string s) {
    string s2 = "";

    char prev = 0;
    for (char c : s) {
        bool current = (c == 'P' || c == 'L');
        bool prev_b = (prev == 'P' || prev == 'L');
        if (prev != 0) {
            if (current != prev_b) {
                s2 += prev;
            }
        }

        prev = c;
    }

    s2 += prev;
    return s2;
}

string op2(string s) {
    string s3 = "";

    char c1 = 0;
    char c2 = 0;
    for (char c : s) {
        bool current = (c == 'P' || c == 'L');

        if (current) {
            if (c1 != c) {
                s3 += c;
            }

            c1 = c;
        } else {
            if (c2 != c) {
                s3 += c;
            }

            c2 = c;
        }
    }

    return s3;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(height);
    in_i(width);

    vector<string> board;
    for (int i = 0; i < height; i++) {
        in_str(s);
        board.pb(s);
    }
    in_i(moves);
    in_str(sequence);

    string prev_seq = "";
    while (sequence != prev_seq) {
        prev_seq = sequence;
        sequence = op1(sequence);
        sequence = op2(sequence);
    }
    
    process(sequence, board, width, height);

    for (string s : board) {
        cout << s << endl;
    }
}