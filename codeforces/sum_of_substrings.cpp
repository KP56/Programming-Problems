#include <bits/stdc++.h>

using namespace std;

enum State {
    ZERO,
    ONE,
    MORE
};

int min_f(vector<int> &arr, int k) {
    int min_arr_right[2];
    int min_arr_left[2];

    fill_n(min_arr_right, 2, INT_MAX);
    fill_n(min_arr_left, 2, INT_MAX);

    State states[2] = {ZERO, ZERO};

    int f = arr[0] * 10 + arr[arr.size() - 1];
    for (int i = 1; i < arr.size() - 1; i++) {
        int left_dist = i;
        int right_dist = arr.size() - i - 1;

        if (states[arr[i]] == ZERO) {
            states[arr[i]] = ONE;
        } else if (states[arr[i]] == ONE) {
            states[arr[i]] = MORE;
        }

        min_arr_right[arr[i]] = min(min_arr_right[arr[i]], right_dist);
        min_arr_left[arr[i]] = min(min_arr_left[arr[i]], left_dist);

        f += arr[i] * 11;
    }

    int new_f = f;
    for (int i = 0; i < 2; i++) {
        if (min_arr_right[i] != INT_MAX) {
            for (int j = 0; j < 2; j++) {
                if (min_arr_left[j] != INT_MAX) {
                    if (min_arr_left[j] + min_arr_right[i] <= k) {
                        if (i != j || states[i] == MORE) {
                            int right_f_decrease = 10 * (i - arr[arr.size() - 1]);
                            int left_f_decrease = j - arr[0];

                            new_f = min(new_f, f - right_f_decrease - left_f_decrease);
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        if (min_arr_right[i] <= k) {
            int right_f_decrease = 10 * (i - arr[arr.size() - 1]);
            new_f = min(new_f, f - right_f_decrease);
        }
    }

    for (int i = 0; i < 2; i++) {
        if (min_arr_left[i] <= k) {
            int left_f_decrease = i - arr[0];
            new_f = min(new_f, f - left_f_decrease);
        }
    }

    if (arr.size() - 1 <= k) {
        if (arr[arr.size() - 1] == 0) {
            int decrease = 9 * (arr[0] - arr[arr.size() - 1]);
            new_f = min(new_f, f - decrease);
        }
    }

    return new_f;
}

void read_arr() {
    int size, k;
    cin >> size >> k;

    string el;
    cin >> el;

    vector<int> arr;
    arr.reserve(size);
    for (int i = 0; i < size; i++) {
        arr.push_back(el[i] - '0');
    }

    int minf = min_f(arr, k);

    cout << minf << "\n";
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