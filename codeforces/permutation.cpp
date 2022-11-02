#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<bool> nums;
vector<int> for_a(int n, int a) {
    vector<int> these_nums;

    int current = a;
    while (current <= n) {
        if (nums[current - 1])
            return {};
        
        nums[current - 1] = true;

        these_nums.push_back(current);

        current *= 2;
    }

    return these_nums;
}

void read_data() {
    int n;
    cin >> n;

    nums = vector<bool>(n);

    vector<int> answ;
    for (int a = 1; a <= n; a++) {
        for (int i : for_a(n, a)) {
            answ.push_back(i);
        }
    }

    cout << 2 << "\n";

    cout << answ[0];
    for (int i = 1; i < answ.size(); i++) {
        cout << " " << answ[i];
    }
    cout << "\n";
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