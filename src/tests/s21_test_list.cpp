#include <gtest/gtest.h>

#include <list>

#include "../Sequence_Containers/list/s21_list.h"

using namespace std;

TEST(ListTest, push_back) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.push_back(412);
  b.push_back(412);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, pop_back) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.pop_back();
  b.pop_back();
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, pop_backErr) {
  s21::list<int> a = {};
  EXPECT_THROW(a.pop_back(), std::out_of_range);
}

TEST(ListTest, pop_back1) {
  s21::list<int> a = {};
  a.push_back(10);
  a.pop_back();
  EXPECT_EQ(a.size(), 0);
}

TEST(ListTest, erase) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  auto it1 = a.begin();
  auto it2 = b.begin();
  a.erase(++it1);
  b.erase(++it2);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    it1++;
    it2++;
  }
  auto it11 = a.begin();
  auto it22 = b.begin();
  a.erase(it11);
  b.erase(it22);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, clear_empty) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};
  a.clear();
  b.clear();

  EXPECT_EQ(a.empty(), b.empty());
}

TEST(ListTest, size) {
  std::list<int> a = {1, 2, 3};
  s21::list<int> b = {1, 2, 3};

  EXPECT_EQ(a.size(), b.size());
  a.clear();
  b.clear();
  EXPECT_EQ(a.size(), b.size());
}

TEST(ListTest, reverse_swap) {
  std::list<int> a = {1, 2, 3};
  std::list<int> a1{a};
  a1.reverse();

  s21::list<int> b = {1, 2, 3};
  s21::list<int> b1{b};
  b1.reverse();
  b.swap(b1);
  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a.begin();
    auto it2 = b1.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, merge) {
  std::list<int> a = {1, 2, 3};
  std::list<int> a1{a};
  a1.merge(a);

  s21::list<int> b = {1, 2, 3};
  s21::list<int> b1{b};
  b1.merge(b);

  for (size_t i = 0; i < a.size(); i++) {
    auto it1 = a1.begin();
    auto it2 = b1.begin();
    EXPECT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
}

TEST(ListTest, splice) {
  std::list<int> a{1, 2, 3, 4, 5, 6};
  std::list<int> b{3, 4, 5, 5, 6, 6};
  a.splice(a.end(), b);

  s21::list<int> a1{1, 2, 3, 4, 5, 6};
  s21::list<int> b1{3, 4, 5, 5, 6, 6};
  a1.splice(a1.end(), b1);

  auto it1 = a.end();
  auto it2 = a1.end();

  ASSERT_EQ(a.size(), a1.size());

  if (it1 != a.begin()) {
    do {
      it1--;
      it2--;
      ASSERT_EQ(*it1, *it2);
    } while (it1 != a.begin());
  }
}

TEST(ListTest, InsertMany) {
  s21::list<int> a{1, 2, 3, 4};
  auto it = a.begin();
  it++;
  a.insert_many(it, 7, 8, 9);
  s21::list<int> b{1, 7, 8, 9, 2, 3, 4};
  it = a.begin();
  for (auto it1 = b.begin(); it1 != b.end(); it1++) {
    ASSERT_EQ(*it, *it1);
    it++;
  }
}

TEST(ListTest, front_FrontMany) {
  s21::list<int> a(5);
  s21::list<int> b{4, 3, 2, 1, 0, 0, 0, 0, 0, 10};
  ASSERT_EQ(a.size(), 5);
  a.push_back(10);
  a.insert_many_front(1, 2, 3, 4);
  ASSERT_EQ(a.size(), 10);
  for (auto it1 = a.begin(), it2 = b.begin(); it1 != a.end(); it1++, it2++) {
    ASSERT_EQ(*it1, *it2);
  }
}

TEST(ListTest, IteratorEnd) {
  s21::list<int> a(5);
  auto it = a.end();
  ASSERT_EQ(it, a.end());
  it++;
  ASSERT_EQ(it, a.end());
  it++;
  ASSERT_EQ(it, a.end());
}

TEST(ListTest, IteratorBegin) {
  s21::list<int> a(5);
  auto it = a.begin();
  ASSERT_EQ(it, a.begin());
  it--;
  ASSERT_EQ(it, a.begin());
  it--;
  ASSERT_EQ(it, a.begin());
}

TEST(ListTest, move) {
  s21::list<int> a(5);
  s21::list<int> b(std::move(a));
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, move1) {
  s21::list<int> a(5);
  s21::list<int> b;
  b = std::move(a);
  ASSERT_EQ(a.size(), 0);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, FrontBack) {
  s21::list<int> a{1, 2, 3, 4, 5};
  ASSERT_EQ(a.front(), 1);
  ASSERT_EQ(a.back(), 5);
}

TEST(ListTest, FrontBackEmpty) {
  s21::list<int> a{};
  EXPECT_THROW(a.front(), std::out_of_range);
  EXPECT_THROW(a.back(), std::out_of_range);
}

TEST(ListTest, Empty) {
  s21::list<int> a{};
  ASSERT_EQ(a.empty(), 1);
  a.push_back(123);
  ASSERT_EQ(a.empty(), 0);
}

TEST(ListTest, MaxSize) {
  s21::list<int> a{};
  EXPECT_GT(a.max_size(), 10000);
}

TEST(ListTest, clear) {
  s21::list<int> a{1, 2, 3, 4, 5, 6};
  a.clear();
  ASSERT_EQ(a.size(), 0);
}

TEST(ListTest, insert1) {
  s21::list<int> a{1, 2, 4, 5, 6};
  auto it = a.begin();
  it++;
  it++;
  a.insert(it, 3);
  it = a.begin();
  for (size_t i = 1; i < 7; i++) {
    ASSERT_EQ(*it, i);
    it++;
  }
}

TEST(ListTest, insertErrors) {
  s21::list<int> a{};
  auto it = a.begin();
  a.insert(it, 3);
  it = a.begin();
  ASSERT_EQ(*it, 3);
}

TEST(ListTest, eraseErr) {
  s21::list<int> a{1, 2, 3, 4};
  auto it = a.end();
  EXPECT_THROW(a.erase(it), std::out_of_range);
}

TEST(ListTest, erase1) {
  s21::list<int> a{1, 2, 3, 4};
  auto it = a.end();
  it--;
  a.erase(it);
  it = a.begin();
  for (size_t i = 1; i < 4; i++, it++) {
    ASSERT_EQ(*it, i);
  }
}

TEST(ListTest, push_front) {
  s21::list<int> a{1, 2, 3, 4};
  a.push_front(10);
  a.push_front(12);
  auto it = a.begin();
  ASSERT_EQ(*it, 12);
  it++;
  ASSERT_EQ(*it, 10);
  ASSERT_EQ(a.size(), 6);
}

TEST(ListTest, pop_front) {
  s21::list<int> a{1, 2, 3, 4};
  a.pop_front();
  auto it = a.begin();
  ASSERT_EQ(*it, 2);
  a.push_front(12);
  a.push_front(142);
  a.pop_front();
  it = a.begin();
  ASSERT_EQ(*it, 12);
  ASSERT_EQ(a.size(), 4);
}

TEST(ListTest, pop_front_one) {
  s21::list<int> a{1};
  a.pop_front();
  ASSERT_EQ(a.size(), 0);
}

TEST(ListTest, swap) {
  s21::list<int> a{1, 2, 3, 4, 5};
  s21::list<int> b{5, 4, 3};
  a.swap(b);
  auto itA = a.begin();
  auto itB = b.begin();
  for (size_t i = 5; i > 2; i--) {
    ASSERT_EQ(*itA, i);
    itA++;
  }

  for (size_t i = 1; i < 6; i++) {
    ASSERT_EQ(*itB, i);
    itB++;
  }

  ASSERT_EQ(a.size(), 3);
  ASSERT_EQ(b.size(), 5);
}

TEST(ListTest, merge1) {
  s21::list<int> a{1, 5, 6, 9, 9};
  s21::list<int> b{5, 6, 7, 8, 12, 12};
  s21::list<int> total{1, 5, 5, 6, 6, 7, 8, 9, 9, 12, 12};
  a.merge(b);
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       it1++, it2++) {
    ASSERT_EQ(*it1, *it2);
  }
  ASSERT_EQ(a.size(), total.size());
}

TEST(ListTest, merge2) {
  s21::list<int> a{1, 5, 6, 9, 9};
  s21::list<int> b{1, 5};
  s21::list<int> total{1, 1, 5, 5, 6, 9, 9};
  a.merge(b);
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       it1++, it2++) {
    ASSERT_EQ(*it1, *it2);
  }
  ASSERT_EQ(a.size(), total.size());
}

TEST(ListTest, max_size) {
  s21::list<int> a = {1, 2, 3};

  EXPECT_GT(a.max_size(), 1000);
}

TEST(ListTest, reverseErr) {
  s21::list<int> a = {};

  EXPECT_THROW(a.reverse(), std::out_of_range);
}

TEST(ListTest, splice1) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6};
  s21::list<int> b = {100, 200, 300, 400, 500};
  s21::list<int> total = {1, 2, 100, 200, 300, 400, 500, 3, 4, 5, 6};
  auto it = a.begin();
  it++;
  it++;
  a.splice(it, b);

  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(ListTest, splice2) {
  s21::list<int> a = {1, 2, 3, 4, 5, 6};
  s21::list<int> b = {100, 200, 300, 400, 500};
  s21::list<int> total = {1, 2, 3, 4, 5, 6, 100, 200, 300, 400, 500};
  auto it = a.end();
  a.splice(it, b);

  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
}

TEST(ListTest, unique) {
  s21::list<int> a = {1, 1, 1, 1, 2, 2, 3, 5, 6, 6, 8};
  s21::list<int> total = {1, 2, 3, 5, 6, 8};
  a.unique();
  for (auto it1 = a.begin(), it2 = total.begin(); it1 != a.end();
       it1++, it2++) {
    EXPECT_EQ(*it1, *it2);
  }
  EXPECT_EQ(a.size(), total.size());
}

TEST(ListTest, uniqueErr) {
  s21::list<int> a = {};
  EXPECT_THROW(a.unique(), std::out_of_range);
}

TEST(ListTest, insertManyBack) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_back(4, 5, 6, 7);
  auto it = a.begin();
  for (size_t i = 1; i < 8; i++) {
    EXPECT_EQ(*it, i);
    it++;
  }
  EXPECT_EQ(a.size(), 7);
}

TEST(ListTest, sort) {
  s21::list<int> a = {1, 2, 3};
  a.insert_many_back(5, 1, 2, 5, 12, 3, 5, 6, 1, 4);
  std::list<int> total{1, 2, 3, 5, 1, 2, 5, 12, 3, 5, 6, 1, 4};
  a.sort();
  total.sort();
  auto it1 = total.begin();
  for (auto it = a.begin(); it != a.end(); it++, it1++) {
    EXPECT_EQ(*it, *it1);
  }
  EXPECT_EQ(a.size(), total.size());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}