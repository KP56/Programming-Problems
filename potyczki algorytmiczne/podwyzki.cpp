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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_i(divisions);

    vector<int> numbers;
    for (int i = 0; i < size; i++) {
        in_i(a);
        numbers.pb(a);
    }

    //Naszym zadaniem jest podzielenie ciągu na takie fragmenty aby wybranie dowolnych
    //elementów z tych fragmentów nie tworzyło ciągu rosnącego
    
    //Najlepszą strategią na stworzenie takiego ciągu, gwarantującą, że jeśli on istnieje, to go
    //otrzymamy jest wybranie minimalnego elementu z pierwszego fragmentu a następnie najmniejszego
    //fragmentu z następnego, który jest większy od poprzedniego. Powtarzamy to, aż otrzymamy ciąg.
    //Jeżeli w którymś momencie nie jesteśmy w stanie znaleźć elementu większego od poprzedniego, to
    //ciąg rosnący nie istnieje. Nazwijmy taki element, który powinien zostać w danym fragmencie wybrany wg. optymalnej strategii
    //elementem optymalnym.

    //Aby doprowadzić do naszego celu, tak naprawdę wystarczy, że istnieją dwa takie kolejne fragmenty gdzie optymalny element pierwszego
    //jest większy bądź równy maksymalnemu elementowi w drugim fragmencie.

    vector<int> solution;

    //Przypadek 1: liczba przedziałów jest większa bądź równa 4
    //Szukamy dwóch kolejnych elementów, takich, że pierwszy jest większy bądź równy drugiemu. Gdy takowe znajdziemy,
    //wydzielamy oba jako osobne przedziały. Wtedy mamy pewność, że nie da się utworzyć rosnącego ciągu. Resztę
    //możemy losowo podzielić. Jeżeli cały ten ciąg jest rosnący to NIEMOŻLIWY jest odpowiedni podział.
    if (divisions >= 4) {
        for (int i = 1; i < numbers.size(); i++) {
            int a = numbers[i];
            int prev = numbers[i - 1];

            bool last = (i == numbers.size() - 1);

            if (prev >= a) {
                for (int j = 1; j < i - 1 && j <= divisions - 4 + last; j++) {
                    solution.pb(j);
                }

                if (i > 1) {
                    solution.pb(i - 1);
                }
                solution.pb(i);
                if (!last) {
                    solution.pb(i + 1);
                }

                for (int j = i + 2; j < i + 2 + (divisions - 4 + last) - (i - 2); j++) {
                    solution.pb(j);
                }

                break;
            }
        }
    }

    //Przypadek 2: w ciągu istnieje minimalny element, który nie jest na początku tego ciągu oraz liczba przedziałów jest równa 3.
    //Wtedy wystarczy wydzielić minimalny element jako osobny przedział a jak resztę podzielimy nie ma żadnego znaczenia.
    int minimal = INT_MAX;
    for (int i : numbers) {
        minimal = min(i,minimal);
    }

    bool found = false;
    if (divisions == 3) {
        for (int i = 1; i < numbers.size(); i++) {
            if (numbers[i] == minimal) {
                if (i == numbers.size() - 1) {
                    solution.pb(i - 1);
                }
                solution.pb(i);
                if (i != numbers.size() - 1) {
                    solution.pb(i + 1);
                }
                found = true;
                break;
            }
        }
    }

    //Przypadek 3: jedyny minimalny element jest na początku ciągu, liczba przedziałów jest równa 3, w ciągu istnieje maksymalny element,
    //który nie jest na końcu tego ciągu
    //Wiadomo, że min pierwszego fragmentu nigdy nie będzie większy bądź równy jakiemukolwiek elementowi.
    //W związku z tym musimy doprowadzić do przypadku w którym min drugiego fragmentu jest większy bądź
    //równy maxowi trzeciego fragmentu. W powyższym przypadku wystarczy wydzielić maksymalny element jako drugi
    //fragment. Zrobienie tego gwarantuje nam, że max trzeciego fragmentu będzie zawsze mniejszy bądź równy.

    int maximal = INT_MIN;
    for (int i : numbers) {
        maximal = max(i,maximal);
    }

    if (divisions == 3 && !found) {
        for (int i = 0; i < numbers.size() - 1; i++) {
            if (numbers[i] == maximal) {
                solution.pb(i);
                solution.pb(i + 1);
                found = true;
                break;
            }
        }
    }

    //Przypadek 4: jedyny minimalny element jest na początku ciągu, liczba przedziałów jest równa 3, jedyny maksymalny element ciągu
    //jest na jego końcu
    //Maksimum ostatniego fragmentu jest zawsze niemożliwe dla drugiego fragmentu do przekroczenia. Drugi fragment również nigdy nie
    //będzie miał elementu mniejszego od minimum pierwszego ciągu. W związku z tym NIEMOŻLIWY jest odpowiedni podział.

    //Przypadek 5: liczba podziałów jest równa 2
    //Wiadomo, że minimalny element pierwszego fragmentu musi być większy bądź równy maksymalnemu
    //elementowi drugiego fragmentu. W związku z tym można zastosować tutaj rozwiązanie brutalne.
    //Na początku dokonamy ewaluacji stanu początkowego gdzie fragment pierwszy jest złożony z jednego
    //elementu (obliczymy max i min). Do tego możemy skorzystać z kolejki minimów i maximów. Następnie
    //usuwamy z kolejki maximów element przy użyciu funkcji pop oraz dodajemy nowy element do kolejki minimów.
    //W ten sposób przesuwamy granicę. Jeżeli napotkamy przypadek gdy min jest większy bądź równy max, jest
    //to nasze rozwiązanie.

    if (divisions == 2) {
        int current_min = numbers[0];
        vector<int> maxes;
        int current = INT_MIN;
        for (int i = numbers.size() - 1; i >= 1; i--) {
            current = max(numbers[i], current);
            maxes.pb(current);
        }

        for (int i = 0; i < numbers.size() - 1; i++) {
            current_min = min(current_min, numbers[i]);

            if (current_min >= maxes[maxes.size() - i - 1]) {
                solution.pb(i + 1);
                break;
            }
        }
    }

    if (solution.empty()) {
        cout << "NIE" << endl;
    } else {
        cout << "TAK" << endl;
    }

    for (int i : solution) {
        cout << i << " ";
    }
    if (!solution.empty()) {
        cout << endl;
    }
}