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

pii place_to_row_column(int num) {
    return {num / 2, num % 2};
}

int dist(pii a, pii b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);
    
    ini(alice_desk);
    ini(alice_sit);

    alice_desk--;
    alice_sit--;

    pii alice_pos = {alice_desk,alice_sit};

    int alice_num = alice_desk * 2 + alice_sit;
    
    int target_num1 = alice_num + k;
    int target_num2 = alice_num - k;

    vector<int> targets;
    if (target_num1 >= 0 && target_num1 < n) {
        targets.pb(target_num1);
    }

    if (target_num2 >= 0 && target_num2 < n) {
        targets.pb(target_num2);
    }

    // {desk number, sit left/right}
    pii best_pos = {-1,-1};
    for (int i : targets) {
        pii pos = place_to_row_column(i);
        
        if (best_pos == mp(-1ll,-1ll) || (dist(pos,alice_pos) < dist(best_pos,alice_pos)
                || (dist(pos,alice_pos) == dist(best_pos,alice_pos) && pos.first > best_pos.first))) {
            best_pos = pos;
        }
    }


    if (best_pos.first == -1) {
        cout << -1 << endl;
        return 0;
    }

    cout << best_pos.first + 1 << " " << best_pos.second + 1 << endl;
}