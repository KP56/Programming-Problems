#include <bits/stdc++.h>
#define lli long long int

using namespace std;

int rec(vector<bool> current, int index, int sum, bool set_to) {
    current[index] = set_to;
    index++;

    if (index == 9) {
        int s = 0;
        for (int i = 0; i < 9; i++) {
            s += current[8 - i] * (9 - i);
        }
        
        if (s != sum)
            return INT_MAX;

        int added = 0;
        int return_result = 0;
        for (int i = 0; i < 9; i++) {
            return_result += current[8 - i] * pow(10, added) * (9 - i);

            if (current[8 - i])
                added++;
        }

        return return_result;
    }
    
    return min(rec(current, index, sum, false), rec(current, index, sum, true));
}

void read_arr() {
    int sum;
    cin >> sum;

    cout << min(rec(vector<bool>(9, false), 0, sum, false), rec(vector<bool>(9, false), 0, sum, true)) << "\n";
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