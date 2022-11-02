#include <bits/stdc++.h>

using namespace std;

bool recursive(bool opened[3], int current_key, int available_keys[3]) {
    if (opened[0] && opened[1] && opened[2]) {
        return true;
    }

    if (current_key == -1) {
        return false;
    }
    
    int new_key = available_keys[current_key];

    opened[current_key] = true;
    available_keys[current_key] = -1;

    return recursive(opened, new_key, available_keys);
}

void read_arr() {
    int key;
    cin >> key;
    key--;

    int keys[3];
    cin >> keys[0] >> keys[1] >> keys[2];
    bool opened[3] = {false, false, false};

    for (int i = 0; i < 3; i++) {
        keys[i]--;
    }

    if (recursive(opened, key, keys)) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
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