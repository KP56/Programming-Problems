#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

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

bool canGetToZero(int at, vector<int> &arr, unordered_set<int> &visited, vector<bool> &sol) {
    if (at < 0 || at >= arr.size()) {
        return false;
    }
    visited.insert(at);

    if (at + arr[at] == 0) {
        return sol[at] = true;
    }

    if (visited.find(at + arr[at]) == visited.end() && canGetToZero(at + arr[at], arr, visited, sol)) {
        return sol[at] = true;
    }

    if (at + arr[at] < 0 || at + arr[at] >= arr.size()) {
        return sol[at] = false;
    }

    return sol[at] = sol[at + arr[at]];
}

bool canGetToEnd(int at, vector<int> &arr, unordered_set<int> &visited, vector<bool> &sol) {
    if (at < 0 || at >= arr.size()) {
        return true;
    }
    visited.insert(at);

    if (visited.find(at + arr[at]) == visited.end() && canGetToEnd(at + arr[at], arr, visited, sol)) {
        return sol[at] = true;
    }

    return sol[at] = sol[at + arr[at]];
}

int connectedTo(int at, vector<int> &arr, unordered_set<int> &connected, unordered_set<int> &visited, vector<int> &sol) {
    if (at < 0 || at >= arr.size()) {
        return -1;
    }

    if (visited.find(at) != visited.end()) {
        return sol[at];
    }

    visited.insert(at);

    if (connected.find(at) != connected.end()) {
        return sol[at] = at;
    }

    return sol[at] = connectedTo(arr[at] + at, arr, connected, visited, sol);
}

int bruteforce(int n, vector<int> arr) {
    int res = 0;

    for (int x = 0; x < n; x++) {
        for (int y = -n; y <= n; y++) {
            vector<int> cp = arr;
            cp[x] = y;

            unordered_set<int> visited;
            int current = 0;
            while (visited.find(current) == visited.end()) {
                if (current < 0 || current >= n) {
                    res++;
                    break;
                }

                visited.insert(current);
                current += cp[current];
            }
        }
    }

    return res;
}

void readCaseData() {
    ini(n);
    //int n = 50;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 101 - n;
        arr.pb(el);
    }

    vector<vector<int>> rev_arr(n);
    for (int i = 0; i < n; i++) {
        if (arr[i] + i < n && arr[i] + i >= 0) {
            rev_arr[arr[i] + i].pb(-arr[i]);
        }
    }

    unordered_set<int> visited;
    int current = 0;
    bool contains_end = false;
    int m = 0;
    while (visited.find(current) == visited.end()) {
        if (current < 0 || current >= n) {
            contains_end = true;
            break;
        }

        m++;
        visited.insert(current);
        current += arr[current];
    }

    vector<bool> can_get_to_zero(n);
    unordered_set<int> visited2;
    can_get_to_zero[0] = true;
    for (int i = 0; i < n; i++) {
        if (rev_arr[i].empty()) {
            canGetToZero(i, arr, visited2, can_get_to_zero);
        }
    }
    can_get_to_zero[0] = true;

    vector<bool> can_get_to_end(n);
    unordered_set<int> visited3;
    for (int i = 0; i < n; i++) {
        if (rev_arr[i].empty()) {
            canGetToEnd(i, arr, visited3, can_get_to_end);
        }
    }

    int k = 0;
    if (contains_end) {
        vector<int> lower_by(n);
        vector<int> sol(n,-1);
        unordered_set<int> visited4;
        for (int i = 0; i < n; i++) {
            if (!can_get_to_zero[i] && visited.find(i) == visited.end() && can_get_to_end[i]) {
                k++;
                int node = connectedTo(i, arr, visited, visited4, sol);
                if (node != -1) {
                    lower_by[node]++;
                }
            }
        }

        int res = (2*n+1)*(n-m) + m*(m-1)/2;
        
        current = 0;
        while (current >= 0 && current < n) {
            k -= lower_by[current];
            res += n + 1 + k;

            current += arr[current];
        }

        /*if (res != bruteforce(n, arr)) {
            cout << "test" << endl;
        }*/

        cout << res << endl;
    } else {
        for (int i = 0; i < n; i++) {
            if (!can_get_to_zero[i] && visited.find(i) == visited.end() && can_get_to_end[i]) {
                k++;
            }
        }

        /*if ((n+1+k)*m != bruteforce(n, arr)) {
            cout << "test" << endl;
        }*/
        cout << (n+1+k)*m << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}