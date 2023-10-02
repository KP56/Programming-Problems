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

vector<int> brute(int A, int B, int C, int k) {
    int min_a = 1;
    for (int i = 0; i < A-1; i++) {
        min_a *= 10;
    }
    int max_a = min_a * 10 - 1;

    int min_b = 1;
    for (int i = 0; i < B-1; i++) {
        min_b *= 10;
    }
    int max_b = min_b * 10 - 1;

    int min_c = 1;
    for (int i = 0; i < C-1; i++) {
        min_c *= 10;
    }
    int max_c = min_c * 10 - 1;

    int evaluated = 0;
    for (int a = min_a; a <= max_a; a++) {
        for (int c = min_c; c <= max_c; c++) {
            for (int b = min_b; b <= max_b; b++) {
                if (a + b == c) {
                    evaluated++;

                    if (evaluated == k) {
                        return {a,b,c};
                    }
                }
            }
        }
    }

    return {-1,-1,-1};
}

void readCaseData() {
    //int A = rand() % 2 + 1;
    ini(A);
    //int B = rand() % 2 + 1;
    ini(B);
    //int C = rand() % 3 + 1;
    ini(C);
    //int k = rand() % 10000 + 1;
    ini(k);

    // Case #1
    if (C == max(A,B)) {
        int a = 1;
        for (int i = 0; i < A-1; i++) {
            a *= 10;
        }
        int initial_a = a;
        int max_a = a*10-1;

        int b = 1;
        for (int i = 0; i < B-1; i++) {
            b *= 10;
        }

        int min_c = 1;
        for (int i = 0; i < C-1; i++) {
            min_c *= 10;
        }
        int max_c = min_c*10-1;

        int initial_b = b;
        int max_b = min(b*10-1,max_c-initial_a);

        // Since we have initial a and b, we can start iterating
        int evaluated = 1;
        while (b+k-evaluated > max_b) {
            evaluated += max_b - b;
            b = max_b;

            if (evaluated < k) {
                a++;
                if (a + max_b > max_c) {
                    max_b--;
                }
                b = initial_b;
                evaluated++;

                if (a > max_a || max_b < initial_b) {
                    /*if (brute(A,B,C,k)[0] != -1) {
                        int test = 0;
                    }*/
                    cout << -1 << endl;
                    return;
                }
            }
        }

        // We found an answer
        b += k - evaluated;
        cout << a << " + " << b << " = " << a+b << endl;

        /*vector<int> vec = {a,b,a+b};
        if (brute(A,B,C,k) != vec) {
            int test = 0;
        }*/
    }

    // Case #2
    else if (C == max(A,B) + 1) {
        if (A < B) {
            int a = 1;
            for (int i = 0; i < A-1; i++) {
                a *= 10;
            }
            int max_a = a*10-1;

            int c = 1;
            for (int i = 0; i < C-1; i++) {
                c *= 10;
            }

            int b = c-a;
            int max_b = 1;
            for (int i = 0; i < B; i++) {
                max_b *= 10;
            }
            int initial_b = b;
            max_b--;

            int evaluated = 1;
            while (b+k-evaluated > max_b) {
                evaluated += max_b - b;
                b = max_b;

                if (evaluated < k) {
                    a++;
                    initial_b--;
                    b = initial_b;
                    evaluated++;

                    if (a > max_a) {
                        /*if (brute(A,B,C,k)[0] != -1) {
                            int test = 0;
                        }*/
                        cout << -1 << endl;
                        return;
                    }
                }
            }

            // We found an answer
            b += k - evaluated;
            cout << a << " + " << b << " = " << a+b << endl;

            /*vector<int> vec = {a,b,a+b};
            if (brute(A,B,C,k) != vec) {
                int test = 0;
            }*/
        } else {
            int a = 1;
            for (int i = 0; i < A-1; i++) {
                a *= 10;
            }
            int initial_a = a;
            int max_a = a*10-1;

            int c = 1;
            for (int i = 0; i < C-1; i++) {
                c *= 10;
            }
            int initial_c = c;

            int max_b = 1;
            for (int i = 0; i < B; i++) {
                max_b *= 10;
            }
            int min_b = max_b / 10;
            max_b--;

            int b;
            if (A == B) {
                b = c-a;
            } else {
                b = max_b;
                a = c-b;
            }
            int initial_b = b;

            int evaluated = 1;
            while (b+k-evaluated > max_b) {
                evaluated += max_b - b;
                b = max_b;

                if (evaluated < k) {
                    a++;
                    if (initial_b != min_b) {
                        initial_b--;
                    }
                    b = initial_b;
                    evaluated++;

                    if (a > max_a) {
                        /*if (brute(A,B,C,k)[0] != -1) {
                            int test = 0;
                        }*/
                        cout << -1 << endl;
                        return;
                    }
                }
            }
            
            // We found an answer
            b += k - evaluated;

            /*vector<int> vec = {a,b,a+b};
            vector<int> brute_res = brute(A,B,C,k);
            if (brute_res != vec) {
                int test = 0;
            }*/

            cout << a << " + " << b << " = " << a+b << endl;
        }
    }

    // Impossible equality
    else {
        /*if (brute(A,B,C,k)[0] != -1) {
            int test = 0;
        }*/

        cout << -1 << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}