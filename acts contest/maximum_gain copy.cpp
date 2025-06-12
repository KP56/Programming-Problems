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

pii get_twos_and_negatives(vector<int> &vec, int l, int r) {
    int twos = 0;
    int negatives = 0;

    for (int i = l; i <= r; i++) {
        int el = vec[i];
        if (el == -1) {
            negatives++;
        } else if (el == -2) {
            negatives++;
            twos++;
        } else if (el == 2) {
            twos++;
        }
    }

    return {twos,negatives};
}

pii solve(vector<int> &vec) {
    vector<vector<int>> prefix;
    vector<int> init = {0,0,0,0};
    prefix.pb(init);
    for (int i : vec) {
        if (i == 2) {
            init[0]++;
        } else if (i == -2) {
            init[1]++;
        } else if (i == 0) {
            init[2]++;
        } else if (i == -1) {
            init[3]++;
        }
 
        prefix.pb(init);
    }
 
    pii best_range = {0,0};
    vector<int> best_diff = {-1,-1,-1,-1};
    for (int l = 0; l < prefix.size(); l++) {
        for (int r = l + 1; r < prefix.size(); r++) {
            vector<int> diff = {prefix[r][0] - prefix[l][0], prefix[r][1] - prefix[l][1], prefix[r][2] - prefix[l][2], prefix[r][3] - prefix[l][3]};
            
            if (diff[2] == 0 && (diff[1] + diff[3]) % 2 == 0 && diff[0] + diff[1] >= best_diff[0] + best_diff[1]) {
                best_diff = diff;
                best_range = {l, r - 1};
            }
        }
    }
 
    if (best_diff[0] == -1) {
        // we look for the greatest element
        int greatest_negative = -3;
        int idx = -1;
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] > greatest_negative) {
                greatest_negative = vec[i];
                idx = i;
            }
        }
  
        return {idx+1,idx+1};
    }
 
    return {best_range.first + 1, best_range.second + 1};
}

int calc(vector<int> &vec, pii sol) {
    int gain = 1;
    for (int i = sol.first-1; i <= sol.second-1; i++) {
        gain *= vec[i];
    }

    return gain;
}

vector<int> random_vec(int n) {
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        int ran = rand() % 5;

        if (ran == 0) {
            vec.pb(-2);
        } else if (ran == 1) {
            vec.pb(-1);
        } else if (ran == 2) {
            vec.pb(0);
        } else if (ran == 3) {
            vec.pb(1);
        } else {
            vec.pb(2);
        }
    }

    return vec;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    for (int t = 0; t < 100000; t++) {
    //ini(n);
    int n = rand() % 10 + 1;
    vector<int> vec = random_vec(n);
    /*for (int i = 0; i < n; i++) {
        ini(a);
        vec.pb(a);
    }*/

    pii res = solve(vec);
    int cres = calc(vec,res);

    vec.pb(0);

    int twos = 0;
    int negatives = 0;

    int init = 0;
    int first_negative = -1;
    int last_negative = -1;

    int best_twos = -1;
    pii best_range = {-1,-1};
    for (int i = 0; i < vec.size(); i++) {
        int el = vec[i];

        if (el == 0) {
            if (negatives % 2 == 0) {
                if (twos > best_twos && init != i) {
                    best_twos = twos;
                    best_range = {init,i-1};
                }
            } else {
                pii res1 = get_twos_and_negatives(vec,first_negative+1,i-1);
                pii res2 = get_twos_and_negatives(vec,init,last_negative-1);

                if (res1.first > res2.first && first_negative != -1 && first_negative+1 <= i-1) {
                    if (res1.first > best_twos) {
                        best_twos = res1.first;
                        best_range = {first_negative+1,i-1};
                    }
                } else if (last_negative != -1 && last_negative-1 >= init) {
                    if (res2.first > best_twos) {
                        best_twos = res2.first;
                        best_range = {init,last_negative-1};
                    }
                }
            }

            twos = 0;
            negatives = 0;
            init = i + 1;
            first_negative = -1;
            last_negative = -1;
        } else if (el == -1) {
            if (first_negative == -1) {
                first_negative = i;
            }

            negatives++;

            last_negative = i;
        } else if (el == -2) {
            if (first_negative == -1) {
                first_negative = i;
            }

            negatives++;
            twos++;

            last_negative = i;
        } else if (el == 2) {
            twos++;
        }
    }

    if (best_range.first == -1) {
        int max_element = -3;
        int idx = -1;
        for (int i = 0; i < vec.size()-1; i++) {
            if (vec[i] > max_element) {
                max_element = vec[i];
                idx = i;
            }
        }

        //cout << idx + 1 << " " << idx + 1 << endl;

        int c1 = calc(vec,mp(idx+1,idx+1));

        if (c1 != cres) {
            cout << "test" << endl;
        }

        continue;
    }

    int c1 = calc(vec,mp(best_range.first+1,best_range.second+1));

    if (c1 != cres) {
        cout << "test" << endl;
    }
    }

    //cout << best_range.first + 1 << " " << best_range.second + 1 << endl;
}