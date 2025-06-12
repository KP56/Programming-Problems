#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define int long long
#define pb push_back


signed main() {
    ordered_set<int> s;
    s.insert(1);
    cout << *s.lower_bound(1) << endl;
    
    if (s.upper_bound(1) == s.end()) {
        cout << "TEST SUCCESSFUL" << endl;
    }
}
