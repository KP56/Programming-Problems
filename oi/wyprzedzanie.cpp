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

ll lcm(ll a, ll b) {
    return a*b/gcd(a,b);
}

ll gcd(ll a, ll b) {
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

struct fraction {
    ll a;
    ll b;

    fraction() {
        this->a = 0;
        this->b = 0;
    }

    fraction(ll a, ll b) {
        this->a = a;
        this->b = b;
    }

    fraction multiply(fraction c) const {
        return fraction(a*c.a,b*c.b);
    }

    fraction divide(fraction c) const {
        if (c.a < 0) {
            return multiply(fraction(-c.b,-c.a));
        }

        if (c.a == 0) {
            cout << "DZIELIMY PRZEZ 0!" << endl;
        }

        return multiply(fraction(c.b,c.a));
    }

    fraction add(fraction c) const {
        ll d = lcm(b,c.b);
        ll e = d/b;
        ll f = d/c.b;

        return fraction(a*e+c.a*f,d);
    }

    fraction subtract(fraction c) const {
        return add(fraction(-c.a,c.b));
    }

    bool operator < (const fraction& fraction2) const {
        return subtract(fraction2).a < 0;
    }

    bool operator > (const fraction& fraction2) const {
        return subtract(fraction2).a > 0;
    }

    bool operator <= (const fraction& fraction2) const {
        return subtract(fraction2).a <= 0;
    }

    bool operator >= (const fraction& fraction2) const {
        return subtract(fraction2).a >= 0;
    }

    bool operator == (const fraction& fraction2) const {
        return subtract(fraction2).a == 0;
    }
};

fraction min(fraction a, fraction b) {
    if (a < b)
        return a;
    return b;
}

fraction max(fraction a, fraction b) {
    if (a > b)
        return a;
    return b;
}

fraction velocity(fraction s, fraction t) {
    return s.divide(t);
}

fraction time(fraction v, fraction s) {
    return s.divide(v);
}

fraction distance(fraction v, fraction t) {
    return v.multiply(t);
}

//Rozwiązanie O(n*log(n))
//Można zauważyć, że do każdej ciężarówki można przyporządkować listę
//par {czas,prędkość} oznaczających od których momentów jakie prędkości
//ta ciężarówka miała. Ponadto dla każdej takiej pary można obliczyć
//średnią prędkość ciężarówki w okresie [0,czas].

//Gdybyśmy zdobyli tą średnią prędkość dla każdej pary, jesteśmy w stanie dokładnie
//policzyć kiedy i gdzie samochód wyprzedzi początek bądź koniec
//tej ciężarówki. Wystarczy policzyć relatywną prędkość dla każdej
//z tych par i sprawdzić czy czas znajduje się w odpowiednim przedziale.
//Jeżeli nie, przechodzimy do kolejnej pary.

//Jeżeli czas będzie posortowany niemalejąco na tej liście, można zastosować
//metodę wyszukiwania binarnego. Wiemy bowiem, że wraz z indeksem pary,
//rośnie czas. Mamy w takim razie gwarancję, że kolejno obliczane pozycje
//będą po sobie następowały.
//Złożoność czasowa takiego przeszukania: log(n)

//Gdybyśmy byli w stanie to wszystko stwierdzić, można by rozwiązać to zadanie
//poprzez dokonywanie symulacji jak powyżej dla każdej pary samochodów i sprawdzanie czy
//auto się mieści.

//Głównym problemem jest stworzenie takiej listy. Jednym ze sposobów, które rozważałem
//to programowanie dynamiczne. Wiadomo, że lista dla ostatniej ciężarówki będzie po prostu
//{0,v}. Co w takim razie dla kolejnej? Jeżeli kolejna jest szybsza od ostatniej,
//wtedy w pewnym momencie jej prędkość stanie się równa v. W takim razie będzie to
//{0,v2} oraz {czas kolizji,v}. Co dalej? Tutaj stanie się sytuacja już nieco bardziej
//skomplikowana. Będzie to tak naprawdę {0,v3}, {czas kolizji,x} gdzie x to jest prędkość
//z pary z poprzedniego vectora o największym czasie, który jest mniejszy bądź równy
//czasowi kolizji oraz wszystko co występuje po tej parze.

//Skoro jeden vector wynika z drugiego oraz będziemy z tych danych korzystać podczas
//jednej iteracji, nie musimy kopiować całego vectora. Jedyne co ulegnie zmianie to:
//- zamiana czasu w jednej z par na czas kolizji
//- usunięcie wszystkiego przed tamtą parą, której zmieniamy czas
//- pojawienie się nowej pary, którą możemy wsadzić na początek

//Usunięcie może wydać się operacją, która zajmie dużo czasu, natomiast można zauważyć,
//że każdy dodany element można usunąć tylko raz, więc łącznie będzie maksymalnie n usunięć dla n elementów.

//Potrzebujemy struktury danych, która pozwala nam na:
//- dostęp do elementów o wybranych indeksach w czasie stałym
//- usuwanie elementu z przodu w czasie stałym
//- dodawanie elementów na sam początek w czasie stałym

//Taką strukturą danych może być na przykład deque z STLa.

//Ostatnią rzeczą potrzebną, aby to rozwiązanie zadziałało jest
//możliwość zdobycia średnich prędkości dla każdej pary. W przeciwnym
//razie wyszukiwanie binarne nie zadziała. Wiadomo, że wzór na średnią
//w tym przypadku będzie Vśr=((T(i)-T(i-1))*V(i-1)+...+(T(1)-T(0))*T(0))/T(i)
//skoro T(0) jest równe 0 to usuwamy je z mianownika.
//Szybko można zauważyć, że wynik średniej prędkości można łatwo zdobyć mając takowy dla
//odpowiadającej pary z poprzedniej listy. T(i) się nie zmieni. Jedynie znikną pewne
//wartości ze środka oraz pojawi się nowa wartość. Odejmujemy wszystkie ((T(j)-T(j-1))*V(j-1))/T(i)
//gdzie j to wszystkie usunięte oraz para, którą zmodyfikowaliśmy a następnie dodajemy nową taką wartość
//dla tej pary. Teraz pytanie jak odjąć tamte wszystkie wyrażenia w czasie stałym oraz czy
//jesteśmy w stanie to zrobić. Gdybyśmy mieli ich sumę wystarczy ją podzielić przez T(i) i dostaniemy
//wynik.

//Są dwa warunki rozwiązania problemu z sumą:
//- musimy być w stanie zdobywać sumę (T(j)-T(j-1))*V(j-1) dla kolejnych j w wyznaczonym przez
//nas zakresie [0,a] w czasie lepszym niż liniowy
//- jesteśmy w stanie przerobić strukturę danych, którą użyliśmy na taką, która obsługuje
//inną listę utworzoną poprzez dodanie jednej pary na początku oraz usunięciu jakiegoś spójnego
//ciągu par w zakresie [0,a] w czasie lepszym niż liniowy

//Gdybyśmy zastosowali klasyczne prefixowanie, moglibyśmy spełnić pierwszy warunek, jednak
//złożoność czasowa dokonania jakiejś zmiany w prefixowaniu to O(n). W takim razie
//musimy się zastanowić jak to poprawić. Całkiem proste jest zauważenie, że gdybyśmy
//usuwali elementy na końcu oraz dodawali elementy na koniec, można by to wszystko robić
//w czasie stałym (każdy element może być tylko raz usunięty). W związku z tym tworzymy
//po prostu odwrócony prefix przy pomocy vectora oraz korzystamy z niego do zrobienia wszystkiego,
//co potrzebujemy.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(trucks);
    in_i(car_l);
    in_i(v1);
    in_i(v2);
    fraction v = fraction(v1,v2);

    for (ll i = 0; i < trucks; i++) {
        in_i(pos);
        in_i(length);
        in_i(v3);
        in_i(v4);
        
    }

    

    cout << 0 << endl;
}