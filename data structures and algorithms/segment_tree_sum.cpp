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

struct segment_tree_range_query {
    vector<int> tree;
    int n;

    segment_tree_range_query(int size) {
        tree = vector<int>(size * 2);
        this->n = size;
    }

    void update(int position, int element) {
        tree[position + n] += element;

        for (position += n; position > 1; position >>= 1) {
            tree[position >> 1] = tree[position] + tree[position^1];
        }
    }

    int query(int l, int r) {
        int res = 0;

        r++;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res += tree[l++];
            if (r&1) res += tree[--r];
        }

        return res;
    }
};

struct segment_tree_range_modification {
    vector<int> tree;
    int n;

    segment_tree_range_modification(int size) {
        tree = vector<int>(size * 2);
        this->n = size;
    }

    void update(int l, int r, int element) {
        r++;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) tree[l++] += element;
            if (r&1) tree[--r] += element;
        }
    }

    int query(int position) {
        int res = 0;

        for (position += n; position > 0; position >>= 1) {
            res += tree[position];
        }

        return res;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    segment_tree_range_query tree_test(5);
    tree_test.update(2,3);
    tree_test.update(0,2);

    cout << tree_test.query(0,2) << endl; // 5
    cout << tree_test.query(2,2) << endl; // 3
    cout << tree_test.query(0,0) << endl; // 2
    cout << tree_test.query(4,5) << endl; // 0
    cout << tree_test.query(0,5) << endl; // 5

    segment_tree_range_modification tree_test2(5);
    tree_test2.update(1,4,3);
    tree_test2.update(3,5,1);

    cout << tree_test2.query(0) << endl; // 0
    cout << tree_test2.query(1) << endl; // 3
    cout << tree_test2.query(2) << endl; // 3
    cout << tree_test2.query(3) << endl; // 4
    cout << tree_test2.query(4) << endl; // 4
    cout << tree_test2.query(5) << endl; // 1
}