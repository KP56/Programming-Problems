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

//Zauważmy, że każdemu wierzchołkowi możemy przypisać wartość, którą nazwiemy jego kierunkiem. Początkowo będzie ona równa 0.
//W chwili gdy jakaś walizka trafi do tego konkretnego wierzchołka, zwiększymy tą wartość o 1 oraz zastosujemy operację x mod y,
//gdzie x to kierunek, a y to liczba krawędzi wychodzących z danego wierzchołka. W chwili gdy wszystkie te wartości będą równe 0,
//możemy powiedzieć, że układ się zresetował.

//Rozwiązanie O(S*n) (S - wynik)
//Możemy przeprowadzić symulację w której używamy zmodyfikowanego algorytmu DFS. Przy każdym wierzchołku modyfikujemy odpowiednio
//wartość oraz na podstawie jej poprzedniego stanu odwiedzamy kolejny wierzchołek. Na końcu liczymy ile kroków nam to zajęło.
//Wiadomo, że graf jest acyklicznie skierowany, ponieważ nie można łączyć wierzchołka z wyższym numerem z wierzchołkiem z niższym
//numerem, efektywnie usuwając jakąkolwiek możliwość powstawania krawędzi obustronnie skierowanych lub cykli.

bool isZero(vector<int> &vec) {
    for (int i : vec) {
        if (i != 0) {
            return false;
        }
    }

    return true;
}

void recursiveModification(int at, vector<vector<int>> &graph, vector<int> &state) {
    if (!graph[at].empty()) {
        recursiveModification(graph[at][state[at]], graph, state);
        state[at] = (state[at] + 1) % graph[at].size();
    }
}

void modifyState(vector<vector<int>> &graph, vector<int> &state) {
    recursiveModification(0, graph, state);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<vector<int>> graph(size);
    for (int i = 0; i < size; i++) {
        in_i(a);
        for (int j = 0; j < a; j++) {
            in_i(b);
            graph[i].pb(b - 1);
        }
    }

    vector<int> state(size);
    int i = 0;
    do {
        modifyState(graph, state);
        i++;
    } while(!isZero(state));

    cout << i << endl;
}