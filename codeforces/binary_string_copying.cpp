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

struct hashFunction
{
  size_t operator()(const pair<int , 
                    int> &x) const
  {
    return x.first ^ x.second;
  }
};

int brute(string &s, vector<pii> &vec) {
    unordered_set<string> uset;
    for (pii i : vec) {
        string cp = s;
        sort(cp.begin() + i.first, cp.begin() + i.second + 1);
        uset.insert(cp);
    }

    return uset.size();
}

void readCaseData() {
    ini(n);
    //int n = rand() % 10 + 1;
    ini(m);
    //int m = rand() % 10 + 1;

    instr(s);
    /*string s = "";
    for (int i = 0; i < n; i++) {
        int r_el = rand() % 2;
        char c = r_el + '0';
        string s2(1,c);
        s += s2;
    }*/

    vector<int> beginning_of_ones(n);
    int prev_one = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (prev_one == -1) prev_one = i;

            beginning_of_ones[i] = prev_one;
        } else {
            prev_one = -1;
        }
    }

    vector<int> end_of_zeros(n);
    int prev_zero = -1;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            if (prev_zero == -1) prev_zero = i;

            end_of_zeros[i] = prev_zero;
        } else {
            prev_zero = -1;
        }
    }

    map<int,int> range_set;
    int range_begin = 0;
    bool found_one = false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0' && found_one) {
            range_set[range_begin] = i-1;
            range_begin = i;
            found_one = false;
        } else if (s[i] == '1' && !found_one) {
            found_one = true;
        }
    }
    
    range_set[range_begin] = s.length()-1;

    vector<pii> brute_arr;
    unordered_set<pii,hashFunction> diff;
    bool any_inside = false;
    for (int i = 0; i < m; i++) {
        ini(x);
        //int x = rand() % n + 1;
        ini(y);
        //int y = rand() % (n - x + 1) + x;

        x--;
        y--;
        brute_arr.pb({x,y});

        if (s[y] == '1') {
            y = max(beginning_of_ones[y]-1, x);
        }
        
        if (s[x] == '0') {
            x = min(end_of_zeros[x]+1, y);
        }

        auto it = range_set.upper_bound(x);
        if (it != range_set.end() && y >= it->first) {
            diff.insert({x,y});
        } else {
            any_inside = true;
        }
    }

    int res = any_inside + diff.size();
    /*int brute_res = brute(s, brute_arr);

    if (brute_res != res) {
        int test = 0;
    }*/

    cout << res << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}