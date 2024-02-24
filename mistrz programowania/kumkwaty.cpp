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

int bruteforce(int i, vector<bool> &vis, bool turn, vector<int> &vec) {
    if (i == -1) {
        int best = turn ? INT_MAX : 0;
        
        for (int j = 0; j < vis.size(); j++) {
            if (!vis[j]) {
                vector<bool> cp = vis;
                cp[j] = true;
                if (!turn) {
                    best = max(best,bruteforce(j,cp,!turn,vec)+vec[j]);
                } else {
                    best = min(best,bruteforce(j,cp,!turn,vec));
                }
            }
        }
        
        if (best == INT_MAX) best = 0;

        return best;
    }
    
    int res = turn ? INT_MAX : 0;
    bool any_move = false;
    if (i>0 && !vis[i-1]) {
        any_move = true;
        vector<bool> cp = vis;
        cp[i-1] = true;
        if (!turn) {
            res = max(res,bruteforce(i-1,cp,!turn,vec)+vec[i-1]);
        } else {
            res = min(res,bruteforce(i-1,cp,!turn,vec));
        }
    }
    
    if (i<vis.size()-1 && !vis[i+1]) {
        any_move = true;
        vector<bool> cp = vis;
        cp[i+1] = true;
        if (!turn) {
            res = max(res,bruteforce(i+1,cp,!turn,vec)+vec[i+1]);
        } else {
            res = min(res,bruteforce(i+1,cp,!turn,vec));
        }
    }

    if (!any_move) {
        return bruteforce(-1,vis,turn,vec);
    }
    
    return res;
}

/*int opportunity_gain(int i, int j, vector<int> &vec) {
    int sum = 0;
    for (int k = i; k <= j; k += 2) {
        sum += vec[k];
        if (k+1<=j) {
            sum -= vec[k+1];
        }
    }

    return sum;
}*/

int solve(vector<int> &vec) {
    int sum = 0;
    for (int i = 0; i < vec.size(); i += 2) {
        sum += vec[i];
    }
    
    int sum2 = 0;
    for (int i = vec.size() - 1; i >= 0; i -= 2) {
        sum2 += vec[i];
    }

    if (vec.size() % 2 == 1) {
        bool not_subproblems_one_two = false;
        for (int i : vec) {
            if (i > 2) {
                not_subproblems_one_two = true;
            }
        }

        if (!not_subproblems_one_two) {
            int sum3 = 0;
            /*bool found_something = false;
            do {
                found_something = false;
                for (int i = 0; i < vec.size()-1; i++) {
                    if (vec[i] == vec[i+1]) {
                        sum3 += vec[i];

                        vec.erase(vec.begin() + i);
                        vec.erase(vec.begin() + i);

                        found_something = true;

                        break;
                    }
                }
            } while (found_something);*/

            list<int> l(all(vec));
            bool decrement = false;
            for (auto it = l.begin(); it != l.end(); it++) {
                if (decrement) it--;
                decrement = false;

                auto it2 = it;
                it2++;

                if (it2 == l.end()) break;

                if (*it == *it2) {
                    sum3 += *it;

                    auto it3 = it2;
                    it3++;

                    l.erase(it);
                    l.erase(it2);

                    decrement = true;
                    if (it3 != l.begin()) it3--;

                    it = it3;
                }
            }

            vector<int> new_vec;
            for (int i : l) {
                if (i != -1) {
                    new_vec.pb(i);
                }
            }

            if (new_vec[0] == 2) {
                // Case 1
                sum3 += 2*(new_vec.size()/2+1);
            } else {
                // Case 2
                sum3 += 2*(new_vec.size()/2)+1;
            }

            return max(sum,max(sum2,sum3));
        }

        vector<int> dp(vec.size()+1);
        for (int i = 1; i < vec.size()+1; i += 2) {
            int current_gain = 0;
            for (int j = 0; j < i; j += 2) {
                current_gain += vec[j] - (j != i-1 ? vec[j+1] : 0);
            }
            for (int j = 0; j < i; j += 2) {
                dp[i] = max(dp[i],min(j != 0 ? dp[j-1] : INT_MAX, current_gain));
                current_gain -= vec[j] - (j != i-1 ? vec[j+1] : 0);
            }
        }

        int sum3 = 0;
        for (int i = 1; i < vec.size(); i += 2) {
            sum3 += vec[i];
        }

        return max(dp[vec.size()]+sum3,max(sum,sum2));
    }

    return max(sum,sum2);
}

/*int solve2(vector<int> &vec, int minimum) {
    int sum = 0;
    for (int i = 0; i < vec.size(); i += 2) {
        sum += vec[i];
    }
    
    int sum2 = 0;
    for (int i = vec.size() - 1; i >= 0; i -= 2) {
        sum2 += vec[i];
    }

    if (vec.size() % 2 == 1) {
        int min_segment = INT_MAX;
        int current_segment_gain = vec[0];
        for (int i = 0; i < vec.size()-1; i += 2) {
            int possible_future_gain = i+2<vec.size() ? vec[i+2] : 0;
            int current_gain = i+2<vec.size() ? vec[i+2] : 0;
            for (int j = i + 3; j < vec.size(); j += 2) {
                current_gain += -vec[j] + (j != vec.size()-1 ? vec[j+1] : 0);
                possible_future_gain = max(possible_future_gain, current_gain);
            }

            if (possible_future_gain > vec[i+1] && current_segment_gain < minimum) {
                current_segment_gain += -vec[i+1] + vec[i+2];
            } else {
                min_segment = min(min_segment,current_segment_gain);
                current_segment_gain = vec[i+2];
            }
        }

        min_segment = min(min_segment,current_segment_gain);

        int sum3 = 0;
        for (int i = 1; i < vec.size(); i += 2) {
            sum3 += vec[i];
        }

        return max(sum,max(sum2,sum3+min_segment));
    }

    return max(sum,sum2);
}*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 10 + 1;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 10 + 1;
        vec.pb(a);
    }

    vector<int> cp = vec;

    int sum = 0;
    for (int i : vec) {
        sum += i;
    }

    /*int sum2 = 0;
    for (int i = 1; i < vec.size(); i += 2) {
        sum2 += vec[i];
    }*/

    vector<bool> vis(n);
    //int brute_res = bruteforce(-1,vis,false,vec);
    int res = solve(vec);
    /*if (brute_res != res) {
        int test = 0;
    }*/

    cout << res << " " << sum - res << endl;
}