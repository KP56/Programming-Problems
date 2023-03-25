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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    vector<pair<string,vector<int>>> operations;
    bool has_there_been_z = false;
    bool is_z_last = true;
    int towers = 0;
    bool less_than_fifty = true;
    bool always_equal_x = true;
    for (int i = 0; i < m; i++) {
        instr(type);
        if (type == "P") {
            ini(x);
            ini(s);
            ini(a);
            x--;
            operations.pb({type,{x,s,a}});
            if (has_there_been_z) is_z_last = false;
            towers++;
            if (towers > 50) less_than_fifty = false;
        } else if (type == "U") {
            ini(x);
            x--;
            operations.pb({type,{x}});
            if (has_there_been_z) is_z_last = false;
            towers--;
        } else {
            ini(x1);
            ini(x2);
            x1--;
            x2--;
            has_there_been_z = true;
            operations.pb({type,{x1,x2}});
            if (x1 != x2) always_equal_x = false;
        }
    }

    if (n <= 0 && m <= 0) {
        //podzadanie 1
        vector<int> state(n);
        vector<vector<int>> towers(n);
        for (auto i : operations) {
            if (i.first == "P") {
                int power = i.second[1];
                for (int j = i.second[0]; j < n && power > 0; j++) {
                    state[j] += power;
                    power -= i.second[2];
                }

                power = i.second[1] - i.second[2];
                for (int j = i.second[0] - 1; j >= 0 && power > 0; j--) {
                    state[j] += power;
                    power -= i.second[2];
                }

                towers[i.second[0]] = i.second;
            } else if (i.first == "U") {
                vector<int> &tower = towers[i.second[0]];
                int power = tower[1];
                for (int j = tower[0]; j < n && power > 0; j++) {
                    state[j] -= power;
                    power -= tower[2];
                }

                power = tower[1] - tower[2];
                for (int j = tower[0] - 1; j >= 0 && power > 0; j--) {
                    state[j] -= power;
                    power -= tower[2];
                }

                towers[tower[0]] = {};
            } else {
                int res = 0;
                for (int j = i.second[0]; j <= i.second[1]; j++) {
                    res += state[j];
                }
                cout << res / (i.second[1] - i.second[0] + 1) << endl;
            }
        }
    } else if (is_z_last) {
        //podzadanie 2
        vector<vector<int>> towers(n);
        for (auto i : operations) {
            if (i.first == "P") {
                towers[i.second[0]] = i.second;
            } else if (i.first == "U") {
                towers[i.second[0]] = {};
            }
        }

        vector<int> state(n);
        int power_sum = 0;
        int power_dec = 0;
        priority_queue<pii,vector<pii>,greater<pii>> q;
        for (int i = 0; i < n; i++) {
            if (!q.empty()) {
                while (!q.empty() && q.top().first == i) {
                    power_dec -= q.top().second;
                    q.pop();
                }
            }

            if (towers[i] != vector<int>()) {
                vector<int> &tower = towers[i];
                power_sum += tower[1];
                power_dec += tower[2];
                q.push({i + tower[1] / tower[2],tower[2] - tower[1] % tower[2]});
                q.push({i + tower[1] / tower[2] + 1,tower[1] % tower[2]});
            }

            state[i] += power_sum;
            power_sum -= power_dec;
        }

        power_sum = 0;
        power_dec = 0;
        priority_queue<pii,vector<pii>> q2;
        for (int i = n - 1; i >= 0; i--) {
            if (!q2.empty()) {
                while (!q2.empty() && q2.top().first == i) {
                    power_dec -= q2.top().second;
                    q2.pop();
                }
            }

            if (towers[i] != vector<int>()) {
                vector<int> &tower = towers[i];
                power_sum += tower[1];
                power_dec += tower[2];
                q2.push({i - tower[1] / tower[2],tower[2] - tower[1] % tower[2]});
                q2.push({i - tower[1] / tower[2] - 1,tower[1] % tower[2]});
            }

            state[i] += power_sum;
            power_sum -= power_dec;
        }

        for (auto i : towers) {
            if (!i.empty()) {
                state[i[0]] -= i[1];
            }
        }

        vector<int> state_prefix;
        int prev = 0;
        for (int i : state) {
            state_prefix.pb(i + prev);
            prev += i;
        }

        for (auto i : operations) {
            if (i.first == "Z") {
                cout << (state_prefix[i.second[1]] - (i.second[0] == 0 ? 0 : state_prefix[i.second[0] - 1])) / (i.second[1] - i.second[0] + 1) << endl;
            }
        }
    }
}