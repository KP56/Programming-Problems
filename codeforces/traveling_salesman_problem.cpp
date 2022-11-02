#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lli = long long int;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using vlli = vector<lli>;
using vvlli = vector<vector<lli>>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)
#define vec(x, y) vector<(x)> y

void readCaseData() {
    in_i(size);

    vector<pair<int, int>> arr;
    for (int i = 0; i < size; i++) {
        in_i(x);
        in_i(y);

        arr.pb({x, y});
    }

    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX;
    for (auto i : arr) {
        max_x = max(max_x, i.first);
        max_y = max(max_y, i.second);
        min_x = min(min_x, i.first);
        min_y = min(min_y, i.second);
    }

    int result = 0;

    if (max_x > 0) {
        result += max_x * 2;
    }

    if (max_y > 0) {
        result += max_y * 2;
    }

    if (min_x < 0) {
        result += min_x * (-2);
    }

    if (min_y < 0) {
        result += min_y * (-2);
    }

    cout << result << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}