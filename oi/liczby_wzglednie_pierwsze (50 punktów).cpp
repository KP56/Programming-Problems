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

//Naszym celem jest napisanie programu, który znajdzie liczby, których
//NWD z x jest równe 1. Dla podzadań 1 i 2 wystarczy rozważać liczby
//mniejsze bądź równe x.

//Obserwacja 1
//Liczba y jest względnie pierwsza z x tylko jeżeli y nie ma wspólnych dzielników
//z x.

//Obserwacja 2
//Na podstawie obserwacji 2 można zauważyć, że jeżeli jakaś liczba y nie jest względnie pierwsza z x,
//to wtedy ilorazy y też nie będą względnie pierwsze.

//Rozwiązanie O(n+f(n)*log(x))
//Rozwiązanie polega na tym, aby stworzyć tablicę booleanów o wielkości n. Naszym następnym celem jest
//korzystanie z algorytmu euklidesa w celu sprawdzenia czy NWD x i y jest równe 1. Jeżeli nie,
//wtedy iterujemy przez kolejne ilorazy tej liczby i oznaczamy w tablicy, że one również nie
//są względnie pierwsze. Jeżeli napotkamy kolejną liczbę, która nie została oznaczona w tablicy,
//powtarzamy krok wcześniejszy.

//Program zadziała tylko dla podzadań 1 i 2 gdzie M <= n. W innych przypadkach wielkość tablicy będzie musiała
//być inna.

//Rozwiązanie O(f(n)(log(x)+log(f(n))))
//Bardzo podobne do wcześniejszego, jedyna różnica polega na wykorzystaniu vectora intów zamiast tablicy booleanów.
//Następnie vector sortujemy i po nim iterujemy. Można policzyć ze wzoru y-x-1 ile jest liczb względnie pierwszych pomiędzy 
//kolejnymi liczbami niewzględnie pierwszymi z n, x i y.

//Obserwacja 4
//Liczby względnie pierwsze to takie, które można stworzyć poprzez iloczyn liczb pierwszych, niepodzielnych
//przez n. Wszystkie pozostałe to te, które tworzymy poprzez mnożenie liczb pierwszych podzielnych przez n.

ll gcd(ll a, ll b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

unordered_set<ll> findPrimeFactors(ll n) {
    unordered_set<ll> ans;
    while (n % 2 == 0) {
        ans.insert(2);
        n = n / 2;
    }
 
    for (ll i = 3; i <= sqrt(n); i = i + 2) {
        while (n % i == 0) {
            ans.insert(i);
            n = n / i;
        }
    }
 
    if (n > 2)
        ans.insert(n);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_ll(number);
    in_ll(position);
    in_ll(length);

    unordered_set<ll> s;
    unordered_set<ll> prime_factors = findPrimeFactors(number);
    for (ll i : prime_factors) {
        for (ll j = 1; j <= number / i; j++) {
            s.insert(i * j);
        }
    }
    vector<ll> v;
    for (ll i : s) {
        v.pb(i);
    }
    sort(all(v));
    ll sum = 0;
    ll prev = 0;
    for (ll i = 0; i < v.size(); i++) {
        ll a = v[i];
        sum += a - prev - 1;

        if (sum >= position) {
            ll iterations = sum - position + 1;
            for (ll j = 0; j < min(length,iterations); j++) {
                cout << v[i] - iterations + j << " ";
            }
            ll left_iterations = length - min(length,iterations);
            i++;
            for (ll j = 0; j < left_iterations; i++) {
                for (ll k = v[i - 1] + 1; k < v[i] && k - v[i - 1] <= left_iterations - j; k++) {
                    cout << k << " ";
                }
                j += v[i] - v[i - 1] - 1;
            }
            break;
        }

        prev = a;
    }
    cout << endl;
}