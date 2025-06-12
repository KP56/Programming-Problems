#include <bits/stdc++.h>

//#include "skolib.h"

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

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

vector<pii> possible_moves {
    {1,2},
    {2,1},
    {-1,2},
    {-2,1},
    {1,-2},
    {2,-1},
    {-1,-2},
    {-2,-1}
};

int bfs_steps = 0;
vector<vector<int>> generate_minimal_moves(int x, int y, int d) {
    vector<vector<int>> dist(d,vector<int>(d,-1));
    queue<pair<pii,int>> q;
    // BFS
    q.push({{x,y},0});
    dist[x][y] = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int x = current.first.first;
        int y = current.first.second;
        int distance = current.second;

        for (auto &move : possible_moves) {
            bfs_steps++;
            int new_x = x + move.first;
            int new_y = y + move.second;
            if (new_x >= 0 && new_y >= 0 && new_x < d && new_y < d && dist[new_x][new_y] == -1) {
                dist[new_x][new_y] = distance + 1;
                q.push({{new_x,new_y}, distance + 1});
            }
        }
    }

    return dist;
}

vector<vector<int>> board;

int n = 10;
int xs = 0;
int ys = 0;

int questions = 0;
int worst_questions = 0;

int daj_n() {
    board = generate_minimal_moves(xs,ys,n);
    questions = 0;

    return n;
}

void odpowiedz(int x, int y) {
    if (x-1 != xs || y-1 != ys) {
        int test = 0;
    }

    worst_questions = max(worst_questions,questions);
}

int pytanie(int x, int y) {
    questions++;
    return board[x-1][y-1];
}

void bruteforce() {
    int d = daj_n();

    vector<pair<vector<vector<int>>,pii>> results;
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            vector<vector<int>> res = generate_minimal_moves(x,y,d);
            results.pb({res,{x,y}});
        }
    }

    for (int t = 1; ; t++) {
        int best_worst_case = INT_MAX;
        int best_x = -1;
        int best_y = -1;
        unordered_map<int,vector<pii>> options_left;
        for (int i = 0; i < d; i++) {
            for (int j = 0; j < d; j++) {
                unordered_map<int,vector<pii>> noticed;
                for (auto &k : results) {
                    noticed[k.first[i][j]].pb(k.second);
                }

                int worst_case = -1;
                for (auto &k : noticed) {
                    if (worst_case < (int) k.second.size()) {
                        worst_case = (int) k.second.size();
                    }
                }

                if (best_worst_case > worst_case) {
                    best_worst_case = worst_case;
                    best_x = i;
                    best_y = j;
                    options_left = noticed;
                }
            }
        }

        // zagrywam ruch
        int dist = pytanie(best_x + 1, best_y + 1);
        vector<pii> options_left_to_play = options_left[dist];
        vector<pair<vector<vector<int>>,pii>> new_results;
        for (auto &i : results) {
            for (auto &j : options_left_to_play) {
                if (i.second == j) {
                    new_results.pb({i.first,i.second});
                    break;
                }
            }
        }

        results = new_results;

        if (results.size() == 1) {
            int ans_x = results[0].second.first;
            int ans_y = results[0].second.second;

            /*if (ans_x != xs || ans_y != ys) {
                int test = 0;
            }

            worst_run = max(worst_run,t);*/

            odpowiedz(ans_x + 1, ans_y + 1);

            //cout << ans_x + 1 << " " << ans_y + 1 << endl;
            break;
        }
    }
}

int distance_f(int x, int y) {
    return sqrt(x) + sqrt(y);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    for (n = 4; n <= 10; n++) {
    int d = daj_n();

    // tworzymy tabelę, która pozwoli nam na łatwiejsze zlokalizowanie skoczka
    map<int,int> max_diff;
    map<int,int> min_diff;
    for (int x = 0; x < d; x++) {
        for (int y = 0; y < d; y++) {
            vector<vector<int>> res = generate_minimal_moves(x,y,d);
            for (int x2 = 0; x2 < d; x2++) {
                for (int y2 = 0; y2 < d; y2++) {
                    int x_diff = abs(x-x2);
                    int y_diff = abs(y-y2);
                    if (max_diff.find(res[x2][y2]) == max_diff.end()) {
                        max_diff[res[x2][y2]] = -1;
                    }

                    if (min_diff.find(res[x2][y2]) == min_diff.end()) {
                        min_diff[res[x2][y2]] = INT_MAX;
                    }

                    max_diff[res[x2][y2]] = max(max_diff[res[x2][y2]], distance_f(x_diff,y_diff));
                    min_diff[res[x2][y2]] = min(min_diff[res[x2][y2]], distance_f(x_diff,y_diff));
                }
            }
        }
    }

    /*cout << "map<int,int> max_diff = {" << endl;
    for (auto &i : max_diff) {
        cout << "{" << i.first << "," << i.second << "}," << endl;
    }
    cout << "};" << endl;

    cout << "map<int,int> min_diff = {" << endl;
    for (auto &i : min_diff) {
        cout << "{" << i.first << "," << i.second << "}," << endl;
    }
    cout << "};" << endl;*/

    /*int max_difference_between = 0;
    for (auto &i : max_diff) {
        int diff_between = i.second - min_diff[i.first];
        max_difference_between = max(max_difference_between, diff_between);
    }*/

    // Obliczyliśmy te wartości, teraz rozwiązujemy
    for (; xs < n; xs++) {
        for (; ys < n; ys++) {
            daj_n();
    vector<vector<bool>> possible(d,vector<bool>(d,true));
    while (true) {
        // Strategia polega na wybieraniu dostępnego pola o minimalnej sumie x i y
        int best_x = -1;
        int best_y = -1;
        int min_sum = INT_MAX;
        for (int x = 0; x < d; x++) {
            for (int y = 0; y < d; y++) {
                if (possible[x][y]) {
                    if (distance_f(x,y) < min_sum) {
                        min_sum = distance_f(x,y);
                        best_x = x;
                        best_y = y;
                    }
                }
            }
        }

        int res = pytanie(best_x + 1, best_y + 1);
        for (int x = 0; x < d; x++) {
            for (int y = 0; y < d; y++) {
                int diff = distance_f(abs(best_x - x), abs(best_y - y));
                if (diff > max_diff[res] || diff < min_diff[res]) {
                    possible[x][y] = false;
                }
            }
        }

        int possible_left = 0;
        pii prev = {-1,-1};
        for (int x = 0; x < d; x++) {
            for (int y = 0; y < d; y++) {
                if (possible[x][y]) {
                    prev = {x,y};
                }
                possible_left += possible[x][y];
            }
        }

        if (possible_left == 1) {
            odpowiedz(prev.first + 1, prev.second + 1);
            break;
        }
    }
        }
    }
    }

    cout << worst_questions << endl;
}