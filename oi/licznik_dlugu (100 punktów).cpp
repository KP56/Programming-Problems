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

vector<int> sum_nums(string &num1, string &num2) {
    vector<int> res(num1.size());
    int sum_next = 0;
    for (int i = 0; i < num1.size(); i++) {
        res[i] = (num1[i] + num2[i] - 2*'0' + sum_next);
        sum_next = res[i] / 10;
    }

    return res;
}

int retrieve(int i, vector<int> &sum_vec, vector<pii> &segments, int k) {
    if (segments[i/k].first == k) {
        return 9;
    }

    if (segments[i/k].second == k) {
        return 10;
    }

    return sum_vec[i];
}

int compute(int i, string &num1, string &num2, vector<int> &sum_vec, vector<pii> &segments, int k) {
    if (segments[i/k].first == k) {
        return 9;
    }

    if (segments[i/k].second == k) {
        return 10;
    }

    return num1[i] + num2[i] - 2*'0' + (i != 0 ? retrieve(i-1,sum_vec,segments,k)/10 : 0);
}

void move_one(int i, vector<int> &sum_vec, vector<pii> &segments, int k) {
    if (retrieve(i,sum_vec,segments,k) == 9) {
        if (segments[i/k].first == k && i%k==0) {
            segments[i/k].first = 0;
            segments[i/k].second = k;

            if (i/k+1<segments.size()) {
                move_one((i/k+1)*k,sum_vec,segments,k);
            }
        } else if (segments[i/k].first == k) {
            segments[i/k].first = 0;
            segments[i/k].second = 0;

            for (int j = i/k*k; j < i; j++) {
                sum_vec[j] = 9;
                segments[j/k].first++;
            }

            for (int j = i; j < (i/k+1)*k; j++) {
                sum_vec[j] = 10;
                segments[j/k].second++;
            }

            if (i/k+1<segments.size()) {
                move_one((i/k+1)*k,sum_vec,segments,k);
            }
        } else {
            sum_vec[i] = 10;
            segments[i/k].second++;
            segments[i/k].first--;
            if (i+1<sum_vec.size()) {
                move_one(i+1,sum_vec,segments,k);
            }
        }

        return;
    }

    if (segments[i/k].second == k) {
        for (int j = i/k*k; j < (i/k+1)*k && j < sum_vec.size(); j++) {
            sum_vec[j] = 10;
        }
    }

    sum_vec[i]++;

    if (sum_vec[i] == 9) {
        segments[i/k].first++;
    }

    if (sum_vec[i] == 10) {
        segments[i/k].first--;
        segments[i/k].second++;
    }

    if (sum_vec[i] == 11) {
        segments[i/k].second--;
    }
}

void move_minus_one(int i, vector<int> &sum_vec, vector<pii> &segments, int k) {
    if (retrieve(i,sum_vec,segments,k) == 10) {
        if (segments[i/k].second == k && i%k==0) {
            segments[i/k].second = 0;
            segments[i/k].first = k;

            if (i/k+1<segments.size()) {
                move_minus_one((i/k+1)*k,sum_vec,segments,k);
            }
        } else if (segments[i/k].second == k) {
            segments[i/k].first = 0;
            segments[i/k].second = 0;

            for (int j = i/k*k; j < i && j < sum_vec.size(); j++) {
                sum_vec[j] = 10;
                segments[j/k].second++;
            }

            for (int j = i; j < (i/k+1)*k && j < sum_vec.size(); j++) {
                sum_vec[j] = 9;
                segments[j/k].first++;
            }

            if (i/k+1<segments.size()) {
                move_minus_one((i/k+1)*k,sum_vec,segments,k);
            }
        } else {
            sum_vec[i] = 9;
            segments[i/k].first++;
            segments[i/k].second--;
            if (i+1<sum_vec.size()) {
                move_minus_one(i+1,sum_vec,segments,k);
            }
        }

        return;
    }

    if (segments[i/k].first == k) {
        for (int j = i/k*k; j < (i/k+1)*k && j < sum_vec.size(); j++) {
            sum_vec[j] = 9;
        }
    }

    sum_vec[i]--;

    if (sum_vec[i] == 10) {
        segments[i/k].second++;
    }

    if (sum_vec[i] == 9) {
        segments[i/k].second--;
        segments[i/k].first++;
    }

    if (sum_vec[i] == 8) {
        segments[i/k].first--;
    }
}

void reevaluate(int i, int c, string &num, string &other_num, vector<int> &sum_vec, vector<pii> &segments, int k) {
    if ((c + '0') != num[i] && retrieve(i,sum_vec,segments,k) == 9) {
        if (segments[i/k].first == k) {
            for (int j = i/k*k; j < (i/k+1)*k && j < sum_vec.size(); j++) {
                sum_vec[j] = 9;
            }
        }

        segments[i/k].first--;
    }

    if ((c + '0') != num[i] && retrieve(i,sum_vec,segments,k) == 10) {
        if (segments[i/k].second == k) {
            for (int j = i/k*k; j < (i/k+1)*k && j < sum_vec.size(); j++) {
                sum_vec[j] = 10;
            }
        }

        segments[i/k].second--;
    }

    num[i] = c + '0';

    int computed = compute(i,num,other_num,sum_vec,segments,k);

    if (retrieve(i,sum_vec,segments,k) != computed && computed == 9) {
        segments[i/k].first++;
    }

    if (retrieve(i,sum_vec,segments,k) != computed && computed == 10) {
        segments[i/k].second++;
    }

    sum_vec[i] = computed;
}

int solve(int i, string &num1, string &num2) {
    vector<int> num(num1.size() + 1);
    int add = 0;
    for (int i = num1.size() - 1; i >= 0; i--) {
        int adding = add + num1[i] + num2[i] - 2*'0';
        num[i+1] = adding % 10;
        add = adding / 10;
    }

    num[0] = add;

    return num[i];
}

signed main() {
    srand(time(NULL));

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    //int n = rand() % 10 + 2;
    ini(z);
    //int z = rand() % 10 + 1;

    instr(num1);
    /*string rand_str = to_string(rand() % (int) pow(10,n-1));
    string num1 = string(n - 1 - min(n-1, (int) rand_str.length()), '0') + rand_str;*/
    instr(num2);
    /*string rand_str2 = to_string(rand() % (int) pow(10,n-1));
    string num2 = string(n - 1 - min(n-1, (int) rand_str2.length()), '0') + rand_str2;

    string num_cp1 = num1;
    string num_cp2 = num2;*/

    reverse(all(num1));
    reverse(all(num2));

    vector<int> sum_vec = sum_nums(num1,num2);

    int k = sqrt(n);
    vector<pii> segments((n-1)/k+((n-1)%k!=0));
    for (int i = 0; i < sum_vec.size(); i++) {
        if (sum_vec[i] == 9) {
            segments[i/k].first++;
        } else if (sum_vec[i] == 10) {
            segments[i/k].second++;
        }
    }

    //vector<string> queries;
    for (int i = 0; i < z; i++) {
        instr(type);
        /*string type;
        int type_i = rand() % 3;
        if (type_i == 0) {
            type = "W";
        } else if (type_i == 1) {
            type = "Z";
        } else {
            type = "S";
        }*/

        if (type == "W") {
            ini(ind);
            //int ind = rand() % (n-1) + 1;
            ini(c);
            //int c = rand() % 10;

            //queries.pb("W " + to_string(ind) + " " + to_string(c));

            ind--;

            //num_cp1[n-2-ind] = c + '0';

            int current_val = retrieve(ind,sum_vec,segments,k);
            reevaluate(ind,c,num1,num2,sum_vec,segments,k);

            int new_val = retrieve(ind,sum_vec,segments,k);
            if (current_val < 10 && new_val >= 10) {
                if (ind+1<sum_vec.size()) {
                    move_one(ind+1,sum_vec,segments,k);
                }
            }

            if (current_val >= 10 && new_val < 10) {
                if (ind+1<sum_vec.size()) {
                    move_minus_one(ind+1,sum_vec,segments,k);
                }
            }
        } else if (type == "Z") {
            ini(ind);
            //int ind = rand() % (n-1) + 1;
            ini(c);
            //int c = rand() % 10;

            //queries.pb("Z " + to_string(ind) + " " + to_string(c));

            ind--;

            //num_cp2[n-2-ind] = c + '0';

            int current_val = retrieve(ind,sum_vec,segments,k);
            reevaluate(ind,c,num2,num1,sum_vec,segments,k);

            int new_val = retrieve(ind,sum_vec,segments,k);
            if (current_val < 10 && new_val >= 10) {
                if (ind+1<sum_vec.size()) {
                    move_one(ind+1,sum_vec,segments,k);
                }
            }

            if (current_val >= 10 && new_val < 10) {
                if (ind+1<sum_vec.size()) {
                    move_minus_one(ind+1,sum_vec,segments,k);
                }
            }
        } else {
            ini(ind);
            //int ind = rand() % n + 1;

            //queries.pb("S " + to_string(ind));

            if (ind == n) {
                int ans = retrieve(sum_vec.size() - 1,sum_vec,segments,k) / 10;
                cout << ans << endl;
                /*int sol = solve(n-ind,num_cp1,num_cp2);
                if (ans != sol) {
                    int test = 0;
                }*/
            }
            else {
                ind--;
                int ans = retrieve(ind,sum_vec,segments,k) % 10;
                cout << ans << endl;
                /*int sol = solve(n-1-ind,num_cp1,num_cp2);
                if (ans != sol) {
                    int test = 0;
                }*/
            }
        }
    }
}