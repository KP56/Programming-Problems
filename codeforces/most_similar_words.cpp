#include <bits/stdc++.h>

using namespace std;

int letter_to_int(char c) {
    return c - 'a';
}

vector<int> word_to_vec(string word) {
    vector<int> alp;
    alp.reserve(word.size());
    for (char c : word) {
        alp.push_back(letter_to_int(c));
    }

    return alp;
}

void read_data() {
    int size, length;
    cin >> size >> length;

    vector<vector<int>> words;
    for (int i = 0; i < size; i++) {
        string s;
        cin >> s;

        words.push_back(word_to_vec(s));
    }

    int min_diff = INT_MAX;
    for (int i = 0; i < words.size(); i++) {
        for (int j = 0; j < words.size(); j++) {
            if (i != j) {
                int diff = 0;
                for (int k = 0; k < length; k++) {
                    diff += abs(words[i][k] - words[j][k]);
                }
                min_diff = min(min_diff, diff);
            }
        }
    }

    cout << min_diff << "\n";
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