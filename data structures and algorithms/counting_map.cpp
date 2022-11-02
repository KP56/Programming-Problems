#include <bits/stdc++.h>

using namespace std;

template<typename T>
class CountingMap {
private:
    int minimum;
    int maximum;

    int beg = INT_MAX;
    int en = INT_MIN;

    vector<vector<T>> s;
public:
    CountingMap(int minimum, int maximum) {
        this->minimum = minimum;
        this->maximum = maximum;

        s = vector<vector<T>>(maximum - minimum + 1);
    }

    //O(1)
    void insert(int x, T obj) {
        if (s[x - minimum].empty()) {
            s[x - minimum].push_back(obj);
            beg = min(beg, x);
            en = max(en, x);
        }
    }

    //O(1)
    void remove(int x) {
        s[x - minimum].clear();
    }

    //O(1)
    T get(int x) {
        return s[x - minimum][0];
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
    vector<pair<int,T>>& toVector() {
        vector<pair<int,T>> vec;

        for (int i = 0; i < s.size(); i++) {
            if (!s[i].empty()) {
                vec.emplace_back(i + minimum, s[i][0]);
            }
        }

        return vec;
    }
};

int main() {
    CountingMap<int> counting_map = CountingMap<int>(-10, 20);

    counting_map.insert(0, 3);
    counting_map.insert(0, 3);

    cout << counting_map.get(0) << endl;

    cout << counting_map.begin() << endl;
    cout << counting_map.end() << endl;

    counting_map.insert(4, 8);
    counting_map.remove(0);

    cout << counting_map.begin() << endl;

    counting_map.insert(12, 12);

    cout << counting_map.begin() << endl;
    cout << counting_map.end() << endl;
    

    for (auto i : counting_map.toVector()) {
        cout << i.first << "," << i.second << " ";
    }
    cout << endl;
}