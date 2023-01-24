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
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
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

vector<int> divisorsOfNumber(int x) {
    vector<int> ret;
    for (int i = 1; i <= sqrt(x); i++) {
        if (x % i == 0) {
            ret.push_back(i);
            if (x / i != i) {
                ret.push_back(x / i);
            }
        }
    }

    return ret;
}

void readCaseData() {
    in_i(size);
    in_i(sum);

    if (sum % size == 0) {
        int nums = sum / size;
        
        cout << "Yes" << endl;
        for (int i = 0; i < size; i++) {
            cout << nums << " ";
        }
        cout << endl;

        return;
    } else if (sum % 2 == 1 && size % 2 == 0) {
        cout << "No" << endl;
        return;
    }

    int real_size = size / 2;
    int real_sum = sum / 2;

    if (size < sum) {
        if (size % 2 == 1) {
            int num = sum - (size - 1);

            vector<int> divisors = divisorsOfNumber(num);

            for (int i : divisors) {
                if (i % 2 == 1) {
                    if (i < size) {
                        cout << "Yes" << endl;
                        int to_display = num/i;
                        for (int j = 0; j < i; j++) {
                            cout << to_display << " ";
                        }

                        for (int j = 0; j < size - i; j++) {
                            cout << "1 ";
                        }

                        return;
                    }                    
                }
            }

            cout << "No" << endl;
            return;
        } else {
            int num = sum - (real_size - 1) * 2;

            cout << "Yes" << endl;
            for (int i = 0; i < real_size - 1; i++) {
                cout << "1 1 ";
            }

            cout << num / 2 << " " << num / 2 << endl;
        }

        return;
    } else {
        cout << "No" << endl;
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}