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

struct block {
    vector<unordered_set<int>> graph = vector<unordered_set<int>>(5);
    vector<unordered_set<int>> reverse_graph = vector<unordered_set<int>>(5);
    vector<int> letter_count = vector<int>(5);
    vector<int> block_contents;

    block(vector<int> contents) {
        this->block_contents = contents;

        for (int i : contents) {
            letter_count[i]++;
        }
    }

    void replace(int letter1, int letter2) {
        if (letter1 == letter2) return;

        for (int i : reverse_graph[letter1]) {
            graph[i].erase(letter1);
            graph[i].insert(letter2);
            reverse_graph[letter2].insert(i);
        }
        reverse_graph[letter1].clear();
        if (graph[letter1].empty()) {
            graph[letter1].insert(letter2);
            reverse_graph[letter2].insert(letter1);
        }

        letter_count[letter2] += letter_count[letter1];
        letter_count[letter1] = 0;
    }

    void push_changes() {
        for (int i = 0; i < block_contents.size(); i++) {
            if (!graph[block_contents[i]].empty()) {
                block_contents[i] = *graph[block_contents[i]].begin();
            }
        }

        graph = vector<unordered_set<int>>(5);
        reverse_graph = vector<unordered_set<int>>(5);
    }

    void replace(int first_letters, int letter1, int letter2) {
        push_changes();

        letter_count[letter2] += first_letters;
        letter_count[letter1] -= first_letters;

        int letter1_count = 0;
        for (int i = 0; i < block_contents.size() && letter1_count < first_letters; i++) {
            if (block_contents[i] == letter1) {
                block_contents[i] = letter2;

                letter1_count++;
            }
        }
    }
};

struct sqrt_decomposition {
    vector<block> blocks;

    sqrt_decomposition(string &s) {
        vector<int> vector_representation;

        for (int i = 0; i < s.length(); i++) {
            vector_representation.pb(s[i] - 'a');
        }

        // dzielimy na bloki
        int block_size = sqrt(s.length());

        int block_count = s.length() / block_size + (s.length() % block_size != 0);

        int current_elements = 0;
        for (int i = 0; i < block_count; i++) {
            vector<int> block_representation;
            for (int j = 0; j < block_size && current_elements < s.length(); j++) {
                block_representation.pb(vector_representation[current_elements]);

                current_elements++;
            }
            blocks.pb(block(block_representation));
        }
    }

    void perform_an_operation(int first_letters, int letter1, int letter2) {
        int letters_so_far = 0;
        for (int i = 0; i < blocks.size(); i++) {
            int letters_in_the_block = blocks[i].letter_count[letter1];

            if (letters_in_the_block <= first_letters) {
                blocks[i].replace(letter1,letter2);
                first_letters -= letters_in_the_block;
            } else {
                blocks[i].replace(first_letters,letter1,letter2);
                return;
            }
        }
    }

    vector<int> retrieve_all() {
        vector<int> answer;
        for (int i = 0; i < blocks.size(); i++) {
            blocks[i].push_changes();
            for (int j : blocks[i].block_contents) {
                answer.pb(j);
            }
        }

        return answer;
    }
};

string random_string(int n) {
    string s = "";
    for (int i = 0; i < n; i++) {
        s += string(1,rand() % 5 + 'a');
    }

    return s;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    ini(n);
    //int n = rand() % 10 + 1;
    ini(m);
    //int m = rand() % 10 + 1;

    instr(s);
    //string s = random_string(n);

    sqrt_decomposition decomposition(s);

    //string bruteforce_str = s;
    //vector<vector<int>> queries_debug;

    for (int i = 0; i < m; i++) {
        ini(replace);
        //int replace = rand() % 10 + 1;
        instr(a);
        //string a = string(1,rand() % 5 + 'a');
        instr(b);
        //string b = string(1,rand() % 5 + 'a');

        //queries_debug.pb({replace,a[0]-'a',b[0]-'a'});

        /*int found_so_far = 0;
        for (int j = 0; j < n && found_so_far < replace; j++) {
            if (bruteforce_str[j] == a[0]) {
                bruteforce_str[j] = b[0];
                found_so_far++;
            }
        }*/

        decomposition.perform_an_operation(replace,a[0]-'a',b[0]-'a');
    }

    //string comparison = "";
    for (int i : decomposition.retrieve_all()) {
        //comparison += string(1,'a' + i);
        cout << string(1,'a' + i);
    }
    cout << endl;

    /*if (comparison != bruteforce_str) {
        int test = 0;
    }*/
}