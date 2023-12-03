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

bool collide0(pii p1, pii p2) {
    return (p1.first > p2.first && p1.first < p2.second) || (p1.second > p2.first && p1.second < p2.second);
}

bool collide(pii p1, pii p2) {
    return collide0(p1,p2) || collide0(p2,p1) || p1 == p2;
}

int bruteforce(vector<pii> &vec, vector<pii> &brute) {
    int ans = 0;

    if (brute.size() % 2 == 0) {
        for (int i = 0; i < brute.size(); i += 2) {
            pii pair1 = brute[i];
            pii pair2 = brute[i + 1];

            bool broke = false;
            for (int j = 0; j < brute.size(); j += 2) {
                if (i != j) {
                    pii pair3 = brute[j];

                    if (collide(pair1, pair3) || collide(pair2, pair3)) {
                        broke = true;
                        break;
                    }
                }
            }

            if (broke) {
                return 0;
            }
        }

        ans = brute.size() / 2;
    }

    for (int i = 0; i < vec.size(); i++) {
        vector<pii> cp = vec;
        pii taking = vec[i];
        if (brute.size() % 2 == 0) {
            cp.erase(cp.begin() + i);
        }
        vector<pii> brute_cp = brute;
        brute_cp.pb(taking);

        ans = max(ans, bruteforce(cp,brute_cp));
    }

    return ans;
}

vector<int> compute_next_block(vector<pair<pii,int>> &vec, int n) {
    vector<int> next_block(n,-1);

    // next_block przechowuje informacje nt. najbliższych klocków do danego, niekolidujących z danym klockiem, które są po nim
    deque<pii> previous;
    for (int i = 0; i < n; i++) {
        while (!previous.empty() && vec[i].first.second >= previous[0].first) {
            next_block[previous[0].second] = i;
            previous.pop_front();
        }

        // {end_pos, index}
        previous.pb({vec[i].first.first, i});
    }

    return next_block;
}

vector<int> compute_dp(vector<pair<pii,int>> &vec, int n) {
    vector<int> dp(n);
    vector<int> next_block = compute_next_block(vec, n);

    dp[vec[n-1].second] = 1;
    for (int i = n-2; i >= 0; i--) {
        int mapping1 = vec[i].second;
        int mapping2 = vec[i+1].second;
        if (next_block[i] != -1) {
            dp[mapping1] = max(dp[mapping2], dp[vec[next_block[i]].second]+1);
        } else {
            dp[mapping1] = dp[mapping2];
        }
    }

    return dp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 10 + 1;
    vector<pair<pii,int>> vec;
    vector<pii> brute_vec;
    int max_end = -1;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 10 + 1;
        ini(b);
        //int b = a + rand() % 10 + 1;
        vec.pb({{b,a},i});
        brute_vec.pb({a,b});

        max_end = max(max_end,b);
    }

    /*vector<pii> brute;
    int ans = bruteforce(brute_vec, brute);*/

    sort(all(vec));
    
    vector<int> dp = compute_dp(vec, n);
    vector<pair<pii,int>> vec_cp = vec;
    for (pair<pii,int> &p : vec_cp) {
        p.first.first = max_end - p.first.first;
        p.first.second = max_end - p.first.second;

        int mem = p.first.first;
        p.first.first = p.first.second;
        p.first.second = mem;
    }

    sort(all(vec_cp));

    unordered_map<int,int> backward_converter;
    for (int i = 0; i < vec_cp.size(); i++) {
        backward_converter[vec_cp[i].second] = i;
    }

    vector<int> dp2 = compute_dp(vec_cp,n);

    vector<int> next_block = compute_next_block(vec,n);
    vector<int> prev_block = compute_next_block(vec_cp,n);

    int res = 0;
    int chosen_index = -1;

    // zmienne do debugowania
    int next_block_idx = -1;
    int prev_block_idx = -1;
    for (int i = 0; i < n; i++) {
        // Przy prev_blocku muszę przekonwertować jeden typ indeksu na drugi
        int standard_index = vec[i].second;
        int prev_index = backward_converter[standard_index];
        int prev_index_prev_block = prev_block[prev_index];

        int potential = (prev_index_prev_block == -1 ? 0 : dp2[vec_cp[prev_index_prev_block].second]) +
                (next_block[i] == -1 ? 0 : dp[vec[next_block[i]].second]);

        if (potential > res) {
            res = potential;
            next_block_idx = next_block[i];
            prev_block_idx = prev_index_prev_block;
            chosen_index = i;
        }
    }

    vector<pii> solution_vec;
    // Próba rekonstrukcji informacji dot. konkretnych zakresów wybranych
    if (chosen_index != -1) {
        // Stosowanie algorytmu zachłannego od konkretnego indeksu w celu znalezienia optymalnych zakresów do przodu
        int prev_end = vec[chosen_index].first.first;
        for (int i = chosen_index + 1; i < n; i++) {
            if (vec[i].first.second >= prev_end) {
                prev_end = vec[i].first.first;
                solution_vec.pb({vec[i].second,vec[chosen_index].second});
            }
        }

        // Stosowanie algorytmu zachłannego od konkretnego indeksu w celu znalezienia optymalnych zakresów do tyłu
        int standard_index = vec[chosen_index].second;
        int prev_index = backward_converter[standard_index];

        int prev_begin = vec_cp[prev_index].first.first;
        for (int i = prev_begin + 1; i < n; i++) {
            if (vec_cp[i].first.second >= prev_begin) {
                prev_begin = vec[i].first.first;
                solution_vec.pb({vec_cp[i].second,vec[chosen_index].second});
            }
        }
    }

    // Tutaj rozwiązanie zachłanne
    int collision_state = 0;
    int first_end = 0;
    int second_end = 0;
    int greedy_sol = 0;

    int new_first_end = 0;
    int new_second_end = 0;

    int have_first_idx = -1;
    int have_second_idx = -1;

    vector<pii> greedy_sol_vec;
    for (int i = 0; i < n; i++) {
        if (vec[i].first.second >= max(first_end,second_end) && have_first_idx == -1) {
            // Może być pierwszym klockiem więc go czynimy pierwszym
            greedy_sol++;
            have_first_idx = i;
            new_first_end = vec[i].first.first;
        } else if (vec[i].first.second >= first_end && have_second_idx == -1) {
            // Może być drugim klockiem a nie może być pierwszym więc go czynimy drugim w parze
            greedy_sol++;
            have_second_idx = i;
            new_second_end = vec[i].first.first;
        }

        if (have_first_idx != -1 && have_second_idx != -1) {
            greedy_sol_vec.pb({vec[have_first_idx].second,vec[have_second_idx].second});

            have_first_idx = -1;
            have_second_idx = -1;

            first_end = new_first_end;
            second_end = new_second_end;
        }
    }

    greedy_sol /= 2;

    bool greedy_is_better = false;
    if (greedy_sol > res) {
        res = greedy_sol;
        greedy_is_better = true;
        solution_vec = greedy_sol_vec;
    }

    cout << res << endl;

    // Weryfikacja konkretnych wybranych zakresów
    /*for (int i = 0; i < solution_vec.size(); i++) {
        pii pair1 = brute_vec[solution_vec[i].first];
        pii pair2 = brute_vec[solution_vec[i].second];

        bool broke = false;
        for (int j = 0; j < solution_vec.size(); j++) {
            if (i != j) {
                pii pair3 = brute_vec[solution_vec[j].first];

                if (collide(pair1, pair3) || collide(pair2, pair3)) {
                    broke = true;
                    break;
                }
            }
        }

        if (broke) {
            int test = 0;
        }
    }*/

    /*if (ans != res || solution_vec.size() != res) {
        int test = 0;
    }*/

    for (pii i : solution_vec) {
        cout << i.first + 1 << " " << i.second + 1 << endl;
    }
}