#ifndef A2I_SORT_H
#define A2I_SORT_H

#include <iostream>
#include <vector>

using namespace std;

void merge(vector<int>& nums, int l, int mid, int r) {
  int n1 = mid - l + 1;
  int n2 = r - mid;

  vector<int> t1(n1), t2(n2);

  for (int i = 0; i < n1; ++i) {
    t1[i] = nums[l + i];
  }
  for (int i = 0; i < n2; ++i) {
    t2[i] = nums[mid + 1 + i];
  }

  int i = 0, j = 0, k = l;
  while (i < n1 && j < n2) {
    if (t1[i] < t2[j]) {
      nums[k++] = t1[i++];
    } else {
      nums[k++] = t2[j++];
    }
  }

  while (i < n1) nums[k++] = t1[i++];
  while (j < n2) nums[k++] = t2[j++];
}

void pure_merge_sort(vector<int>& nums, int l, int r) {
  if (l < r) {
    int mid = l + (r - l) / 2;
    pure_merge_sort(nums, l, mid);
    pure_merge_sort(nums, mid + 1, r);
    merge(nums, l, mid, r);
  }
}

void insertion_sort_range(vector<int>& nums, int l, int r) {
  for (int i = l + 1; i <= r; ++i) {
    int val = nums[i];
    int j = i - 1;
    while (j >= l && nums[j] > val) {
      nums[j + 1] = nums[j];
      j--;
    }
    nums[j + 1] = val;
  }
}

void upgraded_merge_sort(vector<int>& nums, int l, int r, int threshold) {
  if (l < r) {
    int size = r - l + 1;

    if (size <= threshold) {
      insertion_sort_range(nums, l, r);
    } else {
      int mid = l + (r - l) / 2;
      upgraded_merge_sort(nums, l, mid, threshold);
      upgraded_merge_sort(nums, mid + 1, r, threshold);
      merge(nums, l, mid, r);
    }
  }
}

void sort_array(vector<int>& nums, int threshold = 15) {
  if (nums.empty()) return;
  upgraded_merge_sort(nums, 0, nums.size() - 1, threshold);
}


#endif //A2I_SORT_H