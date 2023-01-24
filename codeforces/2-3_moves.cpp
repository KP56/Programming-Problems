#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    int n;
    cin >> n;

    int how_many_threes = n / 3;
    if (n < 3) {
        if (n == 1) {
            cout << 2 << "\n";
        } else {
            cout << 1 << "\n";
        }
    } else if (n % 3 == 1 || n % 3 == 2) {
        cout << how_many_threes + 1 << "\n";
    } else {
        cout << how_many_threes << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        read_arr();
    }
}