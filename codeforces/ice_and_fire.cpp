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
#define in_ll(x) ll x; in(x)
#define in_i(x) int x; in(x)
#define in_str(x) string x; in(x)

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

void readCaseData() {
    in_i(size);
    in_str(bin);
    vector<bool> d;
    for (char c : bin) {
        if (c == '0') {
            d.pb(false);
        } else {
            d.pb(true);
        }
    }

    //There are 2 cases:
    //Case 1: the last environment is 1
    //The optimal solution to ensure the victory of a specific
    //player would be to choose 2 highest ones into a battle in a 1
    //environment and the highest and the lowest one in a 0 environment
    //battle. We don't choose our player until the last battle.
    //Case 2: the last environment is 0
    //We want our player to be the lowest one in the last battle.
    //That's why we will choose the lowest and highest players if the
    //environment is 1 and two lowest ones if the environment is 0.
    
    //Meaning that in case 1 both ones and zeros will reduce the number of players
    //on the left by one, however, if there is only one player on the right, ones
    //will no longer do so. In order to check if the player x can win, we need to
    //get its value r which says how many players there are on the right.
    //If y is the position of the last zero from the left, then player x can win if
    //r<=y. That's because if the number of players on the right is even a little bit
    //higher, we won't be able to remove the last player on the right.

    //For case 2 the proper condition will be l<=y where y is the position of the last one
    //from the left, since if the number of numbers on the left is even a little bit higher,
    //there will be one number impossible to remove on the left.

    //If y in both cases is undefined, we assume that it's 0.

    //Let variables a and b be the number of players which would have a chance to win if
    //the last environment was 0 (for a) or 1 (for b). Their starting values will be equal to 1.
    //When we increase x, the last environment might change. In that case y will definitely increase
    //for one of the cases. Meaning that more players will be able to win.

    int a = 1;
    int b = 1;
    int last_one = -1;
    int last_zero = -1;
    for (int i = 0; i < d.size(); i++) {
        bool c = d[i];
        if (c) {
            a += i - last_one;
            last_one = i;
        } else {
            b += i - last_zero;
            last_zero = i;
        }

        if (c) {
            cout << b << " ";
        } else {
            cout << a << " ";
        }
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