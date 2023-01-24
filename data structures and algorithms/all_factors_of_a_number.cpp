#include <bits/stdc++.h>

using namespace std;

vector<int> divisorsOfNumber(int x) {
    vector<int> ret;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            ret.push_back(i);
            if (x / i != i) {
                ret.push_back(x / i);
            }
        }
    }

    return ret;
}

int main() {
    cout << "Divisors of 20:" << endl;
    for (int i : divisorsOfNumber(20)) {
        cout << i << endl;
    }

    cout << "Divisors of 100:" << endl;
    for (int i : divisorsOfNumber(100)) {
        cout << i << endl;
    }

    cout << "Divisors of 2500:" << endl;
    for (int i : divisorsOfNumber(2500)) {
        cout << i << endl;
    }
}