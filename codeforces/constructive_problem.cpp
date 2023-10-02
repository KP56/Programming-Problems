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

int findMEX(vector<int> vec) {
    sort(all(vec));

    if (vec[0] != 0) {
        return 0;
    }

    int prev = -1;
    for (int i : vec) {
        if (prev != -1) {
            if (i-prev != 0 && i-prev != 1) {
                return prev+1;
            }
        }

        prev = i;
    }

    return vec[vec.size() - 1] + 1;
}

bool brute(vector<int> &vec) {
    int mex = findMEX(vec);
    for (int k = 0; k < 10; k++) {
        for (int l = 0; l < vec.size(); l++) {
            vector<int> cp = vec;
            for (int r = l; r < vec.size(); r++) {
                cp[r] = k;

                if (findMEX(cp) == mex + 1) {
                    return true;
                }
            }
        }
    }

    return false;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 5 + 1;

    vector<int> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 5;
        vec.pb(a);
    }

    vector<int> original = vec;

    int mex = findMEX(vec);

    int a = INT_MAX;
    int b = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (vec[i] == mex+1) {
            a = min(i,a);
            b = max(i,b);
        }
    }

    if (a == INT_MAX) {
        unordered_map<int,int> counts;

        for (int i = 0; i < n; i++) {
            if (vec[i] >= mex) {
                /*if (!brute(original)) {
                    int test = 0;
                }*/

                cout << "YES" << endl;
                return;
            }

            counts[vec[i]]++;

            if (counts[vec[i]] >= 2) {
                /*if (!brute(original)) {
                    int test = 0;
                }*/

                cout << "YES" << endl;
                return;
            }
        }
    } else {
        for (int i = a; i <= b; i++) {
            vec[i] = mex;
        }

        if (findMEX(vec) == mex+1) {
            /*if (!brute(original)) {
                int test = 0;
            }*/

            cout << "YES" << endl;
            return;
        }
    }

    /*if (brute(original)) {
        int test = 0;
    }*/

    cout << "NO" << endl;
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