#include <bits/stdc++.h>

using namespace std;

void read_data() {
    int size;
    cin >> size;

    int min_cand = INT_MAX;

    vector<int> candies;
    candies.reserve(size);
    for (int i = 0; i < size; i++) {
        int cand;
        cin >> cand;

        min_cand = min(min_cand, cand);

        candies.push_back(cand);
    }

    int to_eat = 0;
    for (int i : candies) {
        to_eat += i - min_cand;
    }

    cout << to_eat << "\n";
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