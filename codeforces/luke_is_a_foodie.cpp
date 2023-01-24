#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    lli size, x;
    cin >> size >> x;

    vector<lli> arr;
    for (lli i = 0; i < size; i++) {
        lli el;
        cin >> el;

        arr.push_back(el);
    }

    //there are two cases:
    //- ai > v here ai-v <= x
    //- ai < v here v-ai <= x
    //- ai = v in this case x doesn't matter

    //we iterate and keep track of min and max
    //|v-min| <= x
    //|v-max| <= x
    //we can assume that max > v and min < v
    //in that case:
    //max - v <= x
    //v - min <= x
    
    //we can calculate min_v by:
    //max - min_v = x |-max
    //-min_v = x - max |*(-1)
    //min_v = max - x

    //max_v:
    //max_v - min = x |+(min)
    //max_v = x + min
    
    //we keep iterating while min_v <= max_v
    //if its not the case, we set min and max to initial values and increase counter
    //once we are done we prlli the counter

    lli counter = 0;
    lli max_i = INT_MIN;
    lli min_i = INT_MAX;
    for (lli i : arr) {
        max_i = max(max_i, i);
        min_i = min(min_i, i);

        lli min_v = max_i - x;
        lli max_v = x + min_i;

        if (min_v > max_v) {
            max_i = i;
            min_i = i;

            counter++;
        }
    }

    cout << counter << "\n";
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