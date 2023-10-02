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

void dfs(int at, unordered_set<int,custom_hash> &component, vector<bool> &vis, vector<int> &graph) {
    vis[at] = true;
    component.insert(at);

    if (!vis[graph[at]]) {
        dfs(graph[at], component, vis, graph);
    }
}

vector<unordered_set<int,custom_hash>> components(vector<int> &graph) {
    vector<bool> vis(graph.size());
    vector<unordered_set<int,custom_hash>> components;
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            unordered_set<int,custom_hash> component;
            dfs(i, component, vis, graph);
            components.pb(component);
        }
    }

    return components;
}

int solve(vector<int> arr, vector<int> dest) {
    vector<int> rev_dest(arr.size());
    for (int i = 0; i < dest.size(); i++) {
        rev_dest[dest[i]] = i;
    }
    vector<int> graph(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        graph[i] = rev_dest[arr[i]];
    }

    auto comp = components(graph);
    int res = 0;
    for (auto i : comp) {
        res += i.size() - 1;
    }

    return res;
}

void readCaseData() {
    ini(n);
    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(a);
        a--;
        arr.pb(a);
    }

    vector<int> option = arr;
    sort(all(option));
    
    vector<int> rev_dest(arr.size());
    vector<int> rev_arr(arr.size());
    for (int i = 0; i < option.size(); i++) {
        rev_dest[option[i]] = i;
        rev_arr[arr[i]] = i;
    }
    vector<int> graph(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        graph[i] = rev_dest[arr[i]];
    }

    auto comp = components(graph);
    bool broken = false;
    for (auto i : comp) {
        for (auto j : i) {
            if (rev_arr[j] != arr.size() - 1 && i.find(arr[rev_arr[j]+1]) != i.end()) {
                broken = true;
                break;
            }
        }

        if (broken) {
            break;
        }
    }

    if (!broken) {
        cout << solve(arr, option) + 1 << endl;
    } else {
        cout << solve(arr, option) - 1 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}