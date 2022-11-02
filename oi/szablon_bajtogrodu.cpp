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

struct pair_hash {
    template <class T1, class T2>
    size_t operator() (const pair<T1, T2> &pair) const {
        return hash<T1>()(pair.first) ^ hash<T2>()(pair.second);
    }
};

bool my_compare(string a, string b) {
    if (a.compare(0, b.size(), b) == 0
        || b.compare(0, a.size(), a) == 0)
        return a.size() < b.size();
    else
        return a < b;
}

void dfs(int at, int origin, string current, vector<int> &path, vector<vector<pair<int,char>>> &adj_list, unordered_map<string,unordered_set<int>> &m, vector<bool> &vis) {
    vis[at] = true;
    
    if (!current.empty()) {
        copy(path.begin(),path.end(),inserter(m[current],m[current].end()));
    }

    for (auto i : adj_list[at]) {
        if (!vis[i.first]) {
            vector<int> path_cp = path;
            path_cp.pb(i.first);
            dfs(i.first, origin, current + i.second, path_cp, adj_list, m, vis);
        }
    }
}

unordered_map<string,unordered_set<int>> solve(vector<vector<pair<int,char>>> &adj_list) {
    unordered_map<string,unordered_set<int>> m;
    for (int i = 0; i < adj_list.size(); i++) {
        vector<bool> vis(adj_list.size());
        vector<int> path;
        path.pb(i);
        dfs(i, i, "", path, adj_list, m, vis);
    }

    return m;
}

//Z jakiegoś powodu na niektórych testach nie działa
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<vector<pair<int,char>>> vec(size);
    for (int i = 0; i < size - 1; i++) {
        in_i(a);
        in_i(b);
        in_str(c);
        vec[a - 1].pb({b - 1, c[0]});
        vec[b - 1].pb({a - 1, c[0]});
    }

    vector<string> answers;
    for (auto i : solve(vec)) {
        /*cout << i.first << " " << i.second.size() << " {";
        for (auto j : i.second) {
            cout << j << " ";
        }
        cout << "}" << endl;*/
        if (i.second.size() == size) {
            answers.pb(i.first);
        }
    }

    //sortuję odpowiedzi słownikowo
    sort(all(answers),my_compare);

    cout << answers.size() << endl;
    for (auto i : answers) {
        cout << i << endl;
    }
}