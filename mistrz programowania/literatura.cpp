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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    string vec[100000] = {""};
    for (int i = 0; i < n; i++) {
        instr(s);
        vec[i] = s;
    }

    int best_alone_arr[26] = {0};

    for (string &s : vec) {
        int current_alone = 0;
        char prev = '/';
        for (int j = 0; j < s.length(); j++) {
            if (s[j] == prev) {
                current_alone++;
            } else {
                current_alone = 1;
            }
            prev = s[j];

            best_alone_arr[prev-'a'] = max(current_alone,best_alone_arr[prev-'a']);
        }
        best_alone_arr[prev-'a'] = max(current_alone,best_alone_arr[prev-'a']);
    }


    int res = 0;
    for (int i = 0; i < 26; i++) {
        char c = 'a' + i;
        int best_prefix = 0;
        int second_best_prefix = 0;

        int best_suffix = 0;
        int second_best_suffix = 0;

        int best_suffix_idx = -1;
        int best_prefix_idx = -1;

        int only_letter_sum = 0;
        
        for (int k = 0; k < 100000; k++) {
            string &s = vec[k];
            bool only_letter = true;
            for (int j = 0; j < s.length(); j++) {
                if (s[j] != c) {
                    only_letter = false;
                }
            }

            int prefix = 0;
            for (int j = 0; j < s.length(); j++) {
                if (s[j] != c) {
                    break;
                }
                prefix++;
            }

            int suffix = 0;
            for (int j = s.length() - 1; j >= 0; j--) {
                if (s[j] != c) {
                    break;
                }
                suffix++;
            }

            if (only_letter) only_letter_sum += s.size();
            else {
                if (suffix > best_suffix) {
                    second_best_suffix = best_suffix;
                    best_suffix = suffix;
                    best_suffix_idx = k;
                } else if (suffix > second_best_suffix) {
                    second_best_suffix = suffix;
                }

                if (prefix > best_prefix) {
                    second_best_prefix = best_prefix;
                    best_prefix = prefix;
                    best_prefix_idx = k;
                } else if (prefix > second_best_prefix) {
                    second_best_prefix = prefix;
                }
            }
        }

        int a = best_prefix+best_suffix+only_letter_sum;
        if (best_prefix_idx == best_suffix_idx) {
            a = max(best_prefix+second_best_suffix+only_letter_sum,second_best_prefix+best_suffix+only_letter_sum);
        }
        res = max(res,max(a,best_alone_arr[i]));
    }

    cout << res << endl;
}