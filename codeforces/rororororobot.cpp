#include <bits/stdc++.h>

using namespace std;


int n;
vector<int> tree;

int f(int a, int b) {
    return max(a, b);
}

void build(vector<int> arr) {
    tree = vector<int>(arr.size() * 2);
    n = arr.size();

    for (int i = 0; i < n; i++)    
        tree[n + i] = arr[i];

    for (int i = n - 1; i > 0; --i)     
        tree[i] = f(tree[i << 1], tree[i << 1 | 1]);    
}

void updateTreeNode(int p, int value) {
    tree[p + n] = value;
    p = p + n;

    for (int i = p; i > 1; i >>= 1)
        tree[i >> 1] = f(tree[i], tree[i ^ 1]);
}

int query(int l, int r) {
    r++;
    int res = 0;

    for (l += n, r += n; l < r; l >>= 1, r >>= 1)
    {
        if (l&1) 
            res = f(res, tree[l++]);
      
        if (r&1) 
            res = f(res, tree[--r]);
    }
      
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int rows, columns;
    cin >> rows >> columns;

    vector<int> blocked;
    for (int i = 0; i < columns; i++) {
        int bottom_cells_blocked;
        cin >> bottom_cells_blocked;

        blocked.push_back(bottom_cells_blocked);
    }

    build(blocked);

    int queries;
    cin >> queries;

    for (int i = 0; i < queries; i++) {
        int x1, y1, x2, y2, k;
        cin >> x1 >> y1 >> x2 >> y2 >> k;
        x1--;
        y1--;
        x2--;
        y2--;

        //6 6 0 6
        //3

        int m = query(min(y1, y2), max(y1, y2));
        m -= x1;

        int b = m > 0 ? k * ((m - 1) / k + 1) + x1 : 0;
        if ((x1 - x2) % k == 0 && (y1 - y2) % k == 0 && b < rows) {
            cout << "YES" << "\n";
        } else {
            cout << "NO" << "\n";
        }
    }

    return 0;
}