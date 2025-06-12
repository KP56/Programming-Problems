#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set = tree<
    T,
    null_type,
    std::less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

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

void bruteforce_sol(int moves_so_far, int area_so_far, vector<int> &a, vector<int> &b, vector<int> &sol, bool reversed) {
    if (!reversed) bruteforce_sol(moves_so_far, area_so_far, b, a, sol, true);

    for (int i = 0; i < a.size(); i++) {
        for (int j = i + 1; j < a.size(); j++) {
            vector<int> a_cp = a;
            
            int sel1 = a_cp[i];
            int sel2 = a_cp[j];

            int area = abs(sel1 - sel2);

            a_cp.erase(a_cp.begin() + i);
            a_cp.erase(a_cp.begin() + j - 1);
            for (int k = 0; k < b.size(); k++) {
                vector<int> b_cp = b;
                b_cp.erase(b_cp.begin() + k);
                
                
                if (moves_so_far >= sol.size()) {
                    sol.pb(area_so_far + area);
                } else {
                    sol[moves_so_far] = max(sol[moves_so_far], area_so_far + area);
                }

                bruteforce_sol(moves_so_far + 1, area_so_far + area, a_cp, b_cp, sol, false);
            }
        }
    }
}

vector<int> solve(vector<int> a, vector<int> b) {
    ordered_set<int> a_s;
    for (int i : a) {
        a_s.insert(i);
    }

    ordered_set<int> b_s;
    for (int i : b) {
        b_s.insert(i);
    }

    vector<vector<int>> deleted_a;
    vector<vector<int>> deleted_b;
    int current_res = 0;
    bool force_as = false;
    bool force_bs = false;
    int moves_so_far = 0;

    bool ever_forced_as = false;
    bool ever_forced_bs = false;

    vector<int> ans;
    while (true) {
        int res1 = -1;
        if (a_s.size() >= 2 && b_s.size() >= 1) {
            int el_l = *a_s.begin();
            int el_r = *(--a_s.end());

            res1 = el_r - el_l;
        }

        int res2 = -1;
        if (b_s.size() >= 2 && a_s.size() >= 1) {
            int el_l = *b_s.begin();
            int el_r = *(--b_s.end());

            res2 = el_r - el_l;
        }

        if (res1 == -1 && res2 == -1) {
            if (a_s.size() > 2) {
                // we undo one move
                // since a_s has a lot of point, we undo the latest b_s move and force to perform an a_s move
                if (deleted_b.empty() || ever_forced_bs) {
                    // if there is no move to undo
                    break;
                }
                moves_so_far--;
                force_as = true;
                ever_forced_as = true;
                vector<int> move_to_undo = deleted_b[deleted_b.size() - 1];
                deleted_b.erase(--deleted_b.end());
                current_res -= move_to_undo[1] - move_to_undo[0];
                b_s.insert(move_to_undo[0]);
                b_s.insert(move_to_undo[1]);
                a_s.insert(move_to_undo[2]);
                continue;
            } else if (b_s.size() > 2) {
                // we undo one move
                // since b_s has a lot of points, we undo the latest a_s move and force to perform a b_s move
                if (deleted_a.empty() || ever_forced_as) {
                    // if there is no move to undo
                    break;
                }
                moves_so_far--;
                force_bs = true;
                ever_forced_bs = true;
                vector<int> move_to_undo = deleted_a[deleted_a.size() - 1];
                deleted_a.erase(--deleted_a.end());
                current_res -= move_to_undo[1] - move_to_undo[0];
                a_s.insert(move_to_undo[0]);
                a_s.insert(move_to_undo[1]);
                b_s.insert(move_to_undo[2]);
                continue;

            } else {
                // we break
                break;
            }
        }

        if ((res1 > res2 || force_as) && !force_bs) {
            // we delete two points in a and one point in b
            int deleted_point1 = *a_s.begin();
            int deleted_point2 = *(--a_s.end());
            a_s.erase(a_s.begin());
            a_s.erase(--a_s.end());

            auto p = b_s.find_by_order(b_s.size() / 2);
            int deleted_mid_point = *p;
            b_s.erase(p);

            deleted_a.pb({deleted_point1,deleted_point2,deleted_mid_point});

            current_res += res1;
        } else {
            // we delete two points in b and one point in a
            int deleted_point1 = *b_s.begin();
            int deleted_point2 = *(--b_s.end());
            b_s.erase(b_s.begin());
            b_s.erase(--b_s.end());

            auto p = a_s.find_by_order(a_s.size() / 2);
            int deleted_mid_point = *p;
            a_s.erase(p);

            deleted_b.pb({deleted_point1,deleted_point2,deleted_mid_point});

            current_res += res2;
        }

        moves_so_far++;
        if (moves_so_far > ans.size()) {
            ans.pb(0);
        }
        ans[moves_so_far - 1] = max(ans[moves_so_far - 1], current_res);
        force_as = false;
        force_bs = false;
    }

    return ans;
}

void readCaseData() {
    ini(n);
    ini(m);

    //int n = rand() % 5 + 1;
    //int m = rand() % 5 + 1;

    //unordered_set<int> exist_in_a;
    //unordered_set<int> exist_in_b;

    vector<int> a;
    vector<int> b;
    for (int i = 0; i < n; i++) {
        ini(el);
        /*int el = rand() % 10 - 5;
        while (exist_in_a.find(el) != exist_in_a.end()) {
            el = rand() % 10 - 5;
        }*/
        a.pb(el);
        //exist_in_a.insert(el);
    }

    for (int i = 0; i < m; i++) {
        ini(el);
        /*int el = rand() % 10 - 5;
        while (exist_in_b.find(el) != exist_in_a.end()) {
            el = rand() % 10 - 5;
        }*/
        b.pb(el);
        //exist_in_b.insert(el);
    }

    vector<int> sol = solve(a,b);

    /*vector<int> brute_sol;
    bruteforce_sol(0,0,a,b,brute_sol,false);

    if (sol != brute_sol) {
        cout << "TEST" << endl;
    }*/

    cout << sol.size() << endl;
    for (int i : sol) {
        cout << i << " ";
    }
    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}