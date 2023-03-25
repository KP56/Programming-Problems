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

const int N = 5e5+10;
const int M = 5e3+10;

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

int cti(char c) {
    return c - 'a';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    vector<pii> characters(26,{-1,0});
    vector<string> vec;
    vector<vector<pii>> adj_list;
    for (int i = 0; i < n; i++) {
        instr(str);
        vec.pb(str);
        int current = characters[cti(str[0])].first;
        characters[cti(str[0])].second++;
        int prev = -1;
        for (int j = 1; j < str.length(); j++) {
            if (current == -1) {
                if (prev == -1) {
                    characters[cti(str[0])].first = adj_list.size();
                } else {
                    adj_list[prev][cti(str[j - 1])].first = adj_list.size();
                }
                vector<pii> char_new(26,{-1,0});
                current = adj_list.size();
                adj_list.pb(char_new);
            }
            prev = current;
            adj_list[current][cti(str[j])].second++;
            current = adj_list[current][cti(str[j])].first;
        }
    }

    for (string &s : vec) {
        int current = -1;
        int max_n = 0;
        for (int i = 0; i < s.length(); i++) {
            int char_ind = cti(s[i]);
            if (current == -1) {
                if (characters[char_ind].second > 1) {
                    max_n = i + 1;
                }
                current = characters[char_ind].first;
            } else {
                if (adj_list[current][char_ind].second > 1) {
                    max_n = i + 1;
                }
                current = adj_list[current][char_ind].first;
            }
        }

        cout << max_n << endl;
    }
}