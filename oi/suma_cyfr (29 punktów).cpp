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

//returns the next number greater or equal to this one with specified sum
string findNext(string &str, ll &current_sum, ll &sum) {
    string new_str = str;
    reverse(all(new_str));
    if (current_sum < sum) {
        ll increase = sum - current_sum;

        for (int i = 0; increase > 0; i++) {
            if (i >= new_str.size()) {
                new_str += "0";
            }

            if (increase >= '9' - new_str[i]) {
                increase -= '9' - new_str[i];
                new_str[i] = '9';
            } else {
                new_str[i] += increase;
                increase = 0;
            }
        }
    }
    reverse(all(new_str));

    return new_str;
}

//returns the next number with lower or equal sum
string findNextLowerSum(string &str, ll &current_sum) {
    string new_str = str;
    if (str.length() == 1) {
        return "10";
    } else if (str[str.length() - 1] == '0') {
        new_str.erase(--new_str.end());
        return findNextLowerSum(new_str, current_sum) + "0";
    } else {
        reverse(all(new_str));
        new_str[0] = '0';
        int i = 1;
        for (; new_str[i] == '9' && i < new_str.size(); i++) {
            new_str[i] = '0';
        }

        if (i < new_str.size()) {
            new_str[i]++;
        } else {
            new_str += "1";
        }
        reverse(all(new_str));
    }

    return new_str;
}

bool isDivisible(string &str, ll &divisible) {
    ll rest = 0;
    for (auto i : str)
        rest = ((rest * 10) + i - '0') % divisible;
    return rest == 0;
}

ll getSum(string str) {
    ll sum = 0;
    for (char c : str) {
        sum += c - '0';
    }

    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    inll(sum);
    inll(divisible);
    inll(tests);
    vector<string> ks;
    ll max_k = -1;
    vector<ll> ks_in;
    for (int i = 0; i < tests; i++) {
        inll(k);

        ks_in.pb(k);
        max_k = max(max_k, k);
    }

    string num = "1";

    ll counter = 0;
    while (num.size() <= 200) {
        ll current_sum = getSum(num);
        if (current_sum == sum && isDivisible(num, divisible)) {
            counter++;
            ks.pb(num);

            if (counter == max_k) {
                break;
            }
        }

        if (current_sum < sum) {
            num = findNext(num, current_sum, sum);
        } else {
            num = findNextLowerSum(num, current_sum);
        }
    }

    for (ll k : ks_in) {
        if (ks.size() <= k - 1) {
            cout << "NIE" << endl;
        } else {
            cout << ks[k - 1] << endl;
        }
    }
}