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

//https://jimmy-shen.medium.com/stl-map-unordered-map-with-a-vector-for-the-key-f30e5f670bae
struct vector_hash {
    int operator()(const vector<int> &V) const {
        int hash = V.size();
        for (auto &i : V) {
            hash ^= i + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

struct pair_hash {
    size_t operator() (const pair<int, int>& p) const {
        return ((size_t) p.first << 32) | p.second;
    }
};

struct base_word_layer {
    unordered_map<pii,int,pair_hash> tracker;
    vector<int> layer;

    base_word_layer() {}

    base_word_layer(base_word_layer &prev, int layer_id) {
        // layer_id to id obecnej warstwy a nie poprzedniej
        // layer_id jest równoznaczne z dystansem między elementami, które wspólnie bierzemy
        for (int i = 0; i < prev.layer.size() - layer_id; i++) {
            pii p = {prev.layer[i], prev.layer[i + layer_id]};
            push(p);
        }
    }

    void prev_push(base_word_layer &prev, int layer_id) {
        // layer_id to id obecnej warstwy a nie poprzedniej
        if (((int) prev.layer.size()) - 1 - (1 << (layer_id-1)) >= 0) {
            pii p = {prev.layer[prev.layer.size() - 1 - (1 << (layer_id-1))], prev.layer[prev.layer.size() - 1]};
            push(p);
        }
    }

    void push(pii i) {
        if (tracker.find(i) == tracker.end()) {
            tracker[i] = tracker.size();
        }

        push_id(tracker[i]);
    }

    void push_id(int id) {
        layer.pb(id);
    }
};

struct base_word_dict {
    vector<base_word_layer> dict;
    int k;
    int layers;
    vector<bool> layer_tokens;

    base_word_dict(int k) {
        this->k = k;
        this->layers = log(k)/log(2)+1;

        for (int i = 0; i < layers; i++) {
            base_word_layer layer;
            dict.pb(layer);
        }

        layer_tokens = vector<bool>(layers);
        for (int i = 0; i < layers; i++) {
            layer_tokens[i] = k >> i & 1;
        }
    }

    void push(int num) {
        dict[0].push_id(num);
        for (int i = 1; i < layers; i++) {
            dict[i].prev_push(dict[i-1], i);
        }
    }

    vector<int> encode(int idx) {
        // Koduje podciąg spójny pomiędzy indeksami idx...idx+k-1
        vector<int> encoded;
        for (int i = 0; i < layers; i++) {
            if (layer_tokens[i]) {
                encoded.pb(dict[i].layer[idx]);
                idx += (1 << i);
            }
        }

        return encoded;
    }
};

char find_the_most_common_letter(string s, string a) {
    unordered_map<char,int> occurences;
    for (int i = 0; i < s.length()-a.length(); i++) {
        bool broke = false;
        for (int j = 0; j < a.length(); j++) {
            if (s[i+j] != a[j]) {
                broke = true;
                break;
            }
        }

        if (!broke) {
            occurences[s[i+a.length()]]++;
        }
    }

    char best_letter = 'a';
    int best_occurences = 0;
    for (auto i : occurences) {
        if (i.second > best_occurences || (i.second == best_occurences && i.first < best_letter)) {
            best_occurences = i.second;
            best_letter = i.first;
        }
    }

    return best_letter;
}

string brute(int n, int k, int a, int b, string s) {
    while (s.length() < b) {
        string last_letters = "";
        for (int i = s.length() - k; i < s.length(); i++) {
            last_letters += string(1,s[i]);
        }
        char most_common = find_the_most_common_letter(s, last_letters);
        s += string(1,most_common);
    }

    string res = "";
    for (int i = a-1; i < b; i++) {
        res += string(1,s[i]);
    }

    return res;
}

string random_str(int n, int letters_limit) {
    string s = "";
    for (int i = 0; i < n; i++) {
        char c = 'a' + (rand() % letters_limit);
        s += string(1,c);
    }

    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 100 + 2;
    ini(k);
    //int k = rand() % (n - 1) + 1;
    ini(a);
    //int a = rand() % 100000 + n + 1;
    ini(b);
    //int b = rand() % 100000 + a + 1;

    int a_cp = a;
    int b_cp = b;

    instr(s);
    //string s = random_str(n, rand() % 25 + 2);

    /*ifstream stream("cza1040.in");
    string dummyLine;
    getline(stream, dummyLine);
    string s;
    getline(stream, s);

    string s_cp = s;*/

    //auto start = std::chrono::system_clock::now();

    base_word_dict dict(k);
    for (char c : s) {
        dict.push(c - 'a');
    }

    unordered_map<vector<int>, vector<int>, vector_hash> window_map;
    for (int i = 0; i < n - k; i++) {
        vector<int> encoded = dict.encode(i);
        if (window_map.find(encoded) == window_map.end()) {
            window_map[encoded] = vector<int>(26);
        }
        window_map[encoded][s[i + k] - 'a']++;
    }

    unordered_map<vector<int>, int, vector_hash> letters;
    for (auto i : window_map) {
        int best_letter = 0;
        int best_letter_count = 0;
        for (int j = 0; j < 26; j++) {
            if (i.second[j] > best_letter_count) {
                best_letter_count = i.second[j];
                best_letter = j;
            }
        }

        letters[i.first] = best_letter;
    }

    string final_res;
    unordered_map<vector<int>, int, vector_hash> found_so_far;
    while (true) {
        vector<int> encoding = dict.encode(s.length()-k);
        if (found_so_far.find(encoding) != found_so_far.end()) {
            int memo = found_so_far[encoding];

            // Znaleźliśmy cykl
            int cycle_size = s.length() - memo - 1;

            a--;
            b--;

            string res = "";
            // Jeżeli a jest przed początkiem cyklu
            if (a < memo) {
                // Dla każdej literki od a do początku cyklu, zatrzymujemy się od razu przed cyklem
                for (int i = a; i < memo && i <= b; i++) {
                    res += string(1,s[i]);
                }

                a = memo;

                if (a > b) {
                    cout << res << endl;
                    final_res = res;

                    break;
                }
            }

            int start_pos_in_cycle = (a - memo) % cycle_size;

            // Od początku cyklu aż do końca napisu iterujemy i zbieramy literki
            string cycle = "";
            for (int i = memo; i < s.length()-1; i++) {
                cycle += s[i];
            }

            int current_pos_in_cycle = start_pos_in_cycle;
            for (int i = a; i <= b; i++) {
                res += cycle[current_pos_in_cycle];
                current_pos_in_cycle = (current_pos_in_cycle + 1) % cycle_size;
            }

            cout << res << endl;
            final_res = res;

            break;
        }
        found_so_far[encoding] = s.size()-1;
        int to_generate = letters[encoding];
        s += (to_generate + 'a');
        dict.push(to_generate);
    }

    /*auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    cout << "Elapsed: " << elapsed_seconds.count() << endl;*/

    /*string brute_res = brute(n, k, a_cp, b_cp, s_cp);

    if (brute_res != final_res) {
        int test = 0;
    }*/
}