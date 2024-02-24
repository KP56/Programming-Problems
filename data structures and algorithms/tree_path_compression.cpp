#include <bits/stdc++.h>

using namespace std;

void dfs_compress(int at, int prev, bool prev_compressable, vector<bool> &vis, vector<vector<int>> &tree, vector<vector<int>> &tree_compressed,
            unordered_map<int,int> &mapping) {
    vis[at] = true;
    if (!prev_compressable) {
        mapping[at] = tree_compressed.size();
        tree_compressed.push_back({});
    } else {
        mapping[at] = mapping[prev];
    }

    bool cannot_compress = (tree[at].size() != 2 && at != 0) || (at == 0 && tree[at].size() != 1);

    for (int i : tree[at]) {
        if (!vis[i]) {
            dfs_compress(i,at,!cannot_compress,vis,tree,tree_compressed,mapping);
        } else if (!prev_compressable) {
            tree_compressed[mapping[at]].push_back(mapping[i]);
            tree_compressed[mapping[i]].push_back(mapping[at]);
        }
    }
}

pair<vector<vector<int>>,vector<int>> compress_tree(vector<vector<int>> &tree) {
    vector<vector<int>> tree_compressed;
    unordered_map<int,int> mapping;
    vector<bool> vis(tree.size());

    dfs_compress(0,-1,false,vis,tree,tree_compressed,mapping);

    vector<int> node_counter(tree_compressed.size());
    for (auto i : mapping) {
        node_counter[i.second]++;
    }

    return {tree_compressed,node_counter};
}

vector<vector<int>> reconstruct(vector<vector<int>> &compressed_tree, vector<int> &amounts) {
    vector<vector<int>> reconstructed;
    vector<bool> vis(compressed_tree.size());
    vector<int> mapping(compressed_tree.size());
    for (int i = 0; i < compressed_tree.size(); i++) {
        vis[i] = true;

        for (int j = 0; j < amounts[i]; j++) {
            vector<int> to_push;

            if (j != 0) {
                to_push.push_back(reconstructed.size() - 1);
            }

            if (j != amounts[i] - 1) {
                to_push.push_back(reconstructed.size() + 1);
            }

            reconstructed.push_back(to_push);
        }
        int actual_node = reconstructed.size() - amounts[i];
        mapping[i] = reconstructed.size() - 1;
        for (int j : compressed_tree[i]) {
            if (vis[j]) {
                reconstructed[mapping[j]].push_back(actual_node);
                reconstructed[actual_node].push_back(mapping[j]);
            }
        }
    }

    return reconstructed;
}

int find_height_dfs(int at, vector<bool> &vis, vector<vector<int>> &tree) {
    vis[at] = true;

    int max_val = 1;
    for (int i : tree[at]) {
        if (!vis[i]) {
            max_val = max(max_val,find_height_dfs(i,vis,tree) + 1);
        }
    }

    return max_val;
}

int find_height(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());
    return find_height_dfs(0,vis,tree);
}

vector<vector<int>> height_differences;
void test(vector<vector<int>> &tree) {
    auto compress = compress_tree(tree);
    
    int height_old = find_height(tree);
    int height_new = find_height(compress.first);

    height_differences.push_back({height_old,height_new,(int)tree.size(),(int)compress.first.size()});
}

vector<vector<int>> random_tree_naive(int size) {
    vector<vector<int>> current_tree;

    current_tree.push_back({});
    for (int i = 1; i < size; i++) {
        int parent = rand() % current_tree.size();
        current_tree.push_back({parent});
        current_tree[parent].push_back(i);
    }

    return current_tree;
}

vector<vector<int>> random_tree_naive_with_stretching(int size) {
    vector<vector<int>> current_tree;

    current_tree.push_back({});
    for (int i = 1; i < size; i++) {
        int parent = rand() % current_tree.size();
        int stretch_by = rand() % (size - i) + 1;
        int prev = parent;
        for (int j = i; j < i+stretch_by; j++) {
            current_tree.push_back({prev});
            current_tree[prev].push_back(j);
            prev = j;
        }

        i += stretch_by-1;
    }

    return current_tree;
}

// https://www.geeksforgeeks.org/random-tree-generator-using-prufer-sequence-with-examples/
vector<vector<int>> constructTreePrufer(vector<int> prufer, int m)
{
    int vertices = m + 2;
    vector<int> vertex_set(vertices);
 
    vector<vector<int>> tree(vertices);

    // Initialize the array of vertices
    for (int i = 0; i < vertices; i++)
        vertex_set[i] = 0;
 
    // Number of occurrences of vertex in code
    for (int i = 0; i < vertices - 2; i++)
        vertex_set[prufer[i] - 1] += 1;
 
 
    int j = 0;
 
    // Find the smallest label not present in
    // prufer[].
    for (int i = 0; i < vertices - 2; i++) 
    {
        for (j = 0; j < vertices; j++)
        {
 
            // If j+1 is not present in prufer set
            if (vertex_set[j] == 0)
            {
 
                // Remove from Prufer set and print
                // pair.
                vertex_set[j] = -1;
                tree[j].push_back(prufer[i]-1);
                tree[prufer[i]-1].push_back(j);
 
                vertex_set[prufer[i] - 1]--;
 
                break;
            }
        }
    }
 
    j = 0;
 
    // For the last element
    int vertex1 = -1;
    int vertex2 = -1;
    for (int i = 0; i < vertices; i++)
    {
        if (vertex_set[i] == 0 && j == 0)
        {
            vertex1 = i;
            j++;
        }
        else if (vertex_set[i] == 0 && j == 1) {
            vertex2 = i;
        }
    }

    if (vertex1 == vertex2 || vertex1 == -1 || vertex2 == -1) {
        // for debugging
        cout << "ERROR DETECTED" << endl;
    }

    tree[vertex1].push_back(vertex2);
    tree[vertex2].push_back(vertex1);

    return tree;
}
 
// generate random numbers in between l an r
int ran(int l, int r)
{
    return l + (rand() % (r - l + 1));
}
 
// Function to Generate Random Tree
vector<vector<int>> generateRandomTreePrufer(int n)
{
 
    int length = n - 2;
    vector<int> arr(length);
 
    // Loop to Generate Random Array
    for (int i = 0; i < length; i++) 
    {
        arr[i] = ran(0, length + 1) + 1;
    }
    return constructTreePrufer(arr, length);
}

int rand_tree_size;
const int MAX_RAND_TREE_SIZE = 10000;
const int TREE_NUMBER = 100;

void print_info(ofstream &file) {
    float average_height_old = 0;
    float average_height_new = 0;
    float average_nodes_old = 0;
    float average_nodes_new = 0;
    for (auto i : height_differences) {
        average_height_old += i[0] / (float) height_differences.size();
        average_height_new += i[1] / (float) height_differences.size();
        average_nodes_old += i[2] / (float) height_differences.size();
        average_nodes_new += i[3] / (float) height_differences.size();
    }

    file << average_nodes_old << "," << average_nodes_new << "," << average_height_old << "," << average_height_new << endl;

    cout << "Node count: " << average_nodes_old << endl;
    cout << "Average node count after compression: " << average_nodes_new << endl;
    cout << "Average height of a tree: " << average_height_old << endl;
    cout << "Average height after compression: " << average_height_new << endl;
}

void reset() {
    height_differences = {};
}

int main() {
    srand(time(NULL));

    ofstream file("data.csv");

    file << "\"Node count\",\"Average node count after compression\",\"Average height of a tree\",\"Average height after compression\"" << endl;

    for (rand_tree_size = 100; rand_tree_size <= MAX_RAND_TREE_SIZE; rand_tree_size += 100) {
        cout << "Results for trees of size: " << rand_tree_size << endl;

        for (int i = 0; i < TREE_NUMBER; i++) {
            vector<vector<int>> random_tree = random_tree_naive_with_stretching(rand_tree_size);
            test(random_tree);
        }

        print_info(file);
        reset();
    }

    file.close();
}
