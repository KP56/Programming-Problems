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


struct node {
    vector<int> children;
    int first;
    int second;
    int depth;
    int root_ind;

    node(int first, int second, int depth, int root_ind) {
        this->first = first;
        this->second = second;
        this->depth = depth;
        this->root_ind = root_ind;
    }
};

int maxDepthDFS(int at, vector<node> &forest, vector<int> &res) {
    int ret = forest[at].depth;
    for (int i : forest[at].children) {
        ret = max(res[i] = maxDepthDFS(i,forest,res), ret);
    }
    return ret;
}

vector<int> maxDepth(vector<int> &roots, vector<node> &forest) {
    vector<int> res(forest.size());
    for (int at : roots) {
        res[at] = maxDepthDFS(at,forest,res);
    }
    return res;
}

//wiadomo, że dokonując operacji na jakimś wierzchołku,
//przenosimy wszystkich jego synów na poziom jego rodzica (zmniejszamy ich głębokość o 2), usuwamy go oraz jego rodzica,
//dodatkowo wszyscy synowie tego rodzica są rozdzieleni
//pomiędzy dwa nowe wierzchołki, które pojawią się na poziomie
//rodzica

//wiadomo, że optymalna strategia polega na dokonywaniu operacji na wszystkich
//synach korzeni, pod którymi znajdują się wierzchołki o większej głębokości od H

//tak naprawdę, skoro robimy to jedynie na synach korzenia a na korzeniach nie można
//tej operacji przeprowadzić, można zauważyć, że zdobycie listy wierzchołków na których
//taką operację będziemy przeprowadzać jest trywialne

//wiadomo, że wszyscy synowie synów korzenia staną się nowymi korzeniami, na których synach
//zrobimy to samo
//wszyscy pozostali synowie rodzica zostaną rozdzieleni pomiędzy dwa nowe korzenie, ale nie ma
//to żadnego znaczenia, ponieważ i tak po prostu wykonamy na tych synach korzeni podobną operację

//teraz aby stwierdzić na których synach korzeni będziemy to wykonywać, wystarczy na początku
//użyć algorytmu DFS w celu znalezienia maksymalnej głębokości wierzchołków pod każdym z wierzchołków
//w czasie liniowym

//sprawa jest teraz całkiem prosta, wystarczy bowiem stworzyć taką rekurencyjną funkcję:
//1. wykonujemy ją dla każdego syna korzenia, który ma głębokość maksymalną większą niż H
//2. na każdym kroku dodajemy 1 do globalnej zmiennej
//3. po każdym kroku, przekazujemy H + 2 zamiast H
//3. iterujemy przez wnuki obecnego wierzchołka, który jest korzeniem w naszym "symulowanym" grafie i jeżeli
//ich głębokość maksymalna jest większa niż "obecne H", wykonujemy rekurencję
//4. jedynym wyjątkiem jest sytuacja gdy różnica pomiędzy H a maksymalną głębokością wynosi 1
//w takiej sytuacji zamiast iterować przez wnuki po prostu iterujemy przez synów, dla każdego sprawdzamy
//czy spełnia warunek i jeśli tak to dodajemy 1 do zmiennej globalnej dla każdego z nich

int moves = 0;

void solutionDFS(int at, vector<int> &max_depths, vector<node> &forest, int H) {
    moves++;

    if (max_depths[at] - (H + 2) == 1) {
        for (int i : forest[at].children) {
            if (max_depths[i] > H + 2) {
                for (int j : forest[i].children) {
                    if (max_depths[j] > H + 2) {
                        moves++;
                    }
                }
            }
        }
    } else {
        for (int i : forest[at].children) {
            for (int j : forest[i].children) {
                if (max_depths[j] > H + 2) {
                    solutionDFS(j,max_depths,forest,H + 2);
                }
            }
        }
    }
}

void solve(vector<int> &roots, vector<int> &max_depths, vector<node> &forest, int H) {
    for (int i : roots) {
        for (int j : forest[i].children) {
            if (max_depths[j] > H) {
                solutionDFS(j,max_depths,forest,H);
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(length);
    in_i(depth);

    in_str(parentheses);
    int counter = 0;
    int current_depth = 0;
    for (char c : parentheses) {
        if (c == '(') {
            counter++;
            current_depth = max(current_depth,counter);
        } else {
            counter--;
        }
    }

    if (current_depth > depth) {
        vector<int> v(length);
        deque<int> s;
        for (int i = 0; i < parentheses.size(); i++) {
            char c = parentheses[i];
            if (c == '(') {
                s.pb(i);
            } else {
                int ind = s.back();
                s.pop_back();
                v[ind] = i;
            }
        }

        vector<node> forest;
        counter = 0;
        vector<int> roots;
        for (int i = 0; i < parentheses.size(); i++) {
            char c = parentheses[i];
            if (c == '(') {
                if (!s.empty()) {
                    int a = s.back();
                    forest[a].children.pb(counter);
                } else {
                    roots.pb(counter);
                }
                s.pb(counter);
                forest.emplace_back(i,v[i],s.size(),s.front());
                counter++;
            } else {
                s.pop_back();
            }
        }

        vector<int> max_depths = maxDepth(roots, forest);

        solve(roots,max_depths,forest,depth);

        cout << moves * 2 << endl;
    } else {
        cout << 0 << endl;
    }
}