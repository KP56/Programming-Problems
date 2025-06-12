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

bool is_correct(vector<vector<int>> &original_vec, vector<int> &answer) {
    int bajtyna_sum1 = 0;
    int bajtyna_sum2 = 0;

    int bajtek_sum1 = 0;
    int bajtek_sum2 = 0;

    int lowest_opposing_bajtek = inf;
    int lowest_opposing_bajtyna = inf;

    for (int i = 0; i < answer.size(); i++) {
        if (answer[i] == 1) {
            bajtyna_sum1 += original_vec[i][0];
            bajtek_sum2 += original_vec[i][1];

            lowest_opposing_bajtek = min(original_vec[i][1],lowest_opposing_bajtek);
        } else {
            bajtyna_sum2 += original_vec[i][0];
            bajtek_sum1 += original_vec[i][1];

            lowest_opposing_bajtyna = min(original_vec[i][0],lowest_opposing_bajtyna);
        }
    }

    if (bajtyna_sum1 >= bajtyna_sum2 - lowest_opposing_bajtyna && bajtek_sum1 >= bajtek_sum2 - lowest_opposing_bajtek) {
        return true;
    } else {
        return false;
    }
}

bool cmp(vector<int> &a, vector<int> &b) {
    if (a[1] > b[1]) {
        return true;
    } else {
        if (a[1] == b[1] && a[2] < b[2]) {
            return true;
        } else {
            return false;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 30 + 1;
    vector<vector<int>> vec;
    vector<vector<int>> original_vec;
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 30 + 1;
        vec.pb({a,0,i});
        original_vec.pb({a,0});
    }

    for (int i = 0; i < n; i++) {
        //ini(b);
        //int b = rand() % 5 + 1;
        int b = vec[i][0];
        vec[i][1] = b;
        original_vec[i][1] = b;
    }

    sort(all(vec),cmp);

    int sum_bajtyna = 0;
    for (int i = 0; i < n; i++) {
        sum_bajtyna += vec[i][0];
    }

    int sum_bitek = 0;
    for (int i = 0; i < n; i++) {
        sum_bitek += vec[i][1];
    }

    vector<int> answer(n);

    int min_val_bitek = 0;

    int sum_of_chosen = 0;
    int sum_of_not_chosen = 0;
    for (int i = 0; i < n; i++) {
        if (sum_of_not_chosen <= sum_of_chosen + (sum_bitek - sum_of_chosen - sum_of_not_chosen) - vec[i][0]) {
            min_val_bitek = vec[i][0];
            sum_of_not_chosen += vec[i][0];
            continue;
        }
        sum_of_chosen += vec[i][0];

        answer[vec[i][2]] = 1;
    }

    for (int i : answer) {
        cout << i << " ";
    }
    cout << endl;
}