#ifndef A2I_ARRAY_GENERATOR_H
#define A2I_ARRAY_GENERATOR_H

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class ArrayGenerator {
 private:
  static const int MAX_SIZE = 100000;
  static const int MIN_VALUE = 0;
  static const int MAX_VALUE = 6000;
  static const int COUNT_CHANGES =
      MAX_SIZE / 228;  // пусть это будет "небольшим количеством" перестановок
                       // для "почти" отсортированного массива.
  mt19937 rng;

  vector<int> random_array_;
  vector<int> reverse_sorted_array_;
  vector<int> almost_sorted_array_;

  void generate_random_array() {
    random_array_.resize(MAX_SIZE);
    uniform_int_distribution<int> dist(MIN_VALUE, MAX_VALUE);
    for (int i = 0; i < MAX_SIZE; ++i) {
      random_array_[i] = dist(rng);
    }
  }

  void generate_reverse_sorted_array() {
    reverse_sorted_array_.resize(MAX_SIZE);
    uniform_int_distribution<int> dist(MIN_VALUE, MAX_VALUE);

    for (int i = 0; i < MAX_SIZE; ++i) {
      reverse_sorted_array_[i] = dist(rng);
    }

    sort(reverse_sorted_array_.begin(), reverse_sorted_array_.end(),
         greater<int>());
  }

  void generate_almost_sorted_array_() {
    almost_sorted_array_.resize(MAX_SIZE);
    uniform_int_distribution<int> dist(MIN_VALUE, MAX_VALUE);

    for (int i = 0; i < MAX_SIZE; ++i) {
      almost_sorted_array_[i] = dist(rng);
    }

    sort(almost_sorted_array_.begin(), almost_sorted_array_.end());

    uniform_int_distribution<int> random_indexes(MIN_VALUE, MAX_VALUE - 1);

    for (int i = 0; i < COUNT_CHANGES; ++i) {
      int index_0 = random_indexes(rng);
      int index_1 = random_indexes(rng);
      swap(almost_sorted_array_[index_0], almost_sorted_array_[index_1]);
    }
  }

 public:
  ArrayGenerator() : rng(random_device{}()) {
    generate_random_array();
    generate_reverse_sorted_array();
    generate_almost_sorted_array_();
  }

  explicit ArrayGenerator(unsigned int seed) : rng(seed) {
    generate_random_array();
    generate_reverse_sorted_array();
    generate_almost_sorted_array_();
  }

  vector<int> get_random_array(size_t size) {
    vector<int> res;
    if (size > 0 && size < MAX_SIZE) {
      res = vector<int>(random_array_.begin(), random_array_.begin() + size);
    }
    return res;
  }

  vector<int> get_reverse_sorted_array(size_t size) {
    vector<int> res;
    if (size > 0 && size < MAX_SIZE) {
      res = vector<int>(reverse_sorted_array_.begin(), reverse_sorted_array_.begin() + size);
    }
    return res;
  }

  vector<int> get_almost_sorted_array(size_t size) {
    vector<int> res;
    if (size > 0 && size < MAX_SIZE) {
      res = vector<int>(almost_sorted_array_.begin(), almost_sorted_array_.begin() + size);
    }
    return res;
  }

};


#endif //A2I_ARRAY_GENERATOR_H
