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

struct sum_tree {
    int n;
    vector<int> vec;

    sum_tree(int n) {
        this->n = n;
        vec = vector<int>(n*2);
    }

    int query(int l, int r) {
        int res = 0;
        r++;
        for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
            if (l&1) res += vec[l++];
            if (r&1) res += vec[--r];
        }
        return res;
    }

    void update(int p, int x) {
        for (vec[p += n] = x; p > 1; p >>= 1) vec[p >> 1] = vec[p] + vec[p^1];
    }
};

struct pair_tree {
    int n;
    vector<bool> vec;
    vector<char> chars;

    pair_tree(int n) {
        this->n = n;
        chars = vector<char>(n,'a');
        vec = vector<bool>(n*2);
    }

    bool query(int l, int r) {
        bool res = 0;
        r++;
        for (l += n, r += n; l < r; r >>= 1, l >>= 1) {
            if (l&1) res |= vec[l++];
            if (r&1) res |= vec[--r];
        }
        return res;
    }

    void update(int p, char c) {
        chars[p] = c;
        if (p < n - 1 && chars[p] > chars[p+1]) {
            bool_update(p,true);
        } else {
            bool_update(p,false);
        }
        
        if (p > 0 && chars[p] < chars[p-1]) {
            bool_update(p-1,true);
        } else if (p > 0) {
            bool_update(p-1,false);
        }
    }

    void bool_update(int p, bool x) {
        for (vec[p += n] = x; p > 1; p >>= 1) vec[p >> 1] = vec[p] | vec[p^1];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    instr(s);
    ini(q);

    vector<int> letters(26);
    for (char c : s) {
        letters[c-'a']++;
    }

    vector<sum_tree> trees(26,sum_tree(n));
    pair_tree ascending_checker(n);

    for (int i = 0; i < n; i++) {
        trees[s[i]-'a'].update(i,1);
        ascending_checker.update(i,s[i]);
    }

    for (int i = 0; i < q; i++) {
        ini(t);
        if (t == 1) {
            ini(x);
            instr(c);
            x--;
            ascending_checker.update(x,c[0]);
            trees[s[x]-'a'].update(x,0);
            letters[s[x]-'a']--;
            s[x] = c[0];
            letters[s[x]-'a']++;
            trees[s[x]-'a'].update(x,1);
        } else {
            ini(l);
            ini(r);
            l--;
            r -= 2;
            bool ascending;
            if (r < l) ascending = true;
            else ascending = !ascending_checker.query(l,r);

            vector<int> q_letters(26);
            for (int i = 0; i < 26; i++) {
                q_letters[i] = trees[i].query(l,r+1);
            }
            
            int beginning = 0;
            int end = 25;
            while (q_letters[beginning] == 0) {
                beginning++;
            }

            while (q_letters[end] == 0) {
                end--;
            }

            bool exists = true;
            for (int i = beginning + 1; i < end; i++) {
                if (q_letters[i] != letters[i]) {
                    exists = false;
                    break;
                }
            }

            if (exists && ascending) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
}