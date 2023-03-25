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

/*int brute(int current, int time_left, vector<int> &victories, int total, vector<int> &arr) {
    if (current == arr.size()) {
        int place = 1;
        for (int i : victories) {
            if (i > total) {
                place++;
            }
        }

        return place;
    }

    if (time_left >= arr[current]) {
        vector<int> victories_cp = victories;
        victories_cp[current]--;
        return min(brute(current + 1, time_left - arr[current], victories_cp, total + 1, arr),brute(current + 1, time_left, victories, total, arr));
    }

    return brute(current + 1, time_left, victories, total, arr);
}*/

int upperBound(int x, vector<int> &prefix_vec, int remove_ind, int remove) {
    int mid;

    int low = 0;
    int high = prefix_vec.size();

    while (low < high) {
        mid = low + (high - low) / 2;
        if (x >= (remove_ind <= mid ? prefix_vec[mid] - remove : prefix_vec[mid])) {
            low = mid + 1;
        }

        else {
            high = mid;
        }
    }

    if (low < prefix_vec.size() && (remove_ind <= mid ? prefix_vec[low] - remove : prefix_vec[low]) <= x) {
       low++;
    }

    return low;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 5 + 1;
    ini(m);
    //int m = rand() % 5 + 1;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 5 + 1;
        arr.pb(el);
    }

    vector<int> victories;
    for (int i = 0; i < n; i++) {
        victories.pb(i + 1);
    }
    //int solution_brute = brute(0, m, victories, 0, arr);

    vector<pii> sorted;
    for (int i = 0; i < arr.size(); i++) {
        sorted.pb({arr[i],i});
    }
    sort(all(sorted));
    vector<int> prefix_vec;
    vector<int> prefix_ind(sorted.size());
    int prev = 0;
    for (int i = 0; i < sorted.size(); i++) {
        prefix_vec.pb(sorted[i].fi + prev);
        prev += sorted[i].fi;
        prefix_ind[sorted[i].se] = i;
    }

    for (int i = n - 1; i >= 0; i--) {
        //case 1: we want to win
        if (m >= arr[i]) {
            //we can win against this opponent

            //now we want to count the number of wins we can get
            int possible_wins = upperBound(m - arr[i], prefix_vec, prefix_ind[i], arr[i]) + 1; //adding one because of the initial victory
            if (possible_wins - 1 >= prefix_ind[i]) possible_wins--;
            if (possible_wins >= i) {
                /*if (solution_brute != n - i) {
                    cout << "Found a problem case 1" << endl;
                    cout << solution_brute << " " << n - i << endl;
                    cout << n << " " << m << endl;
                    for (int i : arr) {
                        cout << i << " ";
                    }
                    cout << endl;
                    return;
                }*/
                cout << n - i << endl;
                return;
            }
        }

        //case 2: we want to lose
        int possible_wins = upperBound(m,prefix_vec,0,0);
        if (possible_wins >= i + 1) {
            /*if (solution_brute != n - i) {
                cout << "Found a problem case 2" << endl;
                return;
            }*/
            cout << n - i << endl;
            return;
        }
    }

    cout << n + 1 << endl;
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