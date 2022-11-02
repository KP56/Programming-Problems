//Some weird compiler problem? WTF?

#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool is_phrase(string s, string phrase, int index) {
    for (int i = 0; i < phrase.length(); i++) {
        if (s[i + index] != phrase[i]) {
            return false;
        }
    }

    return true;
}

bool is_colored(int i, int j, vector<bool> v) {
    for (int a = i; a <= j; a++) {
        if (v[a]) {
            return true;
        }
    }

    return false;
}

int uncolored(int i, int j, vector<bool> v) {
    int sum = 0;
    for (int a = i; a <= j; a++) {
        if (!v[a]) {
            sum++;
        }
    }

    return sum;
}

void read_arr() {
    string s;
    cin >> s;

    int size;
    cin >> size;

    vector<string> arr;
    for (int i = 0; i < size; i++) {
        string el;
        cin >> el;

        arr.push_back(el);
    }

    vector<pair<pair<int, int>, string>> strings_with_len;
    for (int i = 0; i < arr.size(); i++) {
        string s = arr[i];
        strings_with_len.push_back({{s.length(), i + 1}, s});
    }
    sort(strings_with_len.begin(), strings_with_len.end(), greater<pair<pair<int, int>, string>>());

    vector<pair<int, int>> steps;
    vector<bool> colored(s.length(), false);
    for (pair<pair<int, int>, string> p : strings_with_len) {
        for (int i = 0; i < s.size(); i++) {
            if (is_phrase(s, p.second, i) && !is_colored(i, i + s.size() - 1, colored)) {
                for (int j = i; j < i + p.first.first; j++) {
                    colored[j] = true;
                }

                steps.emplace_back(i + 1, p.first.second);
            }
        }
    }

    for (int i = 0; i < s.length(); i++) {
        int m = INT_MIN;
        pair<int, int> range;
        int ind = 0;
        for (pair<pair<int, int>, string> p : strings_with_len) {
            for (int j = i; j >= max(0, i - p.first.first + 1); j--) {
                if (is_phrase(s, p.second, j)) {
                    int un = uncolored(j, j + p.first.first - 1, colored);
                    if (m < un) {
                        m = un;
                        range = {j + 1, j + p.first.first};
                        ind = p.first.second;
                    }
                }
            }
        }

        if (m != INT_MIN && m > 0) {
            for (int j = range.first - 1; j < range.second; j++) {
                colored[j] = true;
            }
            steps.emplace_back(range.first, ind);
        }
    }

    for (bool b : colored) {
        if (!b) {
            cout << -1 << "\n";
            return;
        }
    }

    cout << steps.size() << "\n";

    for (pair<int, int> p : steps) {
        cout << p.second << " " << p.first << "\n";
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