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

int solve(deque<int> vec, int ans, int total_sum) {
    while (total_sum < vec.size() * 9) {
        if (vec.size() == 1 && vec[0] == 1) {
            ans -= 2;
            break;
        }

        if (vec[vec.size() - 1] != 0) {
            ans += 9 - vec[vec.size() - 1];
            total_sum += 9 - vec[vec.size() - 1];
            vec[vec.size() - 1] = 9;
        }

        if (total_sum < vec.size() * 9) {
            vec.pb(vec[0]);
            vec.pop_front();
            ans++;
        }

        while (vec[0] == 0) {
            vec.pop_front();
        }
    }

    return ans + 2;
}

int case1(deque<int> vec, int ans, int total_sum) {
    ans += 9 - vec[vec.size() - 1];
    total_sum += 9 - vec[vec.size() - 1];
    vec[vec.size() - 1] = 9;

    return solve(vec,ans,total_sum);
}

int case2(deque<int> vec, vector<int> last_segment, int ans, int total_sum) {
    int last_segment_adding = 0;
    int mul = 1;
    if (last_segment.size() <= 10) {
        int num = 0;
        int last_segment_num = 0;
        for (int i : last_segment) {
            num += 9 * mul;
            last_segment_num += i * mul;
            mul *= 10;
        }

        last_segment_adding = num - last_segment_num;
    } else {
        return inf;
    }

    for (int i = vec.size() - 1; i > vec.size() - 1 - last_segment.size(); i--) {
        total_sum += 9 - vec[i];
        vec[i] = 9;
    }
    ans += last_segment_adding;

    return solve(vec,ans,total_sum);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    instr(n);
    /*string n = "9";
    for (int i = 0; i < 999998; i++) {
        n += "0";
    }*/

    int total_sum = 0;
    deque<int> vec;
    for (char c : n) {
        vec.pb(c - '0');
        total_sum += vec[vec.size() - 1];
    }

    int best_ans = INT_MAX;
    int ans = 0;

    // Rozważamy dwa dodatkowe przypadki: wymuszenie dodawania do ostatniej cyfry i wymuszenie ogólnego dodawania
    best_ans = min(best_ans,case1(vec,ans,total_sum));

    vector<int> last_segment;
    vector<vector<int>> last_segments;
    for (int i = vec.size() - 1; i >= ((int) vec.size()) - 10 && i >= 0; i--) {
        last_segment.pb(vec[i]);
        last_segments.pb(last_segment);
    }

    for (auto &segment : last_segments) {
        best_ans = min(best_ans,case2(vec,segment,ans,total_sum));
    }

    best_ans = min(best_ans,solve(vec,ans,total_sum));

    cout << best_ans << endl;
}