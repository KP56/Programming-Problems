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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(m);

    int current_price = 0;
    vector<int> prices;
    for (int i = 0; i < n; i++) {
        ini(a);
        prices.pb(a);
        current_price += a;
    }

    vector<vector<int>> promotions;
    for (int i = 0; i < m; i++) {
        ini(product);
        ini(beginning);
        ini(finish);
        ini(new_price);

        product--;

        promotions.pb({beginning,finish,product,new_price});
    }

    sort(all(promotions));
    map<int,vector<int>> ends;
    int lowest_price = current_price;
    int day = 1;
    for (int i = 0; i < promotions.size(); i++) {
        auto promotion = promotions[i];

        while (!ends.empty() && (*ends.begin()).first < promotion[0]) {
            auto j = *ends.begin();
            for (int k : j.second) {
                current_price += k;
            }
            ends.erase(ends.begin());
        }

        int saved = prices[promotion[2]] - promotion[3];
        ends[promotion[1]].pb(saved);
        current_price -= saved;

        if (current_price < lowest_price) {
            lowest_price = current_price;
            day = promotion[0];
        }
    }

    cout << lowest_price << " " << day << endl;
}