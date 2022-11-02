#include <bits/stdc++.h>

using namespace std;

class CountingMultiset {
private:
    int minimum;
    int maximum;

    int beg = INT_MAX;
    int en = INT_MIN;

    vector<int> s;
public:
    CountingMultiset(int minimum, int maximum) {
        this->minimum = minimum;
        this->maximum = maximum;

        s = vector<int>(maximum - minimum + 1);
    }

    //O(1)
    void insert(int x) {
        s[x - minimum]++;
        beg = min(beg, x);
        en = max(en, x);
    }

    //O(1)
    void remove(int x) {
        s[x - minimum]--;
    }

    //O(1) if previous lowest value was not removed
    //O(current - prev) if previous lowest value was removed
    int begin() {
        if (s[beg - minimum] <= 0) {
            int i = beg - minimum + 1;
            for (; s[i] <= 0 && i < s.size(); i++);

            if (s[i] > 0) {
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
        if (s[en - minimum] <= 0) {
            int i = en - minimum + 1;
            for (; s[i] <= 0 && i >= 0; i--);

            if (s[i] > 0) {
                en = i + minimum;
            } else {
                en = INT_MIN;
            }
        }

        return en;
    }

    //O(max - min + n)
    vector<int> toVector() {
        vector<int> vec;

        for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < s[i]; j++) {
                vec.push_back(i + minimum);
            }
        }

        return vec;
    }
};

int main() {
    CountingMultiset fast_set = CountingMultiset(-10, 20);

    fast_set.insert(-5);

    cout << "begin: " << fast_set.begin() << endl;
    cout << "end: " << fast_set.begin() << endl;

    fast_set.insert(-5);

    fast_set.remove(-5);
    fast_set.remove(-5);

    fast_set.insert(-8);
    fast_set.insert(-10);

    cout << "begin: " << fast_set.begin() << endl;
    cout << "end: " << fast_set.end() << endl;

    fast_set.remove(-10);

    fast_set.insert(11);
    fast_set.insert(4);

    cout << "begin: " << fast_set.begin() << endl;
    cout << "end: " << fast_set.end() << endl;

    fast_set.insert(-10);

    fast_set.insert(7);
    fast_set.insert(0);

    fast_set.insert(18);

    cout << "begin: " << fast_set.begin() << endl;
    cout << "end: " << fast_set.end() << endl;

    fast_set.insert(20);
    fast_set.insert(20);

    for (auto i : fast_set.toVector()) {
        cout << i << " ";
    }
    cout << endl;
}