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

// Zapisuję binarną reprezentację wszystkich zapałek, aby bruteforcem odnaleźć możliwe zmiany jednych cyfr w
// inne poprzez przenoszenie zapałek
vector<vector<bool>> matches = {
    {1,1,1,0,1,1,1}, // 0
    {0,0,1,0,0,1,0}, // 1
    {1,0,1,1,1,0,1}, // 2
    {1,0,1,1,0,1,1}, // 3
    {0,1,1,1,0,1,0}, // 4
    {1,1,0,1,0,1,1}, // 5
    {1,1,0,1,1,1,1}, // 6
    {1,0,1,0,0,1,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}, // 9
};

vector<vector<pii>> find_transformations() {
    vector<pii> take_transformations;
    vector<pii> add_transformations;
    for (int i = 0; i < 10; i++) {
        vector<bool> &match1 = matches[i];

        for (int j = 0; j < 10; j++) {
            vector<bool> &match2 = matches[j];
            for (int k = 0; k < 7; k++) {
                if (match1[k] != 1) continue;

                vector<bool> match1_cp = match1;
                match1_cp[k] = 0;
                if (match1_cp == match2) {
                    take_transformations.pb({i,j});
                    add_transformations.pb({j,i});
                    break;
                }
            }
        }
    }

    vector<pii> self_transformations;
    for (int i = 0; i < 10; i++) {
        vector<bool> &match = matches[i];
        for (int j = 0; j < 7; j++) {
            if (match[j] != 1) continue;

            vector<bool> match_cp = match;
            match_cp[j] = 0;
            for (int k = 0; k < 7; k++) {
                if (match_cp[k] != 0) continue;

                if (j != k) {
                    vector<bool> match_cp2 = match_cp;
                    match_cp2[k] = 1;

                    for (int k2 = 0; k2 < 10; k2++) {
                        if (matches[k2] == match_cp2) {
                            self_transformations.pb({i,k2});
                            break;
                        }
                    }
                }
            }
        }
    }

    return {add_transformations,take_transformations,self_transformations};
}

vector<pii> compress(vector<pair<vector<int>,int>> &numbers) {
    vector<pii> vec;
    for (auto i : numbers) {
        int mul = i.second;
        int num = 0;
        int zeros_counter = 0;
        for (int j = i.first.size() - 1; j >= 0; j--) {
            num += i.first[j] * mul;
            if (i.first[j] == 0) zeros_counter++;
            else zeros_counter = 0;
            mul *= 10;
        }
        vec.pb({num,zeros_counter});
    }

    return vec;
}

// Znajduje wszystkie możliwe zmiany w sumie po wykonaniu transformacji (w tym przypadku odebrania/dodania zapałki do którejś z cyfr)
void perform_transformations(unordered_map<int,vector<vector<int>>> &after, int sum, vector<pair<vector<int>,int>> &numbers,
            vector<vector<int>> &transformations) {
    for (int i = 0; i < numbers.size(); i++) {
        pair<vector<int>,int> &num = numbers[i];
        int mul = num.second;
        for (int j = num.first.size() - 1; j >= 0; j--) {
            int digit = num.first[j];
            vector<int> new_potential_digits = transformations[digit];

            for (int k : new_potential_digits) {
                int diff = (k-digit)*mul;
                // Zapisywanie nowej sumy po transformacji
                after[diff].pb({i,j,k});
            }

            mul *= 10;
        }
    }
}

vector<vector<int>> to_graph(vector<pii> &vec, int size) {
    vector<vector<int>> graph(size);

    for (auto i : vec) {
        graph[i.first].pb(i.second);
    }

    return graph;
}

// zakładam, że elementy w vec są unikalne
vector<int> extract_first_different(vector<vector<int>> &vec, vector<int> &current) {
    if (!vec.empty()) {
        if (vec[0][0] != current[0] || vec[0][1] != current[1]) {
            return vec[0];
        } else if (vec.size() > 1) {
            return vec[1];
        }
    }

    // jeżeli nie odnaleziono, zwracamy to
    return {-1,-1};
}

pair<vector<int>,vector<int>> verify_tokens(unordered_map<int,vector<vector<int>>> &after, vector<int> &digit_token, int val, bool different_side) {
    auto it = after.find(val);
    if (it != after.end()) {
        auto p = *it;
        vector<vector<int>> tokens = p.second;

        if (different_side) {
            return {digit_token,tokens[0]};
        }

        vector<int> token = extract_first_different(tokens,digit_token);
        if (token[0] != -1) {
            return {digit_token,token};
        }
    }

    return {{-1},{-1}};
}

// side=true jeżeli prawa strona
pair<vector<int>,vector<int>> verify_possibility(unordered_map<int,vector<vector<int>>> &after_take,
        unordered_map<int,vector<vector<int>>> &after_add, bool side1, bool side2, int sum_left, int sum_right) {
    for (auto i : after_take) {
        int diff = i.first;
        for (auto digit_token : i.second) {
            pair<vector<int>,vector<int>> res;
            if (side1 && side2) {
                res = verify_tokens(after_add,digit_token,sum_left-(sum_right+diff),side1!=side2);

                if (res.first[0] != -1) {
                    return res;
                }
            } else if (!side1 && side2) {
                res = verify_tokens(after_add,digit_token,sum_left+diff-sum_right,side1!=side2);

                if (res.first[0] != -1) {
                    return res;
                }
            } else if (side1 && !side2) {
                res = verify_tokens(after_add,digit_token,sum_right+diff-sum_left,side1!=side2);

                if (res.first[0] != -1) {
                    return res;
                }
            } else {
                res = verify_tokens(after_add,digit_token,sum_right-(sum_left+diff),side1!=side2);

                if (res.first[0] != -1) {
                    return res;
                }
            }
        }
    }

    return {{-1},{-1}};
}

bool verify(string &equation) {
    vector<pair<vector<int>,int>> right_numbers;
    vector<pair<vector<int>,int>> left_numbers;

    // Parsowanie napisu
    bool found_equals = false;
    for (char c : equation) {
        if (c == '=') {
            found_equals = true;
            continue;
        } else if (c == '-') {
            if (found_equals) {
                right_numbers.pb({{},-1});
            } else {
                left_numbers.pb({{},-1});
            }
            continue;
        } else if (c == '+') {
            if (found_equals) {
                right_numbers.pb({{},1});
            } else {
                left_numbers.pb({{},1});
            }
            continue;
        }

        if (found_equals) {
            if (right_numbers.empty()) {
                right_numbers.pb({{},1});
            }

            right_numbers[right_numbers.size() - 1].first.pb(c - '0');
        } else {
            if (left_numbers.empty()) {
                left_numbers.pb({{},1});
            }

            left_numbers[left_numbers.size() - 1].first.pb(c - '0');
        }
    }

    // Skoro długość żadnej liczby nie przekroczy 10 cyfr, można je zapisać w 64 bitowym int
    vector<pii> right_numbers_int = compress(right_numbers);
    vector<pii> left_numbers_int = compress(left_numbers);

    int right_numbers_sum = 0;
    for (pii i : right_numbers_int) {
        right_numbers_sum += i.first;
    }

    int left_numbers_sum = 0;
    for (pii i : left_numbers_int) {
        left_numbers_sum += i.first;
    }

    return right_numbers_sum == left_numbers_sum;
}

void ans(vector<pair<vector<int>,int>> &right_numbers, vector<pair<vector<int>,int>> &left_numbers, string equation) {
    vector<pii> new_right_numbers = compress(right_numbers);
    vector<pii> new_left_numbers = compress(left_numbers);

    string to_verify = "";

    bool first = true;
    for (int i = 0; i < new_left_numbers.size(); i++) {
        auto k = new_left_numbers[i];
        if (k.first>=0 && left_numbers[i].second == 1 && !first) {
            to_verify += "+";
            cout << "+";
        } else if (left_numbers[i].second == -1) {
            cout << "-";
            to_verify += "-";
        }

        for (int i = 0; i < k.second - (k.first == 0); i++) {
            to_verify += "0";
            cout << 0;
        }
        if (k.first < 0) {
            to_verify += to_string(k.first * (-1));
            cout << (k.first*(-1));
        } else {
            to_verify += to_string(k.first);
            cout << k.first;
        }
        
        first = false;
    }
    cout << "=";
    to_verify += "=";
    first = true;
    for (int i = 0; i < new_right_numbers.size(); i++) {
        auto k = new_right_numbers[i];
        if (k.first>=0 && right_numbers[i].second == 1 && !first) {
            to_verify += "+";
            cout << "+";
        } else if (right_numbers[i].second == -1) {
            cout << "-";
            to_verify += "-";
        }
        for (int i = 0; i < k.second - (k.first == 0); i++) {
            to_verify += "0";
            cout << 0;
        }
        if (k.first < 0) {
            to_verify += to_string(k.first * (-1));
            cout << (k.first*(-1));
        } else {
            to_verify += to_string(k.first);
            cout << k.first;
        }
        
        first = false;
    }
    cout << endl;

    /*if (to_verify.size() != equation.size()) {
        int test = 0;
    }

    if (!verify(to_verify)) {
        int test = 0;
    }*/
}

string random_equation(int size_left, int size_right) {
    vector<int> left;
    for (int i = 0; i < size_left; i++) {
        int ran = rand() % 10;
        //if (rand() % 2 == 0) ran *= -1;
        left.pb(ran);
    }

    vector<int> right;
    for (int i = 0; i < size_right; i++) {
        int ran = rand() % 10;
        //if (rand() % 2 == 0) ran *= -1;
        right.pb(ran);
    }

    string ans = "";
    bool first = true;
    for (int i : left) {
        if (i > 0 && !first) {
            ans += "+";
        } else if (i == 0 && !first) {
            if (rand() % 2 == 0) {
                //ans += "+";
            } else {
                //ans += "-";
            }
            ans += "+";
        }

        ans += to_string(i);

        first = false;
    }
    ans += "=";
    first = true;
    for (int i : right) {
        if (i > 0 && !first) {
            ans += "+";
        } else if (i == 0 && !first) {
            if (rand() % 2 == 0) {
                //ans += "+";
            } else {
                //ans += "-";
            }

            ans += "+";
        }

        ans += to_string(i);

        first = false;
    }

    return ans;
}

bool bruteforce(string &equation, vector<vector<int>> &self_transformations, vector<vector<int>> &add_transformations, vector<vector<int>> &take_transformations) {
    // self transformation
    for (int i = 0; i < equation.size(); i++) {
        if (equation[i] != '-' && equation[i] != '+' && equation[i] != '=') {
            for (int j : self_transformations[equation[i]-'0']) {
                string cp = equation;
                cp[i] = j + '0';

                if (verify(cp)) {
                    return true;
                }
            }
        }
    }

    for (int i = 0; i < equation.size(); i++) {
        if (equation[i] != '-' && equation[i] != '+' && equation[i] != '=') {
            for (int j = 0; j < equation.size(); j++) {
                if (equation[j] != '-' && equation[j] != '+' && equation[j] != '=') {
                    for (int trans1 : add_transformations[equation[i]-'0']) {
                        for (int trans2 : take_transformations[equation[j]-'0']) {
                            string cp = equation;
                            cp[i] = trans1 + '0';
                            cp[j] = trans2 + '0';

                            if (verify(cp)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    auto res = find_transformations();

    vector<pii> add_transformations_vec = res[0];
    vector<pii> take_transformations_vec = res[1];
    vector<pii> self_transformations_vec = res[2];

    vector<vector<int>> add_transformations = to_graph(add_transformations_vec,10);
    vector<vector<int>> take_transformations = to_graph(take_transformations_vec,10);
    vector<vector<int>> self_transformations = to_graph(self_transformations_vec,10);

    //for (int a = 0; a < 10000; a++) {
    //bool break_out = false;

    instr(equation);
    //string equation = random_equation(rand() % 2 + 1, rand() % 2 + 1);

    vector<pair<vector<int>,int>> right_numbers;
    vector<pair<vector<int>,int>> left_numbers;

    // Parsowanie napisu
    bool found_equals = false;
    for (char c : equation) {
        if (c == '=') {
            found_equals = true;
            continue;
        } else if (c == '-') {
            if (found_equals) {
                right_numbers.pb({{},-1});
            } else {
                left_numbers.pb({{},-1});
            }
            continue;
        } else if (c == '+') {
            if (found_equals) {
                right_numbers.pb({{},1});
            } else {
                left_numbers.pb({{},1});
            }
            continue;
        }

        if (found_equals) {
            if (right_numbers.empty()) {
                right_numbers.pb({{},1});
            }

            right_numbers[right_numbers.size() - 1].first.pb(c - '0');
        } else {
            if (left_numbers.empty()) {
                left_numbers.pb({{},1});
            }

            left_numbers[left_numbers.size() - 1].first.pb(c - '0');
        }
    }

    // Skoro długość żadnej liczby nie przekroczy 10 cyfr, można je zapisać w 64 bitowym int
    vector<pii> right_numbers_int = compress(right_numbers);
    vector<pii> left_numbers_int = compress(left_numbers);

    int right_numbers_sum = 0;
    for (pii i : right_numbers_int) {
        right_numbers_sum += i.first;
    }

    int left_numbers_sum = 0;
    for (pii i : left_numbers_int) {
        left_numbers_sum += i.first;
    }

    unordered_map<int,vector<vector<int>>> after_take_left;
    perform_transformations(after_take_left,left_numbers_sum,left_numbers,take_transformations);
    unordered_map<int,vector<vector<int>>> after_add_left;
    perform_transformations(after_add_left,left_numbers_sum,left_numbers,add_transformations);
    
    unordered_map<int,vector<vector<int>>> after_take_right;
    perform_transformations(after_take_right,right_numbers_sum,right_numbers,take_transformations);
    unordered_map<int,vector<vector<int>>> after_add_right;
    perform_transformations(after_add_right,right_numbers_sum,right_numbers,add_transformations);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            unordered_map<int,vector<vector<int>>> &after_take = i ? after_take_right : after_take_left;
            unordered_map<int,vector<vector<int>>> &after_add = j ? after_add_right : after_add_left;
            pair<vector<int>,vector<int>> res = verify_possibility(after_take, after_add, i, j, left_numbers_sum, right_numbers_sum);

            if (res.first[0] != -1) {
                if (i && j) {
                    // zabieramy i dodajemy z prawej
                    right_numbers[res.first[0]].first[res.first[1]] = res.first[2];
                    right_numbers[res.second[0]].first[res.second[1]] = res.second[2];
                } else if (i && !j) {
                    // zabieramy z prawej i dodajemy z lewej
                    right_numbers[res.first[0]].first[res.first[1]] = res.first[2];
                    left_numbers[res.second[0]].first[res.second[1]] = res.second[2];
                } else if (!i && j) {
                    // zabieramy z lewej i dodajemy z prawej
                    left_numbers[res.first[0]].first[res.first[1]] = res.first[2];
                    right_numbers[res.second[0]].first[res.second[1]] = res.second[2];
                } else {
                    // dodajemy i zabieramy z lewej
                    left_numbers[res.first[0]].first[res.first[1]] = res.first[2];
                    left_numbers[res.second[0]].first[res.second[1]] = res.second[2];
                }

                ans(right_numbers,left_numbers,equation);

                //break_out = true;
                //break;
                return 0;
            }
        }
        //if (break_out) break;
    }

    //if (break_out) continue;

    // tutaj rozważamy self transformation czyli zabieranie zapałki z konkretnej cyfry i dodawanie jej do tej samej cyfry w innym miejscu
    for (auto &i : right_numbers) {
        int mul = i.second;
        for (int j = i.first.size() - 1; j >= 0; j--) {
            for (int k : self_transformations[i.first[j]]) {
                if (right_numbers_sum + (k-i.first[j])*mul == left_numbers_sum) {
                    i.first[j] = k;

                    ans(right_numbers,left_numbers,equation);

                    //break_out = true;
                    //break;
                    return 0;
                }
            }
            //if (break_out) break;

            mul *= 10;
        }

        //if (break_out) break;
    }

    //if (break_out) continue;

    for (auto &i : left_numbers) {
        int mul = i.second;
        for (int j = i.first.size() - 1; j >= 0; j--) {
            for (int k : self_transformations[i.first[j]]) {
                if (left_numbers_sum + (k-i.first[j])*mul == right_numbers_sum) {
                    i.first[j] = k;

                    ans(right_numbers,left_numbers,equation);

                    //break_out = true;
                    //break;
                    return 0;
                }
            }

            //if (break_out) break;

            mul *= 10;
        }

        //if (break_out) break;
    }

    //if (break_out) continue;

    cout << "no" << endl;

    /*if (bruteforce(equation,self_transformations,add_transformations,take_transformations)) {
        int test = 0;
    }*/
}