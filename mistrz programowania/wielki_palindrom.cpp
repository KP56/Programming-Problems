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

string generate_half(int n, int k) {
    string str = "";
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            str += "9";
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) {
                str += "9";
            } else {
                str += "8";
            }
        }
    }

    return str;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    // Dokonajmy pewnej obserwacji.
    // Jeśli n jest nieparzyste to k musi być <= 2, aby nie było sprzeczności
    // Jeśli n jest parzyste to k=1

    if (n % 2 == 1 && k > 2) {
        cout << "NIE" << endl;
        return 0;
    }

    if (n % 2 == 0 && k > 1) {
        cout << "NIE" << endl;
        return 0;
    }

    int actual_n = n/2;
    // Najpierw wygenerujemy pierwszą połowę
    string half = generate_half(actual_n, k);
    string cp = half;
    reverse(all(half));

    string res = cp;
    if (n % 2 == 0) {
        res += half;
    } else if (k == 1) {
        res += "9";
        res += half;
    } else if (actual_n % 2 == 0) {
        res += "9";
        res += half;
    } else {
        res += "8";
        res += half;
    }

    cout << res << endl;
}