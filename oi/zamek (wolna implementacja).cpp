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
#define inll(x) ll x; in(x)
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

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

vector<pii> getCorners(vector<int> &room) {
    return {
        {room[0],room[1]},
        {room[2],room[1]},
        {room[0],room[3]},
        {room[2],room[3]}
    };
}

vector<vector<int>> getSides(vector<int> &room) {
    return {
        {room[0],room[1],room[0],room[3]},
        {room[2],room[1],room[2],room[3]},
        {room[0],room[1],room[2],room[1]},
        {room[0],room[3],room[2],room[3]}
    };
}

bool stickToTheSide(pii &corner, vector<int> &side) {
    if (((corner.first <= side[0] && corner.first >= side[2]) || (corner.first >= side[0] && corner.first <= side[2]))
            && ((corner.second <= side[1] && corner.second >= side[3]) || (corner.second <= side[3] && corner.second >= side[1]))) {
        return true;
    }

    return false;
}

bool stick(vector<int> &room1, vector<int> &room2) {
    vector<pii> corners1 = getCorners(room1);
    vector<pii> corners2 = getCorners(room2);

    int equal_corners = 0;
    for (auto i : corners1) {
        for (auto j : corners2) {
            equal_corners += (i == j);
        }
    }

    int sticking = 0;
    for (auto i : getSides(room1)) {
        for (auto j : corners2) {
            sticking += stickToTheSide(j, i);
        }
    }

    for (auto i : getSides(room2)) {
        for (auto j : corners1) {
            sticking += stickToTheSide(j, i);
        }
    }

    if (equal_corners == 1 && sticking == 4) {
        return false;
    }

    return sticking >= 1;
}

int bfs(int start, int end, vector<vector<int>> &adj_list) {
    queue<pii> q;
    vector<bool> vis(adj_list.size());
    q.push({start,1});
    while (!q.empty()) {
        pii current = q.front();
        vis[current.first] = true;
        q.pop();
        if (current.first == end) {
            return current.second;
        }

        for (int i : adj_list[current.first]) {
            if (!vis[i]) {
                vis[i] = true;
                q.push({i,current.second + 1});
            }
        }
    }

    return -1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(w);
    ini(h);
    ini(n);
    ini(m);

    ini(xp);
    ini(yp);
    ini(xk);
    ini(yk);

    vector<vector<int>> rooms;
    for (int i = 0; i < n; i++) {
        ini(x1);
        ini(y1);
        ini(x2);
        ini(y2);

        rooms.pb({min(x1,x2),min(y1,y2),max(x1,x2),max(y1,y2)});
    }

    int starting_room = -1;
    int ending_room = -1;
    for (int i = 0; i < n; i++) {
        vector<int> &room = rooms[i];
        if (xp >= room[0] && xp <= room[2] && yp >= room[1] && yp <= room[3]) {
            starting_room = i;
        }

        if (xk >= room[0] && xk <= room[2] && yk >= room[1] && yk <= room[3]) {
            ending_room = i;
        }
    }

    for (int i = 0; i < m; i++) {
        ini(x);
        ini(y);

        for (int a = 0; a < n; a++) {
            vector<int> &i = rooms[a];
            if (x >= i[0] && x <= i[2] && y >= i[1] && y <= i[3]) {
                rooms[a] = {};
            }
        }
    }

    vector<vector<int>> adj_list(n);
    for (int i = 0; i < n; i++) {
        if (rooms[i].empty()) continue;

        vector<int> &room1 = rooms[i];
        for (int j = i + 1; j < n; j++) {
            if (rooms[j].empty()) continue;

            vector<int> &room2 = rooms[j];
            if (stick(room1, room2)) {
                adj_list[i].pb(j);
                adj_list[j].pb(i);
            }
        }
    }

    cout << bfs(starting_room, ending_room, adj_list) << endl;
}