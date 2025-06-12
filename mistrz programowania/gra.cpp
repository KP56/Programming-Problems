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

/*
Jakby ktoś się zastanawiał jak działa algorytm w przyszłości. Polega on na obserwacji, że BFS to algorytm programowania dynamicznego
w którym prioretyzujemy sprawdzenia pól w zależności od tego jak wcześnie możemy do nich dojść. Dlatego vis, który sprawdza obecne
położenie oraz grawitację zamienia normalnego BFSa w BFSa rozwiązującego zadanie.
*/

// W grawitacji 0 kulka jest zmuszona do przemieszczania się po maksymalnym możliwym x
// W grawitacji 1 kulka jest zmuszona do przemieszczania się po maksymalnym możliwym y
// W grawitacji 2 kulka jest zmuszona do przemieszczania się po minimalnym możliwym x
// W grawitacji 3 kulka jest zmuszona do przemieszczania się po minimalnym możliwym y

struct state {
    int arr[4];

    int& operator[](size_t i) {
        return this->arr[i];
    }
};

// Kolejka zawiera wektor w tej postaci: {x,y,grawitacja,ilość ruchów}
queue<state> q;
// vis[x][y][grawitacja] stwierdza czy pole było odwiedzone
bool vis[1000][1000][4] = {false};

int move_right[1000][1000] = {0};
int move_left[1000][1000] = {0};
int move_up[1000][1000] = {0};
int move_down[1000][1000] = {0};

void push_on_queue(state vec) {
    if (!vis[vec[0]][vec[1]][vec[2]]) {
        q.push(vec);
        vis[vec[0]][vec[1]][vec[2]] = true;
    }
}

int bfs(int x1, int y1, int x2, int y2, int n, int m) {
    q.push({x1,y1,0,0});
    vis[x1][y1][0] = true;

    while (!q.empty()) {
        state state = q.front();
        q.pop();

        int x = state[0];
        int y = state[1];
        int gravity = state[2];
        int move_count = state[3];

        vis[x][y][gravity] = true;

        if (x == x2 && y == y2) {
            return move_count;
        }

        int new_grav1 = (gravity+1)%4;
        int new_grav2 = (gravity-1+4)%4;
        if (gravity == 0) {
            push_on_queue({x,move_down[x][y],new_grav1,move_count+1});
            push_on_queue({x,move_up[x][y],new_grav2,move_count+1});
        } else if (gravity == 2) {
            push_on_queue({x,move_down[x][y],new_grav2,move_count+1});
            push_on_queue({x,move_up[x][y],new_grav1,move_count+1});
        } else if (gravity == 1) {
            push_on_queue({move_left[x][y],y,new_grav1,move_count+1});
            push_on_queue({move_right[x][y],y,new_grav2,move_count+1});
        } else if (gravity == 3) {
            push_on_queue({move_left[x][y],y,new_grav2,move_count+1});
            push_on_queue({move_right[x][y],y,new_grav1,move_count+1});
        } else {
            cout << "Something unexpected happened" << endl;
        }
    }

    return -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //srand(time(NULL));

    //clock_t t = clock();

    ini(n);
    //int n = 1000;
    ini(m);
    //int m = 1000;

    vector<string> board;
    /*int x_rand1 = rand() % 1000;
    int x_rand2 = rand() % 1000;
    int y_rand1 = rand() % 1000;
    int y_rand2 = rand() % 1000;*/
    for (int i = 0; i < n; i++) {
        instr(s);
        //string s = "";
        /*for (int j = 0; j < m; j++) {
            if (x_rand1 == i && y_rand1 == j) {
                s += "P";
            } else if (x_rand2 == i && y_rand2 == j) {
                s += "K";
            } else {
                int ran = rand() % 3;
                if (ran == 0) s += "#";
                else s += ".";
            }
        }*/
        board.pb(s);
    }

    int x1;
    int y1;
    int x2;
    int y2;
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < m; y++) {
            if (board[x][y] == '#') {
                for (int z = x-1; z >= 0 && board[z][y] != '#'; z--) {
                    move_right[z][y] = x-1;
                }

                for (int z = x+1; z < n && board[z][y] != '#'; z++) {
                    move_left[z][y] = x+1;
                }

                for (int z = y-1; z >= 0 && board[x][z] != '#'; z--) {
                    move_up[x][z] = y-1;
                }

                for (int z = y+1; z < m && board[x][z] != '#'; z++) {
                    move_down[x][z] = y+1;
                }
            } else if (board[x][y] == 'P') {
                x1 = x;
                y1 = y;
            } else if (board[x][y] == 'K') {
                x2 = x;
                y2 = y;
            }
        }
    }

    cout << bfs(x1,y1,x2,y2,n,m) << endl;
    //cout << ((double) clock() - t) / CLOCKS_PER_SEC << " seconds" << endl;
}