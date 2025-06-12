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

vector<int> possible_types = {0,1,2,4,7};

struct prefix_3d {
    vector<vector<vector<int>>> table[8];
    unordered_set<int> to_map1;
    unordered_set<int> to_map2;
    unordered_set<int> to_map3;
    vector<vector<int>> to_push;
    vector<vector<int>> to_later_iterate;
    unordered_map<int,int> mapping;
    unordered_map<int,int> mapping2;
    unordered_map<int,int> mapping3;

    void push(int i, int j, int k, int type) {
        to_map1.insert(i);
        to_map2.insert(j);
        to_map3.insert(k);

        to_push.pb({i,j,k,type});
    }

    void push_to_later_iterate(int i, int j, int k, int type) {
        to_later_iterate.pb({i,j,k,type});
    }

    void construct() {
        vector<int> vec_map1;
        vector<int> vec_map2;
        vector<int> vec_map3;

        vec_map1.insert(vec_map1.end(),all(to_map1));
        vec_map2.insert(vec_map2.end(),all(to_map2));
        vec_map3.insert(vec_map3.end(),all(to_map3));

        sort(all(vec_map1));
        sort(all(vec_map2));
        sort(all(vec_map3));

        for (int i : vec_map1) {
            mapping[i] = mapping.size();
        }

        for (int i : vec_map2) {
            mapping2[i] = mapping2.size();
        }

        for (int i : vec_map3) {
            mapping3[i] = mapping3.size();
        }

        for (auto &i : to_push) {
            int mapped_i = mapping[i[0]];
            int mapped_j = mapping2[i[1]];
            int mapped_k = mapping3[i[2]];

            i[0] = mapped_i, i[1] = mapped_j, i[2] = mapped_k;
        }

        // teraz konstruujemy prefix
        for (int type : possible_types) {
            table[type] = vector<vector<vector<int>>>(mapping.size()+1,vector<vector<int>>(mapping2.size()+1,vector<int>(mapping3.size()+1)));
            for (auto &i : to_push) {
                if (i[3] == type) {
                    table[type][i[0]+1][i[1]+1][i[2]+1] = 1;
                }
            }

            // chcemy, aby każdy indeks był sumą bryły o indeksach i-1, j-1, k-1 oraz 3 płaszczyzn
            for (int i = 1; i <= mapping.size(); i++) {
                for (int j = 1; j <= mapping2.size(); j++) {
                    for (int k = 1; k <= mapping3.size(); k++) {
                        table[type][i][j][k] += table[type][i - 1][j][k] + table[type][i][j - 1][k] + table[type][i][j][k - 1]
                                - table[type][i - 1][j - 1][k] - table[type][i][j - 1][k - 1] - table[type][i - 1][j][k - 1]
                                + table[type][i - 1][j - 1][k - 1];
                    }
                }
            }
        }
    }
};

vector<vector<int>> get_all_unique_triplets_sets(int n) {
    vector<vector<int>> vec;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            for (int k = j; k < n; k++) {
                vec.pb({i,j,k});
            }
        }
    }

    return vec;
}

int bruteforce(vector<int> &vec) {
    vector<int> vec2;

    for (int i = 0; i < vec.size(); i++) {
        int sum = 0;
        for (int j = i; j < vec.size(); j++) {
            sum += vec[j];
            vec2.pb(sum);
        }
    }

    int res = 0;
    for (int i = 0; i < vec2.size(); i++) {
        for (int j = i+1; j < vec2.size(); j++) {
            for (int k = j+1; k < vec2.size(); k++) {
                if (vec2[i] + vec2[j] + vec2[k] == 0) {
                    res++;
                }
            }
        }
    }

    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    ini(n);
    //int n = rand() % 50 + 1;
    vector<int> vec;

    vector<int> prefix;
    prefix.pb(0);
    for (int i = 0; i < n; i++) {
        ini(a);
        //int a = rand() % 50 + 1;
        vec.pb(a);
        prefix.pb(a+prefix[prefix.size() - 1]);
    }

    unordered_map<int,prefix_3d> prefixes_3d;
    for (int i = 0; i < prefix.size(); i++) {
        for (int j = 0; j < prefix.size(); j++) {
            for (int k = 0; k < prefix.size(); k++) {
                // rozważamy trójkę {i,j,k}
                int sum = prefix[i] + prefix[j] + prefix[k];

                // identyfikujemy jeden z 8 typów trójki:
                int type = (i == j) | ((i == k) << 1) | ((j == k) << 2);

                prefixes_3d[sum].push(i,j,k,type);
            }
        }
    }

    for (auto &i : prefixes_3d) {
        i.second.construct();
    }

    int sum_size = 0;
    int map_size = 0;
    int test = prefixes_3d.size();
    for (auto &i : prefixes_3d) {
        sum_size += i.second.mapping.size() * i.second.mapping2.size() * i.second.mapping3.size();
        map_size += i.second.mapping.size();
    }

    // muszę sprawić by zdobyć wszystkie unikalne zbiory trójek
    for (auto &i : get_all_unique_triplets_sets(prefix.size())) {
        int type = (i[0] == i[1]) | ((i[0] == i[2]) << 1) | ((i[1] == i[2]) << 2);
        int sum = prefix[i[0]] + prefix[i[1]] + prefix[i[2]];

        if (prefixes_3d[sum].mapping[i[0]] == 0) {
            continue;
        }

        prefixes_3d[sum].push_to_later_iterate(prefixes_3d[sum].mapping[i[0]],prefixes_3d[sum].mapping2[i[1]],prefixes_3d[sum].mapping3[i[2]],type);
    }

    int sum = 0;
    for (auto &i : prefixes_3d) {
        for (auto &j : i.second.to_later_iterate) {
            int sum2 = 0;
            // dla każdej trójki zdobywamy ilość takich trójek, które są mniejsze od tej z innych typów
            for (int type2 : possible_types) {
                if ((type2 & j[3]) != 0) continue;
                int amount = i.second.table[type2][j[0]][j[1]][j[2]];
                sum2 += amount;
            }

            if (j[3] == 1 || j[3] == 2 || j[3] == 4) {
                sum2 /= 2;
            } else if (j[3] == 7) {
                sum2 /= 6;
            }

            sum += sum2;
        }
    }

    /*int brute_res = bruteforce(vec);
    if (brute_res != sum) {
        int test = 0;
    }*/
    cout << sum << endl;
}