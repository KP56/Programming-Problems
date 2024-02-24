#include <bits/stdc++.h>

using namespace std;

#define int long long int

struct block {
    vector<int> elements;
    int block_sum = 0;
    int sum_of_initial = 0;
    int sum_of_velocities = 0;

    int first_element_position;
    int last_element_position;

    block() {}

    block(int first_element_position, int last_element_position) {
        this->first_element_position = first_element_position;
        this->last_element_position = last_element_position;

        elements = vector<int>(last_element_position - first_element_position + 1);
    }

    bool covers_total_block(int position, int initial_strength, int loses) {
        int val1 = max(0ll,initial_strength-abs(position-first_element_position)*loses);
        int val2 = max(0ll,initial_strength-abs(position-last_element_position)*loses);

        return val1 != 0 && val2 != 0;
    }

    void add_to_total_block(int position, int initial_strength, int loses) {
        int val1 = initial_strength-abs(position-first_element_position)*loses;
        int val2 = initial_strength-abs(position-last_element_position)*loses;

        // jeżeli mamy val1 oraz val2 to wystarczy suma elementów ciągu arytmetycznego
        // initial_strength*n+loses*n*(n+1)/2

        int n = last_element_position-first_element_position+1;

        if (val1 < val2) {
            block_sum += (initial_strength-loses*abs(position-first_element_position))*n+loses*(n-1)*n/2;
        } else {
            block_sum += (initial_strength-loses*abs(position-last_element_position))*n+loses*(n-1)*n/2;
        }
        if (position < first_element_position) {
            // jeżeli jest przed blockiem to mamy opadający sygnał
            sum_of_initial += val1;
            sum_of_velocities -= loses;
        } else {
            // w przeciwnym wypadku sygnał jest rosnący
            sum_of_initial += val1;
            sum_of_velocities += loses;
        }
    }

    void remove_from_total_block(int position, int initial_strength, int loses) {
        int val1 = initial_strength-abs(position-first_element_position)*loses;
        int val2 = initial_strength-abs(position-last_element_position)*loses;

        // jeżeli mamy val1 oraz val2 to wystarczy suma elementów ciągu arytmetycznego
        // initial_strength*n+loses*n*(n+1)/2

        int n = last_element_position-first_element_position+1;

        if (val1 < val2) {
            block_sum -= (initial_strength-loses*abs(position-first_element_position))*n+loses*(n-1)*n/2;
        } else {
            block_sum -= (initial_strength-loses*abs(position-last_element_position))*n+loses*(n-1)*n/2;
        }
        if (position < first_element_position) {
            // jeżeli jest przed blockiem to mamy opadający sygnał
            sum_of_initial -= val1;
            sum_of_velocities += loses;
        } else {
            // w przeciwnym wypadku sygnał jest rosnący
            sum_of_initial -= val1;
            sum_of_velocities -= loses;
        }
    }

    // element jest indeksem BLOKOWYM
    void remove_from_specific_element(int element, int position, int initial_strength, int loses) {
        int add = max(0ll,initial_strength-abs(position-(first_element_position+element))*loses);

        elements[element] -= add;
        block_sum -= add;
    }

    // element jest indeksem BLOKOWYM
    void modify_specific_element(int element, int position, int initial_strength, int loses) {
        int add = max(0ll,initial_strength-abs(position-(first_element_position+element))*loses);

        elements[element] += add;
        block_sum += add;
    }

    // element jest indeksem BLOKOWYM
    int retrieve_specific_element(int element) {
        return elements[element] + sum_of_initial + element * sum_of_velocities;
    }
};

struct sqrt_decomp {
    vector<block> blocks;
    int normal_block_size;
    int n;

    sqrt_decomp(int size) {
        n = size;
        normal_block_size = sqrt(size);

        for (int i = 0; i < n/normal_block_size+1; i++) {
            blocks.push_back(block(i*normal_block_size,(i+1)*normal_block_size-1));
        }
    }

    int query(int l, int r) {
        int elements = r-l+1;

        int left_block = l / normal_block_size;
        int left_block_idx = l % normal_block_size;

        int right_block = r / normal_block_size;
        int right_block_idx = r % normal_block_size;

        int res = 0;
        for (block &b : blocks) {
            if (b.first_element_position > l && b.last_element_position < r) {
                res += b.block_sum;
            }
        }

        if (left_block == right_block) {
            for (int i = left_block_idx; i <= right_block_idx; i++) {
                res += blocks[left_block].retrieve_specific_element(i);
            }
        } else {
            block &left_block_b = blocks[left_block];
            for (int i = left_block_idx; i < normal_block_size; i++) {
                res += left_block_b.retrieve_specific_element(i);
            }

            block &right_block_b = blocks[right_block];
            for (int i = 0; i <= right_block_idx; i++) {
                res += right_block_b.retrieve_specific_element(i);
            }
        }

        return res / elements;
    }

    void add(int position, int initial_strength, int loses) {
        // znajdujemy blok w którym postawiliśmy maszt
        int block_id = position / normal_block_size;

        for (int i = 0; i < blocks.size(); i++) {
            if (i == block_id) continue;

            block &b = blocks[i];
            
            if (b.covers_total_block(position, initial_strength, loses)) {
                b.add_to_total_block(position, initial_strength, loses);
            }
        }

        // dodajemy do wszystkich elementów
        for (int i = 0; i < normal_block_size; i++) {
            blocks[block_id].modify_specific_element(i,position,initial_strength,loses);
        }

        // teraz odnajdujemy bloki skrajne i w nich aktualizujemy jedynie do konkretnych elementów
        // s-a*d>0
        // a*d<s
        // d<s/a

        int d = initial_strength / loses - 1 + (initial_strength % loses != 0);
        int right_position = min(n-1,position + d);
        int left_position = max(0ll,position - d);

        int right_block = right_position / normal_block_size;
        int left_block = left_position / normal_block_size;

        int right_block_el = right_position % normal_block_size;
        int left_block_el = left_position % normal_block_size;

        if (left_block != right_block) {
            block &left_block_b = blocks[left_block];
            block &right_block_b = blocks[right_block];
            if (left_block_el != 0 && left_block != block_id && !left_block_b.covers_total_block(position, initial_strength, loses)) {
                for (int i = left_block_el; i < normal_block_size; i++) {
                    left_block_b.modify_specific_element(i,position,initial_strength,loses);
                }
            }

            if (right_block_el != normal_block_size - 1 && right_block != block_id && !right_block_b.covers_total_block(position, initial_strength, loses)) {
                for (int i = 0; i <= right_block_el; i++) {
                    right_block_b.modify_specific_element(i,position,initial_strength,loses);
                }
            }
        }
    }

    void remove(int position, int initial_strength, int loses) {
        // znajdujemy blok w którym postawiliśmy maszt
        int block_id = position / normal_block_size;

        for (int i = 0; i < blocks.size(); i++) {
            if (i == block_id) continue;

            block &b = blocks[i];
            
            if (b.covers_total_block(position, initial_strength, loses)) {
                b.remove_from_total_block(position, initial_strength, loses);
            }
        }

        // dodajemy do wszystkich elementów
        for (int i = 0; i < normal_block_size; i++) {
            blocks[block_id].remove_from_specific_element(i,position,initial_strength,loses);
        }

        // teraz odnajdujemy bloki skrajne i w nich aktualizujemy jedynie do konkretnych elementów
        // s-a*d>0
        // a*d<s
        // d<s/a

        int d = initial_strength / loses - 1 + (initial_strength % loses != 0);
        int right_position = min(n-1,position + d);
        int left_position = max(0ll,position - d);

        int right_block = right_position / normal_block_size;
        int left_block = left_position / normal_block_size;

        int right_block_el = right_position % normal_block_size;
        int left_block_el = left_position % normal_block_size;

        if (left_block != right_block) {
            block &left_block_b = blocks[left_block];
            block &right_block_b = blocks[right_block];
            if (left_block_el != 0 && left_block != block_id && !left_block_b.covers_total_block(position, initial_strength, loses)) {
                for (int i = left_block_el; i < normal_block_size; i++) {
                    left_block_b.remove_from_specific_element(i,position,initial_strength,loses);
                }
            }

            if (right_block_el != normal_block_size - 1 && right_block != block_id && !right_block_b.covers_total_block(position, initial_strength, loses)) {
                for (int i = 0; i <= right_block_el; i++) {
                    right_block_b.remove_from_specific_element(i,position,initial_strength,loses);
                }
            }
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    srand(time(NULL));

    //int n = rand() % 10 + 1,m = rand() % 10 + 1;
    int n,m;
    cin >> n >> m;

    //vector<int> bruteforce_vec(n);

    sqrt_decomp decomp(n);

    vector<pair<int,int>> mem(n);

    //vector<vector<int>> queries;

    for (int i = 0; i < m; i++) {
        string operation;

        /*int rand_res = rand() % 3;
        if (rand_res == 0) {
            operation = "P";
        } else if (rand_res == 1) {
            operation = "U";
        } else {
            operation = "Z";
        }*/

        cin >> operation;

        if (operation == "P") {
            // postawienie masztu
            //int x = rand() % n + 1,s = rand() % 5 + 1,a = rand() % 5 + 1;
            int x,s,a;
            cin >> x >> s >> a;

            //queries.push_back({x,s,a});

            x--;

            /*for (int j = 0; j < n; j++) {
                bruteforce_vec[j] += max(0ll,s-a*abs(j-x));
            }*/

            mem[x] = {s,a};
            decomp.add(x,s,a);
        } else if (operation == "U") {
            // usunięcie masztu
            //int x = rand() % n + 1;
            int x;
            cin >> x;

            //queries.push_back({x});

            x--;

            /*for (int j = 0; j < n; j++) {
                bruteforce_vec[j] -= max(0ll,mem[x].first-mem[x].second*abs(j-x));
            }*/

            decomp.remove(x,mem[x].first,mem[x].second);
        } else if (operation == "Z") {
            // zapytanie
            //int x1 = rand() % n + 1,x2 = rand() % (n-x1+1) + x1;
            int x1,x2;
            cin >> x1 >> x2;

            //queries.push_back({x1,x2});

            x1--;
            x2--;

            /*int brute_res = 0;
            for (int j = x1; j <= x2; j++) {
                brute_res += bruteforce_vec[j];
            }
            brute_res /= (x2-x1+1);*/

            int res = decomp.query(x1,x2);

            /*if (brute_res != res) {
                int test = 0;
            }*/

            cout << res << "\n";
        }
    }
}