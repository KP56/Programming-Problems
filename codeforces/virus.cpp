#include <bits/stdc++.h>
#define lli long long int

using namespace std;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

void read_arr() {
    int houses, infected;
    cin >> houses >> infected;

    vector<int> arr;
    for (int i = 0; i < infected; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }
    sort(arr.begin(), arr.end());

    vector<int> distances_between;
    int prev = -1;
    for (int i : arr) {
        if (prev != -1) {
            distances_between.push_back(i - prev - 1);
        } else {
            distances_between.push_back(i - 1);
        }

        prev = i;
    }
    distances_between[0] += houses - prev;
    sort(distances_between.begin(), distances_between.end(), greater<int>());

    int saved = 0;
    int propagated_between = 0;
    for (int i : distances_between) {
        //cout << "TEST: " << i << "\n";

        saved += max(0, i - propagated_between - ((i - propagated_between) == 1 ? 0 : 1));

        propagated_between += 4;
    }

    cout << houses - saved << "\n";
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