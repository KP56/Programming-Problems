#include <bits/stdc++.h>

using namespace std;

void read_data() {
    int candies, queries;
    cin >> candies >> queries;

    multiset<int, greater<>> sugar;
    for (int i = 0; i < candies; i++) {
        int sug;
        cin >> sug;

        sugar.insert(sug);
    }

    multimap<int,int> quary_req;
    for (int i = 0; i < queries; i++) {
        int quary;
        cin >> quary;

        quary_req.insert({quary, i});
    }

    int current_amount = 0;
    int current_sugar = 0;

    auto it = sugar.begin();

    vector<int> answers(queries);
    for (pair<int, int> i : quary_req) {
        bool found = false;

        if (current_sugar >= i.first) {
            answers[i.second] = current_amount;
            continue;
        }

        for (; it != sugar.end(); it++) {
            int j = *it;

            current_sugar += j;
            current_amount++;

            if (current_sugar >= i.first) {
                answers[i.second] = current_amount;
                found = true;
                it++;
                break;
            }
        }

        if (!found) {
            answers[i.second] = -1;
        }
    }

    for (int i : answers) {
        cout << i << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        read_data();
    }
}