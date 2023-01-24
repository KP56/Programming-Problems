#include <bits/stdc++.h>

using namespace std;

int char_to_int(char c) {
    return c - '0';
}

void read_data() {
    string ticket;
    cin >> ticket;

    int sum1 = 0;
    for (int i = 0; i < 3; i++) {
        sum1 += char_to_int(ticket[i]);
    }

    int sum2 = 0;
    for (int i = 3; i < 6; i++) {
        sum2 += char_to_int(ticket[i]);
    }

    if (sum1 == sum2) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }
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