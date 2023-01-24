#include <bits/stdc++.h>

using namespace std;

void read_arr() {
    int size;
    cin >> size;

    vector<pair<int, int>> lines;
    for (int i = 0; i < size; i++) {
        int a;
        cin >> a;

        lines.emplace_back(i, a);
    }

    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = i + 1; j < lines.size(); j++) {
            if (lines[i].first == lines[j].first || lines[i].second == lines[j].second ||
                    (lines[i].first > lines[j].first && lines[i].second < lines[j].second) ||
                    (lines[i].first < lines[j].first && lines[i].second > lines[j].second)) {
                //lines[i].first > lines[j].first && lines[i].second < lines[j].second or
                //lines[i].first < lines[j].first && lines[i].second > lines[j].second or
                //lines[i].first == lines[j].first or
                //lines[i].second == lines[j].second
                sum++;
            }
        }
    }

    cout << sum << "\n";
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