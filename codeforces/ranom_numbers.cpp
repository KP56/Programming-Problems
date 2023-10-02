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

int compute(string &s) {
    vector<int> powers = {1, 10, 100, 1000, 10000};
    int sum = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        bool negative = false;
        for (int j = i + 1; j < s.length(); j++) {
            if (s[j] > c) {
                negative = true;
                break;
            }
        }
        if (negative) sum -= powers[c - 'A'];
        else sum += powers[c - 'A'];
    }

    return sum;
}

int brute(string &s) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < 5; j++) {
            string cp = s;
            cp[i] = 'A' + j;
            res = max(res, compute(cp));
        }
    }

    return res;
}

string randomstring(int length) {
    string s = "";
    for (int i = 0; i < length; i++) {
        char c = 'A' + (rand() % 5);
        string s2(1, c);
        s += s2;
    }

    return s;
}

void readCaseData() {
    instr(s);
    /*string s = "";
    int c = rand() % 1000;
    for (int i = 0; i < 40; i++) {
        if (i == c) {
            string ab(1, 'A' + (rand() % 5));
            s += ab;
        } else {
            s += "D";
        }
    }*/
    //string s = randomstring(rand() % 100 + 1);

    vector<int> powers = {1, 10, 100, 1000, 10000};

    vector<int> furthest(5,-1);
    for (int i = 0; i < s.length(); i++) {
        furthest[s[i] - 'A'] = i;
    }

    vector<int> negative(5,-1);
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            negative[i] = max(negative[i], furthest[j]);
        }
    }

    vector<vector<bool>> exists_left(s.length(), vector<bool>(5));
    for (int i = 1; i < s.length(); i++) {
        for (int j = 0; j < 5; j++) {
            exists_left[i][j] = exists_left[i-1][j];
        }
        exists_left[i][s[i-1] - 'A'] = true;
    }

    vector<vector<bool>> exists_right(s.length(), vector<bool>(5));
    for (int i = s.length() - 2; i >= 0; i--) {
        for (int j = 0; j < 5; j++) {
            exists_right[i][j] = exists_right[i+1][j];
        }
        exists_right[i][s[i+1] - 'A'] = true;
    }

    vector<vector<int>> prefix(5, vector<int>(s.length()));
    for (int i = 0; i < s.length(); i++) {
        bool exists_greater = false;
        for (int j = s[i] - 'A' + 1; j < 5; j++) {
            if (exists_right[i][j]) {
                exists_greater = true;
                break;
            }
        }

        prefix[s[i] - 'A'][i] = ((i != 0) ? prefix[s[i] - 'A'][i - 1] : 0) + (exists_greater ? -powers[s[i] - 'A'] : powers[s[i] - 'A']);
        for (int j = 0; j < 5; j++) {
            if (j != s[i] - 'A') {
                prefix[j][i] = ((i != 0) ? prefix[j][i - 1] : 0);
            }
        }
    }

    int initial_sum = 0;
    vector<int> initial_values(s.length());
    for (int i = 0; i < s.length(); i++) {
        bool negative = false;
        for (int j = s[i] - 'A' + 1; j < 5; j++) {
            if (exists_right[i][j]) {
                negative = true;
                break;
            }
        }

        if (negative) {
            initial_values[i] -= powers[s[i] - 'A'];
        } else {
            initial_values[i] += powers[s[i] - 'A'];
        }

        initial_sum += initial_values[i];
    }

    int sum = initial_sum;
    for (int i = 0; i < s.length(); i++) {
        for (int j = 0; j < 5; j++) {
            bool exists = false;
            bool exists_greater = false;
            for (int k = j; k < 5; k++) {
                if (exists_right[i][k]) {
                    exists = true;
                    if (k != j) {
                        exists_greater = true;
                        break;
                    }
                }
            }

            int x = 0;
            for (int k = 0; k < 5; k++) {
                if (k < j && negative[k] == -1) {
                    x -= 2*(i == 0 ? 0 : prefix[k][i-1]);
                    continue;
                }

                if (k < j && i > negative[k]) {
                    x -= 2*(prefix[k][i-1]-prefix[k][negative[k]]);
                }

                if (k >= j && i == negative[k]) {
                    bool found = false;
                    for (int y = i - 1; y >= 0; y--) {
                        if (s[y] - 'A' > k) {
                            x -= 2*(prefix[k][negative[k]]-prefix[k][y]);
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        x -= 2*(prefix[k][negative[k]]);
                    }
                }
            }

            if (exists_greater) {
                sum = max(sum, initial_sum - initial_values[i] - powers[j] + x);
            } else {
                sum = max(sum, initial_sum - initial_values[i] + powers[j] + x);
            }
        }
    }

    /*int brute_sum = brute(s);
    if (sum != brute_sum) {
        int a = 0;
    }*/
    /*if (sum < 0) {
        int a = 0;
    }*/
    cout << sum << endl;
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