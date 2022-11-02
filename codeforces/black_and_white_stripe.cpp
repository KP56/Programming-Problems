#include <bits/stdc++.h>

using namespace std;

void read_data() {
    int size, k;
    cin >> size >> k;

    vector<int> prefix(size);
    string s;
    cin >> s;

    prefix[0] = (s[0] == 'B');
    for (int i = 1; i < size; i++) {
        if (s[i] == 'B') {
            prefix[i] = prefix[i - 1] + 1;
        } else {
            prefix[i] = prefix[i - 1];
        }
    }

    int max_black_cells = prefix[k - 1];
    for (int i = 1; i < size - k + 1; i++) {
        int black_cells = prefix[i + k - 1] - prefix[i - 1];
        max_black_cells = max(max_black_cells, black_cells);
    }

    cout << k - max_black_cells << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        read_data();
    }
}