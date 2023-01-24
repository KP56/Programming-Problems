#include <bits/stdc++.h>

using namespace std;

template<typename T> class OperationQueue {
private:
    stack<pair<T, T>> s1;
    stack<pair<T, T>> s2;
    function<T(T,T)> f;

    void move() {
        if (s1.empty()) {
            if (!s2.empty()) {
                s1.emplace(s2.top().first, s2.top().first);
                s2.pop();
            }

            while (!s2.empty()) {
                s1.emplace(s2.top().first, f(s2.top().first, s1.top().second));
                s2.pop();
            }
        }
    }
public:
    OperationQueue(function<T(T,T)> f) {
        this->f = f;
    }

    void push(T a) {
        if (!s2.empty()) {
            s2.emplace(a, f(a, s2.top().first));
        } else {
            s2.emplace(a, a);
        }
    }

    void pop() {
        move();
        s1.pop();
    }

    int size() {
        return s1.size() + s2.size();
    }

    bool empty() {
        return size() == 0;
    }

    T query() {
        move();

        if (!s2.empty()) {
            return f(s1.top().second, s2.top().second);
        } else {
            return s1.top().second;
        }
    }
};

int f(int a, int b) {
    return max(a,b);
}

int main() {
    OperationQueue<int> queue(&f);
    queue.push(1);
    queue.push(3);
    queue.push(2);
    
    queue.pop();
    queue.pop();
    cout << queue.query() << endl;
}