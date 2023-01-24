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

struct Rectangle {
    int width;
    int height;
    int area;

    Rectangle(int width, int height) {
        this->width = width;
        this->height = height;
        this->area = width * height;
    }
};

void readCaseData() {
    in_i(rectangles);
    in_i(queries);

    vector<vector<ll>> prefix(1000,vector<ll>(1000));
    for (int i = 0; i < rectangles; i++) {
        in_ll(height);
        in_ll(width);
        
        prefix[height - 1][width - 1] += height * width;
    }

    for(int x = 0; x < 1000; x++) {
        for(int y = 1; y < 1000; y++) {
            prefix[x][y] = prefix[x][y] + prefix[x][y - 1];
        }
    }

    for(int y = 0; y < 1000; y++) {
        for(int x = 1; x < 1000; x++) {
            prefix[x][y] = prefix[x][y] + prefix[x - 1][y];
        }
    }


    for (int i = 0; i < queries; i++) {
        in_i(height1);
        in_i(width1);
        in_i(height2);
        in_i(width2);

        ll solution = prefix[height2 - 2][width2 - 2] + prefix[height1 - 1][width1 - 1] - prefix[height1 - 1][width2 - 2] - prefix[height2 - 2][width1 - 1];

        cout << solution << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}