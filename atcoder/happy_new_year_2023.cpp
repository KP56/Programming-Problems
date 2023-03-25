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
     
    void readCaseData() {
        inll(n);
     
        ll lastly = -1;
        int divided = 0;
        while (n % 2 == 0) {
            n /= 2;
            lastly = 2;
            divided++;
        }
     
        if (divided == 1) {
            cout << (ll) sqrtl(n) << " " << lastly << endl;
            return;
        } else if (divided == 2) {
            cout << lastly << " " << n << endl;
            return;
        } else if (divided == 3) {
            cout << lastly << " " << lastly << endl;
            return;
        }
     
        for (int i = 3; ; i += 2) {
            while (n % i == 0) {
                n /= i;
                lastly = i;
                divided++;
            }
     
            if (divided == 1) {
                cout << (ll) sqrtl(n) << " " << lastly << endl;
                return;
            } else if (divided == 2) {
                cout << lastly << " " << n << endl;
                return;
            } else if (divided == 3) {
                cout << lastly << " " << lastly << endl;
                return;
            }
        }
    }
     
    int main() {
        ios_base::sync_with_stdio(false);
        cin.tie(0);
     
        ini(cases);
     
        while (cases--) {
            readCaseData();
        }
    }