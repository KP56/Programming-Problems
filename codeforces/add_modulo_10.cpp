#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void turnMod(vector<vector<int>> &mods, int mod1, int mod2, int increase) {
    for (int i = mods[mod1].size() - 1; i >= 0; i--) {
        mods[mod2].push_back(mods[mod1][i] + increase);
        mods[mod1].erase(--mods[mod1].end());
    }
}

void readArr() {
    int size;
    cin >> size;

    int a = -1;
    bool all_equal = true;
    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        if (a == -1) {
            a = el;
        } else if (el != a) {
            all_equal = false;
        }

        arr.push_back(el);
    }

    if (all_equal) {
        cout << "YES" << "\n";
        return;
    }

    vector<vector<int>> mods(10);
    for (int i : arr) {
        mods[i % 10].push_back(i / 10);
    }

    //all mods 5 will be turned to mods 0
    turnMod(mods, 5, 0, 1);

    //if one of the mods 0 is different or there is some other mod, the answer is no
    a = -1;
    for (int i : mods[0]) {
        if (a == -1) {
            a = i;
        } else if (a != i) {
            cout << "NO" << "\n";
            return;
        }
    }

    if (!mods[0].empty()) {
        for (int i = 1; i < 10; i++) {
            if (!mods[i].empty()) {
                cout << "NO" << "\n";
                return;
            }
        }
    }

    //all mods 1 will be turned to mods 2
    turnMod(mods, 1, 2, 0);

    //all mods 3 will be turned to mods 2
    turnMod(mods, 3, 2, 1);

    //all mods 4 will be turned to mods 2
    turnMod(mods, 4, 2, 2);

    //all mods 6 will be turned to mods 2
    turnMod(mods, 6, 2, 1);

    //all mods 7 will be turned to mods 2
    turnMod(mods, 7, 2, 3);

    //all mods 8 will be turned to mods 2
    turnMod(mods, 8, 2, 2);

    //all mods 9 will be turned to mods 2
    turnMod(mods, 9, 2, 3);

    int mod = -1;
    for (int i : mods[2]) {
        if (mod == -1) {
            mod = i % 2;
        } else if (mod != i % 2) {
            cout << "NO" << "\n";
            return;
        }
    }

    cout << "YES" << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    while (cases--) {
        readArr();
    }
}