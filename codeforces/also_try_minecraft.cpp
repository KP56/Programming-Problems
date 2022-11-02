#include <bits/stdc++.h>
#define lli long long int

using namespace std;
     
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
     
    lli columns, quests;
    cin >> columns >> quests;
        
    vector<lli> heights;
    for (lli i = 0; i < columns; i++) {
        lli height;
        cin >> height;
     
        heights.push_back(height);
    }
    
    lli zero = 0;
    vector<lli> column_vec_right;
    for (lli i = 0; i < columns; i++) {
        if (column_vec_right.size() > 0) {
            column_vec_right.push_back(max(zero, heights[i - 1] - heights[i]) + column_vec_right[column_vec_right.size() - 1]);
        } else {
            column_vec_right.push_back(zero);
        }
    }
     
    vector<lli> column_vec_left;
    for (lli i = columns - 1; i >= 0; i--) {
        if (column_vec_left.size() > 0) {
            column_vec_left.push_back(max(zero, heights[i + 1] - heights[i]) + column_vec_left[column_vec_left.size() - 1]);
        } else {
            column_vec_left.push_back(zero);
        }
    }
     
    reverse(column_vec_left.begin(), column_vec_left.end());
     
    for (lli i = 0; i < quests; i++) {
        lli a, b;
        cin >> a >> b;
        a--;
        b--;
     
        if (a > b) {
            cout << column_vec_left[b] - column_vec_left[a] << "\n";
        } else {
            cout << column_vec_right[b] - column_vec_right[a] << "\n";
        }
    }
}