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

int k2;

struct Comparator
{
    bool operator() (const pii& lhs,
                     const pii& rhs) const
    {
      if ((lhs.first % k2) == (rhs.first % k2))
        return lhs.second < rhs.second;
      else
        return (((lhs.first % k2) == 0) || ((lhs.first % k2) > (rhs.first % k2))) && ((rhs.first % k2) != 0);
    }
};

struct Comparator2
{
    bool operator() (const pii& lhs,
                     const pii& rhs) const
    {
      if (lhs.first == rhs.first)
        return lhs.second > rhs.second;
      else
        return lhs.first < rhs.first;
    }
};

vector<int> brute(vector<int> arr, int k) {
    multiset<pii, Comparator2> s;
    for (int i = 0; i < arr.size(); i++) {
        s.insert({arr[i],i});
    }

    vector<int> ordering;
    while (!s.empty() && s.size() > 1) {
        pii greatest = *(--s.end());
        pii second_greatest = *(--(--s.end()));
 
        int diff = greatest.first - second_greatest.first;
        int required_moves = diff / k + (diff % k != 0);
 
        int new_val = greatest.first - max(1ll,required_moves) * k;
        s.erase(--s.end());
        if (new_val > 0) {
            s.insert({new_val,greatest.second});
        } else {
            ordering.pb(greatest.second);
        }
    }
 
    if (!s.empty()) {
        ordering.pb((*s.begin()).second);
    }

    return ordering;
}

void readCaseData() {
    ini(n);
    //int n = rand() % 3 + 1;
    ini(k);
    //int k = rand() % 3 + 1;

    k2 = k;

    vector<int> arr2;
    vector<pii> arr;
    for (int i = 0; i < n; i++) {
        ini(el);
        //int el = rand() % 5 + 1;
        arr.pb({el,i});
        arr2.pb(el);
    }

    sort(all(arr), Comparator());

    /*vector<int> brute_res = brute(arr2, k);

    vector<int> new_arr;
    for (pii i : arr) {
        new_arr.pb(i.second);
    }

    if (brute_res != new_arr) {
        int test = 0;
    }*/

    for (pii i : arr) {
        cout << i.second + 1 << " ";
    }
    cout << endl;
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