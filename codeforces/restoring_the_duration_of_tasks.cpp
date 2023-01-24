#include <bits/stdc++.h>

using namespace std;


void read_data() {
    int size;
    cin >> size;

    vector<int> task_given;
    vector<int> completed;

    for (int i = 0; i < size; i++) {
        int given;
        cin >> given;

        task_given.push_back(given);
    }

    for (int i = 0; i < size; i++) {
        int comp;
        cin >> comp;

        completed.push_back(comp);
    }

    cout << completed[0] - task_given[0] << " ";
    for (int i = 1; i < size; i++) {
        cout << completed[i] - max(task_given[i], completed[i - 1]) << " ";
    }

    cout << "\n";
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