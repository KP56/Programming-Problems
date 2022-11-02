#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(n);
    in_i(m);
    
    vector<vector<pii>> vec(1000000);
    for (int i = 0; i < m; i++) {
        in_i(l);
        in_i(r);

        in_i(k);
        vec[l - 1].pb(mp(r - 1, k - 1));
    }
    
    vector<vector<pii>> yb_pairs(1000000);
    vector<pii> ranges[3];
    pii prev[3] = {mp(-1,-1),mp(-1,-1),mp(-1,-1)};
    //łączenie wspólnych zakresów
    for (int l = 0; l < vec.size(); l++) {
        for (auto p : vec[l]) {
            int r = p.first;
            int k = p.second;

            if (l <= prev[k].second || prev[k].second == -1) {
                prev[k] = mp(prev[k].first == -1 ? l : prev[k].first, max(r, prev[k].second));
            } else {
                ranges[k].pb(prev[k]);
                if (k != 2) {
                    yb_pairs[prev[k].first].pb(mp(k,prev[k].second));
                }
                prev[k] = mp(l,r);
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (prev[i].second != -1) {
            ranges[i].pb(prev[i]);
            if (i != 2) {
                yb_pairs[prev[i].first].pb(mp(i,prev[i].second));
            }
        }
    }

    vector<pii> g_ranges;
    pii current_b = mp(-1,-1);
    pii current_y = mp(-1,-1);
    for (int l = 0; l < 1000000; l++) {
        for (auto i : yb_pairs[l]) {
            pair<int,pii> p = mp(i.first, mp(l, i.second));
            //cout << "yb: " << l << " " << i.second << endl;
            if (p.first == 0) {
                current_y = p.second;
            } else {
                current_b = p.second;
            }

            if (current_b.first != -1 && current_y.first != -1) {
                pii range = mp(max(current_b.first, current_y.first),min(current_b.second, current_y.second));
                if (range.first <= range.second) {
                    g_ranges.pb(range);
                }
            }
        }
    }

    /*for (auto i : ranges[0]) {
        cout << "yellow: " << i.first << " " << i.second << endl;
    }

    for (auto i : ranges[1]) {
        cout << "blue: " << i.first << " " << i.second << endl;
    }

    for (auto i : g_ranges) {
        cout << "green: " << i.first << " " << i.second << endl;
    }

    for (auto i : ranges[2]) {
        cout << "red: " << i.first << " " << i.second << endl;
    }*/

    vector<vector<pair<bool,int>>> vec2(1000000);
    //sortowanie zakresów zielonych i czerwonych w osobnej strukturze
    for (pii i : g_ranges) {
        vec2[i.first].pb(mp(true,i.second));
    }
    for (pii i : ranges[2]) {
        vec2[i.first].pb(mp(false,i.second));
    }

    //wyszukiwanie wspólnych zakresów zielonych i czerwonych
    pii prev_g = mp(-1,-1);
    pii prev_r = mp(-1,-1);
    vector<pii> rg_ranges;
    for (int l = 0; l < 1000000; l++) {
        for (auto i : vec2[l]) {
            bool is_g = i.first;
            int r = i.second;

            if (is_g)
                prev_g = mp(l,r);
            else
                prev_r = mp(l,r);
            
            if (prev_g.first != -1 && prev_r.first != -1) {
                pii rg_range = mp(max(prev_g.first,prev_r.first),min(prev_g.second,prev_r.second));
                if (rg_range.first <= rg_range.second) {
                    rg_ranges.pb(rg_range);
                }
            }
        }
    }

    int green = 0;
    for (pii i : g_ranges) {
        green += i.second - i.first + 1;
    }
    for (pii i : rg_ranges) {
        green -= i.second - i.first + 1;
    }

    cout << green << endl;
}