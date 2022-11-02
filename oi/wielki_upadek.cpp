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

//H1 nazwiemy wysokością mniejszych kostek a H2 większych

//Łańcuchem domin nazwiemy grupę domin, u których zepchnięcie
//tego najbardziej po lewej w prawą stronę będzie skutkowało
//upadkiem wszystkich.

//Obserwacja 1
//H2/H1 małych kostek domina możemy zastąpić jedną większą kostką.

//Obserwacja 2
//Jeżeli zostaną nam jakieś kostki na sam koniec, możemy je dostawić
//na końcu.

//Obserwacja 3
//Optymalne rozwiązanie w przypadku gdy pchamy domino w prawo jest
//optymalnym rozwiązaniem obróconego domina, gdy pchamy je w lewo.

//Rozwiązanie O(n^2)
//Możemy zauważyć, że dostawianie domin pomiędzy dwoma dominami, które
//w optymalnym rozwiązaniu i tak nie zostaną przewrócone, nie ma sensu.
//W związku z tym mamy tak naprawdę n - 1 możliwości. Możemy zacząć dostawiać
//domina za dokładnie n - 1 dominami. Program oparty o to rozwiązanie dla każdej
//pary następujących po sobie domin policzy ile mniejszych domin będzie potrzebnych.
//Jeżeli mamy więcej niż H2/H1 małych domin pomiędzy dwoma oryginalnymi dominami,
//zastępujemy je większym.

//Rozwiązanie O(n)
//Przy implementacji rozwiązania O(n^2), można zaobserwować, że podczas rozważania
//x-tej pary domin jako naszej pary początkowej możliwe, że powtórzymy dostawianie
//domin w miejscach, które już te domina miały podczas rozważania wcześniejszej pary
//dostawione. 

int getResultFor(int at, vector<int> &vec, int num1, int h1, int num2, int h2) {
    int score = 1;
    while (at < vec.size() && (num1 > 0 || num2 > 0 || vec[at] <= 0)) {
        if (vec[at] <= 0)
            score++;
        else {
            //ile potrzebujemy małych klocków
            int required_smaller = vec[at] / h1 + (vec[at] % h1 != 0);
            //ile małych klocków zastępujemy większych
            int height_ratio = h2/h1;
            //iloma małymi klockami uzupełniamy "dziurę"
            int to_remove_num1 = required_smaller;
            //iloma większymi klockami uzupełniamy "dziurę"
            int to_remove_num2 = 0;
            //jeżeli potrzebnych małych klocków jest więcej niż ilość którą
            //można zastąpić większym klockiem oraz większych klocków jest więcej
            //niż 0
            if (required_smaller >= height_ratio && num2 > 0) {
                //zastępujemy mniejsze klocki większymi
                to_remove_num2 = min(num2, required_smaller / height_ratio);
                //odejmujemy tyle małych klocków ile zastąpiliśmy
                to_remove_num1 -= to_remove_num2 * height_ratio;
            }

            //jeżeli nie mamy wystarczająco małych klocków
            if (num1 < to_remove_num1) {
                //sprawdzamy czy możemy pokryć brak większym klockiem
                if (num2 >= to_remove_num2 + 1) {
                    //jeżeli tak jest, wtedy w ogóle nie skorzystamy z
                    //małych klocków oraz zwiększamy ilość użytych większych
                    //klocków o 1
                    to_remove_num2++;
                    to_remove_num1 = 0;
                } else {
                    //ilość małych klocków jest zbyt niska i większe klocki nie mogą
                    //pokryć tej różnicy

                    //zwracamy pozostałe klocki + wcześniejsze
                    return num1 + num2 + score;
                }
            }

            //dodajemy 1 klocka oraz te, które wykorzystaliśmy
            score += to_remove_num1 + to_remove_num2 + 1;
            //oraz usuwamy z pudełka wykorzystane
            num1 -= to_remove_num1;
            num2 -= to_remove_num2;
        }
        
        at++;
    }
    //zwracamy ilość pozostałych klocków oraz te, które udało nam się "zdobyć"
    return score + num1 + num2;
}

//Nie działa mimo, że przechodzi początkowe testy
//nie mogę znaleźć żadnego błędu
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    int prev = 0;
    vector<int> vec;
    for (int i = 0; i < size; i++) {
        in_i(x);
        in_i(h);
        if (prev != 0) {
            vec.pb(x - prev);
        }
        prev = x + h;
    }
    in_i(num1);
    in_i(h1);
    in_i(num2);
    in_i(h2);

    if (h1 > h2) {
        int h2_cp = h2;
        h2 = h1;
        h1 = h2_cp;
        int num1_cp = num1;
        num1 = num2;
        num2 = num1_cp;
    }

    if (size == 1) {
        cout << num1 + num2 + 1 << endl;
        return 0;
    }

    //h2 > h1
    int m = INT_MIN;
    for (int i = 0; i < vec.size(); i++) {
        m = max(m, getResultFor(i, vec, num1, h1, num2, h2));
    }

    reverse(all(vec));
    for (int i = 0; i < vec.size(); i++) {
        m = max(m, getResultFor(i, vec, num1, h1, num2, h2));
    }

    cout << m << endl;
}