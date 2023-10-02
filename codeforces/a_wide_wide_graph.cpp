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

void findFurthest(int at, int prev, vector<vector<int>> &tree, vector<int> &dist, int distance) {
    dist[at] = distance;
    for (int i : tree[at]) {
        if (i != prev) {
            findFurthest(i, at, tree, dist, distance + 1);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    vector<vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++) {
        ini(a);
        ini(b);
        a--;
        b--;
        tree[a].pb(b);
        tree[b].pb(a);
    }

    //first we want to find a diameter of the tree
    //since we know that the node furthest away from any node is one of the ends of a diameter, we just perform a DFS to find one end
    //and use DFS from that end to find the other end
    vector<int> dist1(n);
    findFurthest(0, -1, tree, dist1, 0);
    int first_end = max_element(all(dist1)) - dist1.begin();
    vector<int> dist2(n);
    findFurthest(first_end, -1, tree, dist2, 0);
    int second_end = max_element(all(dist2)) - dist2.begin();
    vector<int> dist3(n);
    findFurthest(second_end, -1, tree, dist3, 0);
    //since we know both ends, we now just need to generate an array representing the maximal distance to one of those ends
    vector<int> max_dist(n);
    for (int i = 0; i < n; i++) {
        max_dist[i] = max(dist3[i], dist2[i]);
    }

    //sorting distances from greatest to lowest
    sort(all(max_dist), greater<int>());
    max_dist.erase(max_dist.begin());

    //we can use dp to generate answers for next k from k=n to k=1
    vector<int> ans;
    int current = 0;
    for (int k = n; k > 0; k--) {
        while (current < n-1 && max_dist[current] >= k) {
            current++;
        }
        ans.pb(n - current);
    }

    reverse(all(ans));
    for (int i : ans) {
        cout << i << " ";
    }
    cout << endl;
}