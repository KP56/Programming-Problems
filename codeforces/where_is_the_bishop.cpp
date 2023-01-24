#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool compare_vectors(vector<string> a, vector<string> b) {
    for (int i = 0; i < 8; i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

vector<string> generate_empty_board() {
    return vector<string>(8, "........");
}

vector<string> generate_board(int x, int y) {
    vector<string> empty = generate_empty_board();

    for (int i = 0; x - i >= 0 && y - i >= 0; i++) {
        empty[x - i][y - i] = '#';
    }

    for (int i = 0; x + i < 8 && y - i >= 0; i++) {
        empty[x + i][y - i] = '#';
    }

    for (int i = 0; x + i < 8 && y + i < 8; i++) {
        empty[x + i][y + i] = '#';
    }

    for (int i = 0; x - i >= 0 && y + i < 8; i++) {
        empty[x - i][y + i] = '#';
    }

    return empty;
}

void read_arr() {
    vector<string> board;
    for (int i = 0; i < 8; i++) {
        string s;
        cin >> s;

        board.push_back(s);
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            if (compare_vectors(generate_board(x, y), board)) {
                cout << x + 1 << " " << y + 1 << "\n";

                return;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    lli cases;
    cin >> cases;

    for (lli i = 0; i < cases; i++) {
        read_arr();
    }
}