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

vector<int> solve(vector<int> &right_houses, vector<int> &left_houses, vector<int> &color_vec, int houses, int colors) {
    unordered_set<int> candidates;
    for (int i = 0; i < colors; i++) {
        int left_house = INT_MAX;
        int right_house = INT_MIN;
        for (int j = 0; j < houses; j++) {
            if (color_vec[j] == i) {
                left_house = min(j, left_house);
                right_house = max(j, right_house);
            }
        }

        if (right_house == left_house || left_house == INT_MAX) {
            continue;
        }

        queue<int> right_queue;
        for (int j : right_houses) {
            right_queue.push(j);
        }

        int right_index = -1;
        for (int j = left_house + 1; j < right_house; j++) {
            if (color_vec[j] == right_queue.front()) {
                right_queue.pop();
                if (right_queue.empty()) {
                    right_index = j;
                    break;
                }
            }
        }

        queue<int> left_queue;
        for (int j : left_houses) {
            left_queue.push(j);
        }

        int left_index = -1;
        for (int j = right_house - 1; j > left_house; j--) {
            if (color_vec[j] == left_queue.front()) {
                left_queue.pop();
                if (left_queue.empty()) {
                    left_index = j;
                    break;
                }
            }
        }

        if (right_index == -1 || left_index == -1) {
            continue;
        }

        for (int j = right_index; j <= left_index; j++) {
            if (color_vec[j] == right_houses[right_houses.size() - 1]) {
                candidates.insert(j + 1);
            }
        }
    }

    vector<int> vec;
    for (int i : candidates) {
        vec.pb(i);
    }
    sort(all(vec));

    return vec;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(houses);
    ini(colors);

    vector<int> color_vec;
    for (int i = 0; i < houses; i++) {
        ini(c);
        c--;
        color_vec.pb(c);
    }

    ini(bitek_houses);
    ini(bajtek_houses);

    vector<int> right_houses;
    for (int i = 0; i < bitek_houses; i++) {
        ini(x);
        x--;
        right_houses.pb(x);
    }

    vector<int> left_houses;
    for (int i = 0; i < bajtek_houses; i++) {
        ini(y);
        y--;
        left_houses.pb(y);
    }

    vector<int> sol = solve(right_houses, left_houses, color_vec, houses, colors);
    cout << sol.size() << endl;
    for (int i : sol) {
        cout << i << " ";
    }
    cout << endl;
}