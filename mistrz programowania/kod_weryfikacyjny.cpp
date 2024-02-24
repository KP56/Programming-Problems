#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

void subtract(int (&from)[26], int (&what)[26]) {
    for (int i = 0; i < 26; i++) {
        from[i] -= what[i];
    }
}

void add(int (&to_what)[26], int (&what)[26]) {
    for (int i = 0; i < 26; i++) {
        to_what[i] += what[i];
    }
}

void create_result(int digit, char letter, int (&result)[10], int (&tables)[10][26], int (&table)[26], int divide_by) {
    result[digit] = table[letter-'a'] / divide_by;
    for (int i = 0; i < result[digit]; i++) {
        subtract(table,tables[digit]);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 1000000 + 1;
    instr(s);

    // generowanie losowego przypadku
    /*string num = "";
    int current_digit = 9;
    for (int i = 0; i < n; i++) {
        num += string(1,'0' + current_digit);

        if (rand() % 100000 != 0 && current_digit != 0) {
            current_digit--;
        }
    }*/

    string digits[] = {"zero","jeden","dwa","trzy","cztery","piec","szesc","siedem","osiem","dziewiec"};

    /*string s = "";
    for (char c : num) {
        s += digits[c-'0'];
    }*/

    int table[26] = {0};
    for (char c : s) {
        table[c-'a']++;
    }

    int tables[10][26] = {0};

    for (int i = 0; i < 10; i++) {
        string s2 = digits[i];
        for (char c : s2) {
            tables[i][c-'a']++;
        }
    }
    
    int result[10] = {0};
    create_result(1,'j',result,tables,table,1);
    create_result(2,'a',result,tables,table,1);
    create_result(5,'p',result,tables,table,1);
    create_result(9,'w',result,tables,table,1);

    int mem = table['o'-'a'];

    // na początku zakładamy, że mamy same zera
    for (int i = 0; i < mem; i++) {
        result[0]++;
        subtract(table,tables[0]);
    }

    int max_digits_count = -1;

    int best_result[10] = {0};
    // skoro rozważamy wszystkie możliwe ilości ósemek, to musi być <=
    for (int i = 0; i <= mem; i++) {
        if (i != 0) {
            // "i" reprezentuje tutaj ilość ósemek
            // z każdą kolejno dodaną ósemką zwiększamy result
            result[8]++;
            // oraz obniżamy table
            subtract(table,tables[8]);
        
            // teraz skoro mamy jedno zero mniej, musimy cofnąć operację
            result[0]--;
            add(table,tables[0]);
        }

        // mamy tutaj kopie tablic
        int result_cp[10];
        copy(begin(result),end(result),begin(result_cp));
        int table_cp[26];
        copy(begin(table),end(table),begin(table_cp));

        // teraz wykonujemy resztę operacji na nich
        create_result(7,'m',result_cp,tables,table_cp,1);
        create_result(6,'s',result_cp,tables,table_cp,2); // sześć ma dwa s!!!
        create_result(4,'e',result_cp,tables,table_cp,1);
        create_result(3,'y',result_cp,tables,table_cp,1);

        // weryfikacja prawidłowości
        bool wrong = false;
        for (int j = 0; j < 26; j++) {
            if (table_cp[j] != 0) {
                // znaleziono błąd
                wrong = true;
                break;
            }
        }

        if (wrong) {
            continue;
        }

        // jeśli wszystko przebiegło prawidłowo to teraz sprawdzamy czy ta tablica jest lepsza od obecnej najlepszej
        int digits_count = 0;
        for (int j = 0; j < 10; j++) {
            digits_count += (result_cp[j] > 0);
        }

        if (digits_count > max_digits_count) {
            max_digits_count = digits_count;
            // tutaj tablice kopiujemy
            copy(begin(result_cp),end(result_cp),begin(best_result));
        } else if (digits_count == max_digits_count) {
            // tutaj weryfikujemy leksykograficznie
            bool is_greater = false;
            for (int j = 9; j >= 0; j--) {
                if (result_cp[j] > best_result[j]) {
                    is_greater = true;
                    break;
                } else if (result_cp[j] < best_result[j]) {
                    break;
                }
            }

            if (is_greater) {
                // jeśli jest większa tablica leksykograficznie to jest lepsza
                max_digits_count = digits_count;
                // tutaj tablice kopiujemy
                copy(begin(result_cp),end(result_cp),begin(best_result));
            }
        }
    }

    // rekonstruujemy liczbę
    string number = "";
    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < best_result[i]; j++) {
            number += string(1,'0'+i);
        }
    }

    /*if (number != num) {
        int test = 0;
    }
    }*/

    cout << number << endl;
}