#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    vector<vector<int>> adjacency_list;

    void dfsUtils(int at, function<bool(int,vector<any>&,Graph&)> &func, vector<any> &values, vector<bool> &vis) {
        vis[at] = true;

        for (int i : adjacency_list[at]) {
            if (!vis[i] && func(i,values,*this)) {
                dfsUtils(i, func, values, vis);
            }
        }
    }
public:
    Graph(int nodes) {
        adjacency_list = vector<vector<int>>(nodes);
    }

    Graph(vector<vector<int>> adjacency_list) {
        this->adjacency_list = adjacency_list;
    }

    void connect(int n1, int n2) {
        adjacency_list[n1].push_back(n2);
    }

    void createNode() {
        adjacency_list.emplace_back();
    }

    void dfs(int starting_point, function<bool(int,vector<any>&,Graph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        if (func(starting_point, val,*this)) {
            dfsUtils(starting_point, func, val, vis);
        }
    }

    void dfs(function<bool(int,vector<any>&,Graph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        for (int i = 0; i < adjacency_list.size(); i++) {
            if (!vis[i] && func(i,val,*this)) {
                dfsUtils(i, func, val, vis);
            }
        }
    }

    vector<vector<int>> getAdjacencyList() {
        return adjacency_list;
    }
};

class MutableGraph {
private:
    vector<unordered_set<int>> adjacency_list;
    vector<bool> hidden;

    void dfsUtils(int at, function<bool(int,vector<any>&,MutableGraph&)> &func, vector<any> &values, vector<bool> &vis) {
        vis[at] = true;

        for (int i : adjacency_list[at]) {
            if (!hidden[i] && !vis[i] && func(i,values,*this)) {
                dfsUtils(i, func, values, vis);
            }
        }
    }
public:
    MutableGraph(int nodes) {
        adjacency_list = vector<unordered_set<int>>(nodes);
    }

    MutableGraph(vector<unordered_set<int>> adjacency_list) {
        this->adjacency_list = adjacency_list;
    }

    void connect(int n1, int n2) {
        adjacency_list[n1].insert(n2);
    }

    void disconnect(int n1, int n2) {
        adjacency_list[n1].erase(n2);
    }

    void createNode() {
        adjacency_list.emplace_back();
        hidden.push_back(false);
    }

    void removeNode(int n) {
        for (auto i : adjacency_list) {
            i.erase(n);
        }

        adjacency_list.erase(adjacency_list.begin() + n);
    }

    void hideNode(int n) {
        hidden[n] = true;
    }

    void showNode(int n) {
        hidden[n] = true;
    }

    void dfs(int starting_point, function<bool(int, vector<any>&, MutableGraph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        if (func(starting_point, val, *this)) {
            dfsUtils(starting_point, func, val, vis);
        }
    }

    void dfs(function<bool(int, vector<any>&, MutableGraph&)> func) {
        vector<any> val;
        vector<bool> vis(adjacency_list.size());

        for (int i = 0; i < adjacency_list.size(); i++) {
            if (!hidden[i] && !vis[i] && func(i,val,*this)) {
                dfsUtils(i, func, val, vis);
            }
        }
    }
};

bool dfsFunc(int at, vector<any> &vec, MutableGraph&) {
    cout << at << endl;

    return true;
}

int main() {
    MutableGraph graph(10);
    graph.connect(0, 2);
    graph.connect(2, 3);
    graph.connect(3, 1);

    //graph.disconnect(3, 1);

    graph.dfs(0, &dfsFunc);
}