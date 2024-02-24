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

struct board {
    vector<vector<bool>> board_vec;

    board() {}

    board(int width, int height) {
        board_vec = vector<vector<bool>>(width,vector<bool>(height));
    }

    void set_field(int x, int y, bool value) {
        board_vec[x][y] = value;
    }

    pair<board,bool> perform_an_iteration() const {
        vector<vector<bool>> new_board_vec(board_vec.size(),vector<bool>(board_vec[0].size()));

        bool need_fixing = false;
        for (int i = -1; i <= (int) board_vec.size(); i++) {
            for (int j = -1; j <= (int) board_vec[0].size(); j++) {
                int count = 0;
                for (int i2 = i-1; i2 <= i+1; i2++) {
                    if (i2 < 0 || i2 >= board_vec.size()) continue;
                    for (int j2 = j-1; j2 <= j+1; j2++) {
                        if (j2 < 0 || j2 >= board_vec[0].size()) continue;

                        count += board_vec[i2][j2];
                    }
                }

                if (count % 2 == 1) {
                    if (i >= 0 && j >= 0 && i < board_vec.size() && j < board_vec[0].size()) {
                        new_board_vec[i][j] = true;
                    } else {
                        if (need_fixing) {
                            return {};
                        }

                        need_fixing = true;
                    }
                }
            }
        }

        board new_board = board(board_vec.size(),board_vec[0].size());
        new_board.board_vec = new_board_vec;

        return {new_board,need_fixing};
    }

    board reverse_iteration() const {
        board new_board(board_vec.size(),board_vec[0].size());
        for (int i = 0; i < board_vec.size()-1; i++) {
            for (int j = 0; j < board_vec[0].size()-1; j++) {
                int counter = 0;

                for (int k = i-1; k <= i+1; k++) {
                    if (k < 0 || k >= board_vec.size()) continue;

                    for (int l = j-1; l <= j+1; l++) {
                        if (l < 0 || l >= board_vec[0].size()) continue;

                        if (new_board.board_vec[k][l]) {
                            counter++; 
                        }
                    }
                }

                // counter zawiera informacje nt. ilości jedynek w pobliżu, które już wpisaliśmy
                counter %= 2;

                // zależy nam jedynie na parzystości tej ilości

                if ((counter + board_vec[i][j]) % 2 == 1) {
                    // jeśli mamy złą parzystość, wtedy musimy gdzieś wsadzić jedynkę
                    /*if (i == 0 && j == 0) {
                        // lewy górny narożnik
                        new_board.set_field(i,j,false);
                        new_board.set_field(i+1,j,false);
                        new_board.set_field(i,j+1,false);
                        new_board.set_field(i+1,j+1,true);
                    } else if (i == 0) {
                        // jesteśmy po lewej
                        new_board.set_field(i,j+1,false);
                        new_board.set_field(i+1,j+1,true);
                    } else if (j == 0) {
                        // jesteśmy na samej górze
                        new_board.set_field(i+1,j,false);
                        new_board.set_field(i+1,j+1,true);
                    } else {
                        new_board.set_field(i+1,j+1,true);
                    }*/

                    new_board.set_field(i+1,j+1,true);
                }

                // jeśli parzystość jest dobra, wtedy musimy wsadzić same zera, jednak zera są już wsadzone, więc nie ma sensu ich wsadzać
            }
        }

        pair<board,bool> res = new_board.perform_an_iteration();

        if (res.second) {
            return board();
        }

        if (res.first.board_vec == board_vec) {
            return new_board;
        } else {
            return board();
        }
    }

    vector<board> reverse_iterations_bugged() {
        vector<board> result;
        board res2 = reverse_iteration();
        if (!res2.board_vec.empty()) {
            result.pb(res2);
        }
        for (int i = 0; i < board_vec.size(); i++) {
            for (int j = 0; j < board_vec[0].size(); j++) {
                board new_board;
                new_board.board_vec = board_vec;

                new_board.set_field(i,j,!new_board.board_vec[i][j]);

                board res = new_board.reverse_iteration();
                if (!res.board_vec.empty()) {
                    result.pb(res);
                }
            }
        }

        return result;
    }

    vector<board> bugged_iterations() const {
        auto it_res = perform_an_iteration();

        board normal = it_res.first;

        if (normal.board_vec.empty()) {
            return {};
        }

        vector<board> res;
        res.pb(normal);

        if (it_res.second) {
            return res;
        }

        for (int i = 0; i < board_vec.size(); i++) {
            for (int j = 0; j < board_vec[0].size(); j++) {
                normal.board_vec[i][j] = !normal.board_vec[i][j];
                res.pb(normal);
                normal.board_vec[i][j] = !normal.board_vec[i][j];
            }
        }

        return res;
    }

    bool empty() {
        for (auto i : board_vec) {
            for (bool j : i) {
                if (j) return false;
            }
        }

        return true;
    }
};

template <>
struct std::hash<board> {
    size_t operator()(const board& b) const {
        size_t seed = 0;
        for (auto& i : b.board_vec) {
            for (auto j : i) {
                seed ^= j + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
        }
        return seed;
    }
};

bool operator==(const board& lhs, const board& rhs) {
    return lhs.board_vec == rhs.board_vec;
}

void generate_all_possibilities(int n, int m, vector<vector<bool>> &current, int &counter, unordered_map<board,int> &ids) {
    if (current.size() == n && current[current.size()-1].size() == m) {
        board b = board(n,m);
        b.board_vec = current;
        ids[b] = counter++;

        return;
    }

    if (!current.empty() && current[current.size()-1].size() < m) {
        vector<vector<bool>> cp = current;
        cp[cp.size()-1].pb(true);
        generate_all_possibilities(n,m,cp,counter,ids);

        current[current.size()-1].pb(false);
        generate_all_possibilities(n,m,current,counter,ids);
    } else {
        current.pb({});

        generate_all_possibilities(n,m,current,counter,ids);
    }
}

int dfs_counter(int at, vector<bool> &vis, vector<vector<int>> &graph, int empty_state) {
    vis[at] = true;

    int sum = 1;
    for (int i : graph[at]) {
        if (!vis[i] && i != empty_state) {
            sum += dfs_counter(i,vis,graph,empty_state);
        }
    }

    return sum;
}

int solve_bruteforce(int n, int m, board &end_pos) {
    unordered_map<board,int> ids;
    int counter = 0;
    vector<vector<bool>> current;
    generate_all_possibilities(n,m,current,counter,ids);

    vector<board> by_id(counter);
    for (auto &i : ids) {
        by_id[i.second] = i.first;
    }

    vector<vector<int>> state_graph(counter);
    for (auto &i : ids) {
        for (board new_board : i.first.bugged_iterations()) {
            state_graph[i.second].pb(ids[new_board]);
        }
    }

    vector<vector<int>> reversed_graph(counter);
    for (int i = 0; i < counter; i++) {
        for (int j : state_graph[i]) {
            reversed_graph[j].pb(i);
        }
    }

    int empty_state_id = -1;
    for (int i = 0; i < counter; i++) {
        if (by_id[i].empty()) {
            empty_state_id = i;
            break;
        }
    }

    vector<bool> vis(counter);
    return dfs_counter(ids[end_pos],vis,reversed_graph,empty_state_id);
}

int solve(int n, int m, board end_pos) {
    // biorę pod uwagę fakt, że może zostać wprowadzona drobna modyfikacja poza planszą i dalej może być wszystko dobrze jeżeli jest ona
    // przy planszy

    for (int i = 0; i < n; i++) {
        end_pos.board_vec[i].pb(false);
        end_pos.board_vec[i].insert(end_pos.board_vec[i].begin(),false);
    }
    vector<bool> empty(m+2);
    end_pos.board_vec.pb(empty);
    end_pos.board_vec.insert(end_pos.board_vec.begin(),empty);

    vector<board> rev_iterations = end_pos.reverse_iterations_bugged();

    int counter = 0;
    while (!rev_iterations.empty()) {
        board &last = rev_iterations[rev_iterations.size() - 1];
        vector<board> rev_iterations2 = last.reverse_iterations_bugged();

        if (!rev_iterations[rev_iterations.size() - 1].empty()) counter++;

        rev_iterations.erase(--rev_iterations.end());
        for (int j = 0; j < rev_iterations2.size(); j++) {
            if (!rev_iterations2[j].empty()) {
                rev_iterations.pb(rev_iterations2[j]);
            }
        }
    }

    return counter+1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    for (int i = 0; i < 100000; i++) {
    //ini(n);
    int n = rand() % 5 + 1;
    //ini(m);
    int m = rand() % 5 + 1;

    board end_pos = board(n,m);
    /*int hashtags = 0;
    for (int i = 0; i < n; i++) {
        instr(s);
        
        for (int j = 0; j < m; j++) {
            if (s[j] == '#') {
                hashtags++;
                end_pos.set_field(i,j,true);
            }
        }
    }*/

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            end_pos.set_field(i,j,rand() % 2);
        }
    }

    //int bruteres = solve_bruteforce(n,m,end_pos);
    int res = solve(n,m,end_pos);

    /*if (res != bruteres) {
        solve(n,m,end_pos);
        int test = 0;
    }*/

    cout << res << endl;
    }
}