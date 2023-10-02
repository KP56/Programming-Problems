#include <bits/stdc++.h>

using namespace std;

template<typename T>
using pair2 = pair<T, T>;

#define int long long
#define pii pair<int,int>
#define pb push_back
#define pf push_front
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define ini(x) int x; in(x)
#define instr(x) string x; in(x)

#define inf 1e18

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

string brute(string a, string b, int k) {
    int num_a = stoi(a);
    int num_b = stoi(b);

    for (int i = num_b - 1; i >= 0; i--) {
        int different_digits = 0;
        string num = to_string(i);
        for (int j = num.length(); j < a.length(); j++) {
            num = "0" + num;
        }
        for (int j = 0; j < a.length(); j++) {
            if (num[j] != a[j]) {
                different_digits++;
            }
        }

        if (different_digits == k) {
            return num;
        }
    }

    return "";
}

void readCaseData() {
    instr(a);
    //int a_num = rand() % 9000 + 1000;
    //string a = to_string(a_num);
    instr(b);
    //int b_num = rand() % 9000 + 1000;
    //string b = to_string(b_num);
    ini(k);
    //int k = rand() % 4 + 1;

    //if (a_num < b_num) return;

    //string test = brute(a,b,k);

    int required_digits = 0;
    for (int i = 0; i < b.length(); i++) {
        if (b[i] != a[i]) {
            required_digits++;
        }
    }

    // Iterujemy od tyłu. Gdy znajdziemy istniejącą liczbę wiemy, że jest ona maksymalna
    for (int i = b.length() - 1; i >= 0; i--) {
        if (b[i] != a[i]) {
            required_digits--;
        }
        
        // Rozważamy teraz 2 przypadki: zostawiamy cyfrę jak jest (możliwe tylko jeśli już jest niższa) albo zmieniamy ją
        if (a[i] != b[i] - 1) {
            // Jeżeli musimy ją zmienić
            if (b[i] != '0') {
                // Jeżeli byłaby zerem, nie bylibyśmy w stanie jej zmienić na niższą
                if (required_digits + 1 <= k && k - required_digits - 1 <= b.length() - 1 - i) {
                    // Znaleźliśmy odpowiedź
                    string number = "";
                    for (int j = 0; j < i; j++) {
                        number += b[j];
                    }
                    number += b[i] - 1;
                    vector<int> indices_to_revisit;
                    int updated = 0;
                    int c = 0;
                    for (int j = 0; j < k - required_digits - 1 + c && number.length() < b.length(); j++) {
                        if (a[i + j + 1] == '9') {
                            indices_to_revisit.pb(number.length());
                            c++;
                        } else {
                            updated++;
                        }
                        number += "9";
                    }

                    for (int j = 0; j < k - required_digits - 1 - updated && j < indices_to_revisit.size(); j++) {
                        number[indices_to_revisit[indices_to_revisit.size() - 1 - j]] = '8';
                    }

                    for (int j = i + 1 + k - required_digits - 1 + indices_to_revisit.size(); j < b.length(); j++) {
                        number += a[j];
                    }
                    cout << number << endl;
                    /*if (number != test) {
                        int test2 = 0;
                    }*/
                    return;
                }
            }
        } else {
            // Nie musimy nawet jej zmieniać
            if (required_digits <= k && k - required_digits <= b.length() - 1 - i) {
                // Znaleźliśmy odpowiedź
                string number = "";
                for (int j = 0; j < i; j++) {
                    number += b[j];
                }
                number += b[i] - 1;
                vector<int> indices_to_revisit;
                int updated = 0;
                int c = 0;
                for (int j = 0; j < k - required_digits + c && number.length() < b.length(); j++) {
                    if (a[i + j + 1] == '9') {
                        indices_to_revisit.pb(number.length());
                        c++;
                    } else {
                        updated++;
                    }
                    number += "9";
                }

                for (int j = 0; j < k - required_digits - updated && j < indices_to_revisit.size(); j++) {
                    number[indices_to_revisit[indices_to_revisit.size() - 1 - j]] = '8';
                }

                for (int j = i + 1 + k - required_digits + indices_to_revisit.size(); j < b.length(); j++) {
                    number += a[j];
                }
                cout << number << endl;

                /*if (number != test) {
                    int test2 = 0;
                }*/
                return;
            } else if (required_digits <= k && k - required_digits <= b.length() - i) {
                // Znaleźliśmy odpowiedź, ale chcemy nieco obniżyć mimo wszystko liczbę, aby zdobyć dodatkową cyfrę
                if (a[i] != '0') {
                    // Jeżeli byłaby zerem, nie bylibyśmy w stanie jej zmienić na niższą
                    string number = "";
                    for (int j = 0; j < i; j++) {
                        number += b[j];
                    }
                    number += a[i] - 1;
                    vector<int> indices_to_revisit;
                    int updated = 0;
                    int c = 0;
                    for (int j = 0; j < k - required_digits - 1 + c && number.length() < b.length(); j++) {
                        if (a[i + j + 1] == '9') {
                            indices_to_revisit.pb(number.length());
                            c++;
                        } else {
                            updated++;
                        }
                        number += "9";
                    }

                    for (int j = 0; j < k - required_digits - 1 - updated && j < indices_to_revisit.size(); j++) {
                        number[indices_to_revisit[indices_to_revisit.size() - 1 - j]] = '8';
                    }
                    for (int j = i + 1 + k - required_digits - 1 + indices_to_revisit.size(); j < b.length(); j++) {
                        number += a[j];
                    }
                    cout << number << endl;

                    /*if (number != test) {
                        int test2 = 0;
                    }*/
                    return;
                }
            }
        }

        if (a[i] < b[i]) {
            // Możemy ją zostawić
            if (required_digits <= k && k - required_digits <= b.length() - 1 - i) {
                // Znaleźliśmy odpowiedź
                string number = "";
                for (int j = 0; j < i; j++) {
                    number += b[j];
                }
                number += a[i];
                vector<int> indices_to_revisit;
                int updated = 0;
                int c = 0;
                for (int j = 0; j < k - required_digits + c && number.length() < b.length(); j++) {
                    if (a[i + j + 1] == '9') {
                        indices_to_revisit.pb(number.length());
                        c++;
                    } else {
                        updated++;
                    }
                    number += "9";
                }

                for (int j = 0; j < k - required_digits - updated && j < indices_to_revisit.size(); j++) {
                    number[indices_to_revisit[indices_to_revisit.size() - 1 - j]] = '8';
                }
                for (int j = i + 1 + k - required_digits + indices_to_revisit.size(); j < b.length(); j++) {
                    number += a[j];
                }
                cout << number << endl;

                /*if (number != test) {
                    int test2 = 0;
                }*/
                return;
            }
        }
    }

    /*if (test != "") {
        int test2 = 0;
    }*/

    cout << -1 << endl;
}

signed main() {
    srand(time(NULL));

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}