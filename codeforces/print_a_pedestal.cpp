#include <bits/stdc++.h>

using namespace std;

void balance(int &h1, int &h2, int &h3) {
    if (h2 <= h3) {
        h3--;
        h2++;
    }

    if (h2 >= h1) {
        h2--;
        h1++;

        balance(h1, h2, h3);
    }
}

void read_data() {
    int n;
    cin >> n;

    int h1 = 1;
    int h2 = 2;
    int h3 = 3;
    for (int i = 0; i < n - 6; i++) {
        if (h3 >= h2) {
            h2++;
        } else if (h2 >= h1) {
            h1++;
        } else {
            h3++;
        }
    }

    balance(h1, h2, h3);

    cout << h2 << " " << h1 << " " << h3 << "\n";
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