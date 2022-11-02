#include <bits/stdc++.h>
#define lli long long int

using namespace std;

bool check(list<lli> &arr) {
    auto it = arr.begin();
    for (int i = 0; i < arr.size(); i++) {
        for (int j = i + 1; j < arr.size(); j++) {
            lli maximum = *it;
            lli sum = 0;
            auto itcp = it;
            for (lli k = i; k <= j; k++) {
                sum += *itcp;
                maximum = max(maximum, *itcp);

                if (maximum < sum) {
                    return false;
                }

                itcp++;
            }
        }

        it++;
    }

    return true;
}

void read_arr() {
    lli size;
    cin >> size;

    list<lli> arr;
    for (lli i = 0; i < size; i++) {
        lli a;
        cin >> a;

        arr.push_back(a);
    }


    if (!check(arr)) {
        cout << "NO" << "\n";
    } else {
        cout << "YES" << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    lli cases;
    cin >> cases;

    for (lli i = 0; i < cases; i++) {
        read_arr();
    }
}