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


struct node {
    vector<int> children;
    int first;
    int second;
    int depth;
    int root_ind;

    node(int first, int second, int depth, int root_ind) {
        this->first = first;
        this->second = second;
        this->depth = depth;
        this->root_ind = root_ind;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(length);
    in_i(depth);

    in_str(parentheses);
    int counter = 0;
    int current_depth = 0;
    for (char c : parentheses) {
        if (c == '(') {
            counter++;
            current_depth = max(current_depth,counter);
        } else {
            counter--;
        }
    }

    if (current_depth > depth) {
        vector<int> v(length);
        deque<int> s;
        for (int i = 0; i < parentheses.size(); i++) {
            char c = parentheses[i];
            if (c == '(') {
                s.pb(i);
            } else {
                int ind = s.back();
                s.pop_back();
                v[ind] = i;
            }
        }

        vector<node> forest;
        counter = 0;
        int to_keep = 0;
        for (int i = 0; i < parentheses.size(); i++) {
            char c = parentheses[i];
            if (c == '(') {
                if (!s.empty()) {
                    int a = s.back();
                    forest[a].children.pb(counter);
                }

                s.pb(counter);
                forest.emplace_back(i,v[i],s.size(),s.front());
                node n = forest[counter];
                
                int d = current_depth - n.depth + 1;
                if (d < depth) {
                    to_keep++;
                }
                counter++;
            } else {
                s.pop_back();
            }
        }

        cout << length / 2 - to_keep << endl;
    } else {
        cout << 0 << endl;
    }
}