#include <bits/stdc++.h>

using namespace std;

void read_arr() {
    int size_of_a, size_of_str;
    cin >> size_of_a >> size_of_str;

    vector<int> arr;
    for (int i = 0; i < size_of_a; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }

    vector<bool> str(size_of_str);

    for (int i : arr) {
        int a = i;
        int b = size_of_str + 1 - i;

        if ((a < b && !str[a - 1]) || str[b - 1]) {
            str[a - 1] = true;
        } else {
            str[b - 1] = true;
        }
    }

    string s = "";
    for (bool b : str) {
        if (b) {
            s += 'A';
        } else {
            s += 'B';
        }
    }

    cout << s << "\n";
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