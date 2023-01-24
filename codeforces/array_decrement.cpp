#include <bits/stdc++.h>

using namespace std;


void read_data() {
    int size;
    cin >> size;

    vector<int> a;
    vector<int> b;
    for (int i = 0; i < size; i++) {
        int num;
        cin >> num;

        a.push_back(num);
    }

    for (int i = 0; i < size; i++) {
        int num;
        cin >> num;

        b.push_back(num);
    }

    int subtraction = INT_MAX;
    vector<int> zero_verify;
    for (int i = 0; i < size; i++) {
        if (b[i] == 0) {
            zero_verify.push_back(i);
        } else {
            if (subtraction != INT_MAX) {
                if (subtraction != a[i] - b[i]) {
                    cout << "NO" << "\n";
                    return;
                }
            } else {
                if (b[i] > a[i]) {
                    cout << "NO" << "\n";
                    return;
                }
            }

            subtraction = a[i] - b[i];
        }
    }

    for (int i : zero_verify) {
        if (a[i] > subtraction) {
            cout << "NO" << "\n";
            return;
        }
    }

    cout << "YES" << "\n";
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