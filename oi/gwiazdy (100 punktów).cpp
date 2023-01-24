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
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(n);
    in_i(s);
    s--;

    vector<vector<pii>> vec;
    int prev = -1;
    for (int i = 0; i < n - 1; i++) {
        in_i(l);
        in_i(r);
        if (l <= r && prev == 0) {
            vec[vec.size() - 1].push_back({l,r});
        } else if (l > r && prev == 1) {
            vec[vec.size() - 1].push_back({l,r});
        } else {
            vec.push_back({{l,r}});
        }

        if (l <= r) {
            prev = 0;
        } else {
            prev = 1;
        }
    }

    int occupied_left = 0;
    int occupied_right = 0;

    int current_pos = s;

    ll cost = 0;
    vector<bool> moves;
    for (vector<pii> v : vec) {
        int on_the_left = current_pos - ((s < current_pos) + occupied_left);
        int on_the_right = (n - current_pos - 1) - ((s > current_pos) + occupied_right);

        if (v[0].first <= v[0].second) {
            //lewo jest lepsze
            if (on_the_left < v.size()) {
                //mamy niewystarczająco miejsca po lewej, więc w pierwszych on_the_left + 1 ruchach tego segmentu musimy wykonać ruch w prawo
                int best_moment = -1;
                int min_diff = INT_MAX;
                for (int i = 0; i < on_the_left + 1 && i < v.size(); i++) {
                    //szukamy najlepszego momentu aby wykonać ruch w prawo
                    int a = v[i].second - v[i].first;
                    if (a < min_diff) {
                        min_diff = a;
                        best_moment = i;
                    }
                }

                occupied_left += v.size();
                current_pos = occupied_left - 1;

                cost += min_diff;
                for (pii p : v) {
                    cost += p.first;
                }

                for (int i = 0; i < best_moment; i++) {
                    moves.pb(false);
                }
                moves.pb(true);
                for (int i = best_moment + 1; i < v.size(); i++) {
                    moves.pb(false);
                }
            } else {
                //mamy wystarczająco miejsca po lewej, więc wystarczy, że cały czas ruchy w lewo będziemy robić
                for (pii p : v) {
                    cost += p.first;
                }

                occupied_left += v.size();
                current_pos = occupied_left - 1;

                for (int i = 0; i < v.size(); i++) {
                    moves.pb(false);
                }
            }
        } else {
            //prawo jest lepsze
            if (on_the_right < v.size()) {
                //mamy niewystarczająco miejsca po prawej, więc w pierwszych on_the_right + 1 ruchach tego segmentu musimy wykonać ruch w lewo
                int best_moment = -1;
                int min_diff = INT_MAX;
                for (int i = 0; i < on_the_right + 1; i++) {
                    //szukamy najlepszego momentu aby wykonać ruch w lewo
                    int a = v[i].first - v[i].second;
                    if (a < min_diff) {
                        min_diff = a;
                        best_moment = i;
                    }
                }

                occupied_right += v.size();
                current_pos = (n - 1 - occupied_right) + 1;

                cost += min_diff;
                for (pii p : v) {
                    cost += p.second;
                }

                for (int i = 0; i < best_moment; i++) {
                    moves.pb(true);
                }
                moves.pb(false);
                for (int i = best_moment + 1; i < v.size(); i++) {
                    moves.pb(true);
                }
            } else {
                //mamy wystarczająco miejsca po prawej, więc wystarczy, że cały czas ruchy w prawo będziemy robić
                for (pii p : v) {
                    cost += p.second;
                }

                occupied_right += v.size();
                current_pos = (n - 1 - occupied_right) + 1;

                for (int i = 0; i < v.size(); i++) {
                    moves.pb(true);
                }
            }
        }
    }

    vector<pair<int,bool>> packed;
    prev = -1;
    for (bool b : moves) {
        if (prev != -1) {
            if (b == prev) {
                packed[packed.size() - 1].first++;
            } else {
                packed.pb(mp(1,b));
            }
        } else {
            packed.pb(mp(1,b));
        }

        prev = b;
    }

    cout << cost << endl;

    current_pos = s;
    int right_edge = n - 1;
    int left_edge = 0;
    cout << s + 1 << " ";
    for (auto i : packed) {
        if (i.second) {
            for (int j = i.first - 1; j >= 0; j--) {
                //przemieszczamy się w prawo
                if (s >= right_edge - j) {
                    cout << right_edge - j << " ";
                } else {
                    cout << right_edge - j + 1 << " ";
                }
            }
            right_edge -= i.first;
        } else {
            for (int j = i.first - 1; j >= 0; j--) {
                //przemieszczamy się w lewo
                if (s <= left_edge + j) {
                    cout << left_edge + j + 2 << " ";
                } else {
                    cout << left_edge + j + 1 << " ";
                }
            }
            left_edge += i.first;
        }
    }

    cout << endl;
}