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

//https://www.geeksforgeeks.org/find-first-and-last-positions-of-an-element-in-a-sorted-array/
int search(vector<int> &nums, int target, bool find_start_index) {
    int ans = -1;
    int start = 0;
    int end = nums.size() - 1;
    while (start <= end) {
        int mid = start + (end - start) / 2;
 
        if (target > nums[mid]) {
            end = mid - 1;
        } else if (target < nums[mid]) {
            start = mid + 1;
        } else {
            ans = mid;
            if (find_start_index) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
    }
 
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int x = 4;

    vector<int> arr = {6, 6, 6, 4, 4, 3, 3, 3, 2, 1, 1};

    int ans[] = {-1, -1};
    ans[0] = search(arr,x,true);
     
    if(ans[0] != -1){
        ans[1] = search(arr,x,false);
    }

    cout << ans[0] << " " << ans[1] << endl;
}
