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
#define p 1000000007 

vector<int> find_div(int k) {
    vector<int> div;
    for (int i = 1; i <= sqrt(k); i++) {
        if (k % i == 0) {
            div.pb(i);
            if (i != k/i) {
                div.pb(k/i);
            }
        }
    }

    return div;
}

int power(int x, int y, int mod) {
    int res = 1;
    x = x % mod;

    while (y > 0) {
        if (y % 2 == 1) {
            res = res * x;
            res %= mod;
        }

        y = y >> 1;
        x *= x;
        x %= mod;
    }

    return res;
}

int inverse_modulo(int n, int mod) {
    return power(n,mod-2,mod);
}

vector<int> factorial_mem;
void find_factorials(int n, int mod) {
    if (factorial_mem.empty()) factorial_mem.pb(1);
    while (factorial_mem.size() <= n) {
        factorial_mem.pb(factorial_mem[factorial_mem.size()-1]*factorial_mem.size() % p);
    }
}

int factorial(int n, int mod) {
    find_factorials(n,mod);
    return factorial_mem[n];
}

vector<int> inverse_factorial_mem;
void find_inverse_factorials(int n, int mod) {
    find_factorials(n, mod);

    while (inverse_factorial_mem.size() <= n) {
        inverse_factorial_mem.pb(inverse_modulo(factorial_mem[inverse_factorial_mem.size()],mod));
    }
}

int inverse_factorial(int n, int mod) {
    find_inverse_factorials(n, mod);

    return inverse_factorial_mem[n];
}

int newton(int n, int r, int mod) {
    if (n < r) {
        return 0;
    }

    if (r == 0) {
        return 1;
    }
    
    return ((factorial(n,mod) * inverse_factorial(r,mod)) % mod * (inverse_factorial(n-r,mod) % mod)) % mod;
}

int gcd(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }

    return max(a,b);
}

int lcm(int a, int b) {
    return a*b/gcd(a,b);
}

unordered_map<int,unordered_map<int,int>> mem_f;
int f(int k2, int divisor) {
    if (mem_f[k2][divisor] != 0) {
        return mem_f[k2][divisor];
    }

    int multiplier = 1;
    for (int a = 1; a <= k2; a++) {
        //(a*divisor-1)*(a*divisor-2)*...*(a*divisor+1-divisor)=(a*divisor-1)!/(a*divisor-divisor)!
        /*for (int b = 0; b < divisor-1; b++) {
            multiplier *= a*divisor-1-b;
            multiplier %= p;
        }*/

        multiplier *= (factorial(a*divisor-1,p) * (a*divisor-divisor >= 0 ? inverse_factorial(a*divisor-divisor,p) : 1)) % p;
        multiplier %= p;
    }

    return mem_f[k2][divisor] = multiplier;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    ini(k);

    //clock_t timer = clock();

    vector<int> divisors = find_div(k);

    sort(all(divisors));

    //vector<vector<unordered_map<int,int>>> dp(divisors.size()+1,vector<unordered_map<int,int>>(n+1,unordered_map<int,int>()));
    
    vector<unordered_map<int,int>> dp_curr_row(vector<unordered_map<int,int>>(n+1,unordered_map<int,int>()));
    dp_curr_row[0][1] = 1;

    for (int i = 0; i < divisors.size(); i++) {
        vector<unordered_map<int,int>> dp_next_row(vector<unordered_map<int,int>>(n+1,unordered_map<int,int>()));

        vector<int> lcm_mem;
        for (int l : divisors) {
            lcm_mem.pb(lcm(l,divisors[i]));
        }

        for (int j = 0; j <= n; j++) {
            for (int k2 = 0; k2 <= (n-j)/divisors[i]; k2++) {
                int multiplier = newton(n-j,k2*divisors[i],p);
                multiplier *= f(k2,divisors[i]);
                //multiplier *= factorial(divisors[i]-1,p);
                multiplier %= p;
                for (int a = 0; a < divisors.size(); a++) {
                    int l = divisors[a];
            		int lcm_res;
            		
            		if (k2 == 0) {
            			// nie dodajemy żadnej liczby, więc brak aktualizacji lcm
            			lcm_res = l;
            		} else {
            			lcm_res = lcm_mem[a];
            		}

            		dp_next_row[j+k2*divisors[i]][lcm_res] +=
            			    (dp_curr_row[j][l] * multiplier) % p;
            		dp_next_row[j+k2*divisors[i]][lcm_res] %= p;
            	}
        	}
        }
        dp_curr_row = dp_next_row;
    }

    int res = dp_curr_row[n][k];
    //cout << res << endl;

    int divisor = inverse_modulo(factorial(n,p),p);

    cout << (res*divisor) % p << endl;

    //cout << "Elapsed: " << double(clock()-timer) / CLOCKS_PER_SEC << endl;
}
