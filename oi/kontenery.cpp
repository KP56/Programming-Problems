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

struct range_tree {
    vector<int> vec;
    int n;

    range_tree(int n) {
        this->n = n;
        vec = vector<int>(n * 2);
    }

    void update(int l, int r) {
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) vec[l++]++;
            if (r & 1) vec[--r]++;
        }
    }

    int query(int p) {
        int res = 0;
        for (p += n; p > 0; p >>= 1) res += vec[p];
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    int prev_cycle = -1;
    bool task_two = true;
    vector<vector<int>> data;
    for (int i = 0; i < k; i++) {
        ini(pos);
        ini(number);
        ini(cycle);
        pos--;

        if (prev_cycle != -1 && cycle != prev_cycle) task_two = false;
        prev_cycle = cycle;

        data.pb({pos,number,cycle});
    }

    if (!task_two) {
        vector<int> solution(n);
        for (auto i : data) {
            for (int j = 0; j < i[1]; j++) {
                int pos = j * i[2] + i[0];
                solution[pos]++;
            }
        }

        for (int i : solution) {
            cout << i << " ";
        }
        cout << endl;
    } else {
        vector<range_tree> trees(prev_cycle,range_tree(n / prev_cycle + (n % prev_cycle > 0)));
        for (auto i : data) {
            range_tree &tree = trees[i[0] % prev_cycle];
            int tree_index = i[0] / prev_cycle;
            int end_index = tree_index + i[1] - 1;
            tree.update(tree_index,end_index + 1);
        }

        for (int i = 0; i < n; i++) {
            int tree_index = i / prev_cycle;
            int tree = i % prev_cycle;

            cout << trees[tree].query(tree_index) << " ";
        }
        cout << endl;
    }
}