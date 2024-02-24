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

bool cycle_exists = false;
void dfs(int at, vector<int> &vis, vector<vector<int>> &graph, int k) {
    vis[at] = k;

    for (int i : graph[at]) {
        if (vis[i] == -1) {
            dfs(i,vis,graph,k);
        } else if (vis[i] == k) {
            cycle_exists = true;
        }
    }
}

int longest_path(int at, vector<bool> &vis, vector<vector<int>> &graph) {
    vis[at] = true;

    int longest = 0;
    for (int i : graph[at]) {
        if (!vis[i]) {
            longest = max(longest, longest_path(i,vis,graph)+1);
        }
    }

    return longest;
}

void shift_by_one_left(vector<int> &arr) {
    int prev = arr[arr.size()-1];
    for (int j = arr.size()-1; j >= 0; j--) {
        int cp = arr[j];
        arr[j] = prev;
        prev = cp;
    }
    arr[arr.size()-1] = prev;
}

bool brute_force(int k, vector<int> &arr, vector<int> &original_arr) {
    if (k == 0) {
        return arr == original_arr;
    }

    bool res = false;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == i) {
            vector<int> cp_arr = arr;
            for (int j = 0; j <= arr[i]; j++) {
                shift_by_one_left(cp_arr);
            }
            if (brute_force(k-1,cp_arr,original_arr)) {
                res = true;
            }
        }
    }

    return res;
}

void readCaseData() {
    cycle_exists = false;

    ini(n);
    //int n = rand() % 5 + 1;
    ini(k);
    //int k = rand() % 5 + 1;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 8 + 1;
        el--;
        arr.pb(el);
    }

    /*bool brute_res = false;
    vector<int> arr_brute = arr;
    for (int i = 0; i < n; i++) {
        if (brute_force(k,arr_brute,arr)) {
            brute_res = true;
        }

        shift_by_one_left(arr_brute);
    }*/

    vector<vector<int>> possible_x(n);
    for (int i = 0; i < n; i++) {
        if (arr[i] < n) {
            possible_x[n-1-i].pb((n-i+arr[i]) % n);
        }
    }

    // Graph of states
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j : possible_x[i]) {
            graph[i].pb(j);
        }
    }

    // Finding a cycle
    vector<int> vis(n,-1);
    dfs(0,vis,graph,0);

    if (cycle_exists) {
        cout << "YES" << endl;

        /*if (!brute_res) {
            int test = 0;
        }*/
    } else {
        // We need to check the length of the longest path
        vector<bool> vis2(n);
        if (longest_path(0,vis2,graph) >= k) {
            cout << "YES" << endl;

            /*if (!brute_res) {
                int test = 0;
            }*/
        } else {
            cout << "NO" << endl;

            /*if (brute_res) {
                int test = 0;
            }*/
        }
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