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

struct table {
    int x = -1;
    int y = -1;
    int occupied_by = 0;

    table(int x, int y) {
        this->x = x;
        this->y = y;
    }

    table() {}

    int current_x() {
        if (occupied_by == 0) {
            // left-bottom
            return 3 * x + 1;
        } else if (occupied_by == 1) {
            // left-upper
            return 3 * x + 1;
        } else if (occupied_by == 2) {
            // right-bottom
            return 3 * x + 2;
        } else {
            // right-top
            return 3 * x + 2;
        }
    }

    int current_y() {
        if (occupied_by == 0) {
            // left-bottom
            return 3 * y + 1;
        } else if (occupied_by == 1) {
            // left-upper
            return 3 * y + 2;
        } else if (occupied_by == 2) {
            // right-bottom
            return 3 * y + 1;
        } else {
            // right-top
            return 3 * y + 2;
        }
    }

    int dist() {
        if (occupied_by == 3) {
            return current_x() + current_y() + 2;
        }

        return current_x() + current_y();
    }
};

vector<pii> solve(vector<int> arr) {
    map<vector<int>,table> unoccupied_tables;
    map<vector<int>,table> occupied_tables;
    int max_x = 0;
    int max_y = 0;
    table init_table = table(0,0);
    unoccupied_tables[{init_table.dist(),init_table.current_x(),init_table.current_y()}] = init_table;
    
    table max_table = table(INT_MAX,INT_MAX);
    unoccupied_tables[{max_table.dist(),max_table.current_x(),max_table.current_y()}] = max_table;
    occupied_tables[{max_table.dist(),max_table.current_x(),max_table.current_y()}] = max_table;

    vector<pii> points;
    for (int i : arr) {
        table best_t;
        
        if (i == 1) {
            // closest cell
            auto it1 = unoccupied_tables.begin();
            auto it2 = occupied_tables.begin();

            if (it1->first < it2->first) {
                auto best_it = it1;
                best_t = best_it->second;

                table cp = best_t;
                cp.occupied_by += 1;
                occupied_tables[{cp.dist(),cp.current_x(),cp.current_y()}] = cp;

                unoccupied_tables.erase(best_it);
            } else {
                auto best_it = it2;
                best_t = best_it->second;
                table cp = it2->second;
                cp.occupied_by += 1;
                occupied_tables.erase(best_it);

                if (cp.occupied_by != 4) {
                    occupied_tables[{cp.dist(),cp.current_x(),cp.current_y()}] = cp;
                }
            }

            
        } else {
            // closest table without any guests
            auto best_it = unoccupied_tables.begin();
            best_t = best_it->second;

            unoccupied_tables.erase(best_it);
            table cp = best_t;
            cp.occupied_by += 1;
            occupied_tables[{cp.dist(),cp.current_x(),cp.current_y()}] = cp;
        }

        if (best_t.x == max_x || best_t.y == max_y) {
            for (int j = 0; j <= max_x; j++) {
                table t = table(j,max_y+1);
                unoccupied_tables[{t.dist(),t.current_x(),t.current_y()}] = t;
            }

            for (int j = 0; j <= max_y; j++) {
                table t = table(max_x+1,j);
                unoccupied_tables[{t.dist(),t.current_x(),t.current_y()}] = t;
            }
            table t2 = table(max_x+1,max_y+1);
            unoccupied_tables[{t2.dist(),t2.current_x(),t2.current_y()}] = t2;

            max_x += 1;
            max_y += 1;
        }

        points.pb({best_t.current_x(),best_t.current_y()});
    }

    return points;
}

vector<pii> solve2(vector<int> arr) {
    vector<table> tables;
    vector<pii> points;
    int max_x = 0;
    int max_y = 0;
    tables.pb(table(0,0));
    for (int i : arr) {
        table best_t;
        int idx = -1;
        vector<int> best_dist = {INT_MAX,INT_MAX,INT_MAX};
        if (i == 1) {
            // closest cell            
            for (int j = 0; j < tables.size(); j++) {
                table &t = tables[j];
                vector<int> comparison_vec = {t.dist(),t.current_x(),t.current_y()};
                if (comparison_vec < best_dist) {
                    best_dist = comparison_vec;
                    best_t = t;
                    idx = j;
                }
            }
        } else {
            // closest table without any guests
            for (int j = 0; j < tables.size(); j++) {
                table &t = tables[j];
                vector<int> comparison_vec = {t.dist(),t.current_x(),t.current_y()};
                if (comparison_vec < best_dist && t.occupied_by == 0) {
                    best_dist = comparison_vec;
                    best_t = t;
                    idx = j;
                }
            }
        }
 
        if (best_t.x == max_x || best_t.y == max_y) {
            for (int j = 0; j <= max_x; j++) {
                tables.pb(table(j,max_y+1));
            }
 
            for (int j = 0; j <= max_y; j++) {
                tables.pb(table(max_x+1,j));
            }
            tables.pb(table(max_x+1,max_y+1));
 
            max_x += 1;
            max_y += 1;
        }
 
        int x = -1;
        int y = -1;
        if (best_t.occupied_by == 0) {
            // left-bottom
            x = 3 * best_t.x + 1;
            y = 3 * best_t.y + 1;
        } else if (best_t.occupied_by == 1) {
            // left-upper
            x = 3 * best_t.x + 1;
            y = 3 * best_t.y + 2;
        } else if (best_t.occupied_by == 2) {
            // right-bottom
            x = 3 * best_t.x + 2;
            y = 3 * best_t.y + 1;
        } else {
            // right-top
            x = 3 * best_t.x + 2;
            y = 3 * best_t.y + 2;
        }
 
        tables[idx].occupied_by += 1;
        
        if (tables[idx].occupied_by == 4) {
            tables.erase(tables.begin() + idx);
        }
 
        points.pb({x,y});
    }

    return points;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 10 + 1;

    vector<int> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 2;
        arr.pb(el);
    }

    vector<pii> points = solve(arr);


    for (pii i : points) {
        cout << i.first << " " << i.second << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}