#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<
    T,
    null_type,
    std::less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define st first
#define nd second
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

vector<int> query_for_each(vector<vector<int>> vec) {
    sort(all(vec));

    ordered_set<int> s;
    vector<int> elements_lower(vec.size());
    for (vector<int> &i : vec) {
        auto it = s.end();
        if (!s.empty()) {
            it = s.lower_bound(i[1]);

            it--;
        }

        if (it == s.end()) {
            elements_lower[i[2]] = 0;
        } else {
            int elements_with_it = s.order_of_key(*it) + 1;
            elements_lower[i[2]] = elements_with_it;
        }

        s.insert(i[1]);
    }

    return elements_lower;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);

    vector<vector<int>> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        ini(b);
        vec.pb({a,b,i});
    }
    
    vector<vector<int>> reversed_vec = vec;

    for (int i = 0; i < n; i++) {
        reversed_vec[i][0] *= -1;
        reversed_vec[i][1] *= -1;
    }

    vector<int> reversed_values = query_for_each(reversed_vec);

    vector<int> domineering;
    vector<int> not_domineering;
    for (int i = 0; i < n; i++) {
        if (reversed_values[i] == 0) {
            domineering.pb(i);
        } else {
            not_domineering.pb(i);
        }
    }

    if (domineering.size() % 2 == 0) {
        cout << "TAK" << endl;
    } else {
        for (int i : not_domineering) {
            if (reversed_values[i] < domineering.size()) {
                cout << "TAK" << endl;
                return 0;
            }
        }

        cout << "NIE" << endl;
    }
}
