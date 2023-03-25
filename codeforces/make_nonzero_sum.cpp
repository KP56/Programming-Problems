#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define inll(x) ll x; in(x)
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

//https://codeforces.com/blog/entry/62393
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

void readCaseData() {
    ini(size);

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        ini(el);
        arr.pb(el);
    }

    int other_than_zero = 0;
    for (int i : arr) if (i != 0) other_than_zero++;

    if (other_than_zero % 2 == 1) {
        cout << -1 << endl;
        return;
    }

    int count_ones = 0;
    for (int i : arr) if (i == 1) count_ones++;

    vector<pii> solution;
    if (count_ones == other_than_zero / 2) {
        for (int i = 0; i < size; i++) {
            solution.pb({i + 1, i + 1});
        }
    } else if (count_ones > other_than_zero / 2) {
        bool prev = true;
        for (int i = 0; i < size - 1; i += 1) {
            if (((arr[i] == -1 && arr[i + 1] == 1) || (arr[i] == 1 && arr[i + 1] == 1) || (arr[i] == 0 && arr[i + 1] == 1)) && count_ones > other_than_zero / 2) {
                if (prev && !solution.empty()) solution.erase(--solution.end());

                solution.pb({i + 1, i + 2});
                count_ones--;
                i++;
                prev = false;
            } else {
                if (prev && !solution.empty()) solution.erase(--solution.end());

                solution.pb({i + 1, i + 1});
                solution.pb({i + 2, i + 2});
                prev = true;
            }
        }
    } else {
        bool prev = true;
        for (int i = 0; i < size - 1; i += 1) {
            if (((arr[i] == 1 && arr[i + 1] == -1) || (arr[i] == -1 && arr[i + 1] == -1) || (arr[i] == 0 && arr[i + 1] == -1)) && count_ones < other_than_zero / 2) {
                if (prev && !solution.empty()) solution.erase(--solution.end());

                solution.pb({i + 1, i + 2});
                count_ones++;
                i++;
                prev = false;
            } else {
                if (prev && !solution.empty()) solution.erase(--solution.end());

                solution.pb({i + 1, i + 1});
                solution.pb({i + 2, i + 2});
                prev = true;
            }
        }
    }

    if (solution[solution.size() - 1].second < size) {
        solution.pb({size, size});
    }

    cout << solution.size() << endl;
    for (pii p : solution) {
        cout << p.first << " " << p.second << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}