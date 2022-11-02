#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define endl "\n"
#define in(x) cin >> x
#define in_ll(x) ll (x); in(x)
#define in_i(x) int (x); in(x)
#define in_str(x) string (x); in(x)

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

//Implementacja porównywania wektorów w czasie O(1)
class ComparableVectors {
private:
    vector<int> vec1;
    vector<int> vec2;

    int greater_than;
    int lower_than;
    int equal_to;
public:
    ComparableVectors(int size) {
        vec1 = vector<int>(size);
        vec2 = vector<int>(size);
        greater_than = 0;
        lower_than = 0;
        equal_to = size;
    }

    void incrementFirst(int index) {
        if (vec1[index] + 1 == vec2[index]) {
            equal_to++;
            lower_than--;
        } else if (vec1[index] == vec2[index]) {
            equal_to--;
            greater_than++;
        }

        vec1[index]++;
    }

    void incrementSecond(int index) {
        if (vec1[index] == vec2[index] + 1) {
            equal_to++;
            greater_than--;
        } else if (vec1[index] == vec2[index]) {
            equal_to--;
            lower_than++;
        }

        vec2[index]++;
    }

    void decrementFirst(int index) {
        if (vec1[index] - 1 == vec2[index]) {
            equal_to++;
            greater_than--;
        } else if (vec1[index] == vec2[index]) {
            equal_to--;
            lower_than++;
        }

        vec1[index]--;
    }

    void decrementSecond(int index) {
        if (vec1[index] == vec2[index] - 1) {
            equal_to++;
            lower_than--;
        } else if (vec1[index] == vec2[index]) {
            equal_to--;
            greater_than++;
        }

        vec2[index]--;
    }

    int firstAt(int index) {
        return vec1[index];
    }

    int secondAt(int index) {
        return vec2[index];
    }

    int compare() {
        if (greater_than == 0 && lower_than == 0) {
            return 0;
        } else if (lower_than == 0) {
            return 1;
        } else {
            return -1;
        }
    }
};

int lowerBound(vector<int> &vec, int val) {
    int mid;

    int low = 0;
    int high = vec.size();
 
    while (low < high) {
        mid = low + (high - low) / 2;
        if (val <= vec[mid]) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    if (low < val && vec[low] < val) {
       low++;
    }

    return low;
}

vector<int> solve(vector<int> &vec1, vector<int> &vec2, int types) {
    vector<vector<int>> by_type(types);
    for (int i = 0; i < vec1.size(); i++) {
        by_type[vec1[i]].pb(i);
    }

    vector<int> solution(vec2.size(),-1);
    int j = 0;
    int k = vec1.size() - 1;
    for (int i = 0; i < vec2.size(); i++) {
        int a = vec2[i];
        
        //iterujemy, aż nie znajdziemy tego samego elementu
        for (; j < vec1.size() && vec1[j] != a; j++);

        //jeżeli w ogóle to znaleźliśmy
        if (j < vec1.size()) {
            //początek zakresu będzie tutaj i możemy to zaznaczyć
            solution[i] = lowerBound(by_type[a],j);
            j++;
        }
    }

    return solution;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    in_i(size);
    in_i(size2);
    in_i(types);

    vector<int> vec1;
    for (int i = 0; i < size; i++) {
        in_i(a);
        vec1.pb(a - 1);
    }

    vector<int> vec2;
    for (int i = 0; i < size2; i++) {
        in_i(a);
        vec2.pb(a - 1);
    }

    vector<vector<int>> by_type(types);
    for (int i = 0; i < size; i++) {
        by_type[vec1[i]].pb(i);
    }

    vector<int> v1 = solve(vec1,vec2,types);
    reverse(all(vec1));
    reverse(all(vec2));
    vector<int> v2 = solve(vec1,vec2,types);
    reverse(all(vec1));
    reverse(all(vec2));

    reverse(all(v2));
    for (int i = 0; i < v2.size(); i++) {
        if (v2[i] != -1) {
            v2[i] = by_type[vec2[i]].size() - v2[i] - 1;
        }
    }
    vector<vector<pii>> ranges_by_type(types);
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i] != -1 && v2[i] != -1) {
            ranges_by_type[vec2[i]].pb(mp(v1[i],v2[i]));
        } else {
            cout << "Ten test jest błędny." << endl;
        }
    }

    vector<vector<pii>> ranges_by_type2(types);
    for (int i = 0; i < types; i++) {
        pii prev = mp(-1,-1);
        for (pii j : ranges_by_type[i]) {
            if (prev.first == -1 || prev.second == -1 || j.first <= prev.second) {
                prev = mp((prev.first == -1 || prev.second == -1) ? j.first : prev.first, max(j.second,prev.second));
            } else {
                ranges_by_type2[i].pb(prev);
                prev = j;
            }
        }
        if (prev.first != -1 && prev.second != -1) {
            ranges_by_type2[i].pb(prev);
        }
    }

    vector<bool> solution(size);
    for (int i = 0; i < types; i++) {
        for (pii j : ranges_by_type2[i]) {
            for (int k = j.first; k <= j.second; k++) {
                solution[by_type[i][k]] = true;
            }
        }
    }
    
    for (bool b : solution) {
        if (b)
            cout << "1 ";
        else
            cout << "0 ";
    }
    cout << endl;