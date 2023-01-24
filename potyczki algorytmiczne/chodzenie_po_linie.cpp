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

//Można zauważyć, że poniższy warunek musi zostać spełniony, aby liny się przecięły:
//x1 - pozycja x na pierwszej wysokości
//x2 - pozycja x na drugiej wysokości
//x3 - pozycja x drugiej liny na pierwszej wysokości
//x4 - pozycja x drugiej liny na drugiej wysokości

//(x1 < x3 && x2 > x4) || (x1 > x3 && x2 < x4)
//Wiedząc to jesteśmy w stanie skonstruować graf w czasie O(n^2) poprzez
//iterację przez wszystkie pary lin i sprawdzenie powyższego warunku.
//Następnie stosując algorytm Floyda-Warshalla oraz iterację po rzędach
//otrzymanej tabelki znajdujemy odpowiedź w czasie O(n^3).

//Głównym problemem jest stosowanie algorytmu Floyda-Marshalla w celu znalezienia
//odpowiedzi. Wiadomo, że wszystkie krawędzie mają długość 1. W takim razie najkrótsza trasa to taka, która przechodzi
//przez najmniej wierzchołków. W związku z tym przy pomocy algorytmu BFS dla każdego
//wierzchołka możemy znaleźć długość najkrótszej ścieżki do każdego innego w czasie liniowym.
//Skoro szukamy sumy, to wystarczy przechowywać zmienną o nazwie sum podczas iteracji przez wierzchołki
//i dla każdego wierzchołka dodawać jego odległość do sum. Otrzymamy w ten sposób odpowiedź.
//Złożoność czasowa tego rozwiązania to O(n^2).

//Dla każdego x-a na pierwszej wysokości istnieje dokładnie jedna lina. Dokładnie to samo dla x-a na drugiej
//wysokości. Oznacza to, że liny nigdy nie będą przyczepione do tego samego punktu.

int bfs(int at, vector<vector<int>> &graph) {
    vector<bool> vis(graph.size());
    queue<pii> q;
    q.push(mp(at,0));
    int sum = 0;
    while (!q.empty()) {
        int next = q.front().first;
        vis[next] = true;
        int dist = q.front().second;
        sum += dist;
        q.pop();
        for (int i : graph[next]) {
            if (!vis[i]) {
                vis[i] = true;
                q.push(mp(i,dist + 1));
            }
        }
    }

    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    vector<int> vec;
    for (int i = 0; i < size; i++) {
        in_i(a);
        vec.pb(a);
    }

    vector<vector<int>> graph(size);
    for (int x1 = 0; x1 < vec.size(); x1++) {
        int x2 = vec[x1];
        for (int x3 = x1 + 1; x3 < vec.size(); x3++) {
            int x4 = vec[x3];
            if (x2 > x4) {
                graph[x1].pb(x3);
                graph[x3].pb(x1);
            }
        }
    }

    for (int i = 0; i < size; i++) {
        cout << bfs(i, graph) << " ";
    }
    cout << endl;
}