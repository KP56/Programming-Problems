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

void calculate_costs_dfs(int at, vector<vector<int>> &graph, vector<int> &costs, int current) {
    costs[at] = current;

    if (graph[at][0] != -1) {
        calculate_costs_dfs(graph[at][0],graph,costs,current*2);
    }

    if (graph[at][1] != -1) {
        calculate_costs_dfs(graph[at][1],graph,costs,current*2+1);
    }
}

void construct_trie(int at, vector<vector<int>> &graph, vector<pair<vector<int>,vector<int>>> &trie, bool found_one, int trie_pos,
            vector<int> &distances, int dist, vector<int> &mapping) {
    distances[at] = dist;
    if (found_one) {
        mapping[at] = trie_pos;
        trie[trie_pos].second.pb(at);
    }
    
    if (graph[at][0] != -1) {
        if (found_one && trie[trie_pos].first[0] == -1) {
            trie[trie_pos].first[0] = trie.size();
            trie.pb({{-1,-1},{}});
        }

        if (found_one) {
            construct_trie(graph[at][0],graph,trie,found_one,trie[trie_pos].first[0],distances,dist+1,mapping);
        } else {
            construct_trie(graph[at][0],graph,trie,found_one,0,distances,-1,mapping);
        }
    }

    if (graph[at][1] != -1) {
        if (found_one && trie[trie_pos].first[1] == -1) {
            trie[trie_pos].first[1] = trie.size();
            trie.pb({{-1,-1},{}});
        }

        if (found_one) {
            construct_trie(graph[at][1],graph,trie,true,trie[trie_pos].first[1],distances,dist+1,mapping);
        } else {
            construct_trie(graph[at][1],graph,trie,true,0,distances,0,mapping);
        }
    }
}

void find_euler(int at, vector<pair<vector<int>,vector<int>>> &trie, vector<int> &euler, int &euler_counter) {
    euler[at] = euler_counter++;

    if (trie[at].first[0] != -1) {
        find_euler(trie[at].first[0],trie,euler,euler_counter);
    }

    if (trie[at].first[1] != -1) {
        find_euler(trie[at].first[1],trie,euler,euler_counter);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 10 + 1;
    /*vector<bool> chosen(n);
    chosen[0] = true;*/
    vector<vector<int>> graph(n,vector<int>(2));
    for (int i = 0; i < n; i++) {
        ini(l);
        //int l = i + 2;
        ini(r);
        //int r = rand() % n + 1;

        /*if (chosen[l-1] || l > n) l = 0;
        if (chosen[r-1]) r = 0;*/

        l--;
        r--;

        /*if (l != -1) {
            chosen[l] = true;
        }

        if (r != -1) {
            chosen[r] = true;
        }*/

        graph[i][0] = l;
        graph[i][1] = r;
    }

    /*vector<int> costs(n);
    calculate_costs_dfs(0,graph,costs,0);*/

    vector<int> distances(n);
    vector<pair<vector<int>,vector<int>>> trie;

    trie.pb({{-1,-1},{}});

    vector<int> mapping(n);
    construct_trie(0,graph,trie,false,0,distances,-1,mapping);

    int euler_counter = 0;

    vector<int> euler(trie.size());
    find_euler(0,trie,euler,euler_counter);

    //int q = rand() % 10 + 1;
    ini(q);
    for (int i = 0; i < q; i++) {
        ini(a);
        //int a = rand() % n + 1;
        ini(b);
        //int b = rand() % n + 1;

        a--;
        b--;

        if (distances[a] > distances[b]) {
            cout << "TAK" << endl;

            /*if (costs[a] < costs[b]) {
                int test = 0;
            }*/
        } else if (distances[a] < distances[b]) {
            cout << "NIE" << endl;

            /*if (costs[a] >= costs[b]) {
                int test = 0;
            }*/
        } else {
            if (euler[mapping[a]] >= euler[mapping[b]]) {
                cout << "TAK" << endl;

                /*if (costs[a] < costs[b]) {
                    int test = 0;
                }*/
            } else {
                cout << "NIE" << endl;

                /*if (costs[a] >= costs[b]) {
                    int test = 0;
                }*/
            }
        }

        /*if (costs[a] >= costs[b]) {
            cout << "TAK" << endl;
        } else {
            cout << "NIE" << endl;
        }*/
    }
}