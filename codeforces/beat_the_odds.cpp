#include <bits/stdc++.h>

using namespace std;

int remove_elements(vector<int> &arr) {
    int odd = 0;
    int even = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] % 2 == 0) {
            even++;
        } else {
            odd++;
        }
    }

    return min(odd, even);
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

    cout << remove_elements(arr) << "\n";
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