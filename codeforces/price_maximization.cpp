#include <bits/stdc++.h>
#define lli long long int

using namespace std;

lli arr_based_alg(vector<lli> &arr, lli k) {
    vector<lli> array(k);

    lli sum = 0;
    for (lli i : arr) {
        sum += i / k;
        array[i % k]++;
    }

    for (lli i = k - 1; i >= 0; i--) {
        while (array[i] > 0) {
            lli found_ind = -1;

            for (lli j = k - i; j < k; j++) {
                if (array[j] > 0 && (i != j || array[j] > 1)) {
                    sum++;
                    found_ind = j;
                    break;
                }
            }

            if (found_ind == -1) {
                for (lli j = 0; j < k - i; j++) {
                    if (array[j] > 0 && (i != j || array[j] > 1)) {
                        found_ind = j;
                        break;
                    }
                }
            }

            if (found_ind == -1) {
                return sum;
            } else {
                array[found_ind]--;
                array[i]--;
            }
        }
    }

    return sum;
}

void read_arr() {
    lli size, k;
    cin >> size >> k;

    vector<lli> arr;
    for (lli i = 0; i < size; i++) {
        lli a;
        cin >> a;

        arr.push_back(a);
    }
    
    //Array-based algorithm
    cout << arr_based_alg(arr, k) << "\n";
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