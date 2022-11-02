#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    int size_a, size_b;
    cin >> size_a >> size_b;

    string a;
    string b;
    cin >> a;
    cin >> b;

    vector<bool> arr_a(size_a);
    for (int i = 0; i < size_a; i++) {
        arr_a[i] = (a[i] == '1') ? true : false;
    }

    vector<bool> arr_b(size_b);
    for (int i = 0; i < size_b; i++) {
        arr_b[i] = (b[i] == '1') ? true : false;
    }

    while (arr_a != arr_b) {
        if (arr_a.size() <= arr_b.size()) {
            cout << "NO" << "\n";
            return;
        }

        if (arr_a[0] != arr_b[0]) {
            arr_a.erase(arr_a.begin());
        } else {
            arr_a.erase(++arr_a.begin());
        }
    }

    cout << "YES" << "\n";
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