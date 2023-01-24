#include <bits/stdc++.h>

using namespace std;

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

pair<int, int> solve(unordered_set<int, custom_hash> &nums) {
    unordered_map<int, int, custom_hash> ranges;
    unordered_map<int, int, custom_hash> ranges_rev;
    for (int num : nums) {
        auto it = ranges.find(num + 1);
        auto rev_it = ranges_rev.find(num - 1);

        if (it != ranges.end() && rev_it != ranges.end()) {
            int key = (*rev_it).second;
            int value = (*it).second;

            //cout << "{" << (*it).first << ", " << value << "}, {" << key << ", " << (*rev_it).first << "} -> {" << key << ", " << value << "}" << "\n";

            ranges_rev.erase(rev_it);
            ranges.erase(it);
 
            ranges[key] = value;
            ranges_rev[value] = key;
        } else if (it != ranges.end()) {
            int val = (*it).second;

            //cout << "{" << (*it).first << ", " << val << "} -> {" << num << ", " << val << "}" << "\n";

            ranges.erase(it);
            ranges_rev[val] = num;
            ranges[num] = val;
        } else if (rev_it != ranges.end()) {
            int key = (*rev_it).second;

            //cout << "{" << key << ", " << (*rev_it).first << "} -> {" << key << ", " << num << "}" << "\n";

            ranges_rev.erase(rev_it);
            ranges_rev[num] = key;
            ranges[key] = num;
        } else {
            ranges[num] = num;
            ranges_rev[num] = num;

            //cout << "{" << num << ", " << num << "}" << "\n";
        }
    }

    pair<int,int> best_pair = {0, INT_MIN};
    //cout << "Paires: " << "\n";
    for (auto i : ranges) {
        //cout << "{" << i.first << ", " << i.second << "}" << "\n";
        if (i.second - i.first > best_pair.second - best_pair.first) {
            best_pair = i;
        }
    }

    if (ranges.empty()) {
        best_pair = {-1, -1};
    }

    return best_pair;
}

void read_data() {
    int size, k;
    cin >> size >> k;

    unordered_map<int, int, custom_hash> arr;
    for (int i = 0; i < size; i++) {
        int num;
        cin >> num;

        arr[num]++;
    }

    unordered_set<int, custom_hash> nums;
    for (pair<int, int> p : arr) {
        if (p.second >= k) {
            nums.insert(p.first);
        }
    }
    
    pair<int, int> solution = solve(nums);
    if (solution.first == -1) {
        cout << -1 << "\n";
    } else {
        cout << solution.first << " " << solution.second << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tests;
    cin >> tests;

    for (int i = 0; i < tests; i++) {
        read_data();
    }
}