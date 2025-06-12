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

int find_not_these(int a, int b) {
    if (a != 0 && b != 0) return 0;
    if (a != 1 && b != 1) return 1;
    if (a != 2 && b != 2) return 2;

    return -1;
}

vector<int> solve_with_operations(vector<int> &chars) {
    vector<int> operations;

    vector<pii> char_count(3);
    for (int i = 0; i < 3; i++) {
        char_count[i] = mp(0ll,i);
    }

    vector<int> not_sorted_char_count(3);
    for (int i : chars) {
        char_count[i].first++;
        not_sorted_char_count[i]++;
    }

    sort(all(char_count));
    // char_count[2] = {greatest count, greatest particular char}

    if (char_count[2].first == chars.size()) {
        return {-1};
    }
    
    // we look for a place where greatest has a boundary with another number
    for (int i = 0; i < chars.size()-1; i++) {
        if (chars[i] == char_count[2].second && chars[i+1] != char_count[2].second) {
            // on the left there is the greatest and on the right some other number

            // we find the number that is not any of these
            int not_these = find_not_these(chars[i],chars[i+1]);
            int not_greatest = chars[i+1];

            // we insert first not_these then not_greatest until min not_sorted_char_count becomes the greatest count
            while (min(not_sorted_char_count[not_these],not_sorted_char_count[not_greatest]) < char_count[2].first) {
                operations.pb(i+1);
                operations.pb(i+1);

                not_sorted_char_count[not_these]++;
                not_sorted_char_count[not_greatest]++;
            }

            break;
        }

        if (chars[i] != char_count[2].second && chars[i+1] == char_count[2].second) {
            // on the left there is a number and on the right there is the greatest number

            // we find the number that is not any of these
            int not_these = find_not_these(chars[i],chars[i+1]);
            int not_greatest = chars[i];

            // we insert first not_these then not_greatest until min not_sorted_char_count becomes the greatest count
            for (int j = 0; min(not_sorted_char_count[not_these],not_sorted_char_count[not_greatest]) < char_count[2].first; j++) {
                operations.pb(i+1 + j*2);
                operations.pb(i+2 + j*2);

                not_sorted_char_count[not_these]++;
                not_sorted_char_count[not_greatest]++;
            }

            break;
        }
    }

    return operations;
}

vector<int> apply_operations(vector<int> &operations, vector<int> &chars) {
    vector<int> to_add;
    int i = operations[0];
    if (operations[0] == operations[1]) {
        // we want to continue adding a particular chain
        for (int j = 0; j < operations.size() / 2; j++) {
            int to_insert2 = find_not_these(chars[i-1],chars[i]);
            int to_insert = chars[i];

            to_add.pb(to_insert);
            to_add.pb(to_insert2);
        }
    } else {
        for (int j = 0; j < operations.size() / 2; j++) {
            int to_insert = find_not_these(chars[i-1],chars[i]);
            int to_insert2 = chars[i-1];

            to_add.pb(to_insert);
            to_add.pb(to_insert2);
        }
    }

    vector<int> new_chars = chars;
    new_chars.reserve(new_chars.size() + to_add.size());
    new_chars.insert(new_chars.begin() + i, all(to_add));

    return new_chars;
}

string random_string(int s) {
    string st = "";
    for (int i = 0; i < s; i++) {
        int rand_char = rand() % 3;

        if (rand_char == 0) {
            st += "L";
        } else if (rand_char == 1) {
            st += "I";
        } else if (rand_char == 2) {
            st += "T";
        }
    }

    return st;
}

int char_to_num(char c) {
    if (c == 'L') {
        return 0;
    } else if (c == 'I') {
        return 1;
    } else if (c == 'T') {
        return 2;
    }

    return -1;
}

char num_to_char(int n) {
    vector<char> c = {'L','I','T'};

    return c[n];
}

bool verify_answer(string &s, vector<int> &operations) {
    if (operations.size() > s.size() * 2) {
        return false;
    }

    for (int i : operations) {
        s.insert(s.begin() + (i - 1) + 1, num_to_char(find_not_these(char_to_num(s[(i - 1)]),char_to_num(s[(i - 1) + 1]))));
    }

    vector<int> counts(3);
    for (char c : s) {
        counts[char_to_num(c)]++;
    }

    if (counts[0] != counts[1] || counts[1] != counts[2] || counts[0] != counts[2]) return false;

    return true;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 20 + 1;

    instr(s);
    //string s = random_string(n);

    vector<int> chars;
    for (char c : s) {
        if (c == 'L') {
            chars.pb(0);
        } else if (c == 'I') {
            chars.pb(1);
        } else if (c == 'T') {
            chars.pb(2);
        }
    }

    vector<int> total_operations;
    vector<int> operations = solve_with_operations(chars);
    while (!operations.empty()) {
        if (operations[0] == -1) {
            cout << -1 << endl;
            return;
        }

        chars = apply_operations(operations,chars);
        for (int i : operations) {
            total_operations.pb(i);
        }

        operations = solve_with_operations(chars);
    }

    cout << total_operations.size() << endl;
    for (int i : total_operations) {
        cout << i << endl;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(cases);

    while (cases--) {
        readCaseData();
    }
}