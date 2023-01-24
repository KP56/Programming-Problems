#include <bits/stdc++.h>

using namespace std;

void read_arr() {
    int size;
    cin >> size;

    vector<int> arr;
    for (int i = 0; i < size; i++) {
        int el;
        cin >> el;

        arr.push_back(el);
    }

    int* sort_arr = new int[size];

    for (int i = 0; i < arr.size(); i++) {
        sort_arr[arr[i]] = i;
    }

    pair<int,int> current_range = {-1, -1};
    vector<vector<int>> inside_groups;
    int immutable_inside = 0;
    int immutable = 0;
    for (int i = 0; i < size; i++) {
        if (current_range.first != -1) {
            pair<int,int> range_copy = current_range;

            if (sort_arr[i] > current_range.first && sort_arr[i] < current_range.second) {
                //if the number is in the range
                immutable_inside++;
            } else if (sort_arr[i] < current_range.first) {
                //if it expands the range to the left
                current_range = {sort_arr[i], current_range.second};
                immutable++;
            } else if (sort_arr[i] > current_range.second) {
                //if it expands the range to the right
                current_range = {current_range.first, sort_arr[i]};
                immutable++;
            }

            if (current_range.first == 0 && current_range.second == size - 1) {
                //if the addition of that element would have made the range cover all numbers
                int flexible_inside = range_copy.second - range_copy.first + 2 - immutable_inside - immutable;
                int flexible_outside = size - flexible_inside - immutable_inside - immutable;

                /*cout << "range: " << range_copy.first << " " << range_copy.second << "\n";
                cout << "flexible_inside: " << flexible_inside << "\n";
                cout << "flexible_outside: " << flexible_outside << "\n";
                cout << "immutable_inside: " << immutable_inside << "\n";
                cout << "immutable: " << immutable << "\n";*/

                //I need to divide all immutable inside into groups. Each group should contain info about:
                //- its amount of immutable inside
                //- its amount of flexible inside
                //We can replace a flexible inside with:
                //- a flexible inside from this group
                //- a flexible inside from another group
                //- an immutable inside from this group

                //ADDITIONALLY AN IMMUTABLE INSIDE MAY BE REPLACED WITH ANOTHER IMMUTABLE INSIDE FROM THIS GROUP

                //if there are 2 groups:
                //{{1, 2}, {2, 1}}

                //total amount of flexibles inside: 3
                //immutable insides: {1, 2}

                int move_between = 1;
                for (int j = 0; j < flexible_outside; j++) {
                    if (flexible_inside <= j) {
                        move_between *= flexible_outside - j;
                    } else {
                        move_between *= flexible_inside - 2*j + flexible_outside;
                    }
                }

                for (int j = 0; j < immutable_inside + flexible_inside; j++) {
                    move_between *= flexible_inside + immutable_inside - j;
                }

                cout << move_between << "\n";

                return;
            }
        } else {
            current_range = {sort_arr[i], sort_arr[i]};
            immutable++;
        }
    }

    cout << 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int problems;
    cin >> problems;

    for (int i = 0; i < problems; i++) {
        read_arr();
    }
}