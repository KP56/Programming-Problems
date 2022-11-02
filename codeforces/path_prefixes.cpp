#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using lli = long long int;
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
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

struct Edge {
    int parent;
    int child;
    int a;
    int b;

    int binary_line_ind = -1;

    Edge(int parent, int child, int a, int b) {
        this->parent = parent;
        this->child = child;
        this->a = a;
        this->b = b;
    }
};

//find highest element lower than x
int binarySearch(vector<int> vec, int x) {
    int l = 0;
    int r = vec.size() - 1;

    while (l <= r) {
        int m = l + (r - l) / 2;
 
        if (vec[m] == x) {
            return m;
        } if (vec[m] < x) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    return l - 1;
}

class BinarySearchLine {
private:
    vector<Edge> edges;
public:
    int initial_b_sum;
    vector<int> b_sum;
    vector<int> nodes;

    BinarySearchLine(int initial_b_sum) {
        this->initial_b_sum = initial_b_sum;
    }

    void add(Edge edge) {
        if (b_sum.empty()) {
            b_sum.pb(initial_b_sum + edge.b);
        } else {
            b_sum.pb(b_sum[b_sum.size() - 1] + edge.b);
        }

        nodes.pb(edge.child);
        edges.pb(edge);
    }

    //returns an index of a node
    int findBPoint(int a) {
        return binarySearch(b_sum, a);
    }
};

class Tree {
private:
    int size;

    vector<Edge> parents;
    vector<vector<Edge>> children;
    vector<BinarySearchLine> binary_search_lines;

    void binarySearchInit(int at, int prev_line, int current_b_sum) {
        prev_line = binary_search_lines.size();
        
        if (prev_line == -1) {
            binary_search_lines.emplace_back(current_b_sum - parents[at].b);
        }
        parents[at].binary_line_ind = prev_line;
        binary_search_lines[prev_line].add(parents[at]);

        for (auto i : children[at]) {
            if (children[at].size() == 1) {
                binarySearchInit(i.child, prev_line, current_b_sum + i.b);
            } else {
                binarySearchInit(i.child, -1, current_b_sum + i.b);
            }
        }
    }

    vector<int> findNextStuck(int at, int a_sum, int stuck, int prev_result, vector<int> &traversing, vector<int> &solution) {
        BinarySearchLine current = binary_search_lines[parents[stuck].binary_line_ind];
        if (current.b_sum.size() > prev_result + 1 && current.b_sum[prev_result + 1] <= a_sum) {
            int found = current.findBPoint(a_sum);

            if (found == -1) {
                cout << "ERROR #1" << endl;
                exit(0);
            }

            if (found == current.b_sum.size() - 1) {
                BinarySearchLine next_possible = binary_search_lines[parents[traversing[stuck]].binary_line_ind];
                if (next_possible.b_sum[0] <= a_sum) {
                    //here we want to attempt the same thing
                    vector<int> vec = findNextStuck(at, a_sum, next_possible.nodes[0], 0, traversing, solution);
                    vec[2] += found - prev_result;
                    return vec;
                }
            }

            return {current.nodes[found], found, solution[at] + found - prev_result};
        }

        return {stuck, prev_result, solution[at]};
    }

    //DFS ran on binary search lines
    void dfs(int at, int a_sum, int stuck, int prev_result, vector<int> &traversing, vector<int> &solution, int nodes_since_root) {
        auto st = findNextStuck(at, a_sum, stuck, prev_result, traversing, solution);
        stuck = st[0];
        prev_result = st[1];
        solution[at] = min(nodes_since_root, st[2]);

        for (auto i : children[at]) {
            solution[i.child] = solution[at];
            dfs(i.child, a_sum + i.a, stuck, prev_result, traversing, solution, nodes_since_root + 1);
        }
    }
public:
    Tree(vector<Edge> parents, vector<vector<Edge>> children) {
        this->parents = parents;
        this->children = children;

        binarySearchInit(0, -1, 0);

        size = parents.size();
    }

    int size() {
        return size;
    }

    vector<int> solve() {
        vector<int> solution(size);
        vector<int> traversing(size);

        for (auto i : children[0]) {
            dfs(i.child, i.a, 0, -1, traversing, solution, 1);
        }

        return solution;
    }
};

void readCaseData() {
    in_i(size);

    vector<Edge> parents;
    vector<vector<Edge>> children;
    for (int i = 0; i < size; i++) {
        in_i(parent);
        in_i(a);
        in_i(b);


    }

    //cout << 0 << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}