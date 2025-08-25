#include <gtest/gtest.h>

#include <list>

#include "../Sequence_Containers/vector/s21_vector.cpp"

TEST(vector, create) {
  s21::vector<int> vec(5);

  EXPECT_EQ(vec.size(), 5);
};

TEST(vector, empty) {
  s21::vector<int> vec;
  EXPECT_EQ(vec.empty(), true);
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, Iterator) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  for (auto it1 = vec.begin(); it1 != vec.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, const_iterator) {
  const s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  for (auto it1 = vec.begin(); it1 != vec.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, Iterator1) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1 = vec;
  for (auto it1 = vec1.begin(); it1 != vec1.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, const_iterator1) {
  const s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  const s21::vector<int> vec1 = vec;
  for (auto it1 = vec1.begin(); it1 != vec1.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
};

TEST(vector, move) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1(std::move(vec));
  for (auto it1 = vec1.begin(); it1 != vec1.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, move1) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  s21::vector<int> vec1;
  vec1 = std::move(vec);
  for (auto it1 = vec1.begin(); it1 != vec1.end(); it1++) {
    EXPECT_EQ(*it1, 1);
  }
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, at) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};

  EXPECT_EQ(vec.at(4), 1);

  EXPECT_THROW(vec.at(22), std::out_of_range);
}

TEST(vector, bracket) {
  s21::vector<int> vec{1, 1, 1, 1, 1, 1, 1};
  vec[5] = 10;
  EXPECT_EQ(vec[5], 10);
}

TEST(vector, front_back) {
  s21::vector<int> vec{50, 1, 1, 1, 1, 1, 112};
  EXPECT_EQ(vec.front(), 50);
  EXPECT_EQ(vec.back(), 112);

  s21::vector<int> vec1{};
  EXPECT_THROW(vec1.front(), std::out_of_range);
  EXPECT_THROW(vec1.back(), std::out_of_range);
}

TEST(vector, data) {
  s21::vector<int> vec{50, 1, 1, 1, 1, 1, 112};

  int *data = vec.data();
  data[6] = 32;
  EXPECT_EQ(data[0], 50);
  EXPECT_EQ(data[6], 32);
}

TEST(vector, not_empty) {
  s21::vector<int> vec{1, 2, 3};
  EXPECT_EQ(vec.empty(), false);
  EXPECT_EQ(vec.size(), 3);
};

TEST(vector, reserve_capacity) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(152);
  EXPECT_EQ(vec.capacity(), 152);
};

TEST(vector, shrink_to_fit) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(152);
  vec.shrink_to_fit();
  EXPECT_EQ(vec.capacity(), 3);
};

TEST(vector, clear) {
  s21::vector<int> vec{1, 2, 3};
  vec.clear();
  EXPECT_EQ(vec.size(), 0);
};

TEST(vector, insert) {
  s21::vector<int> vec{1, 2, 3, 4, 5, 6};
  auto it = vec.end();
  it--;
  it--;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert1) {
  s21::vector<int> vec{1, 2, 3, 4};
  auto it = vec.end();
  it--;
  it--;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert2) {
  s21::vector<int> vec{};
  auto it = vec.begin();
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};
TEST(vector, insert3) {
  s21::vector<int> vec{1};
  auto it = vec.begin();
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert4) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(5);
  auto it = vec.begin();
  it++;
  it++;
  it++;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, insert5) {
  s21::vector<int> vec{1, 2, 3};
  vec.reserve(4);
  auto it = vec.begin();
  it++;
  it++;
  it++;
  it = vec.insert(it, 10);
  EXPECT_EQ(*it, 10);
};

TEST(vector, erase) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  auto it = vec.end();
  it--;
  it--;
  vec.erase(it);
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 5);
};

TEST(vector, push_back) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.push_back(6);
  vec.push_back(7);
  vec.push_back(9);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 9);
};

TEST(vector, pop_back) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.pop_back();
  vec.pop_back();
  vec.pop_back();
  EXPECT_EQ(vec.size(), 2);
};

TEST(vector, swap) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  s21::vector<int> vec1{5, 4, 3, 2, 1};
  vec.swap(vec1);
  for (size_t i = 0, j = vec.size(); i < vec.size(); i++, j--) {
    EXPECT_EQ(vec[i], j);
    EXPECT_EQ(vec1[i], i + 1);
  }
};

TEST(vector, pop_front) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  vec.pop_front();
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], i + 2);
  }
};

TEST(vector, pop_front_empty) {
  s21::vector<int> vec{};
  EXPECT_THROW(vec.pop_front(), std::out_of_range);
};

TEST(vector, max_size) {
  s21::vector<int> vec{};
  EXPECT_GT(vec.max_size(), 10000);
};

TEST(vector, unique) {
  s21::vector<int> vec{1, 1, 1, 1, 5, 6, 7};
  s21::vector<int> vec1{1, 5, 6, 7};
  vec.unique();
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
};

TEST(vector, unique1) {
  s21::vector<int> vec{1};
  vec.unique();
  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec.size(), 1);
};

TEST(vector, reverse) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  s21::vector<int> vec1{5, 4, 3, 2, 1};
  vec.reverse();
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
};

TEST(vector, erase_error) {
  s21::vector<int> vec{1, 2, 3, 4, 5};
  auto it = vec.end();
  EXPECT_THROW(vec.erase(it), std::out_of_range);
};

TEST(vector, erase_error1) {
  s21::vector<int> vec{};
  auto it = vec.begin();
  EXPECT_THROW(vec.erase(it), std::out_of_range);
};

TEST(vector, insert_many_back) {
  s21::vector<int> vec{};
  vec.insert_many_back(1, 2, 3, 4, 5);
  s21::vector<int> vec1{1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
};

TEST(vector, iterator3) {
  s21::vector<int> vec{};
  auto it = vec.begin();
  EXPECT_EQ(it.getData(), nullptr);
};

TEST(vector, insert_many) {
  s21::vector<int> vec{1, 5};
  auto it = vec.begin();
  it++;
  vec.insert_many(it, 2, 3, 4);
  s21::vector<int> vec1{1, 2, 3, 4, 5};
  for (size_t i = 0; i < vec.size(); i++) {
    EXPECT_EQ(vec[i], vec1[i]);
  }
};

TEST(vector, const_iterator2) {
  const s21::vector<int> vec{1, 5};
  auto it = vec.begin();
  it++;
  EXPECT_EQ(*it, 5);
  it--;
  EXPECT_EQ(*it, 1);
  it = vec.end();
};

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}