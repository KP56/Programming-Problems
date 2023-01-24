#include <bits/stdc++.h>

using namespace std;

bool expand(vector<int> &sub_arr, int new_element) {
    if (!sub_arr.empty() && sub_arr[sub_arr.size() - 1] > new_element) {
        return true;
    } else {
        sub_arr.push_back(new_element);
        return false;
    }
}

int odd_sub_arrs(vector<int> &arr) {
    vector<int> sub_arr;

    int inversion_arrs = 0;
    for (int i : arr) {
        if (expand(sub_arr, i)) {
            sub_arr = {};
            inversion_arrs++;
        }
    }

    return inversion_arrs;
}

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }

    cout << odd_sub_arrs(arr) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int problems;
    cin >> problems;

    for (int i = 0; i < problems; i++) {
        read_arr();
    }
}