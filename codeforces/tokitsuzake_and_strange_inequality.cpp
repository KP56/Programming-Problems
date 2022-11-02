//Issue with one test case

#include <bits/stdc++.h>
#define lli long long int

using namespace std;

vector<lli> matching_pds_to_pbs;
vector<lli> max_matches;
vector<vector<lli>> alpha_for_pa;
void pregenerate(vector<int> &arr) {
    matching_pds_to_pbs = vector<lli>(arr.size());
    max_matches = vector<lli>(arr.size());
    vector<vector<int>> possible_pb_pc_matches;

    for (int i = 0; i < arr.size(); i++) {
        possible_pb_pc_matches.push_back(vector<int>(i + 1, 0));
    }

    alpha_for_pa = vector<vector<lli>>(arr.size(), vector<lli>(arr.size()));
    for (int i = 0; i < arr.size() - 1; i++) {
        int current_sum = 0;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[i] > arr[j]) {
                current_sum++;
                possible_pb_pc_matches[j][i] = 1;
            }

            if (i > 0) {
                possible_pb_pc_matches[j][i] += possible_pb_pc_matches[j][i - 1];
            }
        }

        matching_pds_to_pbs[i] = current_sum;
        if (i > 0) {
            matching_pds_to_pbs[i] += matching_pds_to_pbs[i - 1];
        }
    }

    for (int i = 0; i < arr.size() - 1; i++) {
        max_matches[i] = possible_pb_pc_matches[i + 1][i];

        if (i > 0) {
            max_matches[i] += max_matches[i - 1];
        }
    }

    for (int i = 0; i < arr.size() - 3; i++) {
        for (int j = i + 1; j < arr.size() - 1; j++) {
            alpha_for_pa[i][j] = possible_pb_pc_matches[j + 1][i] + alpha_for_pa[i][j - 1];
        }
    }
}

int for_pa_pc(int pa, int pc, vector<int> &arr) {
    lli combinations = matching_pds_to_pbs[pc - 1] - matching_pds_to_pbs[pa];

    combinations -= max_matches[pc - 1] - max_matches[pa];
    combinations += alpha_for_pa[pa][pc - 1];

    return combinations;
}

int possibilities(vector<int> &arr) {
    pregenerate(arr);

    int current_sum = 0;
    for (int i = 0; i < arr.size() - 3; i++) {
        for (int j = i + 2; j < arr.size() - 1; j++) {
            if (arr[i] < arr[j]) {
                current_sum += for_pa_pc(i, j, arr);
            }
        }
    }

    return current_sum;
}

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int p;
        cin >> p;
        
        arr.push_back(p);
    }

    cout << possibilities(arr) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        read_arr();
    }
}