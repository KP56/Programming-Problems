#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lli = long long int;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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
    in_i(size);

    unordered_set<string> words1;
    for (int i = 0; i < size; i++) {
        in_str(el);
        words1.insert(el);
    }

    unordered_set<string> words2;
    for (int i = 0; i < size; i++) {
        in_str(el);
        words2.insert(el);
    }

    unordered_set<string> words3;
    for (int i = 0; i < size; i++) {
        in_str(el);
        words3.insert(el);
    }

    int points[3] = {0,0,0};
    for (string str : words1) {
        bool found2 = false;
        bool found3 = false;

        auto it2 = words2.find(str);
        if (it2 != words2.end()) {
            found2 = true;
        }

        auto it3 = words3.find(str);
        if (it3 != words3.end()) {
            found3 = true;
        }

        if (!found2 && !found3) {
            points[0] += 3;
        } else if (found2 && !found3) {
            points[0]++;
            points[1]++;

            words2.erase(it2);
        } else if (!found2 && found3) {
            points[0]++;
            points[2]++;

            words3.erase(it3);
        } else {
            words2.erase(it2);
            words3.erase(it3);
        }
    }

    for (string str : words2) {
        bool found1 = false;
        bool found3 = false;

        auto it1 = words1.find(str);
        if (it1 != words1.end()) {
            found1 = true;
        }

        auto it3 = words3.find(str);
        if (it3 != words3.end()) {
            found3 = true;
        }

        if (!found1 && !found3) {
            points[1] += 3;
        } else if (found1 && !found3) {
            points[1]++;
            points[0]++;
        } else if (!found1 && found3) {
            points[1]++;
            points[2]++;

            words3.erase(it3);
        } else {
            words3.erase(it3);
        }
    }

    points[2] += words3.size() * 3;

    cout << points[0] << " " << points[1] << " " << points[2] << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}