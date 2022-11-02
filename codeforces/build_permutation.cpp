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
using vb = vector<bool>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vvvi = vector<vector<vector<int>>>;
using vlli = vector<lli>;
using vvlli = vector<vector<lli>>;

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

int findFirstPerfectSquare(int n) {
    int a = sqrt(n - 1);
    if (a*a == n - 1) {
        return n - 1;
    } else {
        return (a + 1) * (a + 1);
    }
}

void readCaseData() {
    in_i(size);

    //It is possible to find a number n such that size-1+n is a perfect square
    //and n is in range <0, size-1>
    //knowing that I can iterate from index n until the end of the list
    //and insert numbers size-1-i
    //this way I am able to solve the problem for a certain suffix of the list
    //now I just need to repeat that suffix solving every time I get a new list
    //by cutting off that solved suffix

    vi solution(size);
    int apparent_size = size;
    while (apparent_size > 0) {
        int x = findFirstPerfectSquare(apparent_size) - (apparent_size - 1);
        for (int i = x; i < apparent_size; i++) {
            int a = apparent_size - 1 - (i - x);

            solution[i] = a;
        }

        apparent_size = x;
    }

    for (int i : solution) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(cases);

    while (cases--) {
        readCaseData();
    }
}