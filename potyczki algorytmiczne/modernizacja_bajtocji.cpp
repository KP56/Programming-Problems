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

// https://codeforces.com/blog/entry/62393
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

// https://cp-algorithms.com/data_structures/disjoint_set_union.html
struct disjoint_set_union {
    vector<int> parent;
    vector<int> rank;
    vector<int> node_count;
    vector<bool> matches_conditions;

    disjoint_set_union(int size) {
        parent = vector<int>(size,-1);
        rank = vector<int>(size);
        // utrzymuje ilość wierzchołków w zbiorze
        node_count = vector<int>(size);
        // sprawdza czy możemy być pewni, że mieszkaniec ma laptopa
        matches_conditions = vector<bool>(size);
    }

    void add_element() {
        parent.pb(-1);
        rank.pb(0);
        node_count.pb(0);
        matches_conditions.pb(false);
    }

    void make_set(int v) {
        parent[v] = v;
        rank[v] = 0;
        node_count[v] = 1;
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                swap(a, b);
            }
            // gdy zmieniamy parenta, przenosimy node_count
            parent[b] = a;
            node_count[a] += node_count[b];
            node_count[b] = 0;
            matches_conditions[a] = matches_conditions[a] || matches_conditions[b];
            matches_conditions[b] = false;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
        }
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }
        return parent[v] = find_set(parent[v]);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(q);

    // wykorzystam dsu do rozwiązania tego problemu
    disjoint_set_union dsu(n);
    // tworzę mapping, aby obsługiwać usuwanie elementów
    vector<int> mapping;
    for (int i = 0; i < n; i++) {
        mapping.pb(i);
    }
    for (int i = 0; i < q; i++) {
        instr(type);
        if (type == "+") {
            ini(a);
            ini(b);
            a--;
            b--;

            // na początek sprawdzamy czy te elementy już istnieją w dsu
            if (dsu.parent[mapping[a]] == -1) {
                dsu.make_set(mapping[a]);
            }
            
            if (dsu.parent[mapping[b]] == -1) {
                dsu.make_set(mapping[b]);
            }

            int set1 = dsu.find_set(mapping[a]);
            int set2 = dsu.find_set(mapping[b]);
            // jeżeli zbiory w których znajdują się a oraz b są takie same, wtedy stworzyliśmy cykl i oznaczamy zbiór jako spełniający warunki
            if (set1 == set2) {
                dsu.matches_conditions[set1] = true;
            } else {
                // skoro oba elementy już istnieją w dsu, wtedy wystarczy połączyć oba zbiory
                dsu.union_sets(mapping[a],mapping[b]);
            }
        } else if (type == "-") {
            ini(a);
            a--;

            // dsu nie obsługuje usuwania elementów, mógłbym skorzystać z link-cut tree, ale mam lepszy pomysł
            // zwyczajnie każdy element będzie posiadał mapping, który dokona tranzlacji z tego typu indeksowania
            // do wewnętrznego typu indeksowania, następnie zamiast usuwać element, zmienię jedynie mapping tak, aby
            // ten element był nowym elementem oraz zmniejszę node count

            dsu.node_count[dsu.find_set(mapping[a])]--;

            mapping[a] = dsu.parent.size();
            dsu.add_element();
        } else {
            ini(a);
            a--;

            int set_a;

            // jeżeli nie ma w żadnym zbiorze lub wszystko ze zbioru zostało usunięte
            if (dsu.parent[mapping[a]] == -1 || (dsu.node_count[set_a = dsu.find_set(mapping[a])] == 1 && !dsu.matches_conditions[set_a])) {
                cout << "0";
            } else {
                // znajduje się w jakimś zbiorze w którym istnieją inne wierzchołki w tej sytuacji

                if (dsu.matches_conditions[set_a]) {
                    // jeżeli zbiór jest oznaczony jako posiadający same osoby, które mają laptopy, wtedy odpowiedzią jest 1
                    cout << "1";
                } else {
                    // w przeciwnym razie odpowiedź to znak zapytania
                    cout << "?";
                }
            }
        }
    }
    cout << endl;
}