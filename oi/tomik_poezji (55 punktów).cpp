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
    ini(s);

    unordered_map<int,vector<int>,custom_hash> values;
    for (int i = 0; i < n; i++) {
        ini(a);
        a++;
        a %= s;
        values[a].pb(i + 1);
    }
    
    vector<vector<int>> count_queue(n + 1);
    for (auto i : values) {
        count_queue[i.second.size()].pb(i.first);
    }

    int current = 0;
    int res = 0;
    vector<int> res_vec;
    int size = n;
    int queue_index = n;
    int second_queue_index = n;
    while (queue_index >= 0) {
        while (count_queue[queue_index].empty() && queue_index >= 0) queue_index--;
        while (second_queue_index >= 0 && (count_queue[second_queue_index].empty() || second_queue_index >= queue_index)
                && count_queue[second_queue_index].size() <= 1) second_queue_index--;
        if (queue_index < 0) break;

        pii best = {queue_index,*(--count_queue[queue_index].end())};
        int erase_index = 0;
        if ((current + best.second) % s == s - 1) {
            if (second_queue_index == -1 && best.first > 1) {
                res++;
                current++;
            } else {
                if (size > 1) {
                    if (count_queue[queue_index].size() > 1) {
                        best = {queue_index,*(--(--count_queue[queue_index].end()))};
                        erase_index++;
                    } else {
                        //tutaj muszę mieć drugi queue_index który wskazuje drugi element od końca
                        best = {second_queue_index,*(--count_queue[second_queue_index].end())};
                    }
                }
            }
        }

        current = (current + best.second) % s;
        count_queue[best.first].erase(count_queue[best.first].end() - 1 - erase_index);
        size--;
        res_vec.pb(best.second);
        if (best.first != 1) {
            best.first--;
            count_queue[best.first].pb(best.second);
        }
    }

    cout << res << endl;
    for (int i : res_vec) {
        cout << *values[i].begin() << " ";
        values[i].erase(values[i].begin());
    }
    cout << endl;
}