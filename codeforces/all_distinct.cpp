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
    lli size;
    cin >> size;

    vector<lli> arr;
    for (lli i = 0; i < size; i++) {
        lli a;
        cin >> a;

        arr.push_back(a);
    }

    unordered_set<lli, custom_hash> elements;
    for (auto i : arr) {
        elements.insert(i);
    }

    cout << elements.size() - (arr.size() - elements.size()) % 2 << "\n";
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