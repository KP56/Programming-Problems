#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    vector<lli> arr;
    for (lli i = 0; i < 4; i++) {
        lli a;
        cin >> a;

        arr.push_back(a);
    }

    int sum = 0;
    for (int i = 1; i < 4; i++) {
        if (arr[i] > arr[0]) {
            sum++;
        }
    }

    cout << sum << "\n";
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