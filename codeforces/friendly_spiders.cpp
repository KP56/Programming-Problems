#include <bits/stdc++.h>

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

vector<int> sieve(int n) {
    vector<bool> is_prime(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i] && (long long)i * i <= n) {
            for (int j = i * i; j <= n; j += i)
                is_prime[j] = false;
        }
    }

    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.pb(i);
        }
    }

    return primes;
}

vector<int> bfs(int start, int end, unordered_map<int,vector<int>,custom_hash> graph) {
    queue<pii> q;
    unordered_set<int,custom_hash> vis;
    unordered_map<int,int,custom_hash> prev;
    vis.insert(start);
    q.push({start,-1});
    while (!q.empty()) {
        pii current = q.front();
        q.pop();
        int ind = current.fi;
        int score = current.se;
        for (int i : graph[ind]) {
            if (vis.find(i) == vis.end()) {
                vis.insert(i);
                prev[i] = ind;
                q.push({i,score+1});
            }
        }
    }

    if (prev.find(end) == prev.end()) {
        return {};
    } else {
        int current = end;
        vector<int> path;
        while (prev.find(current) != prev.end()) {
            path.pb(current);
            current = prev[current];
        }
        reverse(all(path));
        return path;
    }
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

vector<int> brute(int start, int end, vector<int> vec) {
    unordered_map<int,vector<int>,custom_hash> graph;
    for (int i = 1; i <= vec.size(); i++) {
        for (int j = 1; j <= vec.size(); j++) {
            if (i != j) {
                if (gcd(vec[i-1], vec[j-1]) != 1) {
                    graph[i].pb(j);
                }
            }
        }
    }

    vector<int> path = bfs(start, end, graph);
    if (!path.empty()) {
        path.insert(path.begin(), start);
    }
    return path;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    srand(time(NULL));

    //prime numbers up to sqrt(max)
    vector<int> primes = sieve(547);

    ini(n);
    //int n = 20;
    unordered_map<int,vector<int>,custom_hash> graph;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 10 + 1;
        vec.pb(a);
    }

    ini(s);
    //int s = rand() % n + 1;
    ini(t);
    //int t = rand() % n + 1;

    vector<unordered_set<int,custom_hash>> groups;

    for (int i = 0; i < vec.size(); i++) {
        int a = vec[i];
        unordered_set<int,custom_hash> connected;
        for (int x : primes) {
            while (a % x == 0) {
                connected.insert(x);
                a /= x;
            }
        }

        //we know that the number left has to be a prime greater than sqrt(max) if a != 1
        if (a != 1) {
            connected.insert(a);
        }

        groups.pb(connected);

        if (i + 1 == s) {
            for (int j : connected) {
                graph[0].pb(j);
                graph[j].pb(0);
            }
        } else if (i + 1 == t) {
            for (int j : connected) {
                graph[-1].pb(j);
                graph[j].pb(-1);
            }
        } else {
            for (int j : connected) {
                for (int k : connected) {
                    if (j != k) {
                        graph[j].pb(k);
                    }
                }
            }
        }
    }

    if (s == t) {
        cout << 1 << endl;
        cout << s << endl;
        return 0;
        //continue;
    }

    vector<int> path = bfs(0,-1,graph);
    //vector<int> p = brute(s, t, vec);

    /*if ((path.empty() && !p.empty()) || (p.empty() && !path.empty())) {
        cout << "test" << endl;
    }*/

    if (path.empty()) {
        cout << -1 << endl;
        return 0;
        //continue;
    }

    vector<int> final_path;
    final_path.pb(s);
    for (int i = 1; i < path.size() - 1; i++) {
        int prev = path[i - 1];
        int current = path[i];
        int counter = 0;
        for (auto j : groups) {
            if (j.find(prev) != j.end() && j.find(current) != j.end()) {
                final_path.pb(counter + 1);
                break;
            }
            counter++;
        }
    }
    final_path.pb(t);
    /*if (final_path != p) {
        cout << "test" << endl;
    }*/
    cout << final_path.size() << endl;
    for (int i : final_path) {
        cout << i << " ";
    }
    cout << endl;
}