#include <gtest/gtest.h>

#include <array>

#include "../array/s21_array.h"

TEST(TestArray, list_constructor) {
  s21::array<int, 10> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  for (int i = 1; i < 11; i++) {
    EXPECT_EQ(a[i - 1], i);
  }
  EXPECT_EQ(a.size(), 10);
}

TEST(TestArray, list_constructor_not_full) {
  s21::array<int, 10> a{1, 2, 3, 4, 5};
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(a[i - 1], i);
  }
  for (int i = 6; i < 11; i++) {
    EXPECT_EQ(a[i - 1], 0);
  }
  EXPECT_EQ(a.size(), 10);
}

TEST(TestArray, constructor_copy) {
  s21::array<int, 10> b{1, 2, 3, 4, 5};
  s21::array<int, 10> a{b};
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(a[i - 1], i);
  }
  for (int i = 6; i < 11; i++) {
    EXPECT_EQ(a[i - 1], 0);
  }
  EXPECT_EQ(a.size(), 10);
}

TEST(TestArray, operator_move) {
  s21::array<int, 10> b{1, 2, 3, 4, 5};
  s21::array<int, 10> a;
  a = std::move(b);
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(a[i - 1], i);
  }
  for (int i = 6; i < 11; i++) {
    EXPECT_EQ(a[i - 1], 0);
  }
  EXPECT_EQ(a.size(), 10);
}

TEST(TestArray, constructor_move) {
  s21::array<int, 10> b{1, 2, 3, 4, 5};
  s21::array<int, 10> a(std::move(b));
  for (int i = 1; i < 6; i++) {
    EXPECT_EQ(a[i - 1], i);
  }
  for (int i = 6; i < 11; i++) {
    EXPECT_EQ(a[i - 1], 0);
  }
  EXPECT_EQ(a.size(), 10);

  EXPECT_EQ(b.size(), 10);
}

TEST(TestArray, swap_iterators) {
  s21::array<int, 5> b{1, 2, 3, 4, 5};
  s21::array<int, 5> a{5, 4, 3, 2, 1};
  a.swap(b);
  for (auto it1 = a.begin(), it2 = b.end(); it1 != a.end(); it1++) {
    it2--;
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(TestArray, at) {
  s21::array<int, 5> a{5, 4, 3, 2, 1};
  EXPECT_THROW(a.at(10), std::out_of_range);
  EXPECT_EQ(a.at(2), 3);
}

TEST(TestArray, empty) {
  s21::array<int, 0> a{};
  EXPECT_EQ(a.empty(), 1);
  s21::array<int, 12> b{312};
  EXPECT_EQ(b.empty(), 0);
}

TEST(TestArray, fill) {
  s21::array<int, 10> a{};
  a.fill(100);
  for (auto it = a.begin(); it != a.end(); it++) EXPECT_EQ(*it, 100);
}

TEST(TestArray, front_back) {
  s21::array<int, 10> a{};
  a.fill(100);
  a[0] = 200;
  a[9] = 400;
  EXPECT_EQ(a.front(), 200);
  EXPECT_EQ(a.back(), 400);
}

TEST(TestArray, data) {
  s21::array<int, 10> a{};
  a.fill(100);
  a[0] = 200;
  EXPECT_EQ(*a.data(), 200);
}

TEST(TestArray, ConstIterators) {
  const s21::array<int, 4> arr = {10, 20, 30, 40};

  EXPECT_EQ(arr.data(), &arr[0]);
  EXPECT_EQ(*arr.data(), 10);

  EXPECT_EQ(arr.begin(), &arr[0]);
  EXPECT_EQ(*arr.begin(), 10);

  EXPECT_EQ(arr.end(), arr.begin() + 4);
  EXPECT_EQ(arr.end() - arr.begin(), 4);
  EXPECT_NE(*arr.end(), 40);

  auto it = arr.begin();
  EXPECT_EQ(*it++, 10);
  EXPECT_EQ(*it++, 20);
  EXPECT_EQ(*it++, 30);
  EXPECT_EQ(*it++, 40);
  EXPECT_EQ(it, arr.end());
}

TEST(TestArray, max_size) {
  s21::array<int, 124> a;
  EXPECT_GT(a.max_size(), 1000);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}