#ifndef A2I_SORT_TESTER_H
#define A2I_SORT_TESTER_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "a2i_sort.h"

struct TestResult {
  int size;
  double mean;
  double median;
  double min;
  double max;
};

class SortTester {
 private:
  static const int NUM_OF_RUNS = 10;

  double calculate_mean(vector<double>& times) {
    if (times.size() == 0) return 0;
    double sum = 0;
    for (double x : times) {
      sum += x;
    }
    return sum / times.size();
  }

  double calculate_median(vector<double>& times) {
    sort(times.begin(), times.end());
    size_t n = times.size();
    if (n % 2 == 0) {
      return (times[n / 2 - 1] + times[n / 2]) / 2.0;
    }
    return times[n / 2];
  }

  double check_time_for_ordinary_sort(vector<int> arr) {
    auto start = chrono::high_resolution_clock::now();
    pure_merge_sort(arr, 0, arr.size() - 1);
    auto elapsed = chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
        .count();
  }

  double check_time_for_upgraded_sort(vector<int> arr, int threshold) {
    auto start = chrono::high_resolution_clock::now();
    sort_array(arr, threshold);
    auto elapsed = chrono::high_resolution_clock::now() - start;
    return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)
        .count();
  }

 public:
  SortTester() = default;

  TestResult test_pure_merge_sort(vector<int>& arr) {
    vector<double> amounts_of_time(NUM_OF_RUNS);
    for (int i = 0; i < NUM_OF_RUNS; ++i) {
      vector<int> copy = arr;
      double time = check_time_for_ordinary_sort(copy);
      amounts_of_time[i] = time;
    }

    TestResult res;
    res.size = arr.size();
    res.mean = accumulate(amounts_of_time.begin(), amounts_of_time.end(), 0.0) /
               amounts_of_time.size();
    res.median = calculate_median(amounts_of_time);
    res.min = *min_element(amounts_of_time.begin(), amounts_of_time.end());
    res.max = *max_element(amounts_of_time.begin(), amounts_of_time.end());

    return res;
  }

  TestResult test_upgraded_sort(vector<int>& arr, int threshold) {
    vector<double> amounts_of_time(NUM_OF_RUNS);
    for (int i = 0; i < NUM_OF_RUNS; ++i) {
      vector<int> copy = arr;
      double time = check_time_for_upgraded_sort(copy, threshold);
      amounts_of_time[i] = time;
    }

    TestResult res;
    res.size = arr.size();
    res.mean = accumulate(amounts_of_time.begin(), amounts_of_time.end(), 0.0) /
               amounts_of_time.size();
    res.median = calculate_median(amounts_of_time);
    res.min = *min_element(amounts_of_time.begin(), amounts_of_time.end());
    res.max = *max_element(amounts_of_time.begin(), amounts_of_time.end());

    return res;
  }

  // Экспорт результатов в CSV
  void export_to_csv(const string& filename, const vector<TestResult>& results,
                     const string& algorithm_name) {
    ofstream file(filename);

    file << "Algorithm,Size,Mean,Median,Min,Max\n";

    for (const auto& result : results) {
      file << algorithm_name << "," << result.size << "," << result.mean
           << "," << result.median << "," << result.min << ","
           << result.max << "\n";
    }

    file.close();
    cout << "Данные экспортированы в " << filename << endl;
  }

  void print_results(const vector<TestResult>& results, const string& title) {
    cout << "\n========== " << title << " ==========\n";
    cout << "Size\tMean\tMedian\tMin\t\tMax\n";
    cout << "------------------------------------------------------------------"
            "--\n";

    for (const auto& r : results) {
      cout << r.size << "\t" << r.mean << "\t\t" << r.median << "\t\t"
           << r.min << "\t\t" << r.max << "\n";
    }
  }
};

#endif //A2I_SORT_TESTER_H
