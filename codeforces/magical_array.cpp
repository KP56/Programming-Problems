#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    lli arrays, size;
    cin >> arrays >> size;

    vector<vector<lli>> arrs;
    for (lli i = 0; i < arrays; i++) {
        vector<lli> arr;
        for (lli i = 0; i < size; i++) {
            lli el;
            cin >> el;

            arr.push_back(el);
        }

        arrs.push_back(arr);
    }

    

    cout << 0 << "\n";
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