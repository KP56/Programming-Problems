#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
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

//Naszym celem jest doprowadzić do sytuacji w której
//w każdej gablocie dwa z pól są równe 0.

//Gdybyśmy skupili się na tylko jednej z nich,
//można zauważyć że najlepszą strategią byłoby
//pozbycie się dwóch rodzajów wypieków, których
//suma ilości w tej gablocie jest najniższa.
//Optymalnym wypiekiem w tej gablocie można zatem
//nazwać pozostały po takiej operacji rodzaj wypieków.
//Pojedyńcza gablota może posiadać więcej optymalnych wypieków
//np. drożdżówki=0, pączki=0, rogaliki=0 posiada 3 optymalne wypieki.

//Problem jest jednak taki, że nie można się po prostu pozbywać wypieków.
//Za każdym razem trzeba je gdzieś przełożyć. Oznacza to, że jeśli jakiś
//konkretny rodzaj wypieków jest na którejkolwiek z gablot, to musi posiadać
//osobną dla siebie gablotę.

//Najłatwiejszy przypadek to taki w którym istnieje gablota gdzie
//ten wypiek jest optymalnym wypiekiem oraz pozostałe optymalne
//wypieki tej gabloty (jeśli jakiekolwiek istnieją) mają swoją
//gablotę gdzie są jedynymi optymalnymi wypiekami. Wówczas
//wystarczy wszystkie wypieki tego rodzaju z gablot gdzie nie
//są optymalne przenosić do tych "ekskluzywnych gablot".

//Rozważmy teraz przypadek gdzie jeden z 3 rodzajów wypieków
//nie posiada ekskluzywnej gabloty oraz jest więcej niż 0 wypieków tego rodzaju.
//Są wówczas 2 możliwości:
//1) Ten rodzaj jest optymalnym wypiekiem w którejś z gablot
//2) Ten rodzaj nie jest optymalnym wypiekiem w żadnej z gablot

//Nie trudno zauważyć, że w obu z podanych możliwości
//będziemy zmuszeni poświęcić którąś z gablot na potrzeby
//tego wypieku.

//Na podstawie tego możemy sporządzić rozwiązanie brutalne
//o złożoności czasowej O(n^x) gdzie n jest ilością gablot
//a x (max x=2 czyli w najgorszym przypadku O(n^2)) ilością
//rodzajów wypieków które nie posiadają ekskluzywnej
//gabloty oraz ich suma jest większa od 0.

//Działa ono na takiej zasadzie, że iterujemy na początku
//przez wszystkie gabloty i obliczamy ile będziemy musieli
//dokonać przesunięć dla każdego rodzaju wypieku, który nie
//ma ekskluzywnej gabloty, jeśli własnie go wybierzemy jako ten
//który pozostanie w gablocie na koniec. Następnie po prostu
//sumujemy ilość wypieków do przesunięcia zakładając, że jedynym
//wypiekiem który chcemy pozostawić jest pierwszy z brzegu wypiek
//optymalny. Potem dokonujemy właściwą część rozwiązania brutalnego
//czyli liczymy dla każdej gabloty o ile zmieni się liczba ruchów
//jeśli zmienimy wypiek który pozostawimy na jeden z tych bez
//ekskluzywnej gabloty. Dla każdej tak wybranej gabloty dokonujemy
//również iteracje sprawdzając pozostałe gabloty na drugim wypieku
//który nie ma ekskluzywnej gabloty (jeśli istnieje).

//Istnieje jednak dużo lepsze rozwiązanie działające w czasie liniowym O(n).
//Na początku potrzebne są nam dwie obserwacje:
//Obserwacja 1: w przypadku gdy x=1 można dla takiego przypadku
//po prostu przeiterować i sprawdzać jak zmieni się liczba ruchów
//dla każdej wybranej gabloty. Teraz jeśli mamy przypadek gdzie x=2,
//możemy dokonać podobną iterację jak dla x=1 tylko, że dwa razy.
//Jeżeli najlepsze gabloty do poświęcenia dla obu wypieków się różnią,
//to wtedy są one najlepsze do wybrania.

//Obserwacja 2: jeżeli x=2 oraz po dokonaniu operacji z Obserwacji 1,
//najlepsze dla obu rodzajów wypieków gabloty są takie same, to
//rzeczywiście najlepszym rozwiązaniem będzie kombinacja najlepszej
//gabloty dla 1-szego rodzaju oraz drugiej najlepszej dla 2-ego rodzaju
//lub na odwrót.

//Problem z przypadkiem x=1.
//jeżeli wybierzemy gablote
//która jest jedyną ekskluzywną dla innego
//rodzaju, możemy otrzymać BŁĘDNY wynik.

//Możliwe rozwiązanie: możemy potraktować
//przypadek x=1 jako x=2 oraz rodzaj z
//jedną ekskluzywną gablotą jako rodzaj
//bez eksluzywnej gabloty

//Bez zauważenia tego kłopotliwego przypadku
//szczególnego wynik to: 77 punktów

//Po zauważeniu: 100 punktów

struct Wrapper {
    ll d;
    ll p;
    ll r;

    Wrapper(ll d, ll p, ll r) {
        this->d = d;
        this->p = p;
        this->r = r;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_ll(size);
    vector<Wrapper> arr;
    for (ll i = 0; i < size; i++) {
        in_ll(d);
        in_ll(p);
        in_ll(r);

        arr.pb({d,p,r});
    }

    //Na początek obliczamy dobrą estymację ruchów,
    //sprawdzamy czy jakieś rodzaje wypieków nie mają
    //ekskluzywnej gabloty oraz liczymy łączne wystąpienia
    //każdego rodzaju wypieku
    ll moves_estimation = 0;

    bool r_has_exclusive = false;
    bool p_has_exclusive = false;
    bool d_has_exclusive = false;

    ll r_sum = 0;
    ll p_sum = 0;
    ll d_sum = 0;

    ll r_count = 0;
    ll p_count = 0;
    ll d_count = 0;

    for (Wrapper p : arr) {
        r_sum += p.r;
        p_sum += p.p;
        d_sum += p.d;

        if (p.d >= p.p && p.d >= p.r) {
            moves_estimation += p.p + p.r;
            d_has_exclusive = true;
            d_count++;
        } else if (p.p >= p.d && p.p >= p.r) {
            moves_estimation += p.d + p.r;
            p_has_exclusive = true;
            p_count++;
        } else {
            moves_estimation += p.p + p.d;
            r_has_exclusive = true;
            r_count++;
        }
    }

    //Obliczamy wartość x
    ll x = (!r_has_exclusive && r_sum > 0) + (!p_has_exclusive && p_sum > 0) + (!d_has_exclusive && d_sum > 0);

    //obsłużenie kłopotliwego przypadku specjalnego
    if (x == 1) {
        //traktujemy rodzaj z jedną gablotą
        //ekskluzywną jako taki który jej nie ma
        if (r_count == 1) {
            r_has_exclusive = false;
        } else if (p_count == 1) {
            p_has_exclusive = false;
        } else if (d_count == 1) {
            d_has_exclusive = false;
        } else {
            //upewniamy się, że nic się nie zmienia
            //jeżeli nie ma rodzaju z 1 ekskluzywną gablotą
            x--;
        }
        //zmieniamy x na 2 jeśli jest rodzaj z 1
        //ekskluzywną gablotą
        x++;
    }

    if (x == 1) {
        //Dokonujemy prostej iteracji w celu znalezienia
        //najlepszej gabloty do poświęcenia
        ll min_moves = 9223372036854775807;
        for (ll i = 0; i < size; i++) {
            Wrapper p = arr[i];

            //Liczymy ile ruchów wg. estymacji
            //potrzebuje ta gablota
            ll single_wrapper_m;
            if (p.d >= p.p && p.d >= p.r) {
                single_wrapper_m = p.p + p.r;
            } else if (p.p >= p.d && p.p >= p.r) {
                single_wrapper_m = p.d + p.r;
            } else {
                single_wrapper_m = p.p + p.d;
            }

            //Obliczamy jak będzie wyglądała łączna ilość ruchów
            //po wybraniu tej gabloty
            ll moves_after_selecting = moves_estimation - single_wrapper_m;
            if (!r_has_exclusive && r_sum > 0)
                moves_after_selecting += p.p + p.d;
            else if (!p_has_exclusive && p_sum > 0)
                moves_after_selecting += p.r + p.d;
            else if (!d_has_exclusive && d_sum > 0)
                moves_after_selecting += p.r + p.p;

            min_moves = min(min_moves, moves_after_selecting);
        }

        cout << min_moves << endl;
    } else if (x == 2) {
        //Dokonujemy prostej iteracji w celu znalezienia
        //najlepszej gabloty do poświęcenia dla obu
        //rodzajów wypieków
        ll min_moves1 = 9223372036854775807;
        ll min_moves2 = 9223372036854775807;
        ll snd_min_moves1 = 9223372036854775807;
        ll snd_min_moves2 = 9223372036854775807;

        ll best_wrapper_ind1 = -1;
        ll best_wrapper_ind2 = -1;
        ll snd_best_wrapper_ind1 = -1;
        ll snd_best_wrapper_ind2 = -1;

        ll moves;
        for (ll i = 0; i < size; i++) {
            Wrapper p = arr[i];

            //Liczymy ile ruchów wg. estymacji
            //potrzebuje ta gablota
            ll single_wrapper_m;
            if (p.d >= p.p && p.d >= p.r) {
                single_wrapper_m = p.p + p.r;
            } else if (p.p >= p.d && p.p >= p.r) {
                single_wrapper_m = p.d + p.r;
            } else {
                single_wrapper_m = p.p + p.d;
            }

            //Obliczamy jak zmieni się łączna ilość ruchów
            //po wybraniu tej gabloty dla obu przypadków
            ll moves_diff_after_selecting = -single_wrapper_m;
            bool simulated = false;
            if (!r_has_exclusive && r_sum > 0) {
                ll a = moves_diff_after_selecting + p.p + p.d;
                if (!simulated) {
                    if (a <= min_moves1) {
                        snd_min_moves1 = min_moves1;
                        snd_best_wrapper_ind1 = best_wrapper_ind1;
                        min_moves1 = a;
                        best_wrapper_ind1 = i;
                    } else if (a <= snd_min_moves1) {
                        snd_min_moves1 = a;
                        snd_best_wrapper_ind1 = i;
                    }
                    simulated = true;
                } else if (a <= min_moves2) {
                    snd_min_moves2 = min_moves2;
                    snd_best_wrapper_ind2 = best_wrapper_ind2;
                    min_moves2 = a;
                    best_wrapper_ind2 = i;
                } else if (a <= snd_min_moves2) {
                    snd_min_moves2 = a;
                    snd_best_wrapper_ind2 = i;
                }
            }
            if (!p_has_exclusive && p_sum > 0) {
                ll a = moves_diff_after_selecting + p.r + p.d;
                if (!simulated) {
                    if (a <= min_moves1) {
                        snd_min_moves1 = min_moves1;
                        snd_best_wrapper_ind1 = best_wrapper_ind1;
                        min_moves1 = a;
                        best_wrapper_ind1 = i;
                    } else if (a <= snd_min_moves1) {
                        snd_min_moves1 = a;
                        snd_best_wrapper_ind1 = i;
                    }
                    simulated = true;
                } else if (a <= min_moves2) {
                    snd_min_moves2 = min_moves2;
                    snd_best_wrapper_ind2 = best_wrapper_ind2;
                    min_moves2 = a;
                    best_wrapper_ind2 = i;
                } else if (a <= snd_min_moves2) {
                    snd_min_moves2 = a;
                    snd_best_wrapper_ind2 = i;
                }
            }
            if (!d_has_exclusive && d_sum > 0) {
                ll a = moves_diff_after_selecting + p.r + p.p;
                if (!simulated) {
                    if (a <= min_moves1) {
                        snd_min_moves1 = min_moves1;
                        snd_best_wrapper_ind1 = best_wrapper_ind1;
                        min_moves1 = a;
                        best_wrapper_ind1 = i;
                    } else if (a <= snd_min_moves1) {
                        snd_min_moves1 = a;
                        snd_best_wrapper_ind1 = i;
                    }
                    simulated = true;
                } else if (a <= min_moves2) {
                    snd_min_moves2 = min_moves2;
                    snd_best_wrapper_ind2 = best_wrapper_ind2;
                    min_moves2 = a;
                    best_wrapper_ind2 = i;
                } else if (a <= snd_min_moves2) {
                    snd_min_moves2 = a;
                    snd_best_wrapper_ind2 = i;
                }
            }
        }

        if (best_wrapper_ind1 == best_wrapper_ind2) {
            //Wybieramy odpowiednią kombinację
            cout << moves_estimation + min(min_moves1 + snd_min_moves2, min_moves2 + snd_min_moves1) << endl;
        } else {
            cout << moves_estimation + min_moves1 + min_moves2 << endl;
        }
    } else {
        //dla x=0 prosta estymacja jest optymalnym rozwiązaniem
        cout << moves_estimation << endl;
    }
}