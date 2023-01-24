#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    vector<vector<int>> dp;

    bool isMatch(string s, string p) {
        dp = vector<vector<int>>(p.length(), vector<int>(s.length(), -1));
        return getDP(s, p, 0, 0);
    }
    
    bool getDP(string &s, string &p, int i, int j) {
        if (i < p.length() && j < s.length()) {
            if (dp[i][j] != -1) {
                return dp[i][j];
            }

            return (dp[i][j] = isMatch(s, p, i, j));
        } else {
            return isMatch(s, p, i, j);
        }
    }

    bool starsTillTheEnd(string &p, int i) {
        for (int j = i; j < p.size() - 1; j++) {
            if (p[j] != '*' && p[j + 1] != '*') {
                return false;
            }
        }

        if (p[p.length() - 1] != '*') {
            return false;
        }

        return true;
    }

    bool isMatch(string &s, string &p, int i, int j) {
        for (; i < p.length() && j < s.length(); i++) {
            if (i != p.length() - 1 && p[i + 1] == '*') {
                if (p[i] != '.' && p[i] != s[j]) {
                    continue;
                }

                if (j < s.length() && (p[i] == '.' || p[i] == s[j])) {
                    if (getDP(s, p, i + 2, j) || getDP(s, p, i, j + 1)) {
                        return true;
                    } else {
                        return false;
                    }
                }
            } else if (p[i] == '.') {
                j++;
            } else if (p[i] != '*') {
                if (p[i] == s[j]) {
                    j++;
                } else {
                    return false;
                }
            }
        }

        return (i >= p.length() || starsTillTheEnd(p, i)) && j >= s.length();
    }
};

int main() {
    Solution solution;
    cout << solution.isMatch("aa", "a") << endl; //false
    cout << solution.isMatch("aa", "a*") << endl; //true
    cout << solution.isMatch("ab", ".*") << endl; //true
    cout << solution.isMatch("aab", "c*a*b") << endl; //true
    cout << solution.isMatch("ab", ".*c") << endl; //false
    cout << solution.isMatch("aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c") << endl; //false
    cout << solution.isMatch("aabcbcbcaccbcaabc", ".*a*aa*.*b*.c*.*a*") << endl; //true
    //.*a..*
}