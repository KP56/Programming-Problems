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

bool inRange(int a, int l, int r) {
    return a >= l && a <= r;
}

//1 - dodanie elementu zwiększy liczbę obszarów
//-1 - dodanie elementu zmniejszy liczbę obszarów o 1
//-2 - dodanie elementu zmniejszy liczbę obszarów o 2
//0 - nie zmieni liczby obszarów
int condition(int x, int y, vector<vector<int>> &vec, int l, int r) {
    //Jeżeli żaden z sąsiadów nie jest oznaczony, zwracamy 1.
    if (!inRange(vec[y][(x + 1) % vec[0].size()], l, r) && !inRange(vec[y][(x == 0 ? vec[0].size() - 1 : x - 1)], l, r)
            && !inRange(vec[!y][x], l, r)) {
        return 1;
    }

    //Kolejny przypadek, jeżeli w drugim rzędzie oraz
    //po prawej jest kwadraty oznaczony i tam w drugim rzędzie nie ma
    //lub po lewej jest kwadrat oznaczony i tam w drugim rzędzie nie ma,
    //zwracamy -1 lub -2. (-2 jeśli po prawej i lewej został warunek spełniony)
    if (inRange(vec[!y][x], l, r)) {
        int ret = 0;
        if (inRange(vec[y][(x + 1) % vec[0].size()], l, r) && !inRange(vec[!y][(x + 1) % vec[0].size()], l, r)) {
            ret--;
        }

        if (inRange(vec[y][(x == 0 ? vec[0].size() - 1 : x - 1)], l, r) && !inRange(vec[!y][(x == 0 ? vec[0].size() - 1 : x - 1)], l, r)) {
            ret--;
        }

        return ret;
    }

    //W przeciwnym wypadku jeżeli po lewej i prawej są kwadraty oznaczone oraz
    //w drugim rzędzie w tej samej kolumnie jest pusto lub w jednym z miejsc po lewej lub prawej od tamtego pustego jest pusto,
    //zwracamy -1.
    if (inRange(vec[y][(x + 1) % vec[0].size()], l, r) && inRange(vec[y][(x == 0 ? vec[0].size() - 1 : x - 1)], l, r)) {
        for (int i = -1; i <= 1; i++) {
            if (!inRange(vec[!y][(x + i) % vec[0].size()], l, r)) {
                return -1;
            }
        }
    }

    //W ostatnim przypadku zwracamy 0.
    return 0;
}

int propagate(int x, int y, vector<vector<int>> &vec, vector<vector<bool>> &swapped, int l, int r) {
    vector<pii> v = {
        mp((x + 1) % vec[0].size(), y),
        mp(x == 0 ? vec[0].size() - 1 : x - 1, y),
        mp(x, !y)
    };

    swapped[y][x] = true;

    int a = 0;
    for (pii p : v) {
        if (!swapped[p.second][p.first] && inRange(vec[p.second][p.first], l, r)) {
            a++;
            propagate(p.first, p.second, vec, swapped, l, r);
        }
    }
    
    return a;
}

int neighbourSwap(int x, int y, vector<vector<int>> &vec, vector<vector<bool>> &swapped, int l, int r) {
    vector<pii> v = {
        mp((x + 1) % vec[0].size(), y),
        mp(x == 0 ? vec[0].size() - 1 : x - 1, y),
        mp(x, !y)
    };

    for (pii p : v) {
        if (swapped[p.second][p.first]) {
            return -propagate(x, y, vec, swapped, l, r) - 1;
        }
    }

    if (x == vec[0].size() - 1 && inRange(vec[y][0], l, r)) {
        return -propagate(x, y, vec, swapped, l, r);
    } else if (x == 0 && inRange(vec[y][vec[0].size() - 1], l, r)) {
        return -propagate(x, y, vec, swapped, l, r);
    }

    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_i(interest);

    vector<vector<int>> vec(2);
    vector<pii> loc(size * 2);
    for (int i = 0; i < size; i++) {
        in_i(a);
        loc[a - 1] = mp(i, 0);
        vec[0].pb(a - 1);
    }

    for (int i = 0; i < size; i++) {
        in_i(b);
        loc[b - 1] = mp(i, 1);
        vec[1].pb(b - 1);
    }

    vector<int> solutions(size * 2 + 1);
    for (int l = 0; l < 2*size; l++) {
        int zones = 0;
        vector<vector<bool>> swapped(2, vector<bool>(size));
        for (int r = l; r < 2*size; r++) {
            pii p = loc[r];
            int a = neighbourSwap(p.first, p.second, vec, swapped, l , r);
            if (a != 0) {
                zones += a + 1;
            } else {
                zones += condition(p.first, p.second, vec, l, r);
            }
            if (zones < 0) {
                cout << "COŚ POSZŁO NIE TAK!" << endl;
            } else {
                solutions[zones]++;
            }
        }
    }

    for (int i = 0; i < interest; i++) {
        cout << solutions[i + 1] << " ";
    }
    cout << endl;
}