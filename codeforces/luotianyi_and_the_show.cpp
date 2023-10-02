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

int brute(vector<int> &input, vector<bool> &occupied, int leftmost, int rightmost) {
    if (input.empty()) {
        int res = 0;
        for (bool b : occupied) res += b;

        return res;
    }

    int res = INT_MIN;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == -1) {
            vector<bool> cp_occ = occupied;
            int leftmost_cp = leftmost;
            if (leftmost != -1) {
                cp_occ[leftmost] = true;
                leftmost_cp--;
            }

            vector<int> cp = input;
            cp.erase(cp.begin() + i);
            res = max(res, brute(cp,cp_occ,leftmost_cp,max(rightmost,leftmost)));
        } else if (input[i] == -2) {
            vector<bool> cp_occ = occupied;
            int rightmost_cp = rightmost;
            if (rightmost != occupied.size()) {
                cp_occ[rightmost] = true;
                rightmost_cp++;
            }

            vector<int> cp = input;
            cp.erase(cp.begin() + i);
            res = max(res, brute(cp,cp_occ,min(leftmost,rightmost),rightmost_cp));
        } else {
            vector<bool> cp_occ = occupied;
            cp_occ[input[i]] = true;
            vector<int> cp = input;
            cp.erase(cp.begin() + i);
            res = max(res, brute(cp,cp_occ,min(leftmost,input[i]-1),max(input[i]+1,rightmost)));
        }
    }

    return res;
}

void readCaseData() {
    ini(n);
    //int n = 5;
    ini(m);
    //int m = 5;

    vector<int> input;
    vector<int> arr(m);
    unordered_set<int> specific;
    int left = 0;
    int right = 0;
    for (int i = 0; i < n; i++) {
        ini(el);
        /*int el = rand() % m + 1;
        int ran = rand() % 3;
        if (ran == 1) {
            el = -1;
        } else if (ran == 2) {
            el = -2;
        }*/

        if (el>0) {
            input.pb(el-1);
        } else {
            input.pb(el);
        }

        if (el == -1) left++;
        else if (el == -2) right++;
        else {
            if (specific.find(el-1) == specific.end()) {
                arr[el-1] = 1;
                specific.insert(el-1);
            }
        }
    }

    for (int i = 1; i < m; i++) {
        arr[i] += arr[i-1];
    }

    int ans = 0;
    //case 1
    ans = max(ans, min(left+(int) specific.size(),m));
    //case 2
    ans = max(ans, min(right+(int) specific.size(),m));
    //case 3
    for (int i : specific) {
        int on_the_right = arr[arr.size()-1]-arr[i];
        int on_the_left = arr[i]-1;
        ans = max(ans, 1+min(right+on_the_right,m-i-1)+min(left+on_the_left,i));
    }
    
    /*vector<bool> occupied(m);
    int brute_ans = brute(input,occupied,m-1,0);

    if (ans != brute_ans) {
        int test = 0;
    }*/

    cout << ans << endl;
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