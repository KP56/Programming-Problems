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

struct compare {
    bool operator() (pair<pii,int> &a, pair<pii,int> &b) const {
        if (a.first.first < b.first.first) {
            return true;
        } else if (a.first.first > b.first.first) {
            return false;
        } else {
            if (a.first.second > b.first.second) {
                return true;
            } else if (a.first.second < b.first.second) {
                return false;
            } else {
                return true;
            }
        }
    }
};

struct segment_tree {
    vector<pii> tree;
    int n;

    segment_tree(int n) {
        tree = vector<pii>(2*n);
        this->n = n;
    }

    void update(int idx, int x) {
        tree[idx + n] = {x,idx};

        for (idx = idx + n; idx > 1; idx >>= 1) {
            tree[idx >> 1] = min(tree[idx],tree[idx^1]);
        }
    }

    pii query(int l, int r) {
        r++;

        pii res = {INT_MAX,INT_MAX};
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = min(res,tree[l++]);
            if (r&1) res = min(res,tree[--r]);
        }

        return res;
    }
};

int dfs_iterate(int at, vector<bool> &vis, vector<vector<int>> &tree, segment_tree &r_tree, vector<pair<pii,int>> &ranges, vector<bool> &chosen) {
    vis[at] = true;

    int found_so_far = 0;
    for (int i : tree[at]) {
        if (!vis[i]) {
            found_so_far += dfs_iterate(i,vis,tree,r_tree,ranges,chosen);
        }
    }

    // po skończeniu iteracji przez wszystkie poniższe wierzchołki, dokonujemy wyboru pracowników
    // naszym celem jest odnalezienie najmniejszych pracowników w zakresie
    // zastosujmy w tym celu drzewo przedziałowe

    int found_so_far_cp = found_so_far;
    for (int i = 0; i < ranges[at].second - found_so_far_cp; i++) {
        pii res = r_tree.query(ranges[at].first.first - 1, ranges[at].first.second - 1);
        chosen[res.second] = true;
        r_tree.update(res.second,INT_MAX);

        found_so_far++;
    }

    return found_so_far;
}

int bruteforce(int i, vector<bool> &chosen, vector<int> &costs, vector<pair<pii,int>> &ranges) {
    if (i == chosen.size()) {
        for (auto &range : ranges) {
            int in_range = 0;
            for (int j = range.first.first-1; j <= range.first.second-1; j++) {
                in_range += chosen[j];
            }

            if (in_range < range.second) {
                return INT_MAX;
            }
        }

        int cost_ret = 0;
        for (int j = 0; j < chosen.size(); j++) {
            cost_ret += costs[j] * chosen[j];
        }

        return cost_ret;
    }

    vector<bool> chosen_cp = chosen;
    chosen_cp[i] = true;
    int res = bruteforce(i+1,chosen_cp,costs,ranges);
    res = min(res,bruteforce(i+1,chosen,costs,ranges));

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 6 + 1;
    vector<int> costs;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 5 + 1;
        costs.pb(a);
    }

    ini(m);
    //int m = rand() % 5 + 1;
    vector<pair<pii,int>> ranges;
    for (int i = 0; i < m; i++) {
        ini(from);
        //int from = rand() % n + 1;
        ini(to);
        //int to = rand() % (n - from + 1) + from;
        ini(req);
        //int req = rand() % (to - from + 1) + 1;

        ranges.pb({{from,to},req});
    }

    // weryfikacja pod bruteforce w której sprawdzamy czy jakieś zakresy się nie przecinają
    /*sort(all(ranges));
    bool found = false;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < i; j++) {
            if (ranges[j].first.first <= ranges[i].first.second && ranges[i].first.second > ranges[j].first.second) {
                found = true;
            }
        }
    }

    if (found) {
        continue;
    }*/

    sort(all(ranges),compare());

    // tworzymy drzewo zakresów
    vector<vector<int>> tree(m);
    // niech j będzie potencjalnym parentem
    stack<int> parents;
    for (int i = 0; i < ranges.size(); i++) {
        if (!parents.empty() && ranges[i].first.first > ranges[parents.top()].first.first && ranges[i].first.second > ranges[parents.top()].first.second) {
            // w tym przypadku zakres jest po prawej od górnego, oznaczając zmianę parenta
            while (!parents.empty() && ranges[i].first.first > ranges[parents.top()].first.first && ranges[i].first.second > ranges[parents.top()].first.second) {
                parents.pop();
            }
        }
        
        if (!parents.empty()) {
            tree[i].pb(parents.top());
            tree[parents.top()].pb(i);
        }

        // teraz ten zakres będzie potencjalnie nowym parentem
        parents.push(i);
    }

    segment_tree r_tree(n);
    for (int i = 0; i < n; i++) {
        r_tree.update(i,costs[i]);
    }

    vector<bool> vis(m);
    vector<bool> chosen(n);
    for (int i = 0; i < m; i++) {
        if (!vis[i]) {
            dfs_iterate(i,vis,tree,r_tree,ranges,chosen);
        }
    }

    int total_cost = 0;
    int selected = 0;
    for (int i = 0; i < n; i++) {
        total_cost += chosen[i] * costs[i];
        selected += chosen[i];
    }

    cout << total_cost << endl;
    cout << selected << endl;

    for (int i = 0; i < n; i++) {
        if (chosen[i]) cout << i + 1 << " ";
    }
    cout << endl;

    /*chosen = vector<bool>(n);
    int brute_res = bruteforce(0,chosen,costs,ranges);

    if (brute_res != total_cost) {
        int test = 0;
    }*/
}