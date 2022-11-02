#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    int n;
    cin >> n;

    vector<int> prev_permutation;
    for (int i = 0; i < n; i++) {
        prev_permutation.push_back(i + 1);
    }
    
    cout << n << "\n";

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << prev_permutation[j] << " ";
        }
        cout << "\n";

        int prev = prev_permutation[i];
        prev_permutation[i] = prev_permutation[i - 1];
        prev_permutation[i - 1] = prev;
    }

    for (int j = 0; j < n; j++) {
        cout << prev_permutation[j] << " ";
    }
    cout << "\n";
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