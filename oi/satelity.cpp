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

//https://www.geeksforgeeks.org/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
 
        if (hash1 != hash2) {
            return hash1 ^ hash2;              
        }
         
        // If hash1 == hash2, their XOR is zero.
          return hash1;
    }
};

void recursive_gen(string &current, vector<string> &strings, int steps_left) {
    if (steps_left == 0) {
        strings.pb(current);
        return;
    }

    string cp = current;
    cp += "A";

    recursive_gen(cp, strings, steps_left - 1);

    string cp2 = current;
    cp2 += "B";

    recursive_gen(cp2, strings, steps_left - 1);
}

vector<string> generate_unique_ids(int n) {
    if (n <= 0) {
        int test = 0;
    }

    vector<string> strings;
    int generating = ceil(log(n)/log(2));

    string base = "";
    recursive_gen(base, strings, generating);

    return strings;
}

vector<pii> random_test(int n, int p, int m) {
    vector<pii> vec;
    unordered_set<pii,hash_pair> s;
    for (int i = 0; i < p; i++) {
        int a = rand() % n + 1;
        int b = rand() % n + n + 1;
        
        if (s.find(mp(a,b)) == s.end()) {
            s.insert({a,b});
            vec.pb({a,b});
        } else {
            i--;
        }
    }

    return vec;
}

bool verify(vector<string> &answer, vector<pii> &random_test_vec) {
    int prev_size = -1;
    for (int i = 0; i < answer.size(); i++) {
        if (prev_size != -1 && answer[i].size() != prev_size) {
            return false;
        }

        prev_size = answer[i].size();
    }

    vector<unordered_set<int>> graph_recreation(answer.size());
    for (int i = 0; i < answer[0].size(); i++) {
        vector<int> a_symbol;
        vector<int> b_symbol;
        vector<int> c_symbol;
        for (int j = 0; j < answer.size(); j++) {
            if (answer[j][i] == 'A') {
                a_symbol.pb(j);
            } else if (answer[j][i] == 'B') {
                b_symbol.pb(j);
            } else {
                c_symbol.pb(j);
            }
        }

        for (int j : a_symbol) {
            for (int k : a_symbol) {
                if (j != k) {
                    graph_recreation[j].insert(k);
                }
            }
        }

        for (int j : b_symbol) {
            for (int k : b_symbol) {
                if (j != k) {
                    graph_recreation[j].insert(k);
                }
            }
        }

        for (int j : c_symbol) {
            for (int k : c_symbol) {
                if (j != k) {
                    graph_recreation[j].insert(k);
                }
            }
        }
    }

    vector<unordered_set<int>> graph_from_test(answer.size());
    for (pii i : random_test_vec) {
        graph_from_test[i.first - 1].insert(i.second - 1);
        graph_from_test[i.second - 1].insert(i.first - 1);
    }
    for (int i = 0; i < answer.size() / 2; i++) {
        for (int j = 0; j < answer.size() / 2; j++) {
            if (i != j) {
                graph_from_test[i].insert(j);
                graph_from_test[j].insert(i);
            }
        }
    }

    for (int i = answer.size() / 2; i < answer.size(); i++) {
        for (int j = answer.size() / 2; j < answer.size(); j++) {
            if (i != j) {
                graph_from_test[i].insert(j);
                graph_from_test[j].insert(i);
            }
        }
    }

    for (int i = 0; i < answer.size(); i++) {
        for (int j = i + 1; j < answer.size(); j++) {
            if (answer[i] == answer[j])
                return false;
        }
    }

    return graph_recreation == graph_from_test;
}

struct unordered_set_hash {
    std::size_t operator()(const std::unordered_set<int>& s) const {
        std::size_t hash = 0;
        for (const int& value : s) {
            hash ^= std::hash<int>()(value);
        }
        return hash;
    }
};

void apply_encodings(vector<string> &strings, vector<int> &vertices, bool first_team) {
    unordered_map<string,vector<int>> string_groups;
    for (int i : vertices) {
        string_groups[strings[i]].pb(i);
    }

    for (auto i : string_groups) {
        int encoding_len = i.second.size();
        vector<string> encodings = generate_unique_ids(encoding_len);
        for (int j = 0; j < i.second.size(); j++) {
            strings[i.second[j]] += encodings[j];
        }
    }

    int max_len = 0;
    for (string &s : strings) {
        max_len = max((int) s.size(), max_len);
    }

    for (int j = 0; j < strings.size(); j++) {
        string &s = strings[j];
        if (s.size() < max_len) {
            int s_size = s.size();
            for (int i = 0; i < max_len - s_size; i++) {
                if (first_team == (j < strings.size() / 2)) {
                    s += "A";
                } else {
                    s += "C";
                }
            }
        }
    }
}

vector<string> parallel_encode(vector<string> strings, vector<int> &groups_by_el_idx, vector<unordered_set<int>> &groups,
        vector<unordered_set<int>> &graph, bool allow_different_team_parallel_enc) {
    vector<bool> connection_groups(groups.size());
    for (int i = 0; i < graph.size(); i++) {
        if (graph[i].size() > 0) {
            connection_groups[groups_by_el_idx[i]] = true;
        }
    }

    vector<int> simultaneous_group_vertices;
    int simultaneous_group_idx = -1;
    if (allow_different_team_parallel_enc) {
        for (int i = 0; i < groups.size(); i++) {
            if (graph[*groups[i].begin()].size() == graph.size() / 2 && groups[i].size() > 1) {
                // Znaleziono połączony do wszystkich wierzchołków z przeciwnej drużyny
                for (int j : groups[i]) {
                    simultaneous_group_vertices.pb(j);
                }
                for (int j : graph[*groups[i].begin()]) {
                    simultaneous_group_vertices.pb(j);
                }
                simultaneous_group_idx = i;
                break;
            }
        }
    }

    
    if (!simultaneous_group_vertices.empty()) {
        // Jeśli znaleźliśmy taką grupę, kodujemy ją
        apply_encodings(strings, simultaneous_group_vertices, *groups[simultaneous_group_idx].begin() >= graph.size() / 2);
    }

    vector<int> first_team_vertices;
    vector<int> second_team_vertices;
    for (int i = 0; i < groups.size(); i++) {
        // Sprawdzamy czy grupa ma jakieś połączenia oraz czy należy do niej więcej niż 1 wierzchołek
        // Dodatkowo weryfikujemy czy już nie dokonaliśmy dla tej grupy kodowania
        if (connection_groups[i] && groups[i].size() > 1) {
            if (*groups[i].begin() < graph.size() / 2 && simultaneous_group_idx != i && (simultaneous_group_idx == -1 || *groups[simultaneous_group_idx].begin() < graph.size() / 2)) {
                for (int j : groups[i]) {
                    first_team_vertices.pb(j);
                }
            } else if (simultaneous_group_idx != i && (simultaneous_group_idx == -1 || *groups[simultaneous_group_idx].begin() >= graph.size() / 2)) {
                for (int j : groups[i]) {
                    second_team_vertices.pb(j);
                }
            }
        } else if (!connection_groups[i] && groups[i].size() > 1) {
            for (int j : groups[i]) {
                if (j < graph.size() / 2) {
                    first_team_vertices.pb(j);
                } else {
                    second_team_vertices.pb(j);
                }
            }
        }
    }

    // Gdy mam już podzielone na wierzchołki, które będę kodował z pierwszej i drugiej drużyny, dokonuję kodowania
    if (!first_team_vertices.empty()) {
        apply_encodings(strings, first_team_vertices, true);
    }

    if (!second_team_vertices.empty()) {
        apply_encodings(strings, second_team_vertices, false);
    }

    return strings;
}

void team_encode(vector<string> &encoded, int n) {
    // Sprawdzanie czy mogę pominąć kodowanie drużyny
    bool first_team_same_letters = false;
    bool second_team_same_letters = false;
    for (int i = 0; i < encoded[0].size(); i++) {
        int prev = -1;
        bool same_letters = true;
        for (int j = 0; j < n; j++) {
            if (prev != -1 && prev != encoded[j][i] - 'A') {
                same_letters = false;
                break;
            }

            prev = encoded[j][i] - 'A';
        }

        if (same_letters) {
            first_team_same_letters = true;
        }

        prev = -1;
        same_letters = true;
        for (int j = n; j < 2*n; j++) {
            if (prev != -1 && prev != encoded[j][i] - 'A') {
                same_letters = false;
                break;
            }

            prev = encoded[j][i] - 'A';
        }

        if (same_letters) {
            second_team_same_letters = true;
        }
    }

    if (!first_team_same_letters || !second_team_same_letters) {
        // Muszę zakodować drużynę dodatkowo
        for (int i = 0; i < n; i++) {
            encoded[i] += "A";
        }

        for (int i = n; i < 2*n; i++) {
            encoded[i] += "B";
        }
    }
}

vector<string> solve(int n, int p, int M, vector<unordered_set<int>> &graph) {
    vector<string> strings(2*n);

    // Znajduję grupy wierzchołków
    unordered_map<unordered_set<int>, int, unordered_set_hash> umap;
    vector<int> groups_by_el_idx(2*n);
    int global_counter = 0;
    for (int i = 0; i < graph.size(); i++) {
        auto &j = graph[i];
        if (umap.find(j) != umap.end()) {
            groups_by_el_idx[i] = groups_by_el_idx[umap[j]];
        } else {
            groups_by_el_idx[i] = global_counter++;
            umap[j] = i;
        }
    }

    vector<unordered_set<int>> groups(global_counter);
    for (int i = 0; i < 2*n; i++) {
        groups[groups_by_el_idx[i]].insert(i);
    }

    vector<unordered_set<int>> first_team_groups;
    for (auto i : groups) {
        if (*i.begin() < n && !graph[*i.begin()].empty()) {
            first_team_groups.pb(i);
        }
    }

    // Zacznę od kodowania połączeń, ponieważ to zawsze muszę zrobić niezależnie od sytuacji
    bool pre_encoded = false;
    if (first_team_groups.size() == 2 && first_team_groups[0].size() + first_team_groups[1].size() == n) {
        // Przypadek szczególny, kiedy można uproszczenie zrobić
        unordered_map<int,int> vertices;
        for (int i : graph[*first_team_groups[0].begin()]) {
            vertices[i] = 0;
        }

        bool condition_not_fulfilled = false;
        for (int i : graph[*first_team_groups[1].begin()]) {
            if (vertices.find(i) != vertices.end()) {
                condition_not_fulfilled = true;
                break;
            }
            vertices[i] = 1;
        }

        if (!condition_not_fulfilled && vertices.size() == n) {
            pre_encoded = true;

            for (auto i : vertices) {
                strings[i.first] += string(1,'A'+i.second);
            }

            for (auto i : first_team_groups[0]) {
                strings[i] += "A";
            }

            for (auto i : first_team_groups[1]) {
                strings[i] += "B";
            }
        }
    }

    if (!pre_encoded) {
        for (auto i : groups) {
            if (*i.begin() >= n || graph[*i.begin()].empty()) {
                continue;
            }
            for (int j = 0; j < 2*n; j++) {
                if (i.find(j) != i.end() || graph[*i.begin()].find(j) != graph[*i.begin()].end()) {
                    strings[j] += "A";
                } else if (j < n) {
                    strings[j] += "B";
                } else {
                    strings[j] += "C";
                }
            }
        }
    }

    // Jednoczesne kodowanie unikalności różnych grup
    vector<string> encoded = parallel_encode(strings, groups_by_el_idx, groups, graph, false);
    vector<string> second_encoded = parallel_encode(strings, groups_by_el_idx, groups, graph, true);

    // Kodowanie drużyny, jeśli trzeba
    team_encode(encoded, n);
    team_encode(second_encoded, n);

    if (second_encoded[0].size() < encoded[0].size()) {
        encoded = second_encoded;
    }

    return encoded;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 20 + 1;
    ini(p);
    //int p = rand() % (n*n) + 1;
    ini(M);
    //int M = n+2;

    //vector<pii> random_test_vec = random_test(n, p, M);
    vector<pii> random_test_vec;

    vector<unordered_set<int>> graph(n*2);
    vector<unordered_set<int>> reversed_graph(n*2);
    for (int i = 0; i < p; i++) {
        ini(a);
        //int a = random_test_vec[i].first;
        ini(b);
        //int b = random_test_vec[i].second;

        random_test_vec.pb({a,b});

        a--;
        b--;

        graph[a].insert(b);
        graph[b].insert(a);
        reversed_graph[a + n].insert(b - n);
        reversed_graph[b - n].insert(a + n);
    }

    vector<string> encoded = solve(n, p, M, graph);
    vector<string> encoded2 = solve(n, p, M, reversed_graph);

    if (encoded2[0].size() < encoded[0].size()) {
        encoded = encoded2;

        for (int i = 0; i < n; i++) {
            string s = encoded[i+n];
            encoded[i+n] = encoded[i];
            encoded[i] = s;
        }
    }

    if (n == 1) {
        encoded[0] += "A";
        encoded[1] += "B";
    }

    /*if (!verify(encoded, random_test_vec)) {
        int test = 0;
    }

    if (encoded[0].size() > n + 2) {
        int test = 0;
    }*/
    //}

    cout << encoded[0].size() << endl;
    for (string s : encoded) {
        cout << s << endl;
    }
}