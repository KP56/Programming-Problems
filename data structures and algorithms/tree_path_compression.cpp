#include <bits/stdc++.h>

using namespace std;

// https://cp-algorithms.com/graph/hld.html
struct hld {
    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;

    int dfs(int v, vector<vector<int>> const& adj) {
        int size = 1;
        int max_c_size = 0;
        for (int c : adj[v]) {
            if (c != parent[v]) {
                parent[c] = v, depth[c] = depth[v] + 1;
                int c_size = dfs(c, adj);
                size += c_size;
                if (c_size > max_c_size)
                    max_c_size = c_size, heavy[v] = c;
            }
        }
        return size;
    }

    void decompose(int v, int h, vector<vector<int>> const& adj) {
        head[v] = h, pos[v] = cur_pos++;
        if (heavy[v] != -1)
            decompose(heavy[v], h, adj);
        for (int c : adj[v]) {
            if (c != parent[v] && c != heavy[v])
                decompose(c, c, adj);
        }
    }

    void init(vector<vector<int>> const& adj) {
        int n = adj.size();
        parent = vector<int>(n);
        depth = vector<int>(n);
        heavy = vector<int>(n, -1);
        head = vector<int>(n);
        pos = vector<int>(n);
        cur_pos = 0;

        dfs(0, adj);
        decompose(0, 0, adj);
    }

    int dist(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]])
                swap(a, b);
            int cur_heavy_path_dist = pos[b] - pos[head[b]];
            res += cur_heavy_path_dist;
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_dist = pos[b] - pos[a];
        res += last_heavy_path_dist;
        return res;
    }
};

void dfs_compress(int at, int prev, bool prev_compressable, vector<bool> &vis, vector<vector<int>> &tree, vector<vector<int>> &tree_compressed,
            vector<int> &mapping, unordered_map<int,vector<int>> &reversed_mapping) {
    vis[at] = true;
    if (!prev_compressable) {
        mapping[at] = tree_compressed.size();
        reversed_mapping[tree_compressed.size()].push_back(at);
        tree_compressed.push_back({});
    } else {
        mapping[at] = mapping[prev];
        reversed_mapping[mapping[prev]].push_back(at);
    }

    bool cannot_compress = (tree[at].size() != 2 && at != 0) || (at == 0 && tree[at].size() != 1);

    for (int i : tree[at]) {
        if (!vis[i]) {
            dfs_compress(i,at,!cannot_compress,vis,tree,tree_compressed,mapping,reversed_mapping);
        } else if (!prev_compressable) {
            tree_compressed[mapping[at]].push_back(mapping[i]);
            tree_compressed[mapping[i]].push_back(mapping[at]);
        }
    }
}


void find_root_distances_dfs(int at, vector<bool> &vis, vector<vector<int>> &tree, vector<int> &dist) {
    vis[at] = true;

    for (int i : tree[at]) {
        if (!vis[i]) {
            dist[i] = dist[at] + 1;
            find_root_distances_dfs(i,vis,tree,dist);
        }
    }
}

vector<int> find_root_distances(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());
    vector<int> dist(tree.size());
    find_root_distances_dfs(0,vis,tree,dist);

    return dist;
}

// {tree,compressed -> real,real -> compressed,distance from root on compressed,index in the group vector}
tuple<vector<vector<int>>,vector<vector<int>>,vector<int>,vector<int>,vector<int>> compress_tree(vector<vector<int>> &tree) {
    vector<vector<int>> tree_compressed;
    vector<int> mapping(tree.size());
    vector<bool> vis(tree.size());

    unordered_map<int,vector<int>> reversed_mapping;
    dfs_compress(0,-1,false,vis,tree,tree_compressed,mapping,reversed_mapping);

    vector<vector<int>> reversed_mapping_vec(tree_compressed.size());
    for (auto &i : reversed_mapping) {
        reversed_mapping_vec[i.first] = i.second;
    }

    vector<int> indices_in_group_vector(tree.size());
    for (int i = 0; i < reversed_mapping_vec.size(); i++) {
        for (int j = 0; j < reversed_mapping_vec[i].size(); j++) {
            indices_in_group_vector[reversed_mapping_vec[i][j]] = j;
        }
    }

    return {tree_compressed,reversed_mapping_vec,mapping, find_root_distances(tree_compressed), indices_in_group_vector};
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

int find_height_compressed_dfs(int at, vector<bool> &vis, vector<vector<int>> &tree, vector<vector<int>> &reversed_mapping) {
    vis[at] = true;

    int max_val = (int) reversed_mapping[at].size();
    for (int i : tree[at]) {
        if (!vis[i]) {
            max_val = max(max_val,find_height_compressed_dfs(i,vis,tree,reversed_mapping) + (int) reversed_mapping[at].size());
        }
    }

    return max_val;
}

int find_height_compressed(vector<vector<int>> &tree, vector<vector<int>> &reversed_mapping) {
    vector<bool> vis(tree.size());
    return find_height_compressed_dfs(0,vis,tree,reversed_mapping);
}

double measure_time(function<void(vector<vector<int>>&,vector<vector<int>>&)> func, vector<vector<int>> &tree, vector<vector<int>> &m) {
    auto start = chrono::high_resolution_clock::now();

    func(tree,m);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    return duration.count();
}

double measure_time(function<void(vector<vector<int>>&,vector<int>&,vector<vector<int>>&,vector<int>&,vector<int>&)> func,
        vector<vector<int>> &tree, vector<int> &mapping, vector<vector<int>> &reversed_mapping, vector<int> &indices_in_group_vector,
        vector<int> &root_distances) {
    auto start = chrono::high_resolution_clock::now();

    func(tree,mapping,reversed_mapping,indices_in_group_vector,root_distances);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    return duration.count();
}

double measure_time(function<void(hld&)> func, hld &tree) {
    auto start = chrono::high_resolution_clock::now();

    func(tree);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    return duration.count();
}

double measure_time(function<void(vector<vector<int>>&)> func, vector<vector<int>> &tree) {
    auto start = chrono::high_resolution_clock::now();

    func(tree);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    return duration.count();
}

int distance_between_nodes_rec(int at, int dist, int end, vector<vector<int>> &tree, vector<bool> &vis) {
    vis[at] = true;
    
    if (at == end) {
        return dist;
    }

    int res = -1;
    for (int i : tree[at]) {
        if (!vis[i]) {
            res = max(res,distance_between_nodes_rec(i,dist+1,end,tree,vis));
        }
    }

    return res;
}

int distance_between_nodes(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());
    int rand_node1 = rand() % tree.size();
    int rand_node2 = rand() % tree.size();

    return distance_between_nodes_rec(rand_node1,0,rand_node2,tree,vis);
}

int distance_between_nodes_hld(hld &h) {
    int rand_node1 = rand() % h.parent.size();
    int rand_node2 = rand() % h.parent.size();

    return h.dist(rand_node1,rand_node2);
}

int distance_between_nodes_compressed_rec(int at, int dist, int start, int end, vector<vector<int>> &tree, vector<bool> &vis,
        int pos_group1, int pos_group2, vector<int> &root_distances, vector<vector<int>> &reversed_mapping) {
    vis[at] = true;
    
    if (at == end) {
        return dist;
    }

    int res = -1;
    for (int i : tree[at]) {
        if (!vis[i]) {
            int distance_traveled = reversed_mapping[at].size();
            if (at == start) {
                if (root_distances[i] < root_distances[at]) {
                    distance_traveled = pos_group1 + 1;
                } else {
                    distance_traveled = reversed_mapping[at].size() - pos_group1;
                }
            }
            
            if (i == end) {
                if (root_distances[i] < root_distances[at]) {
                    distance_traveled += reversed_mapping[i].size() - pos_group2 - 1;
                } else {
                    distance_traveled += pos_group2;
                }
            }
            res = max(res,distance_between_nodes_compressed_rec(i,dist+distance_traveled,start,end,tree,vis,pos_group1,pos_group2,root_distances,reversed_mapping));
        }
    }

    return res;
}

int distance_between_nodes_compressed(vector<vector<int>> &tree, vector<int> &mapping, vector<vector<int>> &reversed_mapping,
            vector<int> &indices_in_group_vector, vector<int> &root_distances) {
    vector<bool> vis(tree.size());
    int rand_node1 = rand() % mapping.size();
    int rand_node2 = rand() % mapping.size();

    int compressed_node1 = mapping[rand_node1];
    int compressed_node2 = mapping[rand_node2];

    int index1 = indices_in_group_vector[rand_node1];
    int index2 = indices_in_group_vector[rand_node2];

    if (compressed_node1 == compressed_node2) {
        return abs(index1 - index2);
    }
    
    int dist = distance_between_nodes_compressed_rec(compressed_node1,0,compressed_node1,compressed_node2,tree,vis,index1,index2,root_distances, reversed_mapping);
    
    return dist;
}

void normal_dfs_rec(int at, vector<vector<int>> &tree, vector<bool> &vis) {
    vis[at] = true;

    for (int i : tree[at]) {
        if (!vis[i]) {
            normal_dfs_rec(i,tree,vis);
        }
    }
}

void normal_dfs(vector<vector<int>> &tree) {
    vector<bool> vis(tree.size());
    normal_dfs_rec(0,tree,vis);
}

vector<vector<double>> height_differences;
void test(vector<vector<int>> &tree) {
    auto compress = compress_tree(tree);
    hld decomposition;

    double compress_time = measure_time(compress_tree,tree);
    
    auto start = chrono::high_resolution_clock::now();
    decomposition.init(tree);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    
    double hld_time = duration.count();

    int height_old = find_height(tree);
    int height_new = find_height(get<0>(compress));

    double time_old_dfs = measure_time(normal_dfs,tree);
    double time_new_dfs = measure_time(normal_dfs,get<0>(compress));

    double time_old_bfs = 0;
    double time_new_bfs = 0;
    
    double time_old_dist = measure_time(distance_between_nodes,tree);
    double time_new_dist = measure_time(distance_between_nodes_compressed,get<0>(compress),get<2>(compress),get<1>(compress),get<4>(compress),get<3>(compress));
    double time_hld_dist = measure_time(distance_between_nodes_hld,decomposition);

    double time_old_height = measure_time(find_height,tree);
    double time_new_height = measure_time(find_height_compressed,get<0>(compress),get<1>(compress));

    double time_old_perimeter = 0;
    double time_new_perimeter = 0;

    height_differences.push_back({(double)height_old,(double)height_new,(double)tree.size(),(double)get<0>(compress).size(),time_old_dfs,time_new_dfs,
            time_old_bfs,time_new_bfs,time_old_dist,time_new_dist,time_old_height,time_new_height,time_old_perimeter,
            time_new_perimeter,compress_time,hld_time,time_hld_dist});
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

int random_leaf(unordered_set<int> &leaves) {
    int ran = rand() % leaves.size();
    int counter = 0;
    for (int i : leaves) {
        if (counter == ran) {
            return i;
        }
        counter++;
    }

    return ran;
}

void mutate_delete(vector<vector<int>> &tree, unordered_set<int> &leaves) {
    int ran = random_leaf(leaves);
    leaves.erase(ran);
    int parent = tree[ran][0];
    if (tree[parent].size() <= 2 && (parent != 0 || tree[parent].size() <= 1)) {
        leaves.insert(parent);
    }
    tree[parent].erase(find(tree[parent].begin(),tree[parent].end(),ran));
    // This deletion causes indices to shift, to account for it, all indices greater than ran should be reduced by 1
    tree.erase(tree.begin() + ran);

    unordered_set<int> cp = leaves;
    vector<int> to_insert;
    for (int i : cp) {
        if (i > ran) {
            leaves.erase(i);
            to_insert.push_back(i - 1);
        }
    }

    for (int i : to_insert) {
        leaves.insert(i);
    }

    for (auto &i : tree) {
        for (int j = 0; j < i.size(); j++) {
            if (i[j] > ran) {
                i[j]--;
            }
        }
    }
}

void mutate_offspring(vector<vector<int>> &tree, unordered_set<int> &leaves) {
    int ran = random_leaf(leaves);
    leaves.insert(tree.size());
    leaves.insert(tree.size() + 1);
    leaves.erase(ran);
    tree[ran].push_back(tree.size());
    tree[ran].push_back(tree.size() + 1);
    tree.push_back({ran});
    tree.push_back({ran});
}

pair<vector<vector<int>>,unordered_set<int>> crossover(vector<vector<int>> tree1, unordered_set<int> leaves1, vector<vector<int>> tree2, unordered_set<int> leaves2) {
    for (auto &i : tree2) {
        for (int j = 0; j < i.size(); j++) {
            i[j] += tree1.size();
        }
    }

    for (auto &i : tree2) {
        tree1.push_back(i);
    }

    int ran = random_leaf(leaves1);
    tree1[ran].push_back(tree1.size() - tree2.size());
    tree1[tree1.size() - tree2.size()].push_back(ran);
    leaves1.erase(ran);

    for (int i : leaves2) {
        leaves1.insert(i + tree1.size() - tree2.size());
    }

    return {tree1,leaves1};
}

vector<vector<int>> random_tree_genetic(int size) {
    vector<pair<vector<vector<int>>,unordered_set<int>>> generation;

    int generation_size = 5;
    for (int i = 0; i < generation_size; i++) {
        generation.push_back({{{}},{0}});
    }

    int generations = 3;
    for (int gen = 1; gen <= generations || generation[0].first.size() < size; gen++) {
        vector<pair<vector<vector<int>>,unordered_set<int>>> new_generation;
        // Mutating
        int random_mutations_offspring = rand() % generation_size;
        for (int i = 0; i < random_mutations_offspring; i++) {
            int a = rand() % generation_size;
            mutate_offspring(generation[a].first, generation[a].second);
        }

        int random_mutations_delete = rand() % generation_size;
        for (int i = 0; i < random_mutations_delete; i++) {
            int a = rand() % generation_size;
            if (generation[a].second.size() > 1) {
                mutate_delete(generation[a].first, generation[a].second);
            }
        }


        while (new_generation.size() < generation_size) {
            int random_tree1 = rand() % generation_size;
            int random_tree2 = rand() % generation_size;

            new_generation.push_back(crossover(generation[random_tree1].first, generation[random_tree1].second,
                        generation[random_tree2].first, generation[random_tree2].second));
        }

        generation = new_generation;
    }

    while (generation[0].first.size() > size) {
        mutate_delete(generation[0].first, generation[0].second);
    }

    return generation[0].first;
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
    float average_time_old_dfs = 0;
    float average_time_new_dfs = 0;
    float average_time_old_bfs = 0;
    float average_time_new_bfs = 0;
    float average_time_old_dist = 0;
    float average_time_new_dist = 0;
    float average_time_old_height = 0;
    float average_time_new_height = 0;
    float average_time_old_perimeter = 0;
    float average_time_new_perimeter = 0;
    float average_time_compress = 0;
    float average_time_hld = 0;
    float average_time_hld_dist = 0;
    for (auto i : height_differences) {
        average_height_old += i[0] / (float) height_differences.size();
        average_height_new += i[1] / (float) height_differences.size();
        average_nodes_old += i[2] / (float) height_differences.size();
        average_nodes_new += i[3] / (float) height_differences.size();
        average_time_old_dfs += i[4] / (float) height_differences.size();
        average_time_new_dfs += i[5] / (float) height_differences.size();
        average_time_old_bfs += i[6] / (float) height_differences.size();
        average_time_new_bfs += i[7] / (float) height_differences.size();
        average_time_old_dist += i[8] / (float) height_differences.size();
        average_time_new_dist += i[9] / (float) height_differences.size();
        average_time_old_height += i[10] / (float) height_differences.size();
        average_time_new_height += i[11] / (float) height_differences.size();
        average_time_old_perimeter += i[12] / (float) height_differences.size();
        average_time_new_perimeter += i[13] / (float) height_differences.size();
        average_time_compress += i[14] / (float) height_differences.size();
        average_time_hld += i[15] / (float) height_differences.size();
        average_time_hld_dist += i[16] / (float) height_differences.size();
    }

    file << average_nodes_old << "," << average_nodes_new << "," << average_height_old << "," << average_height_new << "," << 
        average_time_old_dfs << "," << average_time_new_dfs << "," << average_time_old_bfs << "," << average_time_new_bfs
        << "," << average_time_old_dist << "," << average_time_new_dist << "," << average_time_old_height << ","
        << average_time_new_height << "," << average_time_old_perimeter << "," << average_time_new_perimeter
        << "," << average_time_compress << "," << average_time_hld << "," << average_time_hld_dist * 1000 << endl;

    cout << "Node count: " << average_nodes_old << endl;
    cout << "Average node count after compression: " << average_nodes_new << endl;
    cout << "Average height of a tree: " << average_height_old << endl;
    cout << "Average height after compression: " << average_height_new << endl;
    cout << "Average DFS time: " << average_time_old_dfs << " seconds" << endl;
    cout << "Average DFS time after compression: " << average_time_new_dfs << " seconds" << endl;
    cout << "Average BFS time: " << average_time_old_bfs << " seconds" << endl;
    cout << "Average BFS time after compression: " << average_time_new_bfs << " seconds" << endl;
    cout << "Average distance calculation time: " << average_time_old_dist << " seconds" << endl;
    cout << "Average distance calculation time after compression: " << average_time_new_dist << " seconds" << endl;
    cout << "Average height calculation time: " << average_time_old_height << " seconds" << endl;
    cout << "Average height calculation time after compression: " << average_time_new_height << " seconds" << endl;
    cout << "Average perimeter calculation time: " << average_time_old_perimeter << " seconds" << endl;
    cout << "Average perimeter calculation time after compression: " << average_time_new_perimeter << " seconds" << endl;
    //compress_time,hld_time,time_hld_dist
    cout << "Average compression time: " << average_time_compress << " seconds" << endl;
    cout << "Average hld time: " << average_time_hld << " seconds" << endl;
    cout << "Average hld distance calculation time: " << average_time_hld_dist * 1000 << " ms" << endl;
}

void reset() {
    height_differences = {};
}

int main() {
    srand(time(NULL));

    ofstream file("data.csv");

    file << "\"Node count\",\"Average node count after compression\",\"Average height of a tree\",\"Average height after compression\","
     << "\"Average DFS time\",\"Average DFS time after compression\",\"Average BFS time\",\"Average BFS time after compression\","
     << "\"Average distance calculation time\",\"Average distance calculation time after compression\",\"Average height calculation time\","
     << "\"Average height calculation time after compression\",\"Average perimeter calculation time\",\"Average perimeter calculation time after compression\","
     << "\"Average compression time\",\"Average hld time\",\"Average hld distance calculation time (ms)\""<< endl;

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
