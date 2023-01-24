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

void recursiveMark(int at, vector<bool> &vis, vector<int> &graph) {
    vis[at] = true;
    if (!vis[graph[at]]) {
        recursiveMark(graph[at],vis,graph);
    }
}

vector<int> stronglyConnectedComponents(vector<int> &graph) {
    vector<bool> vis(graph.size());
    vector<int> ans;
    for (int i = 0; i < graph.size(); i++) {
        if (!vis[i]) {
            ans.pb(i);
            recursiveMark(i,vis,graph);
        }
    }

    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);


    in_i(size);
    vector<pii> heights;
    for (int i = 0; i < size; i++) {
        in_i(h);
        heights.pb(mp(h,i));
    }
    sort(all(heights));
    vector<int> graph(size);
    vector<int> rev_graph(size);
    for (int i = 0; i < size; i++) {
        graph[heights[i].second] = i;
        rev_graph[i] = heights[i].second;
    }

    //Można udowodnić, że wyświetlanie list o nieparzystej liczbie elementów nie ma sensu, ponieważ
    //środkowy element zostanie na tym samym miejscu.

    //Każdą listę liczb o parzystej liczbie elementów można podzielić na dwie połowy, a drugą połowę
    //obrócić. Po zrobieniu tego osoby o tych samych indeksach na obu listach zamienią się miejscami.

    //Jesteśmy w stanie również znaleźć informację nt. indeksu na jakim liczba ostatecznie musi się znaleźć.

    //Można zauważyć, że obecny problem w takim razie polega na znalezieniu takich kombinacji zamian, aby
    //doprowadzić wszystkie liczby na odpowiednie indeksy.

    //Jeżeli zreprezentujemy sobie jako graf zależności dot. miejsca w którym dana liczba powinna się znaleźć,
    //możemy zauważyć, że pojedyńcza zamiana powoduje usunięcie krawędzi, które były skierowane z pierwszego wierzchołka
    //do drugiego lub z drugiego do pierwszego. W przypadku gdy jest tam druga krawędź, która nie zostanie usunięta,
    //zostanie ona przeniesiona na drugi wierzchołek.

    //W takim razie wystarczy, że nasz program doprowadzi do sytuacji w której wszystkie wierzchołki są połączone ze sobą dwoma
    //krawędziami. Wtedy w jednym ruchu można rozwiązać ten problem.

    //Zamiany potrzebne, aby graph[graph[i]] = i, można dokonać w jednej rundzie. Po prostu tworzymy odwrócony graf o nazwie
    //rev_graph. Dla każdej składowej spójnie silnej, zaczynając od pierwszego wierzchołka, dokonujemy takiej modyfikacji, że
    //zamieniamy miejscami (graph[i],rev_graph[i]). Następnie w miejscu rev_graph[i] pojawia się graph[i]. Dokonujemy dokładnie
    //ten sam krok co wcześniej tylko teraz dla tego nowego miejsca. Jeżeli dojdziemy do takiej sytuacji, że po wykonaniu operacji
    //w nowym miejscu graph[graph[i]] = i jest prawdziwe, kończymy i przechodzimy do następnej składowej spójnie silnej.

    vector<int> vec = stronglyConnectedComponents(graph);
    vector<pii> pairs;
    vector<int> changed(graph.size());
    for (int i = 0; i < changed.size(); i++) {
        changed[i] = i;
    }
    for (int i : vec) {
        while (i != graph[graph[i]]) {
            pairs.pb(mp(graph[i],rev_graph[i]));
            changed[graph[i]] = rev_graph[i];
            changed[rev_graph[i]] = graph[i];
            int currently_connected = graph[i];
            int newly_connected = rev_graph[i];
            //graph[i] oznacza do czego podłączone jest i
            //rev_graph[i] oznacza co jest podłączone do i

            //w chwili zamiany miejscami to do jakich wierzchołków są te wierzchołki
            //podłączone nie ulega zmianie, jednak wszystkie wierzchołki które były podłączone
            //do nich się zmieniają

            int cp = rev_graph[currently_connected];
            graph[rev_graph[currently_connected]] = newly_connected;
            graph[rev_graph[newly_connected]] = currently_connected;
            rev_graph[currently_connected] = rev_graph[newly_connected];
            rev_graph[newly_connected] = cp;

            i = currently_connected;
        }
    }

    int req_moves = 2;
    if (pairs.empty()) {
        req_moves--;
    }

    vector<int> first;
    vector<int> second;
    for (pii p : pairs) {
        first.pb(p.first);
        second.pb(p.second);
    }
    reverse(all(second));

    vector<int> total = first;
    for (int i : second) {
        total.pb(i);
    }

    vector<int> first2;
    vector<int> second2;
    bool remove = true;
    vector<bool> vis(graph.size());
    for (int i = 0; i < graph.size(); i++) {
        if (graph[graph[i]] == i && graph[i] != i) {
            if (!vis[i] && !vis[graph[i]]) {
                remove = false;
                first2.pb(changed[i]);
                second2.pb(changed[graph[i]]);
                vis[i] = true;
                vis[graph[i]] = true;
            }
        }
    }
    req_moves -= remove;
    reverse(all(second2));
    vector<int> total2 = first2;
    for (int i : second2) {
        total2.pb(i);
    }

    cout << req_moves << endl;
    if (req_moves == 2) {
        cout << total.size() << endl;
        for (int i : total) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }

    if (req_moves >= 1) {
        cout << total2.size() << endl;
        for (int i : total2) {
            cout << i + 1 << " ";
        }
        cout << endl;
    }
}