#include <bits/stdc++.h>
using namespace std;

//point modifications, range queries
//https://www.geeksforgeeks.org/segment-tree-efficient-implementation/
template<typename T> struct RangeTree {
    int n;
    vector<T> tree;
    function<T(T,T)> f;
    T operation;

    RangeTree(vector<T> arr, function<T(T,T)> f, T operation) {
        tree = vector<T>(arr.size() * 2);
        n = arr.size();
        this->f = f;

        for (int i = 0; i < n; i++)
            tree[n + i] = arr[i];

        for (int i = n - 1; i > 0; --i)
            tree[i] = f(tree[i << 1], tree[i << 1 | 1]);
        
        this->operation = operation;
    }

    void updateTreeNode(int p, T value) {
        tree[p + n] = value;
        p = p + n;

        for (int i = p; i > 1; i >>= 1)
            tree[i >> 1] = f(tree[i], tree[i ^ 1]);
    }

    T query(int l, int r) {
        r++;
        T res = operation;

        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) 
                res = f(res, tree[l++]);
      
            if (r&1) 
                res = f(res, tree[--r]);
        }
      
        return res;
    }
};

//range modifications, point queries
template<typename T> class IntervalTree {
private:
    function<T(T,T)> inc_f;
    vector<T> t;
    int n;
    T def;
public:
    IntervalTree(vector<T> vec, function<T(T,T)> inc_f, T def) {
        t = vector<T>(vec.size() * 2, def);
        n = vec.size();
        this->inc_f = inc_f;
        this->def = def;

        for (int i = 0; i < vec.size(); i++) {
            inc(i,i,vec[i]);
        }
    }

    void inc(int l, int r, T value) {
        r++;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) {
                t[l] = inc_f(t[l], value);
                l++;
            }
            if (r&1) {
                t[r - 1] = inc_f(t[r - 1], value);
                r--;
            }
        }
    }

    T query(int p) {
        T res = def;
        for (p += n; p > 0; p >>= 1) res = inc_f(res, t[p]);
        return res;
    }
};

int f(int x, int y) {
    return max(x,y);
}

int increase(int x, int y) {
    return x + y;
}

int main() {
    /*SegmentTree<int> tree({1,3,5,7},&f,&increase,0,INT_MIN);
    tree.inc(0,1,10);
    cout << tree.query(0,2) << endl;*/
    /*RangeTree<int> tree({1,3,5,7},&f,INT_MIN);
    tree.updateTreeNode(0,10);
    cout << tree.query(1,2) << endl;*/
    /*IntervalTree<int> tree({1,3,5,7},&increase,0);
    tree.inc(0,1,10);
    cout << tree.query(3) << endl;*/

    return 0;
}