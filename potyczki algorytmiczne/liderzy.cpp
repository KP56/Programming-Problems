#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

int bruteforce2(int idx, vector<int> &vec, vector<vector<int>> &subsequences, int max_val) {
    if (idx == vec.size()) {
        for (auto i : subsequences) {
            vector<int> vec_reconstruction(max_val+1);
            for (int j : i) {
                vec_reconstruction[j]++;
            }

            bool found_leader = false;
            for (int j : vec_reconstruction) {
                if (j > i.size() / 2) {
                    found_leader = true;
                    break;
                }
            }

            if (!found_leader) {
                return INT_MAX;
            }
        }

        return subsequences.size();
    }

    int min_val = INT_MAX;
    
    for (int i = 0; i < subsequences.size(); i++) {
        vector<vector<int>> subsequences_cp = subsequences;
        subsequences_cp[i].pb(vec[idx]);
        min_val = min(min_val,bruteforce2(idx+1,vec,subsequences_cp,max_val));
    }

    return min_val;
}

int bruteforce(vector<int> &vec) {
    vector<int> actual_vec;
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i]; j++) {
            actual_vec.pb(i);
        }
    }

    int min_val = INT_MAX;
    for (int i = 1; i <= vec.size(); i++) {
        vector<vector<int>> subsequences(i);
        min_val = min(min_val,bruteforce2(0,actual_vec,subsequences,vec.size()));
    }

    return min_val;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 5 + 1;
    vector<int> vec(n);
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % n + 1;
        a--;
        vec[a]++;
    }

    vector<int> original = vec;

    //int brute_res = bruteforce(vec);

    // sortujemy elementy różnych wag
    sort(all(vec),greater<int>());

    int l = 0;
    int r = n-1;
    for (; l < r; l++) {
        int can_throw = vec[l]-1;
        while (can_throw - vec[r] > 0) {
            can_throw -= vec[r];
            vec[r] = 0;
            r--;
        }

        vec[r] -= can_throw;
    }

    int res = 0;
    for (int i : vec) {
        if (i != 0) res++;
    }
    /*if (res != brute_res) {
        int test = 0;
    }*/
    
    cout << res << endl;
}