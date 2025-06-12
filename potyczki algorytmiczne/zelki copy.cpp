#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);
    ini(m);

    // po kolorze: {masa,cena}
    vector<vector<pii>> by_color(k);
    for (int i = 0; i < n; i++) {
        ini(ki);
        ini(mi);
        ini(wi);

        ki--;

        by_color[ki].pb({mi,wi});
    }

    int max_quantity = n*m;

    // implementacja rozwiązania programowaniem dynamicznym
    vector<vector<vector<int>>> items(k,vector<vector<int>>(m,vector<int>(max_quantity+1)));
    for (int current_color = 0; current_color < k; current_color++) {
        vector<vector<vector<int>>> dp(by_color[current_color].size()+1,vector<vector<int>>(m,vector<int>(max_quantity+1,inf)));
        for (int i = 0; i <= by_color[current_color].size(); i++) {
            dp[i][0][0] = 0;
        }

        for (int i = 0; i < by_color[current_color].size(); i++) {
            for (int j = 0; j < m; j++) {
                for (int l = 0; l < max_quantity; l++) {
                    if (dp[i][j][l] != inf) {
                        for (int a = 1; a <= min(m,max_quantity-l); a++) {
                            dp[i+1][(j+a*by_color[current_color][i].first) % m][l+a] = min(dp[i+1][(j+a*by_color[current_color][i].first) % m][l+a],
                                    dp[i][j][l]+a*by_color[current_color][i].second);
                        }

                        dp[i+1][j][l] = min(dp[i+1][j][l],dp[i][j][l]);
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= max_quantity; j++) {
                items[current_color][i][j] = dp[by_color[current_color].size()][i][j];
            }
        }
    }

    // po znalezieniu tablicy items, wykonujemy kolejne programowanie dynamiczne
    vector<int> ans(m,inf);
    for (int jelly_quantity = 0; jelly_quantity <= max_quantity; jelly_quantity++) {
        vector<vector<int>> dp2(k+1,vector<int>(m,inf));

        dp2[0][0] = 0;

        for (int i = 0; i < k; i++) {
            for (int j = 0; j < m; j++) {
                if (dp2[i][j] != inf) {
                    for (int a = 0; a < m; a++) {
                        dp2[i+1][(j + a) % m] = min(dp2[i+1][(j + a) % m], dp2[i][j] + items[i][a][jelly_quantity]);
                    }
                }
            }
        }

        for (int i = 0; i < m; i++) {
            ans[i] = min(ans[i],dp2[k][i]);
        }
    }

    for (int i : ans) {
        if (i == inf) cout << -1 << endl;
        else cout << i << endl;
    }
}