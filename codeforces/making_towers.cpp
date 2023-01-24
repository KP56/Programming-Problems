#include <bits/stdc++.h>

using namespace std;

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        arr.push_back(el - 1);
    }

    unordered_map<int, int> m;
    vector<int> scores(size);
    for (int i = 0; i < arr.size(); i++) {
        int color = arr[i];
        if (m.find(color) == m.end()) {
            m[color] = i;
            scores[color]++;
        } else if ((i - m[color] - 1) % 2 == 0) {
            m[color] = i;
            scores[color]++;
        }
    }

    for (int i : scores) {
        cout << i << " ";
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