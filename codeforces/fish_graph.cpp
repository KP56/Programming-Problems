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

deque<int> ans;
void dfs(int at, deque<int> &deq, vector<bool> &vis, vector<vector<int>> &graph, vector<bool> &is_connected, bool connected_so_far) {
    if (!ans.empty()) {
        return;
    }

    vis[at] = true;
    deq.pf(at);

    if (connected_so_far && is_connected[at]) {
        ans = deq;
    } else if (is_connected[at]) {
        connected_so_far = true;
    }

    for (int i : graph[at]) {
        if (!vis[i]) {
            dfs(i, deq, vis, graph, is_connected, connected_so_far);
        }
    }

    deq.pop_front();
}

void readCaseData() {
    ini(n);
    ini(m);
    ans = {};

    vector<vector<int>> graph(n);
    for (int i = 0; i < m; i++) {
        ini(a);
        ini(b);
        a--;
        b--;
        graph[a].pb(b);
        graph[b].pb(a);
    }

    for (int i = 0; i < n; i++) {
        if (graph[i].size() >= 4) {
            deque<int> deq;
            vector<bool> vis(n);
            vector<bool> is_connected(n);
            for (int j : graph[i]) {
                is_connected[j] = true;
            }
            dfs(i, deq, vis, graph, is_connected, false);
            if (!ans.empty()) {
                unordered_set<int, custom_hash> in_cycle;
                cout << "YES" << endl;
                cout << ans.size() + 2 << endl;
                int prev = -1;
                for (int v : ans) {
                    in_cycle.insert(v);

                    if (prev != -1) {
                        cout << prev + 1 << " " << v + 1 << endl;
                    }

                    prev = v;
                }
                cout << ans[ans.size() - 1] + 1 << " " << ans[0] + 1 << endl;

                int counter = 0;
                for (int v : graph[i]) {
                    if (in_cycle.find(v) == in_cycle.end()) {
                        cout << i + 1 << " " << v + 1 << endl;
                        counter++;

                        if (counter == 2) {
                            break;
                        }
                    }
                }

                return;
            }
        }
    }

    cout << "NO" << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}