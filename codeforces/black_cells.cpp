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

//bruteforce for automatic test generation before submitting
int bruteforce(int k, vector<bool> &areas, int current_moves, int current_score, int current_pos, int shift_start) {
    if (current_score == k) {
        return current_moves;
    }

    if (current_pos >= areas.size()) {
        return INT_MAX;
    }

    int minimum_moves = INT_MAX;
    if (areas[current_pos]) {
        if (current_pos + 1 == areas.size() || !areas[current_pos + 1]) {
            //if we hold shift, we are forced to stop holding shift and move right
            if (shift_start != -1) {
                current_score += current_pos - shift_start + 1;
                shift_start = -1;
                current_moves += 2;
                current_pos++;

                if (current_score == k) {
                    return current_moves-1;
                }
            }
        }

        if (shift_start != -1) {
            //in this case we shouldn't move right
            if (current_score + current_pos - shift_start + 1 == k) {
                //accounting for stopping holding shift
                return current_moves + 1;
            } else {
                //stop holding shift and move right
                minimum_moves = min(minimum_moves, bruteforce(k, areas, current_moves + 2, current_score + current_pos - shift_start + 1, current_pos + 1, -1));
            }
        } else {
            //press shift
            minimum_moves = min(minimum_moves, bruteforce(k, areas, current_moves + 1, current_score, current_pos, current_pos));
        }

        //move right
        minimum_moves = min(minimum_moves, bruteforce(k, areas, current_moves + 1, current_score, current_pos + 1, shift_start));
    } else {
        //move right
        minimum_moves = min(minimum_moves, bruteforce(k, areas, current_moves + 1, current_score, current_pos + 1, shift_start));
    }

    return minimum_moves;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 5 + 1;
    ini(k);
    //int k = rand() % n + 1;

    vector<int> left;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 3 + 1 + (left.empty() ? 0 : left[left.size() - 1]);
        left.pb(el);
    }

    vector<pii> pairs;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = left[i] + (i == (n - 1) ? (rand() % 5 + 1) : (rand() % (left[i+1]-left[i])));

        pairs.pb({left[i],el});
    }

    vector<pii> original = pairs;

    vector<pii> pair_reconstruction;
    pii prev = {-1,-1};
    for (pii p : pairs) {
        if (prev == mp(-1ll,-1ll)) {
            prev = p;
            continue;
        }

        if (p.first == prev.second+1) {
            prev.second = p.second;
        } else {
            pair_reconstruction.pb(prev);
            prev = p;
        }
    }

    if (prev != mp(-1ll,-1ll)) {
        pair_reconstruction.pb(prev);
    }

    pairs = pair_reconstruction;

    int solution = INT_MAX;
    int len_sum = 0;
    //I could use priority queue too, but I'm more used to working with c++'s sets so I took rb tree instead
    multiset<int> lengths;
    for (int current = 0; current < pairs.size(); current++) {
        int length = pairs[current].second - pairs[current].first + 1;
        len_sum += length;
        lengths.insert(length);

        if (len_sum >= k) {
            //we have reached a point when we can start doing actual work
            //removing all unnecessary ranges
            int difference = len_sum - k;
            while (difference >= *lengths.begin() && *lengths.begin() <= 2) {
                difference -= *lengths.begin();
                len_sum -= *lengths.begin();
                lengths.erase(lengths.begin());
            }

            //since difference is equal to the unnecessary cells which we have, we can finish "difference" cells before the end
            //knowing that, we can compute the optimal end position
            int optimal_end = pairs[current].second - difference;

            //for this ending range the optimal solution can be computed with the following formula
            int current_solution = 2 * lengths.size() + optimal_end;
            solution = min(solution, current_solution);
        }
    }

    if (len_sum < k) {
        cout << -1 << endl;
        return;
    }

    /*int maximum_r = pairs[pairs.size() - 1].second;
    vector<bool> areas(maximum_r+1);
    for (pii p : pairs) {
        for (int i = p.first; i <= p.second; i++) {
            areas[i] = true;
        }
    }

    int brute_res = bruteforce(k, areas, 0, 0, 0, -1);

    if (brute_res != solution) {
        int test = 0;
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