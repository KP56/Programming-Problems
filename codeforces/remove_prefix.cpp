#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }

    vector<int> prev(size, -1);
    int m = INT_MIN;
    for (int i = 0; i < size; i++) {
        int num = arr[i];

        if (prev[num - 1] != -1) {
            m = max(m, prev[num - 1]);
        }

        prev[num - 1] = i;
    }

    if (m == INT_MIN) {
        m = -1;
    }

    cout << m + 1 << "\n";
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