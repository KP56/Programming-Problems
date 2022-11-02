#include <bits/stdc++.h>

using namespace std;

template<typename T> class CountingMultimap {
private:
    int minimum;
    int maximum;

    int beg = INT_MAX;
    int en = INT_MIN;

    vector<unordered_multiset<T>> s;
public:
    CountingMultimap(int minimum, int maximum) {
        this->minimum = minimum;
        this->maximum = maximum;

        s = vector<unordered_multiset<T>>(maximum - minimum + 1);
    }

    //O(1)
    void insert(int x, T obj) {
        s[x - minimum].insert(obj);
        beg = min(beg, x);
        en = max(en, x);
    }

    //O(1)
    void remove(int x, T obj) {
        s[x - minimum].erase(s[x - minimum].find(obj));
    }

    //O(1)
    unordered_multiset<T>& get(int x) {
        return s[x - minimum];
    }

    //O(1) if previous lowest value was not removed
    //O(current - prev) if previous lowest value was removed
    int begin() {
        if (s[beg - minimum].empty()) {
            int i = beg - minimum + 1;
            for (; s[i].empty() && i < s.size(); i++);

            if (!s[i].empty()) {
                beg = i + minimum;
            } else {
                beg = INT_MAX;
            }
        }

        return beg;
    }

    //O(1) if previous greatest value was not removed
    //O(prev - current) if previous lowest value was removed
    int end() {
        if (s[en - minimum].empty()) {
            int i = en - minimum + 1;
            for (; s[i].empty() && i >= 0; i--);

            if (!s[i].empty()) {
                en = i + minimum;
            } else {
                en = INT_MIN;
            }
        }

        return en;
    }

    //O(max - min + n)
    vector<pair<int,unordered_multiset<T>>> toVector() {
        vector<pair<int,unordered_multiset<T>>> vec;

        for (int i = 0; i < s.size(); i++) {
            if (!s[i].empty()) {
                vec.emplace_back(i + minimum, s[i]);
            }
        }

        return vec;
    }
};

int main() {
    CountingMultimap<int> counting_map = CountingMultimap<int>(-10, 20);

    counting_map.insert(0, 3);
    counting_map.insert(0, 3);

    cout << *counting_map.get(0).begin() << endl;
    cout << counting_map.end() << endl;

    counting_map.insert(4, 8);
    counting_map.remove(0, 3);

    cout << counting_map.begin() << endl;

    counting_map.insert(12, 12);

    cout << counting_map.begin() << endl;
    cout << counting_map.end() << endl;
    
    for (auto i : counting_map.toVector()) {
        for (auto j : i.second) {
            cout << i.first << "," << j << " ";
        }
    }
    cout << endl;
}