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

bool real_brute(int i, int j, vector<vector<int>> &board, vector<int> &nums) {
    if (i == board.size()) {
        i = 0;
        j++;
    }

    if (j == board[0].size()) {
        vector<pii> rel = {
            {0,1},
            {1,0},
            {0,-1},
            {-1,0}
        };
        for (int x = 0; x < board.size(); x++) {
            for (int y = 0; y < board[0].size(); y++) {
                int counter = 0;
                for (auto r : rel) {
                    int new_x = x + r.first;
                    int new_y = y + r.second;
                    if (new_x < 0) new_x += board.size();
                    if (new_y < 0) new_y += board[0].size();
                    new_x %= board.size();
                    new_y %= board[0].size();
                    if (board[x][y] == board[new_x][new_y]) counter++;
                }

                if (counter < 3) {
                    return false;
                }
            }
        }

        return true;
    }

    bool res = false;
    for (int k = 0; k < nums.size(); k++) {
        if (nums[k] > 0) {
            vector<int> cp_nums = nums;
            cp_nums[k]--;
            vector<vector<int>> cp = board;
            cp[i][j] = k;
            res |= real_brute(i+1,j,cp,cp_nums);
        }
    }

    return res;
}

bool brute(int w, int h, vector<int> nums) {
    vector<vector<int>> board(w, vector<int>(h));

    return real_brute(0, 0, board, nums);
}

bool solve(int w, int h, vector<int> nums) {
    //Firstly we try to get as many pairs as possible
    int left = w;
    vector<bool> markings(nums.size());
    for (int i = 0; i < nums.size() && left != 0; i++) {
        if (left == 1) {
            for (int j = 0; j < nums.size(); j++) {
                if (nums[j] >= h && markings[j]) {
                    return true;
                } else if (!markings[j] && nums[j] / h >= 3) {
                    return true;
                }
            }

            return false;
        }

        int n = nums[i];
        if (n / h >= 2) {
            nums[i] -= h * 2;
            markings[i] = true;
            left -= 2;
        }
    }

    for (int i = 0; i < nums.size(); i++) {
        if (markings[i]) {
            left -= nums[i] / h;
            nums[i] -= nums[i] / h * h;
        }
    }

    if (left <= 0) {
        return true;
    }

    return false;
}

void readCaseData() {
    ini(w);
    //int w = 3;
    ini(h);
    //int h = 3;
    ini(n);
    //int n = 3;
    vector<int> nums;
    //int sum = 0;
    for (int i = 0; i < n; i++) {
        ini(a);
        /*int a = rand() % 9 + 2;
        if (i == n - 1 && sum < w * h) {
            a = w * h - sum;
        }
        sum += a;*/
        nums.pb(a);
    }

    if (solve(w, h, nums) || solve(h, w, nums)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
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