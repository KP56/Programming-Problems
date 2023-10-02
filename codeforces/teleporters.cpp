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

int brute2(vector<int> &arr, vector<int> &cost1, vector<int> &cost2, vector<int> &current, vector<bool> &vis, int coins) {
    int res = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        if (!vis[i]) {
            vector<int> current_cp = current;
            current_cp.pb(i);
            vector<bool> vis_cp = vis;
            vis_cp[i] = true;
            res = max(res, brute2(arr, cost1, cost2, current_cp, vis_cp, coins));
        }
    }

    if (res == INT_MIN) {
        bool first = true;
        res = 0;
        for (int i : current) {
            if (first) {
                coins -= cost1[i];
            } else {
                coins -= cost2[i];
            }
            if (coins >= 0) {
                res++;
            } else {
                break;
            }

            first = false;
        }

        return res;
    }

    return res;
}

int brute(vector<int> arr, int coins) {
    vector<int> cost1(arr.size());
    vector<int> cost2(arr.size());
    for (int i = 0; i < arr.size(); i++) {
        cost1[i] = i + 1 + arr[i];
        cost2[i] = min((int) arr.size()+1-i-1,i+1) + arr[i];
    }

    int res = INT_MIN;
    for (int i = 0; i < arr.size(); i++) {
        vector<int> current = {i};
        vector<bool> vis(arr.size());
        vis[i] = true;
        res = max(res, brute2(arr, cost1, cost2, current, vis, coins));
    }

    return res;
}

void readCaseData() {
    ini(n);
    //int n = 7;
    ini(c);
    //int c = rand() % 20 + 1;
    //int coins = c;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 6 + 1;
        arr.pb(el);
    }

    vector<int> cost1(n);
    vector<int> cost2(n);
    vector<pii> cost1_sorted;
    vector<pii> cost2_sorted;
    for (int i = 0; i < n; i++) {
        cost1[i] = i + 1 + arr[i];
        cost2[i] = min(n+1-i-1,i+1) + arr[i];
        cost1_sorted.pb({cost1[i],i});
        cost2_sorted.pb({cost2[i],i});
    }
    sort(all(cost1_sorted));
    sort(all(cost2_sorted));

    int future_costs = 0;
    vector<bool> vis(n);
    pii prev = {-1,-1};
    for (auto i : cost1_sorted) {
        if (i.first + future_costs > c) {
            //will not be able to get to it in the future, let's take the previous candidate
            if (prev == mp((int) -1, (int) -1)) {
                /*if (brute(arr, coins) != 0) {
                    cout << "test" << endl;
                }*/
                cout << 0 << endl;
                return;
            }
            auto best_candidate = mp((int) -1, (int) -1);
            int second_sum = 0;
            for (auto i : cost1_sorted) {
                second_sum += cost2[i.second];

                if (i == prev) {
                    break;
                }
            }
            int minimal_total = 10000000000000;
            for (auto i : cost1_sorted) {
                int for_this = second_sum - cost2[i.second] + i.first;
                if (for_this < minimal_total) {
                    minimal_total = for_this;
                    best_candidate = i;
                }

                if (i == prev) {
                    break;
                }
            }
            vis[best_candidate.second] = true;
            c -= best_candidate.first;
            break;
        }

        if (cost2[i.second] == i.first) {
            //we found the best candidate for first teleporter to travel to
            vis[i.second] = true;
            c -= i.first;
            break;
        } else {
            future_costs += cost2[i.second];
        }

        prev = i;
    }

    int solution = 1;
    for (auto i : cost2_sorted) {
        if (!vis[i.second]) {
            if (c - i.first >= 0) {
                c -= i.first;
                solution++;
            } else {
                break;
            }
        }
    }

    /*if (brute(arr, coins) != solution) {
        cout << "test" << endl;
    }*/
    cout << solution << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}