#include <bits/stdc++.h>
#include "kaslib.h"

using namespace std;

#define int __int128
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

int limit = inf;

int find_pow(int a, int k) {
    int b = a;
    while (b <= k / a) {
        b *= a;
    }

    return b;
}

vector<int> primes_up_to_n(int n) {
    vector<bool> v(n + 1,true);
    v[0] = false;
    v[1] = false;

    for (int i = 2; i * i <= n; i++) {
        if (v[i]) {
            for (int j = i * i; j <= n; j += i) {
                v[j] = false;
            }
        }
    }

    vector<int> primes;
    for (int i = 0; i <= n; i++) {
        if (v[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int k = 30000;
    int t = 0;

    vector<int> orig = primes_up_to_n(k);

    vector<pii> all_ps;
    for (int i : orig) {
        int j = i;
        while (j < limit) {
            all_ps.pb({j,i});
            j *= i;
        }
    }
    sort(all(all_ps));

    while (true) {
        int resulting_num = 1;
        int current = 0;
        vector<bool> vis(k+1);
        while (current < all_ps.size()) {
            int current_query_num = 1;
            vector<pii> to_cross_check;
            for (; current < all_ps.size(); current++) {
                pii i = all_ps[current];
                if (vis[i.second]) {
                    continue;
                }

                if (current_query_num * i.first > limit) {
                    break;
                }
                current_query_num *= i.first;
                to_cross_check.pb(i);
            }

            int die_antworte = Pytaj(current_query_num);

            for (pii i : to_cross_check) {
                if (die_antworte % i.first == 0) {
                    resulting_num *= i.second;
                } else {
                    vis[i.second] = true;
                }
            }
        }

        if (resulting_num <= limit / orig[orig.size() - 1]) {
            Szturchnij();
            continue;
        }

        Odpowiedz(resulting_num);
    }
}