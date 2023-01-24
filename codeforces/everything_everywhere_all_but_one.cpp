#include <bits/stdc++.h>

using namespace std;

int average_of(vector<int> &arr, int exclude) {
    int sum = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (i != exclude) {
            sum += arr[i];
        }
    }

    if (sum % (arr.size() - 1) != 0)
        return 101;

    return sum / (arr.size() - 1);
}

bool equal_after_operations(vector<int> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        if (average_of(arr, i) == arr[i]) {
            return true;
        }
    }

    return false;
}

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    arr.reserve(size);
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }

    if (equal_after_operations(arr)) {
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
        read_arr();
    }
}