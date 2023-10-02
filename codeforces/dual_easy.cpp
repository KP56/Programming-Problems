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

bool verify(vector<int> vec, vector<pii> &operations) {
    for (pii i : operations) {
        vec[i.first] += vec[i.second];
    }

    int prev = INT_MIN;
    for (int i : vec) {
        if (i < prev) {
            return false;
        }

        prev = i;
    }

    return true;
}

void solve(vector<int> &vec, int n, bool reversed, vector<pii> &operations_so_far) {
    // Looking for a positive number
    int greatest_positive_ind = -1;
    int greatest_positive = INT_MIN;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > 0) {
            if (vec[i] > greatest_positive) {
                greatest_positive = vec[i];
                greatest_positive_ind = i;
            }
        }
    }

    vector<pii> &operations = operations_so_far;
    if (vec[vec.size() - 1] > 0) {
        // If last element is positive, we don't need another positive number
        // We iterate through the entire vector and keep track of the required exponential product to sort everything properly
        map<int,int> exponential_map;
        exponential_map[vec[vec.size() - 1]] = 0;

        // Vector for storing the ordering of operations
        vector<pii> moment;

        int increased = 0;

        for (int i = 1; i < vec.size() - 1; i++) {
            if (vec[i-1] > vec[i]) {
                while (vec[i-1] > vec[i] + vec[vec.size() - 1]) {
                    vec[vec.size() - 1] *= 2;
                    exponential_map[vec[vec.size() - 1]] = exponential_map.size();
                    increased++;
                }

                auto it = exponential_map.lower_bound(vec[i - 1] - vec[i]);
                int to_add = it->first;
                int time = it->second;
                vec[i] += to_add;
                moment.pb({time,i});
            }
        }

        vector<pii> moment_with_ind;
        for (pii i : moment) {
            moment_with_ind.pb({i.first,i.second});
        }
        sort(all(moment_with_ind));

        int prev = 0;
        for (pii i : moment_with_ind)  {
            if (i.first > prev) {
                for (int j = 0; j < i.first - prev; j++) {
                    operations.pb({vec.size() - 1,vec.size() - 1});
                }
            }

            operations.pb({i.second,vec.size() - 1});

            prev = i.first;
        }

        if (n > 1) {
            while (vec[vec.size() - 1] < vec[vec.size() - 2]) {
                vec[vec.size() - 1] *= 2;
                operations.pb({vec.size() - 1,vec.size() - 1});
            }
        }
    } else if (greatest_positive_ind != -1) {
        // Otherwise, we need to take the greatest positive
        while (greatest_positive + vec[vec.size() - 1] <= 0) {
            greatest_positive *= 2;
            vec[greatest_positive_ind] *= 2;
            operations.pb({greatest_positive_ind, greatest_positive_ind});
        }

        vec[vec.size() - 1] += greatest_positive;
        operations.pb({vec.size() - 1, greatest_positive_ind});

        // Now that we managed to get the last element to be positive, we call the solve function
        solve(vec,n,reversed,operations);
        return;
    } else {
        // If no positive number exists, we multiply everything by -1 and reverse it then solve
        for (int i = 0; i < n; i++) {
            vec[i] *= -1;
        }
        reverse(all(vec));

        solve(vec,n,true,operations);
        return;
    }

    for (pii &i : operations) {
        if (reversed) {
            i = {n - i.first - 1, n - i.second - 1};
        }
    }

    cout << operations.size() << endl;
    for (pii i : operations) {
        cout << i.first + 1 << " " << i.second + 1 << endl;
    }
}

void readCaseData() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    //int n = rand() % 20 + 1;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 41 - 20;
        vec.pb(a);
    }

    bool all_zeros = true;
    for (int i : vec) {
        if (i != 0) {
            all_zeros = false;
            break;
        }
    }

    if (all_zeros) {
        cout << 0 << endl;
        return;
    }

    vector<int> original_vec = vec;
    vector<pii> operations;
    solve(vec,n,false,operations);

    /*if (!verify(original_vec, operations) || operations.size() > 50) {
        int test = 0;
    }*/
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