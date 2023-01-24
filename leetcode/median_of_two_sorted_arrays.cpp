#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        int i = 0, j = 0;
        vector<int> res;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] > nums2[j]) {
                res.push_back(nums2[j]);
                j++;
            } else {
                res.push_back(nums1[i]);
                i++;
            }
        }

        while (j < nums2.size()) {
            res.push_back(nums2[j]);
            j++;
        }

        while (i < nums1.size()) {
            res.push_back(nums1[i]);
            i++;
        }

        if (res.size() & 1) {
            return res[res.size() / 2];
        } else {
            return (double) (res[res.size() / 2] + res[res.size() / 2 - 1]) / 2;
        }
    }
};