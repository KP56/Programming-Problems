#include <bits/stdc++.h>

#define int long long int

using namespace std;

// aktualizacje na przedziałach, zapytania o punkty
struct range_tree {
    vector<int> tree;
    int n;

    range_tree(int n) {
        this->n = n;
        tree = vector<int>(2*n);
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

vector<int> solve(int n, int k, vector<vector<int>> q) {
    unordered_map<int,unordered_map<int,vector<pair<int,int>>>> queries;
    for (auto i : q) {
        int a = i[0];
        int l = i[1];
        int d = i[2];

        int modulo = a % d;

        queries[d][modulo].push_back({a/d,a/d+l-1});
    }

    vector<int> res(n);
    // gdy mam stworzoną tablicę queries, dla każdego modulo tworzę drzewo przedziałowe o n/d+1 elementach
    for (auto i : queries) {
        int divisor = i.first;

        for (auto j : i.second) {
            int modulo = j.first;
            
            range_tree tree(n/divisor+1);

            for (auto k : j.second) {
                int range_begin = k.first;
                int range_end = k.second;

                tree.update(range_begin,range_end,1);
            }

            // teraz iterujemy po drzewie i zbieramy odpowiedzi
            for (int k = 0; k < n/divisor+1; k++) {
                if (k*divisor+modulo < n) {
                    res[k*divisor+modulo] += tree.query(k);
                }
            }
        }
    }

    return res;
}

vector<int> bruteforce(int n, int k, vector<vector<int>> q) {
    vector<int> res(n);

    for (auto i : q) {
        for (int j = i[0]; j <= i[0]+(i[1]-1)*i[2]; j += i[2]) {
            res[j]++;
        }
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    //int n = rand() % 10 + 1, k = rand() % 10 + 1;
    int n, k;
    cin >> n >> k;

    vector<vector<int>> q;
    for (int i = 0; i < k; i++) {
        /*int a = rand() % n + 1;
        int d = rand() % n + 1;
        int l = rand() % ((n-a)/d+1) + 1; //a+d*(l-1) <= n <=> l-1 <= (n-a)/d <=> l <= (n-a)/d+1*/
        int a,l,d;
        cin >> a >> l >> d;

        a--;

        q.push_back({a,l,d});
    }

    //vector<int> brute_res = bruteforce(n,k,q);
    vector<int> res = solve(n,k,q);

    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;
}
